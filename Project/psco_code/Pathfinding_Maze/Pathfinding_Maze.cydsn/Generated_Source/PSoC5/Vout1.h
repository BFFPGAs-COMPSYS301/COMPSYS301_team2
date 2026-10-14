/*******************************************************************************
* File Name: Vout1.h  
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

#if !defined(CY_PINS_Vout1_H) /* Pins Vout1_H */
#define CY_PINS_Vout1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vout1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vout1__PORT == 15 && ((Vout1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vout1_Write(uint8 value);
void    Vout1_SetDriveMode(uint8 mode);
uint8   Vout1_ReadDataReg(void);
uint8   Vout1_Read(void);
void    Vout1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vout1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vout1_SetDriveMode() function.
     *  @{
     */
        #define Vout1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vout1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vout1_DM_RES_UP          PIN_DM_RES_UP
        #define Vout1_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vout1_DM_OD_LO           PIN_DM_OD_LO
        #define Vout1_DM_OD_HI           PIN_DM_OD_HI
        #define Vout1_DM_STRONG          PIN_DM_STRONG
        #define Vout1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vout1_MASK               Vout1__MASK
#define Vout1_SHIFT              Vout1__SHIFT
#define Vout1_WIDTH              1u

/* Interrupt constants */
#if defined(Vout1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vout1_SetInterruptMode() function.
     *  @{
     */
        #define Vout1_INTR_NONE      (uint16)(0x0000u)
        #define Vout1_INTR_RISING    (uint16)(0x0001u)
        #define Vout1_INTR_FALLING   (uint16)(0x0002u)
        #define Vout1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vout1_INTR_MASK      (0x01u) 
#endif /* (Vout1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vout1_PS                     (* (reg8 *) Vout1__PS)
/* Data Register */
#define Vout1_DR                     (* (reg8 *) Vout1__DR)
/* Port Number */
#define Vout1_PRT_NUM                (* (reg8 *) Vout1__PRT) 
/* Connect to Analog Globals */                                                  
#define Vout1_AG                     (* (reg8 *) Vout1__AG)                       
/* Analog MUX bux enable */
#define Vout1_AMUX                   (* (reg8 *) Vout1__AMUX) 
/* Bidirectional Enable */                                                        
#define Vout1_BIE                    (* (reg8 *) Vout1__BIE)
/* Bit-mask for Aliased Register Access */
#define Vout1_BIT_MASK               (* (reg8 *) Vout1__BIT_MASK)
/* Bypass Enable */
#define Vout1_BYP                    (* (reg8 *) Vout1__BYP)
/* Port wide control signals */                                                   
#define Vout1_CTL                    (* (reg8 *) Vout1__CTL)
/* Drive Modes */
#define Vout1_DM0                    (* (reg8 *) Vout1__DM0) 
#define Vout1_DM1                    (* (reg8 *) Vout1__DM1)
#define Vout1_DM2                    (* (reg8 *) Vout1__DM2) 
/* Input Buffer Disable Override */
#define Vout1_INP_DIS                (* (reg8 *) Vout1__INP_DIS)
/* LCD Common or Segment Drive */
#define Vout1_LCD_COM_SEG            (* (reg8 *) Vout1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vout1_LCD_EN                 (* (reg8 *) Vout1__LCD_EN)
/* Slew Rate Control */
#define Vout1_SLW                    (* (reg8 *) Vout1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vout1_PRTDSI__CAPS_SEL       (* (reg8 *) Vout1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vout1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vout1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vout1_PRTDSI__OE_SEL0        (* (reg8 *) Vout1__PRTDSI__OE_SEL0) 
#define Vout1_PRTDSI__OE_SEL1        (* (reg8 *) Vout1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vout1_PRTDSI__OUT_SEL0       (* (reg8 *) Vout1__PRTDSI__OUT_SEL0) 
#define Vout1_PRTDSI__OUT_SEL1       (* (reg8 *) Vout1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vout1_PRTDSI__SYNC_OUT       (* (reg8 *) Vout1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vout1__SIO_CFG)
    #define Vout1_SIO_HYST_EN        (* (reg8 *) Vout1__SIO_HYST_EN)
    #define Vout1_SIO_REG_HIFREQ     (* (reg8 *) Vout1__SIO_REG_HIFREQ)
    #define Vout1_SIO_CFG            (* (reg8 *) Vout1__SIO_CFG)
    #define Vout1_SIO_DIFF           (* (reg8 *) Vout1__SIO_DIFF)
#endif /* (Vout1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vout1__INTSTAT)
    #define Vout1_INTSTAT            (* (reg8 *) Vout1__INTSTAT)
    #define Vout1_SNAP               (* (reg8 *) Vout1__SNAP)
    
	#define Vout1_0_INTTYPE_REG 		(* (reg8 *) Vout1__0__INTTYPE)
#endif /* (Vout1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vout1_H */


/* [] END OF FILE */
