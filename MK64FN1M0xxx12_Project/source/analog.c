
#include "analog.h"
#include "fsl_debug_console.h"
#include "types.h"


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
  ADC16_Init(ADC16_BASE, &Adc16ConfigStruct);
  /* Make sure the software trigger is used. */
  //Make sure adc is polling mode
  ADC16_EnableHardwareTrigger(ADC16_BASE, false); 
  //Disabling the interrupt
  Adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false; 


  
  /* Configure the DAC. */
  /*
   * dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2;
   * dacConfigStruct.enableLowPowerMode = false;
  */
  DAC_GetDefaultConfig(&DacConfigStruct);
  //Initialise the dac module for channel 0
  DAC_Init(DAC_BASEADDR, &DacConfigStruct);
  //Enable the output
  DAC_Enable(DAC_BASEADDR, true);


  return true;
}

//#define DEMO_ADC16_USER_CHANNEL  12U


bool Analog_Get(const uint8_t channelNb, int16_t* const valuePtr)
{
  Adc16ChannelConfigStruct.channelNumber = channelNb;

  //Conversion


  return true;
}




bool Analog_Put(const uint8_t channelNb, const int16_t value)
{

  //Init the union type data
  int16union_t dacValue;
  dacValue.l = value;

  //Write to the DAT0 to output data without using buffer
  //DAC_DATL_DATA0(dacValue.s.Lo);  
  //DAC_DATH_DATA0(dacValue.s.Hi); //!!!!! 

  DAC_SetBufferReadPointer(DAC_BASEADDR, 0U) //U is unsigned
  /* Make sure the read pointer to the start. */
    /*
     * The buffer is not enabled, so the read pointer can not move automatically. However, the buffer's read pointer
     * and itemss can be written manually by user.
     */
  DAC_SetBufferValue(DAC_BASEADDR, 0U, dacValue.l);
  

  return true;
}



