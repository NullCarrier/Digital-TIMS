

#include "pit.h"
#include "fsl_debug_console.h"


//Necesary structure for configuring timer
static hal_timer_config_t halTimerConfig;
//Define the timer handler
TIMER_HANDLE_DEFINE(halTimerHandle);

static hal_timer_status_t statusFlag;



bool DT_PIT_Init() 
{
  //Configuration of timer 
  //Set up 1s period
  halTimerConfig.timeout = 1000000; //The unit is microsecond
  
  halTimerConfig.srcClock_Hz = PIT_SOURCE_CLOCK; 
  //Dont need instance
  halTimerConfig.instance = 0;
  
  statusFlag = HAL_TimerInit((hal_timer_handle_t)halTimerHandle, &halTimerConfig);

  switch (statusFlag)
  {
    case kStatus_HAL_TimerNotSupport : 
      PRINTF("\r\nThe timer is supported...");
      break;
    case kStatus_HAL_TimerIsUsed : 
      PRINTF("\r\nThe timer is used...");
      break;
    case kStatus_HAL_TimerInvalid : 
      PRINTF("\r\nThe timer is invalid...");
      break;
    case kStatus_HAL_TimerOutOfRanger : 
      PRINTF("\r\nThe timer is out of range...");
      break;
    default :
      PRINTF("\r\nThe timer is initialised successfully...");
      break;
  }


  return true;
}


void DT_PIT_Set(const uint32_t period, uint8_t channelNum)
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



void DT_PIT_Enable(const bool enable)
{
  if (enable)
    PIT_StartTimer(D_PIT_BASEADDR, PitChannel);

}   



