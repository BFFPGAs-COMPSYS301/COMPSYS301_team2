/*******************************************************************************
* File Name: Timeout_5_PM.c
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

#include "Timeout_5.h"

static Timeout_5_backupStruct Timeout_5_backup;


/*******************************************************************************
* Function Name: Timeout_5_SaveConfig
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
*  Timeout_5_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timeout_5_SaveConfig(void) 
{
    #if (!Timeout_5_UsingFixedFunction)
        Timeout_5_backup.TimerUdb = Timeout_5_ReadCounter();
        Timeout_5_backup.InterruptMaskValue = Timeout_5_STATUS_MASK;
        #if (Timeout_5_UsingHWCaptureCounter)
            Timeout_5_backup.TimerCaptureCounter = Timeout_5_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timeout_5_UDB_CONTROL_REG_REMOVED)
            Timeout_5_backup.TimerControlRegister = Timeout_5_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timeout_5_RestoreConfig
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
*  Timeout_5_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timeout_5_RestoreConfig(void) 
{   
    #if (!Timeout_5_UsingFixedFunction)

        Timeout_5_WriteCounter(Timeout_5_backup.TimerUdb);
        Timeout_5_STATUS_MASK =Timeout_5_backup.InterruptMaskValue;
        #if (Timeout_5_UsingHWCaptureCounter)
            Timeout_5_SetCaptureCount(Timeout_5_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timeout_5_UDB_CONTROL_REG_REMOVED)
            Timeout_5_WriteControlRegister(Timeout_5_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timeout_5_Sleep
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
*  Timeout_5_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timeout_5_Sleep(void) 
{
    #if(!Timeout_5_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timeout_5_CTRL_ENABLE == (Timeout_5_CONTROL & Timeout_5_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timeout_5_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timeout_5_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timeout_5_Stop();
    Timeout_5_SaveConfig();
}


/*******************************************************************************
* Function Name: Timeout_5_Wakeup
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
*  Timeout_5_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timeout_5_Wakeup(void) 
{
    Timeout_5_RestoreConfig();
    #if(!Timeout_5_UDB_CONTROL_REG_REMOVED)
        if(Timeout_5_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timeout_5_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
