

#include "pit.h"
#include "fsl_debug_console.h"


 /* Structure of initialize PIT */
static pit_config_t pitConfig;

//Function ptr to callback function
static void (*FuncPtr)() = NULL; 

bool DT_PIT_Init(void)
{
  /*
     * pitConfig.enableRunInDebug = false;
     */
  PIT_GetDefaultConfig(&pitConfig);
  /* Init pit module */
  PIT_Init(D_PIT_BASEADDR, &pitConfig);

  return true;
}



void DT_PIT_Set(const uint32_t period)
{
  /* Set timer period for channel 0 */
  PIT_SetTimerPeriod(D_PIT_BASEADDR, D_PIT_CHANNEL, USEC_TO_COUNT(period, PIT_SOURCE_CLOCK));
}



void DT_PIT_Enable(const bool enable, void (*userFunc)() )
{
  //Assign the function pointer   
  FuncPtr = userFunc;

  if (enable)
  {
  /* Enable timer interrupts for channel 0 */
    PIT_EnableInterrupts(D_PIT_BASEADDR, D_PIT_CHANNEL, kPIT_TimerInterruptEnable);

  /* Enable at the NVIC */
    EnableIRQ(PIT_IRQ_ID);

  //Start the timer
    PIT_StartTimer(D_PIT_BASEADDR, D_PIT_CHANNEL);
  }

}



void PIT_LED_HANDLER(void)
{
    /* Clear interrupt flag.*/
  PIT_ClearStatusFlags(D_PIT_BASEADDR, D_PIT_CHANNEL, kPIT_TimerFlag);

  //call the callback function
  if (FuncPtr)
    FuncPtr();

    /* Added for, and affects, all PIT handlers. For CPU clock which is much larger than the IP bus clock,
     * CPU can run out of the interrupt handler before the interrupt flag being cleared, resulting in the
     * CPU's entering the handler again and again. Adding DSB can prevent the issue from happening.
     */
  __DSB();


}





