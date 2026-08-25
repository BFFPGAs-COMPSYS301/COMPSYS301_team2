/*******************************************************************************
* File Name: ISR_QUAD.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_ISR_QUAD_H)
#define CY_ISR_ISR_QUAD_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ISR_QUAD_Start(void);
void ISR_QUAD_StartEx(cyisraddress address);
void ISR_QUAD_Stop(void);

CY_ISR_PROTO(ISR_QUAD_Interrupt);

void ISR_QUAD_SetVector(cyisraddress address);
cyisraddress ISR_QUAD_GetVector(void);

void ISR_QUAD_SetPriority(uint8 priority);
uint8 ISR_QUAD_GetPriority(void);

void ISR_QUAD_Enable(void);
uint8 ISR_QUAD_GetState(void);
void ISR_QUAD_Disable(void);

void ISR_QUAD_SetPending(void);
void ISR_QUAD_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ISR_QUAD ISR. */
#define ISR_QUAD_INTC_VECTOR            ((reg32 *) ISR_QUAD__INTC_VECT)

/* Address of the ISR_QUAD ISR priority. */
#define ISR_QUAD_INTC_PRIOR             ((reg8 *) ISR_QUAD__INTC_PRIOR_REG)

/* Priority of the ISR_QUAD interrupt. */
#define ISR_QUAD_INTC_PRIOR_NUMBER      ISR_QUAD__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ISR_QUAD interrupt. */
#define ISR_QUAD_INTC_SET_EN            ((reg32 *) ISR_QUAD__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ISR_QUAD interrupt. */
#define ISR_QUAD_INTC_CLR_EN            ((reg32 *) ISR_QUAD__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ISR_QUAD interrupt state to pending. */
#define ISR_QUAD_INTC_SET_PD            ((reg32 *) ISR_QUAD__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ISR_QUAD interrupt. */
#define ISR_QUAD_INTC_CLR_PD            ((reg32 *) ISR_QUAD__INTC_CLR_PD_REG)


#endif /* CY_ISR_ISR_QUAD_H */


/* [] END OF FILE */
