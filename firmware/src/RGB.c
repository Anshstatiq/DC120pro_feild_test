#include "RGB.h"



void GREEN_BLUE( uint16_t Compare_0_Value ,uint16_t Compare_1_Value)
{
    TC1_CompareStop();

    /* Reset TC */
    TC1_REGS->COUNT16.TC_CTRLA = TC_CTRLA_SWRST_Msk;

    while((TC1_REGS->COUNT16.TC_SYNCBUSY & TC_SYNCBUSY_SWRST_Msk) == TC_SYNCBUSY_SWRST_Msk)
    {
        /* Wait for Write Synchronization */
    }

    /* Configure counter mode & prescaler */
    TC1_REGS->COUNT16.TC_CTRLA = TC_CTRLA_MODE_COUNT16 | TC_CTRLA_PRESCALER_DIV1 | TC_CTRLA_PRESCSYNC_PRESC ;

    /* Configure waveform generation mode */
    TC1_REGS->COUNT16.TC_WAVE = (uint8_t)TC_WAVE_WAVEGEN_NPWM;


    TC1_REGS->COUNT16.TC_CC[0] = Compare_0_Value;
    TC1_REGS->COUNT16.TC_CC[1] = Compare_1_Value;

    /* Clear all interrupt flags */
    TC1_REGS->COUNT16.TC_INTFLAG = (uint8_t)TC_INTFLAG_Msk;


    while((TC1_REGS->COUNT16.TC_SYNCBUSY) != 0U)
    {
        /* Wait for Write Synchronization */
    }
    TC1_CompareStart();
}


void RED_t( uint16_t Compare_0_Value)
{
     TC0_CompareStop();
   
       /* Reset TC */
    TC0_REGS->COUNT16.TC_CTRLA = TC_CTRLA_SWRST_Msk;

    while((TC0_REGS->COUNT16.TC_SYNCBUSY & TC_SYNCBUSY_SWRST_Msk) == TC_SYNCBUSY_SWRST_Msk)
    {
        /* Wait for Write Synchronization */
    }

    /* Configure counter mode & prescaler */
    TC0_REGS->COUNT16.TC_CTRLA = TC_CTRLA_MODE_COUNT16 | TC_CTRLA_PRESCALER_DIV1 | TC_CTRLA_PRESCSYNC_PRESC ;

    /* Configure waveform generation mode */
    TC0_REGS->COUNT16.TC_WAVE = (uint8_t)TC_WAVE_WAVEGEN_NPWM;


    TC0_REGS->COUNT16.TC_CC[0] = Compare_0_Value;
    TC0_REGS->COUNT16.TC_CC[1] = 24U;

    /* Clear all interrupt flags */
    TC0_REGS->COUNT16.TC_INTFLAG = (uint8_t)TC_INTFLAG_Msk;


    while((TC0_REGS->COUNT16.TC_SYNCBUSY) != 0U)
    {
        /* Wait for Write Synchronization */
    }
     
     
     TC0_CompareStart();
}


