#ifndef D_PIT_H 
#define D_PIT_H



#include "types.h"
//Timer adapter for PIT timer 
#include "timer.h"

//Assuming using the channel 0
#define PIT_IRQ_ID   PIT0_IRQn
//Define the base address
#define D_PIT_BASEADDR PIT
/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

//default initialise the pit module
bool DT_PIT_Init(void);



/*! @brief Sets the value of the desired period of the PIT.
 *
 *  @param period The desired value of the timer period in microseconds.
 *  @param channelNum The channel number ranging from 0 to 3 for pit timer 
 *                 
 *  @note The function will enable the timer and interrupts for the PIT.
 */
void DT_PIT_Set(const uint32_t period, uint8_t channelNum);

/*! @brief Enables or disables the PIT.
 *
 *  @param enable - TRUE if the PIT is to be enabled, FALSE if the PIT is to be disabled.
 */
void DT_PIT_Enable(const bool enable);






#endif