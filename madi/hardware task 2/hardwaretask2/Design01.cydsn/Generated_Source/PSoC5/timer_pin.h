/*******************************************************************************
* File Name: timer_pin.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_timer_pin_H) /* Pins timer_pin_H */
#define CY_PINS_timer_pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "timer_pin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 timer_pin__PORT == 15 && ((timer_pin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    timer_pin_Write(uint8 value);
void    timer_pin_SetDriveMode(uint8 mode);
uint8   timer_pin_ReadDataReg(void);
uint8   timer_pin_Read(void);
void    timer_pin_SetInterruptMode(uint16 position, uint16 mode);
uint8   timer_pin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the timer_pin_SetDriveMode() function.
     *  @{
     */
        #define timer_pin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define timer_pin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define timer_pin_DM_RES_UP          PIN_DM_RES_UP
        #define timer_pin_DM_RES_DWN         PIN_DM_RES_DWN
        #define timer_pin_DM_OD_LO           PIN_DM_OD_LO
        #define timer_pin_DM_OD_HI           PIN_DM_OD_HI
        #define timer_pin_DM_STRONG          PIN_DM_STRONG
        #define timer_pin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define timer_pin_MASK               timer_pin__MASK
#define timer_pin_SHIFT              timer_pin__SHIFT
#define timer_pin_WIDTH              1u

/* Interrupt constants */
#if defined(timer_pin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in timer_pin_SetInterruptMode() function.
     *  @{
     */
        #define timer_pin_INTR_NONE      (uint16)(0x0000u)
        #define timer_pin_INTR_RISING    (uint16)(0x0001u)
        #define timer_pin_INTR_FALLING   (uint16)(0x0002u)
        #define timer_pin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define timer_pin_INTR_MASK      (0x01u) 
#endif /* (timer_pin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define timer_pin_PS                     (* (reg8 *) timer_pin__PS)
/* Data Register */
#define timer_pin_DR                     (* (reg8 *) timer_pin__DR)
/* Port Number */
#define timer_pin_PRT_NUM                (* (reg8 *) timer_pin__PRT) 
/* Connect to Analog Globals */                                                  
#define timer_pin_AG                     (* (reg8 *) timer_pin__AG)                       
/* Analog MUX bux enable */
#define timer_pin_AMUX                   (* (reg8 *) timer_pin__AMUX) 
/* Bidirectional Enable */                                                        
#define timer_pin_BIE                    (* (reg8 *) timer_pin__BIE)
/* Bit-mask for Aliased Register Access */
#define timer_pin_BIT_MASK               (* (reg8 *) timer_pin__BIT_MASK)
/* Bypass Enable */
#define timer_pin_BYP                    (* (reg8 *) timer_pin__BYP)
/* Port wide control signals */                                                   
#define timer_pin_CTL                    (* (reg8 *) timer_pin__CTL)
/* Drive Modes */
#define timer_pin_DM0                    (* (reg8 *) timer_pin__DM0) 
#define timer_pin_DM1                    (* (reg8 *) timer_pin__DM1)
#define timer_pin_DM2                    (* (reg8 *) timer_pin__DM2) 
/* Input Buffer Disable Override */
#define timer_pin_INP_DIS                (* (reg8 *) timer_pin__INP_DIS)
/* LCD Common or Segment Drive */
#define timer_pin_LCD_COM_SEG            (* (reg8 *) timer_pin__LCD_COM_SEG)
/* Enable Segment LCD */
#define timer_pin_LCD_EN                 (* (reg8 *) timer_pin__LCD_EN)
/* Slew Rate Control */
#define timer_pin_SLW                    (* (reg8 *) timer_pin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define timer_pin_PRTDSI__CAPS_SEL       (* (reg8 *) timer_pin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define timer_pin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) timer_pin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define timer_pin_PRTDSI__OE_SEL0        (* (reg8 *) timer_pin__PRTDSI__OE_SEL0) 
#define timer_pin_PRTDSI__OE_SEL1        (* (reg8 *) timer_pin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define timer_pin_PRTDSI__OUT_SEL0       (* (reg8 *) timer_pin__PRTDSI__OUT_SEL0) 
#define timer_pin_PRTDSI__OUT_SEL1       (* (reg8 *) timer_pin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define timer_pin_PRTDSI__SYNC_OUT       (* (reg8 *) timer_pin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(timer_pin__SIO_CFG)
    #define timer_pin_SIO_HYST_EN        (* (reg8 *) timer_pin__SIO_HYST_EN)
    #define timer_pin_SIO_REG_HIFREQ     (* (reg8 *) timer_pin__SIO_REG_HIFREQ)
    #define timer_pin_SIO_CFG            (* (reg8 *) timer_pin__SIO_CFG)
    #define timer_pin_SIO_DIFF           (* (reg8 *) timer_pin__SIO_DIFF)
#endif /* (timer_pin__SIO_CFG) */

/* Interrupt Registers */
#if defined(timer_pin__INTSTAT)
    #define timer_pin_INTSTAT            (* (reg8 *) timer_pin__INTSTAT)
    #define timer_pin_SNAP               (* (reg8 *) timer_pin__SNAP)
    
	#define timer_pin_0_INTTYPE_REG 		(* (reg8 *) timer_pin__0__INTTYPE)
#endif /* (timer_pin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_timer_pin_H */


/* [] END OF FILE */
