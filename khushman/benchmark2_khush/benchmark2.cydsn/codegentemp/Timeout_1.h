/*******************************************************************************
* File Name: Timeout_1.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_Timeout_1_H)
#define CY_TIMER_Timeout_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Timeout_1_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define Timeout_1_Resolution                 16u
#define Timeout_1_UsingFixedFunction         0u
#define Timeout_1_UsingHWCaptureCounter      0u
#define Timeout_1_SoftwareCaptureMode        0u
#define Timeout_1_SoftwareTriggerMode        0u
#define Timeout_1_UsingHWEnable              0u
#define Timeout_1_EnableTriggerMode          0u
#define Timeout_1_InterruptOnCaptureCount    0u
#define Timeout_1_RunModeUsed                0u
#define Timeout_1_ControlRegRemoved          0u

#if defined(Timeout_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define Timeout_1_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (Timeout_1_UsingFixedFunction)
    #define Timeout_1_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define Timeout_1_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End Timeout_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!Timeout_1_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (Timeout_1_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!Timeout_1_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}Timeout_1_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    Timeout_1_Start(void) ;
void    Timeout_1_Stop(void) ;

void    Timeout_1_SetInterruptMode(uint8 interruptMode) ;
uint8   Timeout_1_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define Timeout_1_GetInterruptSource() Timeout_1_ReadStatusRegister()

#if(!Timeout_1_UDB_CONTROL_REG_REMOVED)
    uint8   Timeout_1_ReadControlRegister(void) ;
    void    Timeout_1_WriteControlRegister(uint8 control) ;
#endif /* (!Timeout_1_UDB_CONTROL_REG_REMOVED) */

uint16  Timeout_1_ReadPeriod(void) ;
void    Timeout_1_WritePeriod(uint16 period) ;
uint16  Timeout_1_ReadCounter(void) ;
void    Timeout_1_WriteCounter(uint16 counter) ;
uint16  Timeout_1_ReadCapture(void) ;
void    Timeout_1_SoftwareCapture(void) ;

#if(!Timeout_1_UsingFixedFunction) /* UDB Prototypes */
    #if (Timeout_1_SoftwareCaptureMode)
        void    Timeout_1_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!Timeout_1_UsingFixedFunction) */

    #if (Timeout_1_SoftwareTriggerMode)
        void    Timeout_1_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (Timeout_1_SoftwareTriggerMode) */

    #if (Timeout_1_EnableTriggerMode)
        void    Timeout_1_EnableTrigger(void) ;
        void    Timeout_1_DisableTrigger(void) ;
    #endif /* (Timeout_1_EnableTriggerMode) */


    #if(Timeout_1_InterruptOnCaptureCount)
        void    Timeout_1_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (Timeout_1_InterruptOnCaptureCount) */

    #if (Timeout_1_UsingHWCaptureCounter)
        void    Timeout_1_SetCaptureCount(uint8 captureCount) ;
        uint8   Timeout_1_ReadCaptureCount(void) ;
    #endif /* (Timeout_1_UsingHWCaptureCounter) */

    void Timeout_1_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void Timeout_1_Init(void)          ;
void Timeout_1_Enable(void)        ;
void Timeout_1_SaveConfig(void)    ;
void Timeout_1_RestoreConfig(void) ;
void Timeout_1_Sleep(void)         ;
void Timeout_1_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define Timeout_1__B_TIMER__CM_NONE 0
#define Timeout_1__B_TIMER__CM_RISINGEDGE 1
#define Timeout_1__B_TIMER__CM_FALLINGEDGE 2
#define Timeout_1__B_TIMER__CM_EITHEREDGE 3
#define Timeout_1__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define Timeout_1__B_TIMER__TM_NONE 0x00u
#define Timeout_1__B_TIMER__TM_RISINGEDGE 0x04u
#define Timeout_1__B_TIMER__TM_FALLINGEDGE 0x08u
#define Timeout_1__B_TIMER__TM_EITHEREDGE 0x0Cu
#define Timeout_1__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define Timeout_1_INIT_PERIOD             65535u
#define Timeout_1_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << Timeout_1_CTRL_CAP_MODE_SHIFT))
#define Timeout_1_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << Timeout_1_CTRL_TRIG_MODE_SHIFT))
#if (Timeout_1_UsingFixedFunction)
    #define Timeout_1_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << Timeout_1_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << Timeout_1_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define Timeout_1_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << Timeout_1_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << Timeout_1_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << Timeout_1_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (Timeout_1_UsingFixedFunction) */
