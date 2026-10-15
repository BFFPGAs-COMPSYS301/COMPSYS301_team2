/*******************************************************************************
* File Name: L_quad_a.h  
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

#if !defined(CY_PINS_L_quad_a_H) /* Pins L_quad_a_H */
#define CY_PINS_L_quad_a_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "L_quad_a_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 L_quad_a__PORT == 15 && ((L_quad_a__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    L_quad_a_Write(uint8 value);
void    L_quad_a_SetDriveMode(uint8 mode);
uint8   L_quad_a_ReadDataReg(void);
uint8   L_quad_a_Read(void);
void    L_quad_a_SetInterruptMode(uint16 position, uint16 mode);
uint8   L_quad_a_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the L_quad_a_SetDriveMode() function.
     *  @{
     */
        #define L_quad_a_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define L_quad_a_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define L_quad_a_DM_RES_UP          PIN_DM_RES_UP
        #define L_quad_a_DM_RES_DWN         PIN_DM_RES_DWN
        #define L_quad_a_DM_OD_LO           PIN_DM_OD_LO
        #define L_quad_a_DM_OD_HI           PIN_DM_OD_HI
        #define L_quad_a_DM_STRONG          PIN_DM_STRONG
        #define L_quad_a_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define L_quad_a_MASK               L_quad_a__MASK
#define L_quad_a_SHIFT              L_quad_a__SHIFT
#define L_quad_a_WIDTH              1u

/* Interrupt constants */
#if defined(L_quad_a__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in L_quad_a_SetInterruptMode() function.
     *  @{
     */
        #define L_quad_a_INTR_NONE      (uint16)(0x0000u)
        #define L_quad_a_INTR_RISING    (uint16)(0x0001u)
        #define L_quad_a_INTR_FALLING   (uint16)(0x0002u)
        #define L_quad_a_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define L_quad_a_INTR_MASK      (0x01u) 
#endif /* (L_quad_a__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define L_quad_a_PS                     (* (reg8 *) L_quad_a__PS)
/* Data Register */
#define L_quad_a_DR                     (* (reg8 *) L_quad_a__DR)
/* Port Number */
#define L_quad_a_PRT_NUM                (* (reg8 *) L_quad_a__PRT) 
/* Connect to Analog Globals */                                                  
#define L_quad_a_AG                     (* (reg8 *) L_quad_a__AG)                       
/* Analog MUX bux enable */
#define L_quad_a_AMUX                   (* (reg8 *) L_quad_a__AMUX) 
/* Bidirectional Enable */                                                        
#define L_quad_a_BIE                    (* (reg8 *) L_quad_a__BIE)
/* Bit-mask for Aliased Register Access */
#define L_quad_a_BIT_MASK               (* (reg8 *) L_quad_a__BIT_MASK)
/* Bypass Enable */
#define L_quad_a_BYP                    (* (reg8 *) L_quad_a__BYP)
/* Port wide control signals */                                                   
#define L_quad_a_CTL                    (* (reg8 *) L_quad_a__CTL)
/* Drive Modes */
#define L_quad_a_DM0                    (* (reg8 *) L_quad_a__DM0) 
#define L_quad_a_DM1                    (* (reg8 *) L_quad_a__DM1)
#define L_quad_a_DM2                    (* (reg8 *) L_quad_a__DM2) 
/* Input Buffer Disable Override */
#define L_quad_a_INP_DIS                (* (reg8 *) L_quad_a__INP_DIS)
/* LCD Common or Segment Drive */
#define L_quad_a_LCD_COM_SEG            (* (reg8 *) L_quad_a__LCD_COM_SEG)
/* Enable Segment LCD */
#define L_quad_a_LCD_EN                 (* (reg8 *) L_quad_a__LCD_EN)
/* Slew Rate Control */
#define L_quad_a_SLW                    (* (reg8 *) L_quad_a__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define L_quad_a_PRTDSI__CAPS_SEL       (* (reg8 *) L_quad_a__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define L_quad_a_PRTDSI__DBL_SYNC_IN    (* (reg8 *) L_quad_a__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define L_quad_a_PRTDSI__OE_SEL0        (* (reg8 *) L_quad_a__PRTDSI__OE_SEL0) 
#define L_quad_a_PRTDSI__OE_SEL1        (* (reg8 *) L_quad_a__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define L_quad_a_PRTDSI__OUT_SEL0       (* (reg8 *) L_quad_a__PRTDSI__OUT_SEL0) 
#define L_quad_a_PRTDSI__OUT_SEL1       (* (reg8 *) L_quad_a__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define L_quad_a_PRTDSI__SYNC_OUT       (* (reg8 *) L_quad_a__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(L_quad_a__SIO_CFG)
    #define L_quad_a_SIO_HYST_EN        (* (reg8 *) L_quad_a__SIO_HYST_EN)
    #define L_quad_a_SIO_REG_HIFREQ     (* (reg8 *) L_quad_a__SIO_REG_HIFREQ)
    #define L_quad_a_SIO_CFG            (* (reg8 *) L_quad_a__SIO_CFG)
    #define L_quad_a_SIO_DIFF           (* (reg8 *) L_quad_a__SIO_DIFF)
#endif /* (L_quad_a__SIO_CFG) */

/* Interrupt Registers */
#if defined(L_quad_a__INTSTAT)
    #define L_quad_a_INTSTAT            (* (reg8 *) L_quad_a__INTSTAT)
    #define L_quad_a_SNAP               (* (reg8 *) L_quad_a__SNAP)
    
	#define L_quad_a_0_INTTYPE_REG 		(* (reg8 *) L_quad_a__0__INTTYPE)
#endif /* (L_quad_a__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_L_quad_a_H */


/* [] END OF FILE */
