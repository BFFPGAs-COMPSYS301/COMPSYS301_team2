/*******************************************************************************
* File Name: Timeout_4_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timeout_4.h"

static Timeout_4_backupStruct Timeout_4_backup;


/*******************************************************************************
* Function Name: Timeout_4_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timeout_4_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timeout_4_SaveConfig(void) 
{
    #if (!Timeout_4_UsingFixedFunction)
        Timeout_4_backup.TimerUdb = Timeout_4_ReadCounter();
        Timeout_4_backup.InterruptMaskValue = Timeout_4_STATUS_MASK;
        #if (Timeout_4_UsingHWCaptureCounter)
            Timeout_4_backup.TimerCaptureCounter = Timeout_4_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timeout_4_UDB_CONTROL_REG_REMOVED)
            Timeout_4_backup.TimerControlRegister = Timeout_4_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timeout_4_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timeout_4_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timeout_4_RestoreConfig(void) 
{   
    #if (!Timeout_4_UsingFixedFunction)

        Timeout_4_WriteCounter(Timeout_4_backup.TimerUdb);
        Timeout_4_STATUS_MASK =Timeout_4_backup.InterruptMaskValue;
        #if (Timeout_4_UsingHWCaptureCounter)
            Timeout_4_SetCaptureCount(Timeout_4_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timeout_4_UDB_CONTROL_REG_REMOVED)
            Timeout_4_WriteControlRegister(Timeout_4_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timeout_4_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timeout_4_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timeout_4_Sleep(void) 
{
    #if(!Timeout_4_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timeout_4_CTRL_ENABLE == (Timeout_4_CONTROL & Timeout_4_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timeout_4_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timeout_4_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timeout_4_Stop();
    Timeout_4_SaveConfig();
}


/*******************************************************************************
* Function Name: Timeout_4_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timeout_4_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timeout_4_Wakeup(void) 
{
    Timeout_4_RestoreConfig();
    #if(!Timeout_4_UDB_CONTROL_REG_REMOVED)
        if(Timeout_4_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timeout_4_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