#define Timeout_1_INIT_CAPTURE_COUNT      (2u)
#define Timeout_1_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << Timeout_1_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (Timeout_1_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define Timeout_1_STATUS         (*(reg8 *) Timeout_1_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define Timeout_1_STATUS_MASK    (*(reg8 *) Timeout_1_TimerHW__SR0 )
    #define Timeout_1_CONTROL        (*(reg8 *) Timeout_1_TimerHW__CFG0)
    #define Timeout_1_CONTROL2       (*(reg8 *) Timeout_1_TimerHW__CFG1)
    #define Timeout_1_CONTROL2_PTR   ( (reg8 *) Timeout_1_TimerHW__CFG1)
    #define Timeout_1_RT1            (*(reg8 *) Timeout_1_TimerHW__RT1)
    #define Timeout_1_RT1_PTR        ( (reg8 *) Timeout_1_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define Timeout_1_CONTROL3       (*(reg8 *) Timeout_1_TimerHW__CFG2)
        #define Timeout_1_CONTROL3_PTR   ( (reg8 *) Timeout_1_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define Timeout_1_GLOBAL_ENABLE  (*(reg8 *) Timeout_1_TimerHW__PM_ACT_CFG)
    #define Timeout_1_GLOBAL_STBY_ENABLE  (*(reg8 *) Timeout_1_TimerHW__PM_STBY_CFG)

    #define Timeout_1_CAPTURE_LSB         (* (reg16 *) Timeout_1_TimerHW__CAP0 )
    #define Timeout_1_CAPTURE_LSB_PTR       ((reg16 *) Timeout_1_TimerHW__CAP0 )
    #define Timeout_1_PERIOD_LSB          (* (reg16 *) Timeout_1_TimerHW__PER0 )
    #define Timeout_1_PERIOD_LSB_PTR        ((reg16 *) Timeout_1_TimerHW__PER0 )
    #define Timeout_1_COUNTER_LSB         (* (reg16 *) Timeout_1_TimerHW__CNT_CMP0 )
    #define Timeout_1_COUNTER_LSB_PTR       ((reg16 *) Timeout_1_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define Timeout_1_BLOCK_EN_MASK                     Timeout_1_TimerHW__PM_ACT_MSK
    #define Timeout_1_BLOCK_STBY_EN_MASK                Timeout_1_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define Timeout_1_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define Timeout_1_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define Timeout_1_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define Timeout_1_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define Timeout_1_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define Timeout_1_CTRL_ENABLE                        ((uint8)((uint8)0x01u << Timeout_1_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Timeout_1_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define Timeout_1_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << Timeout_1_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define Timeout_1_CTRL_MODE_SHIFT                 0x01u
        #define Timeout_1_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << Timeout_1_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define Timeout_1_CTRL_RCOD_SHIFT        0x02u
        #define Timeout_1_CTRL_ENBL_SHIFT        0x00u
        #define Timeout_1_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define Timeout_1_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << Timeout_1_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define Timeout_1_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << Timeout_1_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define Timeout_1_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << Timeout_1_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define Timeout_1_CTRL_RCOD       ((uint8)((uint8)0x03u << Timeout_1_CTRL_RCOD_SHIFT))
        #define Timeout_1_CTRL_ENBL       ((uint8)((uint8)0x80u << Timeout_1_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define Timeout_1_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define Timeout_1_RT1_MASK                        ((uint8)((uint8)0x03u << Timeout_1_RT1_SHIFT))
    #define Timeout_1_SYNC                            ((uint8)((uint8)0x03u << Timeout_1_RT1_SHIFT))
    #define Timeout_1_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define Timeout_1_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << Timeout_1_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define Timeout_1_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << Timeout_1_SYNCDSI_SHIFT))

    #define Timeout_1_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << Timeout_1_CTRL_MODE_SHIFT))
    #define Timeout_1_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << Timeout_1_CTRL_MODE_SHIFT))
    #define Timeout_1_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << Timeout_1_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define Timeout_1_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define Timeout_1_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define Timeout_1_STATUS_TC_INT_MASK_SHIFT        (Timeout_1_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define Timeout_1_STATUS_CAPTURE_INT_MASK_SHIFT   (Timeout_1_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define Timeout_1_STATUS_TC                       ((uint8)((uint8)0x01u << Timeout_1_STATUS_TC_SHIFT))
    #define Timeout_1_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << Timeout_1_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define Timeout_1_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << Timeout_1_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define Timeout_1_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << Timeout_1_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define Timeout_1_STATUS              (* (reg8 *) Timeout_1_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define Timeout_1_STATUS_MASK         (* (reg8 *) Timeout_1_TimerUDB_rstSts_stsreg__MASK_REG)
    #define Timeout_1_STATUS_AUX_CTRL     (* (reg8 *) Timeout_1_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define Timeout_1_CONTROL             (* (reg8 *) Timeout_1_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(Timeout_1_Resolution <= 8u) /* 8-bit Timer */
        #define Timeout_1_CAPTURE_LSB         (* (reg8 *) Timeout_1_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define Timeout_1_CAPTURE_LSB_PTR       ((reg8 *) Timeout_1_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define Timeout_1_PERIOD_LSB          (* (reg8 *) Timeout_1_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define Timeout_1_PERIOD_LSB_PTR        ((reg8 *) Timeout_1_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define Timeout_1_COUNTER_LSB         (* (reg8 *) Timeout_1_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define Timeout_1_COUNTER_LSB_PTR       ((reg8 *) Timeout_1_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(Timeout_1_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define Timeout_1_CAPTURE_LSB         (* (reg16 *) Timeout_1_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define Timeout_1_CAPTURE_LSB_PTR       ((reg16 *) Timeout_1_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define Timeout_1_PERIOD_LSB          (* (reg16 *) Timeout_1_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define Timeout_1_PERIOD_LSB_PTR        ((reg16 *) Timeout_1_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define Timeout_1_COUNTER_LSB         (* (reg16 *) Timeout_1_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define Timeout_1_COUNTER_LSB_PTR       ((reg16 *) Timeout_1_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define Timeout_1_CAPTURE_LSB         (* (reg16 *) Timeout_1_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define Timeout_1_CAPTURE_LSB_PTR       ((reg16 *) Timeout_1_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define Timeout_1_PERIOD_LSB          (* (reg16 *) Timeout_1_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define Timeout_1_PERIOD_LSB_PTR        ((reg16 *) Timeout_1_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define Timeout_1_COUNTER_LSB         (* (reg16 *) Timeout_1_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define Timeout_1_COUNTER_LSB_PTR       ((reg16 *) Timeout_1_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(Timeout_1_Resolution <= 24u)/* 24-bit Timer */
        #define Timeout_1_CAPTURE_LSB         (* (reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define Timeout_1_CAPTURE_LSB_PTR       ((reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define Timeout_1_PERIOD_LSB          (* (reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define Timeout_1_PERIOD_LSB_PTR        ((reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define Timeout_1_COUNTER_LSB         (* (reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define Timeout_1_COUNTER_LSB_PTR       ((reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define Timeout_1_CAPTURE_LSB         (* (reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define Timeout_1_CAPTURE_LSB_PTR       ((reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define Timeout_1_PERIOD_LSB          (* (reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define Timeout_1_PERIOD_LSB_PTR        ((reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define Timeout_1_COUNTER_LSB         (* (reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define Timeout_1_COUNTER_LSB_PTR       ((reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define Timeout_1_CAPTURE_LSB         (* (reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define Timeout_1_CAPTURE_LSB_PTR       ((reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define Timeout_1_PERIOD_LSB          (* (reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define Timeout_1_PERIOD_LSB_PTR        ((reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define Timeout_1_COUNTER_LSB         (* (reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define Timeout_1_COUNTER_LSB_PTR       ((reg32 *) Timeout_1_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define Timeout_1_COUNTER_LSB_PTR_8BIT       ((reg8 *) Timeout_1_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (Timeout_1_UsingHWCaptureCounter)
        #define Timeout_1_CAP_COUNT              (*(reg8 *) Timeout_1_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define Timeout_1_CAP_COUNT_PTR          ( (reg8 *) Timeout_1_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define Timeout_1_CAPTURE_COUNT_CTRL     (*(reg8 *) Timeout_1_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define Timeout_1_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) Timeout_1_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (Timeout_1_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define Timeout_1_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define Timeout_1_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define Timeout_1_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define Timeout_1_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define Timeout_1_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define Timeout_1_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << Timeout_1_CTRL_INTCNT_SHIFT))
    #define Timeout_1_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << Timeout_1_CTRL_TRIG_MODE_SHIFT))
    #define Timeout_1_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << Timeout_1_CTRL_TRIG_EN_SHIFT))
    #define Timeout_1_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << Timeout_1_CTRL_CAP_MODE_SHIFT))
    #define Timeout_1_CTRL_ENABLE                    ((uint8)((uint8)0x01u << Timeout_1_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define Timeout_1_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define Timeout_1_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define Timeout_1_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define Timeout_1_STATUS_TC_INT_MASK_SHIFT       Timeout_1_STATUS_TC_SHIFT
    #define Timeout_1_STATUS_CAPTURE_INT_MASK_SHIFT  Timeout_1_STATUS_CAPTURE_SHIFT
    #define Timeout_1_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define Timeout_1_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define Timeout_1_STATUS_FIFOFULL_INT_MASK_SHIFT Timeout_1_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define Timeout_1_STATUS_TC                      ((uint8)((uint8)0x01u << Timeout_1_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define Timeout_1_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << Timeout_1_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Timeout_1_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << Timeout_1_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Timeout_1_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << Timeout_1_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define Timeout_1_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << Timeout_1_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define Timeout_1_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << Timeout_1_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Timeout_1_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << Timeout_1_STATUS_FIFOFULL_SHIFT))

    #define Timeout_1_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define Timeout_1_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define Timeout_1_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define Timeout_1_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define Timeout_1_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define Timeout_1_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_Timeout_1_H */


/* [] END OF FILE */
