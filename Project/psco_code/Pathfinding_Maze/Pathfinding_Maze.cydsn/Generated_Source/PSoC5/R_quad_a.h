/*******************************************************************************
* File Name: R_quad_a.h  
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

#if !defined(CY_PINS_R_quad_a_H) /* Pins R_quad_a_H */
#define CY_PINS_R_quad_a_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "R_quad_a_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 R_quad_a__PORT == 15 && ((R_quad_a__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    R_quad_a_Write(uint8 value);
void    R_quad_a_SetDriveMode(uint8 mode);
uint8   R_quad_a_ReadDataReg(void);
uint8   R_quad_a_Read(void);
void    R_quad_a_SetInterruptMode(uint16 position, uint16 mode);
uint8   R_quad_a_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the R_quad_a_SetDriveMode() function.
     *  @{
     */
        #define R_quad_a_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define R_quad_a_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define R_quad_a_DM_RES_UP          PIN_DM_RES_UP
        #define R_quad_a_DM_RES_DWN         PIN_DM_RES_DWN
        #define R_quad_a_DM_OD_LO           PIN_DM_OD_LO
        #define R_quad_a_DM_OD_HI           PIN_DM_OD_HI
        #define R_quad_a_DM_STRONG          PIN_DM_STRONG
        #define R_quad_a_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define R_quad_a_MASK               R_quad_a__MASK
#define R_quad_a_SHIFT              R_quad_a__SHIFT
#define R_quad_a_WIDTH              1u

/* Interrupt constants */
#if defined(R_quad_a__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in R_quad_a_SetInterruptMode() function.
     *  @{
     */
        #define R_quad_a_INTR_NONE      (uint16)(0x0000u)
        #define R_quad_a_INTR_RISING    (uint16)(0x0001u)
        #define R_quad_a_INTR_FALLING   (uint16)(0x0002u)
        #define R_quad_a_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define R_quad_a_INTR_MASK      (0x01u) 
#endif /* (R_quad_a__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define R_quad_a_PS                     (* (reg8 *) R_quad_a__PS)
/* Data Register */
#define R_quad_a_DR                     (* (reg8 *) R_quad_a__DR)
/* Port Number */
#define R_quad_a_PRT_NUM                (* (reg8 *) R_quad_a__PRT) 
/* Connect to Analog Globals */                                                  
#define R_quad_a_AG                     (* (reg8 *) R_quad_a__AG)                       
/* Analog MUX bux enable */
#define R_quad_a_AMUX                   (* (reg8 *) R_quad_a__AMUX) 
/* Bidirectional Enable */                                                        
#define R_quad_a_BIE                    (* (reg8 *) R_quad_a__BIE)
/* Bit-mask for Aliased Register Access */
#define R_quad_a_BIT_MASK               (* (reg8 *) R_quad_a__BIT_MASK)
/* Bypass Enable */
#define R_quad_a_BYP                    (* (reg8 *) R_quad_a__BYP)
/* Port wide control signals */                                                   
#define R_quad_a_CTL                    (* (reg8 *) R_quad_a__CTL)
/* Drive Modes */
#define R_quad_a_DM0                    (* (reg8 *) R_quad_a__DM0) 
#define R_quad_a_DM1                    (* (reg8 *) R_quad_a__DM1)
#define R_quad_a_DM2                    (* (reg8 *) R_quad_a__DM2) 
/* Input Buffer Disable Override */
#define R_quad_a_INP_DIS                (* (reg8 *) R_quad_a__INP_DIS)
/* LCD Common or Segment Drive */
#define R_quad_a_LCD_COM_SEG            (* (reg8 *) R_quad_a__LCD_COM_SEG)
/* Enable Segment LCD */
#define R_quad_a_LCD_EN                 (* (reg8 *) R_quad_a__LCD_EN)
/* Slew Rate Control */
#define R_quad_a_SLW                    (* (reg8 *) R_quad_a__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define R_quad_a_PRTDSI__CAPS_SEL       (* (reg8 *) R_quad_a__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define R_quad_a_PRTDSI__DBL_SYNC_IN    (* (reg8 *) R_quad_a__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define R_quad_a_PRTDSI__OE_SEL0        (* (reg8 *) R_quad_a__PRTDSI__OE_SEL0) 
#define R_quad_a_PRTDSI__OE_SEL1        (* (reg8 *) R_quad_a__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define R_quad_a_PRTDSI__OUT_SEL0       (* (reg8 *) R_quad_a__PRTDSI__OUT_SEL0) 
#define R_quad_a_PRTDSI__OUT_SEL1       (* (reg8 *) R_quad_a__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define R_quad_a_PRTDSI__SYNC_OUT       (* (reg8 *) R_quad_a__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(R_quad_a__SIO_CFG)
    #define R_quad_a_SIO_HYST_EN        (* (reg8 *) R_quad_a__SIO_HYST_EN)
    #define R_quad_a_SIO_REG_HIFREQ     (* (reg8 *) R_quad_a__SIO_REG_HIFREQ)
    #define R_quad_a_SIO_CFG            (* (reg8 *) R_quad_a__SIO_CFG)
    #define R_quad_a_SIO_DIFF           (* (reg8 *) R_quad_a__SIO_DIFF)
#endif /* (R_quad_a__SIO_CFG) */

/* Interrupt Registers */
#if defined(R_quad_a__INTSTAT)
    #define R_quad_a_INTSTAT            (* (reg8 *) R_quad_a__INTSTAT)
    #define R_quad_a_SNAP               (* (reg8 *) R_quad_a__SNAP)
    
	#define R_quad_a_0_INTTYPE_REG 		(* (reg8 *) R_quad_a__0__INTTYPE)
#endif /* (R_quad_a__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_R_quad_a_H */


/* [] END OF FILE */
