/* ========================================
 *
 * Hardware Task 1
 *
 * RC circuit -> ADC -> digital samples -> DAC
 *                         |
 *                         -> buffer -> USBUART
 *
 * ADC configuration:
 *   - 12-bit
 *   - 0 V to 2.048 V input range
 *   - Hardware triggered
 *
 * DAC configuration:
 *   - 8-bit
 *   - 0 V to 4.080 V output range
 *
 * Timer configuration:
 *   - 50 kHz terminal-count frequency
 *   - Timer TC connected to ADC SOC
 *
 * Interrupt connection:
 *   - ADC EOC connected to isr_1
 *
 * ========================================
 */

#include "project.h"
#include <stdio.h>


/*
 * Number of ADC samples captured before USB transmission.
 *
 * At 50 kSamples/s:
 *
 * capture time = 500 / 50000
 *              = 0.01 seconds
 *              = 10 milliseconds
 */
#define BUFFER_SIZE 500u


/*
 * Array used to store the ADC samples.
 *
 * The ADC produces a 12-bit result from 0 to 4095.
 * A uint16 variable can hold values from 0 to 65535,
 * so it is large enough for each ADC result.
 *
 * volatile is used because the interrupt writes to this
 * array while main() reads from it.
 */
volatile uint16 adcBuffer[BUFFER_SIZE];


/*
 * Index of the next available location in adcBuffer.
 *
 * It begins at zero and increases after every sample:
 *
 * 0, 1, 2, ..., BUFFER_SIZE - 1
 */
volatile uint16 bufferIndex = 0u;


/*
 * Flag indicating whether the ADC buffer is full.
 *
 * bufferFull = 0:
 *     The ISR may continue storing ADC samples.
 *
 * bufferFull = 1:
 *     The buffer contains a complete block and is
 *     ready to be sent through USBUART.
 */
volatile uint8 bufferFull = 0u;


/*
 * ADC End-of-Conversion interrupt service routine.
 *
 * This ISR runs every time the SAR ADC finishes
 * one conversion.
 *
 * Sequence:
 *
 * Timer TC
 *     -> ADC SOC
 *     -> ADC conversion
 *     -> ADC EOC
 *     -> isr_1
 *     -> MyISR
 */
CY_ISR(MyISR)
{
    /*
     * Stores the completed 12-bit ADC result.
     */
    uint16 adcValue;

    /*
     * Stores the scaled 8-bit value written to the DAC.
     */
    uint8 dacValue;


    /*
     * Read the most recently completed ADC conversion.
     *
     * For a 12-bit ADC:
     *
     * ADC result range = 0 to 4095
     */
    adcValue = (uint16)ADC_SAR_1_GetResult16();


    /*
     * Scale the ADC result for the DAC.
     *
     * ADC configuration:
     *     0 V to 2.048 V
     *     4096 possible codes
     *
     * ADC step size:
     *
     *     2.048 V / 4096 = 0.0005 V
     *                          = 0.5 mV/count
     *
     * DAC configuration:
     *     0 V to 4.080 V
     *     16 mV/count
     *
     * Number of ADC counts per DAC count:
     *
     *     16 mV / 0.5 mV = 32
     *
     * Therefore:
     *
     *     DAC code = ADC code / 32
     *
     * Shifting right by five bits divides an unsigned
     * integer by:
     *
     *     2^5 = 32
     */
    dacValue = (uint8)(adcValue >> 5);


    /*
     * Write the scaled value to the DAC.
     *
     * The DAC converts this digital value back into
     * an analogue voltage on Pin_2.
     */
    VDAC8_1_SetValue(dacValue);


    /*
     * Store the ADC value only while the buffer has space.
     *
     * Once bufferFull becomes 1, this section is skipped.
     * This prevents writing beyond the end of the array.
     */
    if (bufferFull == 0u)
    {
        /*
         * Store the current sample at the location selected
         * by bufferIndex.
         */
        adcBuffer[bufferIndex] = adcValue;


        /*
         * Move to the next buffer location.
         */
        bufferIndex++;


        /*
         * Check whether BUFFER_SIZE samples have now
         * been captured.
         */
        if (bufferIndex >= BUFFER_SIZE)
        {
            /*
             * Tell main() that the sample buffer is full
             * and ready for USB transmission.
             */
            bufferFull = 1u;
        }
    }
}


