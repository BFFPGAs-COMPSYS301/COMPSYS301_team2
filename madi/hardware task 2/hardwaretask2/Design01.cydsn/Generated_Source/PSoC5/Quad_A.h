/*******************************************************************************
* File Name: Quad_A.h  
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

#if !defined(CY_PINS_Quad_A_H) /* Pins Quad_A_H */
#define CY_PINS_Quad_A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Quad_A_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Quad_A__PORT == 15 && ((Quad_A__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Quad_A_Write(uint8 value);
void    Quad_A_SetDriveMode(uint8 mode);
uint8   Quad_A_ReadDataReg(void);
uint8   Quad_A_Read(void);
void    Quad_A_SetInterruptMode(uint16 position, uint16 mode);
uint8   Quad_A_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Quad_A_SetDriveMode() function.
     *  @{
     */
        #define Quad_A_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Quad_A_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Quad_A_DM_RES_UP          PIN_DM_RES_UP
        #define Quad_A_DM_RES_DWN         PIN_DM_RES_DWN
        #define Quad_A_DM_OD_LO           PIN_DM_OD_LO
        #define Quad_A_DM_OD_HI           PIN_DM_OD_HI
        #define Quad_A_DM_STRONG          PIN_DM_STRONG
        #define Quad_A_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Quad_A_MASK               Quad_A__MASK
#define Quad_A_SHIFT              Quad_A__SHIFT
#define Quad_A_WIDTH              1u

/* Interrupt constants */
#if defined(Quad_A__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Quad_A_SetInterruptMode() function.
     *  @{
     */
        #define Quad_A_INTR_NONE      (uint16)(0x0000u)
        #define Quad_A_INTR_RISING    (uint16)(0x0001u)
        #define Quad_A_INTR_FALLING   (uint16)(0x0002u)
        #define Quad_A_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Quad_A_INTR_MASK      (0x01u) 
#endif /* (Quad_A__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Quad_A_PS                     (* (reg8 *) Quad_A__PS)
/* Data Register */
#define Quad_A_DR                     (* (reg8 *) Quad_A__DR)
/* Port Number */
#define Quad_A_PRT_NUM                (* (reg8 *) Quad_A__PRT) 
/* Connect to Analog Globals */                                                  
#define Quad_A_AG                     (* (reg8 *) Quad_A__AG)                       
/* Analog MUX bux enable */
#define Quad_A_AMUX                   (* (reg8 *) Quad_A__AMUX) 
/* Bidirectional Enable */                                                        
#define Quad_A_BIE                    (* (reg8 *) Quad_A__BIE)
/* Bit-mask for Aliased Register Access */
#define Quad_A_BIT_MASK               (* (reg8 *) Quad_A__BIT_MASK)
/* Bypass Enable */
#define Quad_A_BYP                    (* (reg8 *) Quad_A__BYP)
/* Port wide control signals */                                                   
#define Quad_A_CTL                    (* (reg8 *) Quad_A__CTL)
/* Drive Modes */
#define Quad_A_DM0                    (* (reg8 *) Quad_A__DM0) 
#define Quad_A_DM1                    (* (reg8 *) Quad_A__DM1)
#define Quad_A_DM2                    (* (reg8 *) Quad_A__DM2) 
/* Input Buffer Disable Override */
#define Quad_A_INP_DIS                (* (reg8 *) Quad_A__INP_DIS)
/* LCD Common or Segment Drive */
#define Quad_A_LCD_COM_SEG            (* (reg8 *) Quad_A__LCD_COM_SEG)
/* Enable Segment LCD */
#define Quad_A_LCD_EN                 (* (reg8 *) Quad_A__LCD_EN)
/* Slew Rate Control */
#define Quad_A_SLW                    (* (reg8 *) Quad_A__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Quad_A_PRTDSI__CAPS_SEL       (* (reg8 *) Quad_A__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Quad_A_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Quad_A__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Quad_A_PRTDSI__OE_SEL0        (* (reg8 *) Quad_A__PRTDSI__OE_SEL0) 
#define Quad_A_PRTDSI__OE_SEL1        (* (reg8 *) Quad_A__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Quad_A_PRTDSI__OUT_SEL0       (* (reg8 *) Quad_A__PRTDSI__OUT_SEL0) 
#define Quad_A_PRTDSI__OUT_SEL1       (* (reg8 *) Quad_A__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Quad_A_PRTDSI__SYNC_OUT       (* (reg8 *) Quad_A__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Quad_A__SIO_CFG)
    #define Quad_A_SIO_HYST_EN        (* (reg8 *) Quad_A__SIO_HYST_EN)
    #define Quad_A_SIO_REG_HIFREQ     (* (reg8 *) Quad_A__SIO_REG_HIFREQ)
    #define Quad_A_SIO_CFG            (* (reg8 *) Quad_A__SIO_CFG)
    #define Quad_A_SIO_DIFF           (* (reg8 *) Quad_A__SIO_DIFF)
#endif /* (Quad_A__SIO_CFG) */

/* Interrupt Registers */
#if defined(Quad_A__INTSTAT)
    #define Quad_A_INTSTAT            (* (reg8 *) Quad_A__INTSTAT)
    #define Quad_A_SNAP               (* (reg8 *) Quad_A__SNAP)
    
	#define Quad_A_0_INTTYPE_REG 		(* (reg8 *) Quad_A__0__INTTYPE)
#endif /* (Quad_A__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Quad_A_H */


/* [] END OF FILE */
