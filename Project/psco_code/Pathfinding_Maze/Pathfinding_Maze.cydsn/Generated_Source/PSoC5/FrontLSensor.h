/*******************************************************************************
* File Name: FrontLSensor.h  
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

#if !defined(CY_PINS_FrontLSensor_H) /* Pins FrontLSensor_H */
#define CY_PINS_FrontLSensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FrontLSensor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FrontLSensor__PORT == 15 && ((FrontLSensor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FrontLSensor_Write(uint8 value);
void    FrontLSensor_SetDriveMode(uint8 mode);
uint8   FrontLSensor_ReadDataReg(void);
uint8   FrontLSensor_Read(void);
void    FrontLSensor_SetInterruptMode(uint16 position, uint16 mode);
uint8   FrontLSensor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FrontLSensor_SetDriveMode() function.
     *  @{
     */
        #define FrontLSensor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FrontLSensor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FrontLSensor_DM_RES_UP          PIN_DM_RES_UP
        #define FrontLSensor_DM_RES_DWN         PIN_DM_RES_DWN
        #define FrontLSensor_DM_OD_LO           PIN_DM_OD_LO
        #define FrontLSensor_DM_OD_HI           PIN_DM_OD_HI
        #define FrontLSensor_DM_STRONG          PIN_DM_STRONG
        #define FrontLSensor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FrontLSensor_MASK               FrontLSensor__MASK
#define FrontLSensor_SHIFT              FrontLSensor__SHIFT
#define FrontLSensor_WIDTH              1u

/* Interrupt constants */
#if defined(FrontLSensor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FrontLSensor_SetInterruptMode() function.
     *  @{
     */
        #define FrontLSensor_INTR_NONE      (uint16)(0x0000u)
        #define FrontLSensor_INTR_RISING    (uint16)(0x0001u)
        #define FrontLSensor_INTR_FALLING   (uint16)(0x0002u)
        #define FrontLSensor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FrontLSensor_INTR_MASK      (0x01u) 
#endif /* (FrontLSensor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FrontLSensor_PS                     (* (reg8 *) FrontLSensor__PS)
/* Data Register */
#define FrontLSensor_DR                     (* (reg8 *) FrontLSensor__DR)
/* Port Number */
#define FrontLSensor_PRT_NUM                (* (reg8 *) FrontLSensor__PRT) 
/* Connect to Analog Globals */                                                  
#define FrontLSensor_AG                     (* (reg8 *) FrontLSensor__AG)                       
/* Analog MUX bux enable */
#define FrontLSensor_AMUX                   (* (reg8 *) FrontLSensor__AMUX) 
/* Bidirectional Enable */                                                        
#define FrontLSensor_BIE                    (* (reg8 *) FrontLSensor__BIE)
/* Bit-mask for Aliased Register Access */
#define FrontLSensor_BIT_MASK               (* (reg8 *) FrontLSensor__BIT_MASK)
/* Bypass Enable */
#define FrontLSensor_BYP                    (* (reg8 *) FrontLSensor__BYP)
/* Port wide control signals */                                                   
#define FrontLSensor_CTL                    (* (reg8 *) FrontLSensor__CTL)
/* Drive Modes */
#define FrontLSensor_DM0                    (* (reg8 *) FrontLSensor__DM0) 
#define FrontLSensor_DM1                    (* (reg8 *) FrontLSensor__DM1)
#define FrontLSensor_DM2                    (* (reg8 *) FrontLSensor__DM2) 
/* Input Buffer Disable Override */
#define FrontLSensor_INP_DIS                (* (reg8 *) FrontLSensor__INP_DIS)
/* LCD Common or Segment Drive */
#define FrontLSensor_LCD_COM_SEG            (* (reg8 *) FrontLSensor__LCD_COM_SEG)
/* Enable Segment LCD */
#define FrontLSensor_LCD_EN                 (* (reg8 *) FrontLSensor__LCD_EN)
/* Slew Rate Control */
#define FrontLSensor_SLW                    (* (reg8 *) FrontLSensor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FrontLSensor_PRTDSI__CAPS_SEL       (* (reg8 *) FrontLSensor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FrontLSensor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FrontLSensor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FrontLSensor_PRTDSI__OE_SEL0        (* (reg8 *) FrontLSensor__PRTDSI__OE_SEL0) 
#define FrontLSensor_PRTDSI__OE_SEL1        (* (reg8 *) FrontLSensor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FrontLSensor_PRTDSI__OUT_SEL0       (* (reg8 *) FrontLSensor__PRTDSI__OUT_SEL0) 
#define FrontLSensor_PRTDSI__OUT_SEL1       (* (reg8 *) FrontLSensor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FrontLSensor_PRTDSI__SYNC_OUT       (* (reg8 *) FrontLSensor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FrontLSensor__SIO_CFG)
    #define FrontLSensor_SIO_HYST_EN        (* (reg8 *) FrontLSensor__SIO_HYST_EN)
    #define FrontLSensor_SIO_REG_HIFREQ     (* (reg8 *) FrontLSensor__SIO_REG_HIFREQ)
    #define FrontLSensor_SIO_CFG            (* (reg8 *) FrontLSensor__SIO_CFG)
    #define FrontLSensor_SIO_DIFF           (* (reg8 *) FrontLSensor__SIO_DIFF)
#endif /* (FrontLSensor__SIO_CFG) */

/* Interrupt Registers */
#if defined(FrontLSensor__INTSTAT)
    #define FrontLSensor_INTSTAT            (* (reg8 *) FrontLSensor__INTSTAT)
    #define FrontLSensor_SNAP               (* (reg8 *) FrontLSensor__SNAP)
    
	#define FrontLSensor_0_INTTYPE_REG 		(* (reg8 *) FrontLSensor__0__INTTYPE)
#endif /* (FrontLSensor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FrontLSensor_H */


/* [] END OF FILE */
