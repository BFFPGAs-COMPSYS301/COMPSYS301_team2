/*******************************************************************************
* File Name: Vout3.h  
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

#if !defined(CY_PINS_Vout3_H) /* Pins Vout3_H */
#define CY_PINS_Vout3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vout3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vout3__PORT == 15 && ((Vout3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vout3_Write(uint8 value);
void    Vout3_SetDriveMode(uint8 mode);
uint8   Vout3_ReadDataReg(void);
uint8   Vout3_Read(void);
void    Vout3_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vout3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vout3_SetDriveMode() function.
     *  @{
     */
        #define Vout3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vout3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vout3_DM_RES_UP          PIN_DM_RES_UP
        #define Vout3_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vout3_DM_OD_LO           PIN_DM_OD_LO
        #define Vout3_DM_OD_HI           PIN_DM_OD_HI
        #define Vout3_DM_STRONG          PIN_DM_STRONG
        #define Vout3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vout3_MASK               Vout3__MASK
#define Vout3_SHIFT              Vout3__SHIFT
#define Vout3_WIDTH              1u

/* Interrupt constants */
#if defined(Vout3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vout3_SetInterruptMode() function.
     *  @{
     */
        #define Vout3_INTR_NONE      (uint16)(0x0000u)
        #define Vout3_INTR_RISING    (uint16)(0x0001u)
        #define Vout3_INTR_FALLING   (uint16)(0x0002u)
        #define Vout3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vout3_INTR_MASK      (0x01u) 
#endif /* (Vout3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vout3_PS                     (* (reg8 *) Vout3__PS)
/* Data Register */
#define Vout3_DR                     (* (reg8 *) Vout3__DR)
/* Port Number */
#define Vout3_PRT_NUM                (* (reg8 *) Vout3__PRT) 
/* Connect to Analog Globals */                                                  
#define Vout3_AG                     (* (reg8 *) Vout3__AG)                       
/* Analog MUX bux enable */
#define Vout3_AMUX                   (* (reg8 *) Vout3__AMUX) 
/* Bidirectional Enable */                                                        
#define Vout3_BIE                    (* (reg8 *) Vout3__BIE)
/* Bit-mask for Aliased Register Access */
#define Vout3_BIT_MASK               (* (reg8 *) Vout3__BIT_MASK)
/* Bypass Enable */
#define Vout3_BYP                    (* (reg8 *) Vout3__BYP)
/* Port wide control signals */                                                   
#define Vout3_CTL                    (* (reg8 *) Vout3__CTL)
/* Drive Modes */
#define Vout3_DM0                    (* (reg8 *) Vout3__DM0) 
#define Vout3_DM1                    (* (reg8 *) Vout3__DM1)
#define Vout3_DM2                    (* (reg8 *) Vout3__DM2) 
/* Input Buffer Disable Override */
#define Vout3_INP_DIS                (* (reg8 *) Vout3__INP_DIS)
/* LCD Common or Segment Drive */
#define Vout3_LCD_COM_SEG            (* (reg8 *) Vout3__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vout3_LCD_EN                 (* (reg8 *) Vout3__LCD_EN)
/* Slew Rate Control */
#define Vout3_SLW                    (* (reg8 *) Vout3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vout3_PRTDSI__CAPS_SEL       (* (reg8 *) Vout3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vout3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vout3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vout3_PRTDSI__OE_SEL0        (* (reg8 *) Vout3__PRTDSI__OE_SEL0) 
#define Vout3_PRTDSI__OE_SEL1        (* (reg8 *) Vout3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vout3_PRTDSI__OUT_SEL0       (* (reg8 *) Vout3__PRTDSI__OUT_SEL0) 
#define Vout3_PRTDSI__OUT_SEL1       (* (reg8 *) Vout3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vout3_PRTDSI__SYNC_OUT       (* (reg8 *) Vout3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vout3__SIO_CFG)
    #define Vout3_SIO_HYST_EN        (* (reg8 *) Vout3__SIO_HYST_EN)
    #define Vout3_SIO_REG_HIFREQ     (* (reg8 *) Vout3__SIO_REG_HIFREQ)
    #define Vout3_SIO_CFG            (* (reg8 *) Vout3__SIO_CFG)
    #define Vout3_SIO_DIFF           (* (reg8 *) Vout3__SIO_DIFF)
#endif /* (Vout3__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vout3__INTSTAT)
    #define Vout3_INTSTAT            (* (reg8 *) Vout3__INTSTAT)
    #define Vout3_SNAP               (* (reg8 *) Vout3__SNAP)
    
	#define Vout3_0_INTTYPE_REG 		(* (reg8 *) Vout3__0__INTTYPE)
#endif /* (Vout3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vout3_H */


/* [] END OF FILE */
