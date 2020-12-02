

#include "pit.h"


static pit_chnl_t PitChannel;  


bool D_PIT_Init() 
{

  /*
     * pitConfig.enableRunInDebug = false;
     */
  PIT_GetDefaultConfig(&pitConfig);

  /* Init pit module */
  PIT_Init(D_PIT_BASEADDR, &pitConfig);

  return true;
}


void PIT_Set(const uint32_t period, uint8_t channelNum)
{
  switch (channelNum)
  {
  case 0: 
    PitChannel = kPIT_Chnl_0; 
    break;
  case 1: 
    PitChannel = kPIT_Chnl_1; 
    break;
  case 2: 
    PitChannel = kPIT_Chnl_2; 
    break;
  case 3: 
    PitChannel = kPIT_Chnl_3; 
    break;
  default: //Error case message
    return;
  }


  /* Set timer period for channel 0*/
                                                 /*! Macro to convert a microsecond(us) period to raw count value    e.g. 1000000U */
  PIT_SetTimerPeriod(D_PIT_BASEADDR, PitChannel, USEC_TO_COUNT(period, PIT_SOURCE_CLOCK));
  /* Enable timer interrupts for channel 0 */
  PIT_EnableInterrupts(D_PIT_BASEADDR, PitChannel, kPIT_TimerInterruptEnable);
  /* Enable at the NVIC */
  EnableIRQ(PIT_IRQ_ID);

}



void PIT_Enable(const bool enable)
{
  if (enable)
    PIT_StartTimer(D_PIT_BASEADDR, PitChannel);

}   



