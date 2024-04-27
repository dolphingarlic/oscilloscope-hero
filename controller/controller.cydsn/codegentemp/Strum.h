/*******************************************************************************
* File Name: Strum.h  
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

#if !defined(CY_PINS_Strum_H) /* Pins Strum_H */
#define CY_PINS_Strum_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Strum_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Strum__PORT == 15 && ((Strum__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Strum_Write(uint8 value);
void    Strum_SetDriveMode(uint8 mode);
uint8   Strum_ReadDataReg(void);
uint8   Strum_Read(void);
void    Strum_SetInterruptMode(uint16 position, uint16 mode);
uint8   Strum_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Strum_SetDriveMode() function.
     *  @{
     */
        #define Strum_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Strum_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Strum_DM_RES_UP          PIN_DM_RES_UP
        #define Strum_DM_RES_DWN         PIN_DM_RES_DWN
        #define Strum_DM_OD_LO           PIN_DM_OD_LO
        #define Strum_DM_OD_HI           PIN_DM_OD_HI
        #define Strum_DM_STRONG          PIN_DM_STRONG
        #define Strum_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Strum_MASK               Strum__MASK
#define Strum_SHIFT              Strum__SHIFT
#define Strum_WIDTH              1u

/* Interrupt constants */
#if defined(Strum__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Strum_SetInterruptMode() function.
     *  @{
     */
        #define Strum_INTR_NONE      (uint16)(0x0000u)
        #define Strum_INTR_RISING    (uint16)(0x0001u)
        #define Strum_INTR_FALLING   (uint16)(0x0002u)
        #define Strum_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Strum_INTR_MASK      (0x01u) 
#endif /* (Strum__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Strum_PS                     (* (reg8 *) Strum__PS)
/* Data Register */
#define Strum_DR                     (* (reg8 *) Strum__DR)
/* Port Number */
#define Strum_PRT_NUM                (* (reg8 *) Strum__PRT) 
/* Connect to Analog Globals */                                                  
#define Strum_AG                     (* (reg8 *) Strum__AG)                       
/* Analog MUX bux enable */
#define Strum_AMUX                   (* (reg8 *) Strum__AMUX) 
/* Bidirectional Enable */                                                        
#define Strum_BIE                    (* (reg8 *) Strum__BIE)
/* Bit-mask for Aliased Register Access */
#define Strum_BIT_MASK               (* (reg8 *) Strum__BIT_MASK)
/* Bypass Enable */
#define Strum_BYP                    (* (reg8 *) Strum__BYP)
/* Port wide control signals */                                                   
#define Strum_CTL                    (* (reg8 *) Strum__CTL)
/* Drive Modes */
#define Strum_DM0                    (* (reg8 *) Strum__DM0) 
#define Strum_DM1                    (* (reg8 *) Strum__DM1)
#define Strum_DM2                    (* (reg8 *) Strum__DM2) 
/* Input Buffer Disable Override */
#define Strum_INP_DIS                (* (reg8 *) Strum__INP_DIS)
/* LCD Common or Segment Drive */
#define Strum_LCD_COM_SEG            (* (reg8 *) Strum__LCD_COM_SEG)
/* Enable Segment LCD */
#define Strum_LCD_EN                 (* (reg8 *) Strum__LCD_EN)
/* Slew Rate Control */
#define Strum_SLW                    (* (reg8 *) Strum__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Strum_PRTDSI__CAPS_SEL       (* (reg8 *) Strum__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Strum_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Strum__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Strum_PRTDSI__OE_SEL0        (* (reg8 *) Strum__PRTDSI__OE_SEL0) 
#define Strum_PRTDSI__OE_SEL1        (* (reg8 *) Strum__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Strum_PRTDSI__OUT_SEL0       (* (reg8 *) Strum__PRTDSI__OUT_SEL0) 
#define Strum_PRTDSI__OUT_SEL1       (* (reg8 *) Strum__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Strum_PRTDSI__SYNC_OUT       (* (reg8 *) Strum__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Strum__SIO_CFG)
    #define Strum_SIO_HYST_EN        (* (reg8 *) Strum__SIO_HYST_EN)
    #define Strum_SIO_REG_HIFREQ     (* (reg8 *) Strum__SIO_REG_HIFREQ)
    #define Strum_SIO_CFG            (* (reg8 *) Strum__SIO_CFG)
    #define Strum_SIO_DIFF           (* (reg8 *) Strum__SIO_DIFF)
#endif /* (Strum__SIO_CFG) */

/* Interrupt Registers */
#if defined(Strum__INTSTAT)
    #define Strum_INTSTAT            (* (reg8 *) Strum__INTSTAT)
    #define Strum_SNAP               (* (reg8 *) Strum__SNAP)
    
	#define Strum_0_INTTYPE_REG 		(* (reg8 *) Strum__0__INTTYPE)
#endif /* (Strum__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Strum_H */


/* [] END OF FILE */
