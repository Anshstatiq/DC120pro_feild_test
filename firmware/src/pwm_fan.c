#include "pwm_fan.h"





void FAN_ON( uint16_t Compare_0_Value)
{
     TC7_CompareStop();
   
       /* Reset TC */
    TC7_REGS->COUNT16.TC_CTRLA = TC_CTRLA_SWRST_Msk;

    while((TC7_REGS->COUNT16.TC_SYNCBUSY & TC_SYNCBUSY_SWRST_Msk) == TC_SYNCBUSY_SWRST_Msk)
    {
        /* Wait for Write Synchronization */
    }

    /* Configure counter mode & prescaler */
    TC7_REGS->COUNT16.TC_CTRLA = TC_CTRLA_MODE_COUNT16 | TC_CTRLA_PRESCALER_DIV1 | TC_CTRLA_PRESCSYNC_PRESC ;

    /* Configure waveform generation mode */
    TC7_REGS->COUNT16.TC_WAVE = (uint8_t)TC_WAVE_WAVEGEN_NPWM;


    TC7_REGS->COUNT16.TC_CC[0] = Compare_0_Value;
    TC7_REGS->COUNT16.TC_CC[1] = 0;

    /* Clear all interrupt flags */
    TC7_REGS->COUNT16.TC_INTFLAG = (uint8_t)TC_INTFLAG_Msk;


    while((TC7_REGS->COUNT16.TC_SYNCBUSY) != 0U)
    {
        /* Wait for Write Synchronization */
    }
     
     
     TC7_CompareStart();
}