int main(void)
{
    /*
     * Counter used to move through the sample buffer
     * during USB transmission.
     */
    uint16 i;


    /*
     * Character array used to hold one ADC value
     * after it has been converted into text.
     *
     * For example:
     *
     * ADC value 2500 becomes "2500\r\n"
     */
    char usbText[20];


    /*
     * Enable interrupts globally.
     *
     * Without this instruction, isr_1 cannot execute
     * MyISR when the ADC finishes a conversion.
     */
    CyGlobalIntEnable;


    /*
     * Start and power the SAR ADC.
     *
     * Because the ADC is configured for hardware triggering,
     * it waits for a pulse on its SOC input before beginning
     * each conversion.
     */
    ADC_SAR_1_Start();


    /*
     * Start and power the 8-bit DAC.
     *
     * The DAC initially outputs its configured initial value.
     * MyISR will update it after every ADC conversion.
     */
    VDAC8_1_Start();


    /*
     * Start the interrupt component and connect it
     * to the MyISR interrupt function.
     *
     * The schematic connection is:
     *
     * ADC EOC -> isr_1
     *
     * This software instruction provides:
     *
     * isr_1 -> MyISR
     */
    isr_1_StartEx(MyISR);


    /*
     * Start the USBUART hardware.
     *
     * 0u selects USB device number zero.
     *
     * USBUART_1_5V_OPERATION configures the USB component
     * for the 5 V operating mode.
     */
    USBUART_1_Start(0u, USBUART_1_5V_OPERATION);


    /*
     * Wait until the computer detects and configures
     * the PSoC USB device.
     *
     * GetConfiguration() returns zero until the USB
     * connection has been successfully configured.
     *
     * The program stays in this loop while USB is not ready.
     */
    while (USBUART_1_GetConfiguration() == 0u)
    {
        /* Wait for the computer to configure USB */
    }


    /*
     * Initialise the USB CDC interface.
     *
     * CDC makes the USB connection operate like a
     * virtual serial communication device.
     */
    USBUART_1_CDC_Init();
    


    /*
     * Start Timer_1 last, after all other components
     * are ready.
     *
     * Timer_1 produces a terminal-count pulse at 50 kHz.
     *
     * The schematic connection is:
     *
     * Timer TC -> ADC SOC
     *
     * Therefore, one ADC conversion begins every:
     *
     *     1 / 50000 = 20 microseconds
     */
    Timer_1_Start();


    /*
     * Main application loop.
     *
     * The program remains inside this loop indefinitely.
     */
    for (;;)
    {
        /*
         * Check whether MyISR has captured a complete
         * block of BUFFER_SIZE ADC samples.
         */
        if (bufferFull == 1u)
        {
            /*
             * Stop Timer_1.
             *
             * This stops new ADC hardware triggers while
             * the captured samples are being transmitted.
             *
             * The DAC holds its most recently written voltage
             * until the timer and ADC are started again.
             */
            Timer_1_Stop();


            /*
             * Send every stored ADC sample to the computer.
             *
             * For BUFFER_SIZE = 500, i takes the values:
             *
             * 0, 1, 2, ..., 499
             */
            for (i = 0u; i < BUFFER_SIZE; i++)
            {
                /*
                 * Convert the current ADC sample from a
                 * binary integer into a text string.
                 *
                 * %u:
                 *     Insert an unsigned integer.
                 *
                 * \r:
                 *     Carriage return.
                 *
                 * \n:
                 *     New line.
                 *
                 * Example:
                 *
                 * adcBuffer[i] = 2500
                 *
                 * usbText becomes:
                 *
                 * "2500\r\n"
                 */
                sprintf(
                    usbText,
                    "%u\r\n",
                    (unsigned int)adcBuffer[i]
                );


                /*
                 * Wait until the USB CDC interface is ready
                 * to accept another transmission.
                 *
                 * CDCIsReady() returns zero while the previous
                 * USB data is still being processed.
                 */
                while (USBUART_1_CDCIsReady() == 0u)
                {
                    /* Wait until USB is ready */
                }


                /*
                 * Send the current ADC value to the computer
                 * as a line of text.
                 */
                USBUART_1_PutString(usbText);
            }


            /*
             * All 500 samples have now been transmitted.
             *
             * Reset bufferIndex to zero so the next capture
             * starts again at adcBuffer[0].
             */
            bufferIndex = 0u;


            /*
             * Mark the buffer as empty.
             *
             * This allows MyISR to begin storing new
             * ADC samples.
             */
            bufferFull = 0u;


            /*
             * Restart Timer_1.
             *
             * The timer begins producing TC pulses again,
             * so the ADC captures another block of samples.
             */
            Timer_1_Start();
        }
    }
}

/* [] END OF FILE */