#ifndef ANALOG_H
#define ANALOG_H

//Basic hardware setup
#include "peripherals.h"
#include "clock_config.h"
#include "pin_mux.h"

//Driver files for adc and dac
#include "fsl_adc16.h"
#include "fsl_dac.h"


// new types
#include "types.h"

//Paramers for configuration

#define DAC_BASEADDR DAC0  //DAC Channel 0
#define ADC16_BASE_0    ADC0 //ADC Channel 0
#define ADC16_BASE_1    ADC1 //ADC Channel 1

//Ref for adc
#define VREF_BRD 3.600 //3.6v
#define SE_12BIT 4096.0
#define VREF 20000 //+- 10v = 10 000mv



//Enable the differential mode
#define FSL_FEATURE_ADC16_HAS_DIFF_MODE 1


#define FSL_FEATURE_ADC16_MAX_RESOLUTION 16U



//Set the channel number
#define ADC16_USER_CHANNEL 0U /* ADC0_DM0 / DP0 */





/*! @brief Sets up two ADC0 and ADC1 and DAC0 before first use.
 *
 *  @return bool - true if the ADC was successfully initialized.
 */
bool Analog_Init();

/*! @brief Gets a sample value from an analog input channel.
 *
 *  @param channelNb is the number of the analog input channel to receive the value .
 *  @param valuePtr A pointer to a memory location to place the analog value in mV.
 *  @return bool - true if the analog value was acquired successfully.
 */
void Analog_Get(const uint32_t channelNb, int16_t* const valuePtr);

/*! @brief Sends a value to an analog output channel.
 *
 *  @param value is the value to write to the analog channel. (12 bit only)
 *  @return bool - true if the analog value was output successfully.
 */
bool Analog_Put(DAC_Type *base, const int16_t value);

#endif
