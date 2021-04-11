
#include "analog.h"
#include "fsl_debug_console.h"
#include "types.h"

//#define DEMO_ADC16_USER_CHANNEL  12U

//Configure struct for adc and dac
static adc16_config_t Adc16ConfigStruct;
static adc16_channel_config_t Adc16ChannelConfigStruct;
static dac_config_t DacConfigStruct;



//Configuring for the dac first
bool Analog_Init(const uint32_t moduleClock)
{
  /* Configure the ADC. */
  /*
     * adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
     * adc16ConfigStruct.clockSource = kADC16_ClockSourceAsynchronousClock;
     * adc16ConfigStruct.enableAsynchronousClock = true;
     * adc16ConfigStruct.clockDivider = kADC16_ClockDivider8;
     * adc16ConfigStruct.resolution = kADC16_ResolutionSE12Bit;
     * adc16ConfigStruct.longSampleMode = kADC16_LongSampleDisabled;
     * adc16ConfigStruct.enableHighSpeed = false;
     * adc16ConfigStruct.enableLowPower = false;
     * adc16ConfigStruct.enableContinuousConversion = false;
     */
  ADC16_GetDefaultConfig(&Adc16ConfigStruct);
  //Init the adc
  ADC16_Init(ADC16_BASE, &Adc16ConfigStruct);

  /* Make sure the software trigger is used. */
  //Make sure adc is polling mode
  ADC16_EnableHardwareTrigger(ADC16_BASE, false); 
  //Disabling the interrupt
  Adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false; 


  
  /* Configure the DAC. */
  /*
   * dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2; DACREF_2 as the reference voltage -- VDDA = 3.3V
   * dacConfigStruct.enableLowPowerMode = false;
  */
  DAC_GetDefaultConfig(&DacConfigStruct);
  //Initialise the dac module for channel 0
  DAC_Init(DAC_BASEADDR, &DacConfigStruct);
  //Enable the output
  DAC_Enable(DAC_BASEADDR, true);

  /* Make sure the read pointer to the start. */
    /*
     * The buffer is not enabled, so the read pointer can not move automatically. However, the buffer's read pointer
     * and itemss can be written manually by user.
     */
 
  DAC_SetBufferReadPointer(DAC_BASEADDR, 0U); //U is unsigned


  return true;
}


#if 0
bool Analog_Get(const uint8_t channelNb, int16_t* const valuePtr)
{
  Adc16ChannelConfigStruct.channelNumber = channelNb;

  //Conversion


  return true;
}
#endif

//DAC_BASEADDR for base address
//Note that dac only supports 12 bit only
bool Analog_Put(DAC_Type *base, const int16_t value)
{

  //Write to the DAT0 to output data without using buffer
  //using first item only
  base->DAT[0].DATL = (uint8_t)(0xFFU & value);         /* Low 8-bit. */
  base->DAT[0].DATH = (uint8_t)((0xF00U & value) >> 8); /* High 4-bit. */

  return true;
}



