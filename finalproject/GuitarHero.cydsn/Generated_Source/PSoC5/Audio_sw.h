/*******************************************************************************
* File Name: Audio_sw.h  
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

#if !defined(CY_PINS_Audio_sw_H) /* Pins Audio_sw_H */
#define CY_PINS_Audio_sw_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Audio_sw_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Audio_sw__PORT == 15 && ((Audio_sw__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Audio_sw_Write(uint8 value);
void    Audio_sw_SetDriveMode(uint8 mode);
uint8   Audio_sw_ReadDataReg(void);
uint8   Audio_sw_Read(void);
void    Audio_sw_SetInterruptMode(uint16 position, uint16 mode);
uint8   Audio_sw_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Audio_sw_SetDriveMode() function.
     *  @{
     */
        #define Audio_sw_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Audio_sw_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Audio_sw_DM_RES_UP          PIN_DM_RES_UP
        #define Audio_sw_DM_RES_DWN         PIN_DM_RES_DWN
        #define Audio_sw_DM_OD_LO           PIN_DM_OD_LO
        #define Audio_sw_DM_OD_HI           PIN_DM_OD_HI
        #define Audio_sw_DM_STRONG          PIN_DM_STRONG
        #define Audio_sw_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Audio_sw_MASK               Audio_sw__MASK
#define Audio_sw_SHIFT              Audio_sw__SHIFT
#define Audio_sw_WIDTH              1u

/* Interrupt constants */
#if defined(Audio_sw__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Audio_sw_SetInterruptMode() function.
     *  @{
     */
        #define Audio_sw_INTR_NONE      (uint16)(0x0000u)
        #define Audio_sw_INTR_RISING    (uint16)(0x0001u)
        #define Audio_sw_INTR_FALLING   (uint16)(0x0002u)
        #define Audio_sw_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Audio_sw_INTR_MASK      (0x01u) 
#endif /* (Audio_sw__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Audio_sw_PS                     (* (reg8 *) Audio_sw__PS)
/* Data Register */
#define Audio_sw_DR                     (* (reg8 *) Audio_sw__DR)
/* Port Number */
#define Audio_sw_PRT_NUM                (* (reg8 *) Audio_sw__PRT) 
/* Connect to Analog Globals */                                                  
#define Audio_sw_AG                     (* (reg8 *) Audio_sw__AG)                       
/* Analog MUX bux enable */
#define Audio_sw_AMUX                   (* (reg8 *) Audio_sw__AMUX) 
/* Bidirectional Enable */                                                        
#define Audio_sw_BIE                    (* (reg8 *) Audio_sw__BIE)
/* Bit-mask for Aliased Register Access */
#define Audio_sw_BIT_MASK               (* (reg8 *) Audio_sw__BIT_MASK)
/* Bypass Enable */
#define Audio_sw_BYP                    (* (reg8 *) Audio_sw__BYP)
/* Port wide control signals */                                                   
#define Audio_sw_CTL                    (* (reg8 *) Audio_sw__CTL)
/* Drive Modes */
#define Audio_sw_DM0                    (* (reg8 *) Audio_sw__DM0) 
#define Audio_sw_DM1                    (* (reg8 *) Audio_sw__DM1)
#define Audio_sw_DM2                    (* (reg8 *) Audio_sw__DM2) 
/* Input Buffer Disable Override */
#define Audio_sw_INP_DIS                (* (reg8 *) Audio_sw__INP_DIS)
/* LCD Common or Segment Drive */
#define Audio_sw_LCD_COM_SEG            (* (reg8 *) Audio_sw__LCD_COM_SEG)
/* Enable Segment LCD */
#define Audio_sw_LCD_EN                 (* (reg8 *) Audio_sw__LCD_EN)
/* Slew Rate Control */
#define Audio_sw_SLW                    (* (reg8 *) Audio_sw__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Audio_sw_PRTDSI__CAPS_SEL       (* (reg8 *) Audio_sw__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Audio_sw_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Audio_sw__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Audio_sw_PRTDSI__OE_SEL0        (* (reg8 *) Audio_sw__PRTDSI__OE_SEL0) 
#define Audio_sw_PRTDSI__OE_SEL1        (* (reg8 *) Audio_sw__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Audio_sw_PRTDSI__OUT_SEL0       (* (reg8 *) Audio_sw__PRTDSI__OUT_SEL0) 
#define Audio_sw_PRTDSI__OUT_SEL1       (* (reg8 *) Audio_sw__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Audio_sw_PRTDSI__SYNC_OUT       (* (reg8 *) Audio_sw__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Audio_sw__SIO_CFG)
    #define Audio_sw_SIO_HYST_EN        (* (reg8 *) Audio_sw__SIO_HYST_EN)
    #define Audio_sw_SIO_REG_HIFREQ     (* (reg8 *) Audio_sw__SIO_REG_HIFREQ)
    #define Audio_sw_SIO_CFG            (* (reg8 *) Audio_sw__SIO_CFG)
    #define Audio_sw_SIO_DIFF           (* (reg8 *) Audio_sw__SIO_DIFF)
#endif /* (Audio_sw__SIO_CFG) */

/* Interrupt Registers */
#if defined(Audio_sw__INTSTAT)
    #define Audio_sw_INTSTAT            (* (reg8 *) Audio_sw__INTSTAT)
    #define Audio_sw_SNAP               (* (reg8 *) Audio_sw__SNAP)
    
	#define Audio_sw_0_INTTYPE_REG 		(* (reg8 *) Audio_sw__0__INTTYPE)
#endif /* (Audio_sw__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Audio_sw_H */


/* [] END OF FILE */
