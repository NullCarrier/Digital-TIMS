#ifndef D_PIT_H 
#define D_PIT_H



#include "types.h"
#include "fsl_pit.h"

//Configuring macro
//Assuming using the channel 0
#define PIT_IRQ_ID   PIT0_IRQn
//Define the base address
#define D_PIT_BASEADDR PIT
/* Get source clock for PIT timer*/
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
//Channel number for PIT timer
#define D_PIT_CHANNEL  kPIT_Chnl_0
//hanlder for pit channel 0 
#define PIT_ISR_HANDLER   PIT0_IRQHandler 


//default initialise the pit module
bool DT_PIT_Init(void);


/*! @brief Sets the value of the desired period of the PIT.
 *
 *  @param period The desired value of the timer period in microseconds.
 *                 
 *  @note The function will enable the timer and interrupts for the PIT.
 */
void DT_PIT_Set(const uint32_t period );


/*! @brief Enables or disables the PIT and start it.
 *
 *  @param enable - TRUE if the PIT is to be enabled, FALSE if the PIT is to be disabled.
 */
void DT_PIT_Enable(const bool enable, void (*userFunc)() );






#endif