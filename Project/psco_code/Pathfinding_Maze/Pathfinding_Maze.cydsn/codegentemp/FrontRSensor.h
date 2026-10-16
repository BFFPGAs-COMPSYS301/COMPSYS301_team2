/*******************************************************************************
* File Name: FrontRSensor.h  
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

#if !defined(CY_PINS_FrontRSensor_H) /* Pins FrontRSensor_H */
#define CY_PINS_FrontRSensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FrontRSensor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FrontRSensor__PORT == 15 && ((FrontRSensor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FrontRSensor_Write(uint8 value);
void    FrontRSensor_SetDriveMode(uint8 mode);
uint8   FrontRSensor_ReadDataReg(void);
uint8   FrontRSensor_Read(void);
void    FrontRSensor_SetInterruptMode(uint16 position, uint16 mode);
uint8   FrontRSensor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FrontRSensor_SetDriveMode() function.
     *  @{
     */
        #define FrontRSensor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FrontRSensor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FrontRSensor_DM_RES_UP          PIN_DM_RES_UP
        #define FrontRSensor_DM_RES_DWN         PIN_DM_RES_DWN
        #define FrontRSensor_DM_OD_LO           PIN_DM_OD_LO
        #define FrontRSensor_DM_OD_HI           PIN_DM_OD_HI
        #define FrontRSensor_DM_STRONG          PIN_DM_STRONG
        #define FrontRSensor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FrontRSensor_MASK               FrontRSensor__MASK
#define FrontRSensor_SHIFT              FrontRSensor__SHIFT
#define FrontRSensor_WIDTH              1u

/* Interrupt constants */
#if defined(FrontRSensor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FrontRSensor_SetInterruptMode() function.
     *  @{
     */
        #define FrontRSensor_INTR_NONE      (uint16)(0x0000u)
        #define FrontRSensor_INTR_RISING    (uint16)(0x0001u)
        #define FrontRSensor_INTR_FALLING   (uint16)(0x0002u)
        #define FrontRSensor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FrontRSensor_INTR_MASK      (0x01u) 
#endif /* (FrontRSensor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FrontRSensor_PS                     (* (reg8 *) FrontRSensor__PS)
/* Data Register */
#define FrontRSensor_DR                     (* (reg8 *) FrontRSensor__DR)
/* Port Number */
#define FrontRSensor_PRT_NUM                (* (reg8 *) FrontRSensor__PRT) 
/* Connect to Analog Globals */                                                  
#define FrontRSensor_AG                     (* (reg8 *) FrontRSensor__AG)                       
/* Analog MUX bux enable */
#define FrontRSensor_AMUX                   (* (reg8 *) FrontRSensor__AMUX) 
/* Bidirectional Enable */                                                        
#define FrontRSensor_BIE                    (* (reg8 *) FrontRSensor__BIE)
/* Bit-mask for Aliased Register Access */
#define FrontRSensor_BIT_MASK               (* (reg8 *) FrontRSensor__BIT_MASK)
/* Bypass Enable */
#define FrontRSensor_BYP                    (* (reg8 *) FrontRSensor__BYP)
/* Port wide control signals */                                                   
#define FrontRSensor_CTL                    (* (reg8 *) FrontRSensor__CTL)
/* Drive Modes */
#define FrontRSensor_DM0                    (* (reg8 *) FrontRSensor__DM0) 
#define FrontRSensor_DM1                    (* (reg8 *) FrontRSensor__DM1)
#define FrontRSensor_DM2                    (* (reg8 *) FrontRSensor__DM2) 
/* Input Buffer Disable Override */
#define FrontRSensor_INP_DIS                (* (reg8 *) FrontRSensor__INP_DIS)
/* LCD Common or Segment Drive */
#define FrontRSensor_LCD_COM_SEG            (* (reg8 *) FrontRSensor__LCD_COM_SEG)
/* Enable Segment LCD */
#define FrontRSensor_LCD_EN                 (* (reg8 *) FrontRSensor__LCD_EN)
/* Slew Rate Control */
#define FrontRSensor_SLW                    (* (reg8 *) FrontRSensor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FrontRSensor_PRTDSI__CAPS_SEL       (* (reg8 *) FrontRSensor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FrontRSensor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FrontRSensor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FrontRSensor_PRTDSI__OE_SEL0        (* (reg8 *) FrontRSensor__PRTDSI__OE_SEL0) 
#define FrontRSensor_PRTDSI__OE_SEL1        (* (reg8 *) FrontRSensor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FrontRSensor_PRTDSI__OUT_SEL0       (* (reg8 *) FrontRSensor__PRTDSI__OUT_SEL0) 
#define FrontRSensor_PRTDSI__OUT_SEL1       (* (reg8 *) FrontRSensor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FrontRSensor_PRTDSI__SYNC_OUT       (* (reg8 *) FrontRSensor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FrontRSensor__SIO_CFG)
    #define FrontRSensor_SIO_HYST_EN        (* (reg8 *) FrontRSensor__SIO_HYST_EN)
    #define FrontRSensor_SIO_REG_HIFREQ     (* (reg8 *) FrontRSensor__SIO_REG_HIFREQ)
    #define FrontRSensor_SIO_CFG            (* (reg8 *) FrontRSensor__SIO_CFG)
    #define FrontRSensor_SIO_DIFF           (* (reg8 *) FrontRSensor__SIO_DIFF)
#endif /* (FrontRSensor__SIO_CFG) */

/* Interrupt Registers */
#if defined(FrontRSensor__INTSTAT)
    #define FrontRSensor_INTSTAT            (* (reg8 *) FrontRSensor__INTSTAT)
    #define FrontRSensor_SNAP               (* (reg8 *) FrontRSensor__SNAP)
    
	#define FrontRSensor_0_INTTYPE_REG 		(* (reg8 *) FrontRSensor__0__INTTYPE)
#endif /* (FrontRSensor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FrontRSensor_H */


/* [] END OF FILE */
