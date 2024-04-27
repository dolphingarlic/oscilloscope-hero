/*******************************************************************************
* File Name: update_isr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_update_isr_H)
#define CY_ISR_update_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void update_isr_Start(void);
void update_isr_StartEx(cyisraddress address);
void update_isr_Stop(void);

CY_ISR_PROTO(update_isr_Interrupt);

void update_isr_SetVector(cyisraddress address);
cyisraddress update_isr_GetVector(void);

void update_isr_SetPriority(uint8 priority);
uint8 update_isr_GetPriority(void);

void update_isr_Enable(void);
uint8 update_isr_GetState(void);
void update_isr_Disable(void);

void update_isr_SetPending(void);
void update_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the update_isr ISR. */
#define update_isr_INTC_VECTOR            ((reg32 *) update_isr__INTC_VECT)

/* Address of the update_isr ISR priority. */
#define update_isr_INTC_PRIOR             ((reg8 *) update_isr__INTC_PRIOR_REG)

/* Priority of the update_isr interrupt. */
#define update_isr_INTC_PRIOR_NUMBER      update_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable update_isr interrupt. */
#define update_isr_INTC_SET_EN            ((reg32 *) update_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the update_isr interrupt. */
#define update_isr_INTC_CLR_EN            ((reg32 *) update_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the update_isr interrupt state to pending. */
#define update_isr_INTC_SET_PD            ((reg32 *) update_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the update_isr interrupt. */
#define update_isr_INTC_CLR_PD            ((reg32 *) update_isr__INTC_CLR_PD_REG)


#endif /* CY_ISR_update_isr_H */


/* [] END OF FILE */
