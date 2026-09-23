/*******************************************************************************
* File Name: Vout5.h  
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

#if !defined(CY_PINS_Vout5_H) /* Pins Vout5_H */
#define CY_PINS_Vout5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vout5_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vout5__PORT == 15 && ((Vout5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vout5_Write(uint8 value);
void    Vout5_SetDriveMode(uint8 mode);
uint8   Vout5_ReadDataReg(void);
uint8   Vout5_Read(void);
void    Vout5_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vout5_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vout5_SetDriveMode() function.
     *  @{
     */
        #define Vout5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vout5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vout5_DM_RES_UP          PIN_DM_RES_UP
        #define Vout5_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vout5_DM_OD_LO           PIN_DM_OD_LO
        #define Vout5_DM_OD_HI           PIN_DM_OD_HI
        #define Vout5_DM_STRONG          PIN_DM_STRONG
        #define Vout5_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vout5_MASK               Vout5__MASK
#define Vout5_SHIFT              Vout5__SHIFT
#define Vout5_WIDTH              1u

/* Interrupt constants */
#if defined(Vout5__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vout5_SetInterruptMode() function.
     *  @{
     */
        #define Vout5_INTR_NONE      (uint16)(0x0000u)
        #define Vout5_INTR_RISING    (uint16)(0x0001u)
        #define Vout5_INTR_FALLING   (uint16)(0x0002u)
        #define Vout5_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vout5_INTR_MASK      (0x01u) 
#endif /* (Vout5__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vout5_PS                     (* (reg8 *) Vout5__PS)
/* Data Register */
#define Vout5_DR                     (* (reg8 *) Vout5__DR)
/* Port Number */
#define Vout5_PRT_NUM                (* (reg8 *) Vout5__PRT) 
/* Connect to Analog Globals */                                                  
#define Vout5_AG                     (* (reg8 *) Vout5__AG)                       
/* Analog MUX bux enable */
#define Vout5_AMUX                   (* (reg8 *) Vout5__AMUX) 
/* Bidirectional Enable */                                                        
#define Vout5_BIE                    (* (reg8 *) Vout5__BIE)
/* Bit-mask for Aliased Register Access */
#define Vout5_BIT_MASK               (* (reg8 *) Vout5__BIT_MASK)
/* Bypass Enable */
#define Vout5_BYP                    (* (reg8 *) Vout5__BYP)
/* Port wide control signals */                                                   
#define Vout5_CTL                    (* (reg8 *) Vout5__CTL)
/* Drive Modes */
#define Vout5_DM0                    (* (reg8 *) Vout5__DM0) 
#define Vout5_DM1                    (* (reg8 *) Vout5__DM1)
#define Vout5_DM2                    (* (reg8 *) Vout5__DM2) 
/* Input Buffer Disable Override */
#define Vout5_INP_DIS                (* (reg8 *) Vout5__INP_DIS)
/* LCD Common or Segment Drive */
#define Vout5_LCD_COM_SEG            (* (reg8 *) Vout5__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vout5_LCD_EN                 (* (reg8 *) Vout5__LCD_EN)
/* Slew Rate Control */
#define Vout5_SLW                    (* (reg8 *) Vout5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vout5_PRTDSI__CAPS_SEL       (* (reg8 *) Vout5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vout5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vout5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vout5_PRTDSI__OE_SEL0        (* (reg8 *) Vout5__PRTDSI__OE_SEL0) 
#define Vout5_PRTDSI__OE_SEL1        (* (reg8 *) Vout5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vout5_PRTDSI__OUT_SEL0       (* (reg8 *) Vout5__PRTDSI__OUT_SEL0) 
#define Vout5_PRTDSI__OUT_SEL1       (* (reg8 *) Vout5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vout5_PRTDSI__SYNC_OUT       (* (reg8 *) Vout5__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vout5__SIO_CFG)
    #define Vout5_SIO_HYST_EN        (* (reg8 *) Vout5__SIO_HYST_EN)
    #define Vout5_SIO_REG_HIFREQ     (* (reg8 *) Vout5__SIO_REG_HIFREQ)
    #define Vout5_SIO_CFG            (* (reg8 *) Vout5__SIO_CFG)
    #define Vout5_SIO_DIFF           (* (reg8 *) Vout5__SIO_DIFF)
#endif /* (Vout5__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vout5__INTSTAT)
    #define Vout5_INTSTAT            (* (reg8 *) Vout5__INTSTAT)
    #define Vout5_SNAP               (* (reg8 *) Vout5__SNAP)
    
	#define Vout5_0_INTTYPE_REG 		(* (reg8 *) Vout5__0__INTTYPE)
#endif /* (Vout5__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vout5_H */


/* [] END OF FILE */
