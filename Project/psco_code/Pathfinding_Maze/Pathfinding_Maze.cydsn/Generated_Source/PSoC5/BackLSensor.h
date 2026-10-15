/*******************************************************************************
* File Name: BackLSensor.h  
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

#if !defined(CY_PINS_BackLSensor_H) /* Pins BackLSensor_H */
#define CY_PINS_BackLSensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BackLSensor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BackLSensor__PORT == 15 && ((BackLSensor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BackLSensor_Write(uint8 value);
void    BackLSensor_SetDriveMode(uint8 mode);
uint8   BackLSensor_ReadDataReg(void);
uint8   BackLSensor_Read(void);
void    BackLSensor_SetInterruptMode(uint16 position, uint16 mode);
uint8   BackLSensor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BackLSensor_SetDriveMode() function.
     *  @{
     */
        #define BackLSensor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BackLSensor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BackLSensor_DM_RES_UP          PIN_DM_RES_UP
        #define BackLSensor_DM_RES_DWN         PIN_DM_RES_DWN
        #define BackLSensor_DM_OD_LO           PIN_DM_OD_LO
        #define BackLSensor_DM_OD_HI           PIN_DM_OD_HI
        #define BackLSensor_DM_STRONG          PIN_DM_STRONG
        #define BackLSensor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BackLSensor_MASK               BackLSensor__MASK
#define BackLSensor_SHIFT              BackLSensor__SHIFT
#define BackLSensor_WIDTH              1u

/* Interrupt constants */
#if defined(BackLSensor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BackLSensor_SetInterruptMode() function.
     *  @{
     */
        #define BackLSensor_INTR_NONE      (uint16)(0x0000u)
        #define BackLSensor_INTR_RISING    (uint16)(0x0001u)
        #define BackLSensor_INTR_FALLING   (uint16)(0x0002u)
        #define BackLSensor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BackLSensor_INTR_MASK      (0x01u) 
#endif /* (BackLSensor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BackLSensor_PS                     (* (reg8 *) BackLSensor__PS)
/* Data Register */
#define BackLSensor_DR                     (* (reg8 *) BackLSensor__DR)
/* Port Number */
#define BackLSensor_PRT_NUM                (* (reg8 *) BackLSensor__PRT) 
/* Connect to Analog Globals */                                                  
#define BackLSensor_AG                     (* (reg8 *) BackLSensor__AG)                       
/* Analog MUX bux enable */
#define BackLSensor_AMUX                   (* (reg8 *) BackLSensor__AMUX) 
/* Bidirectional Enable */                                                        
#define BackLSensor_BIE                    (* (reg8 *) BackLSensor__BIE)
/* Bit-mask for Aliased Register Access */
#define BackLSensor_BIT_MASK               (* (reg8 *) BackLSensor__BIT_MASK)
/* Bypass Enable */
#define BackLSensor_BYP                    (* (reg8 *) BackLSensor__BYP)
/* Port wide control signals */                                                   
#define BackLSensor_CTL                    (* (reg8 *) BackLSensor__CTL)
/* Drive Modes */
#define BackLSensor_DM0                    (* (reg8 *) BackLSensor__DM0) 
#define BackLSensor_DM1                    (* (reg8 *) BackLSensor__DM1)
#define BackLSensor_DM2                    (* (reg8 *) BackLSensor__DM2) 
/* Input Buffer Disable Override */
#define BackLSensor_INP_DIS                (* (reg8 *) BackLSensor__INP_DIS)
/* LCD Common or Segment Drive */
#define BackLSensor_LCD_COM_SEG            (* (reg8 *) BackLSensor__LCD_COM_SEG)
/* Enable Segment LCD */
#define BackLSensor_LCD_EN                 (* (reg8 *) BackLSensor__LCD_EN)
/* Slew Rate Control */
#define BackLSensor_SLW                    (* (reg8 *) BackLSensor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BackLSensor_PRTDSI__CAPS_SEL       (* (reg8 *) BackLSensor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BackLSensor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BackLSensor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BackLSensor_PRTDSI__OE_SEL0        (* (reg8 *) BackLSensor__PRTDSI__OE_SEL0) 
#define BackLSensor_PRTDSI__OE_SEL1        (* (reg8 *) BackLSensor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BackLSensor_PRTDSI__OUT_SEL0       (* (reg8 *) BackLSensor__PRTDSI__OUT_SEL0) 
#define BackLSensor_PRTDSI__OUT_SEL1       (* (reg8 *) BackLSensor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BackLSensor_PRTDSI__SYNC_OUT       (* (reg8 *) BackLSensor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BackLSensor__SIO_CFG)
    #define BackLSensor_SIO_HYST_EN        (* (reg8 *) BackLSensor__SIO_HYST_EN)
    #define BackLSensor_SIO_REG_HIFREQ     (* (reg8 *) BackLSensor__SIO_REG_HIFREQ)
    #define BackLSensor_SIO_CFG            (* (reg8 *) BackLSensor__SIO_CFG)
    #define BackLSensor_SIO_DIFF           (* (reg8 *) BackLSensor__SIO_DIFF)
#endif /* (BackLSensor__SIO_CFG) */

/* Interrupt Registers */
#if defined(BackLSensor__INTSTAT)
    #define BackLSensor_INTSTAT            (* (reg8 *) BackLSensor__INTSTAT)
    #define BackLSensor_SNAP               (* (reg8 *) BackLSensor__SNAP)
    
	#define BackLSensor_0_INTTYPE_REG 		(* (reg8 *) BackLSensor__0__INTTYPE)
#endif /* (BackLSensor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BackLSensor_H */


/* [] END OF FILE */
