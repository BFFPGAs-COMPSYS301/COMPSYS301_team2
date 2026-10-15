/*******************************************************************************
* File Name: BackRSensor.h  
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

#if !defined(CY_PINS_BackRSensor_H) /* Pins BackRSensor_H */
#define CY_PINS_BackRSensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BackRSensor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BackRSensor__PORT == 15 && ((BackRSensor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BackRSensor_Write(uint8 value);
void    BackRSensor_SetDriveMode(uint8 mode);
uint8   BackRSensor_ReadDataReg(void);
uint8   BackRSensor_Read(void);
void    BackRSensor_SetInterruptMode(uint16 position, uint16 mode);
uint8   BackRSensor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BackRSensor_SetDriveMode() function.
     *  @{
     */
        #define BackRSensor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BackRSensor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BackRSensor_DM_RES_UP          PIN_DM_RES_UP
        #define BackRSensor_DM_RES_DWN         PIN_DM_RES_DWN
        #define BackRSensor_DM_OD_LO           PIN_DM_OD_LO
        #define BackRSensor_DM_OD_HI           PIN_DM_OD_HI
        #define BackRSensor_DM_STRONG          PIN_DM_STRONG
        #define BackRSensor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BackRSensor_MASK               BackRSensor__MASK
#define BackRSensor_SHIFT              BackRSensor__SHIFT
#define BackRSensor_WIDTH              1u

/* Interrupt constants */
#if defined(BackRSensor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BackRSensor_SetInterruptMode() function.
     *  @{
     */
        #define BackRSensor_INTR_NONE      (uint16)(0x0000u)
        #define BackRSensor_INTR_RISING    (uint16)(0x0001u)
        #define BackRSensor_INTR_FALLING   (uint16)(0x0002u)
        #define BackRSensor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BackRSensor_INTR_MASK      (0x01u) 
#endif /* (BackRSensor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BackRSensor_PS                     (* (reg8 *) BackRSensor__PS)
/* Data Register */
#define BackRSensor_DR                     (* (reg8 *) BackRSensor__DR)
/* Port Number */
#define BackRSensor_PRT_NUM                (* (reg8 *) BackRSensor__PRT) 
/* Connect to Analog Globals */                                                  
#define BackRSensor_AG                     (* (reg8 *) BackRSensor__AG)                       
/* Analog MUX bux enable */
#define BackRSensor_AMUX                   (* (reg8 *) BackRSensor__AMUX) 
/* Bidirectional Enable */                                                        
#define BackRSensor_BIE                    (* (reg8 *) BackRSensor__BIE)
/* Bit-mask for Aliased Register Access */
#define BackRSensor_BIT_MASK               (* (reg8 *) BackRSensor__BIT_MASK)
/* Bypass Enable */
#define BackRSensor_BYP                    (* (reg8 *) BackRSensor__BYP)
/* Port wide control signals */                                                   
#define BackRSensor_CTL                    (* (reg8 *) BackRSensor__CTL)
/* Drive Modes */
#define BackRSensor_DM0                    (* (reg8 *) BackRSensor__DM0) 
#define BackRSensor_DM1                    (* (reg8 *) BackRSensor__DM1)
#define BackRSensor_DM2                    (* (reg8 *) BackRSensor__DM2) 
/* Input Buffer Disable Override */
#define BackRSensor_INP_DIS                (* (reg8 *) BackRSensor__INP_DIS)
/* LCD Common or Segment Drive */
#define BackRSensor_LCD_COM_SEG            (* (reg8 *) BackRSensor__LCD_COM_SEG)
/* Enable Segment LCD */
#define BackRSensor_LCD_EN                 (* (reg8 *) BackRSensor__LCD_EN)
/* Slew Rate Control */
#define BackRSensor_SLW                    (* (reg8 *) BackRSensor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BackRSensor_PRTDSI__CAPS_SEL       (* (reg8 *) BackRSensor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BackRSensor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BackRSensor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BackRSensor_PRTDSI__OE_SEL0        (* (reg8 *) BackRSensor__PRTDSI__OE_SEL0) 
#define BackRSensor_PRTDSI__OE_SEL1        (* (reg8 *) BackRSensor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BackRSensor_PRTDSI__OUT_SEL0       (* (reg8 *) BackRSensor__PRTDSI__OUT_SEL0) 
#define BackRSensor_PRTDSI__OUT_SEL1       (* (reg8 *) BackRSensor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BackRSensor_PRTDSI__SYNC_OUT       (* (reg8 *) BackRSensor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BackRSensor__SIO_CFG)
    #define BackRSensor_SIO_HYST_EN        (* (reg8 *) BackRSensor__SIO_HYST_EN)
    #define BackRSensor_SIO_REG_HIFREQ     (* (reg8 *) BackRSensor__SIO_REG_HIFREQ)
    #define BackRSensor_SIO_CFG            (* (reg8 *) BackRSensor__SIO_CFG)
    #define BackRSensor_SIO_DIFF           (* (reg8 *) BackRSensor__SIO_DIFF)
#endif /* (BackRSensor__SIO_CFG) */

/* Interrupt Registers */
#if defined(BackRSensor__INTSTAT)
    #define BackRSensor_INTSTAT            (* (reg8 *) BackRSensor__INTSTAT)
    #define BackRSensor_SNAP               (* (reg8 *) BackRSensor__SNAP)
    
	#define BackRSensor_0_INTTYPE_REG 		(* (reg8 *) BackRSensor__0__INTTYPE)
#endif /* (BackRSensor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BackRSensor_H */


/* [] END OF FILE */
