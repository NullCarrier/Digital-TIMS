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


#define DAC_BASEADDR DAC0  //DAC Channel 0
#define ADC16_BASE    ADC0 //ADC Channel 0
//Ref for adc
#define VREF_BRD 3.300
#define SE_12BIT 4096.0




/*! @brief Sets up the ADC before first use.
 *
 *  @param moduleClock The module clock rate in Hz.
 *  @return bool - true if the UART was successfully initialized.
 */
bool Analog_Init(const uint32_t moduleClock);

/*! @brief Gets a value from an analog input channel.
 *
 *  @param channelNb is the number of the analog input channel to get a value from.
 *  @param valuePtr A pointer to a memory location to place the analog value.
 *  @return bool - true if the analog value was acquired successfully.
 */
//bool Analog_Get(const uint8_t channelNb, int16_t* const valuePtr);

/*! @brief Sends a value to an analog output channel.
 *
 *  @param channelNb is the number of the analog output channel to send the value to.
 *  @param value is the value to write to the analog channel. (12 bit only)
 *  @return bool - true if the analog value was output successfully.
 */
bool Analog_Put(DAC_Type *base, const int16_t value);

#endif
