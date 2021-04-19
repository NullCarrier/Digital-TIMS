
#include "analog.h"
#include "fsl_debug_console.h"
#include "types.h"

#define ADC16_CHANNEL_GROUP 0U //Group A -- SC1A

//Configure struct for adc and dac
static adc16_config_t Adc16ConfigStruct;
static adc16_channel_config_t Adc16ChannelConfigStruct;
static dac_config_t DacConfigStruct;



//Configuring for the dac first
bool Analog_Init()
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

  //Differential Sample 16-bit
  Adc16ConfigStruct.resolution = kADC16_ResolutionDF16Bit; // !!!


  //using external voltage source 
  Adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;


  //Init the adc 0
  ADC16_Init(ADC16_BASE_0, &Adc16ConfigStruct);

  //Init the adc 1
  ADC16_Init(ADC16_BASE_1, &Adc16ConfigStruct);

  /* Make sure the software trigger is used. */
  //Make sure adc is polling mode
  ADC16_EnableHardwareTrigger(ADC16_BASE_0, false); 
  ADC16_EnableHardwareTrigger(ADC16_BASE_1, false); 

  //Enabling the differential mode
  Adc16ChannelConfigStruct.enableDifferentialConversion = true;

  //Setting up channel : DADP0 DADM0 
  Adc16ChannelConfigStruct.channelNumber  = ADC16_USER_CHANNEL;

  //Disabling the interrupt
  Adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false; 


  //Starting the conversion for adc0
  ADC16_SetChannelConfig(ADC16_BASE_0, ADC16_CHANNEL_GROUP, &Adc16ChannelConfigStruct);
  //Starting the conversion for adc1
  ADC16_SetChannelConfig(ADC16_BASE_1, ADC16_CHANNEL_GROUP, &Adc16ChannelConfigStruct);
  
  /* Configure the DAC. */
  /*
   * dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2; DACREF_2 as the reference voltage -- VDDA = 3.6V
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





void Analog_Get(const uint32_t channelNb, int16_t* const valuePtr)
{
  uint32_t dataInADC = 0;
  //Conversion
  /*
    When in software trigger mode, each conversion would be launched once calling the "ADC16_ChannelConfigure()"
    function, which works like writing a conversion command and executing it. For another channel's conversion,
    just to change the "channelNumber" field in channel's configuration structure, and call the
    "ADC16_ChannelConfigure() again.
  */  
  if ( channelNb == 0)
  {
    //Read adc0 value
    dataInADC = ADC16_GetChannelConversionValue(ADC16_BASE_0, ADC16_CHANNEL_GROUP); 
    *valuePtr = (dataInADC * VREF) / (1 << 16) ; //Coversion value in mV    
  }
  else if (channelNb == 1)
  {
    //Read adc1 value
    dataInADC = ADC16_GetChannelConversionValue(ADC16_BASE_1, ADC16_CHANNEL_GROUP); 
    *valuePtr = (dataInADC * VREF) / (1 << 16) ; //Coversion value in mV    
  }


}


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



