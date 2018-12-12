/*
 * Copyright (c) by RTX A/S, Denmark
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of RTX A/S nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */


/****************************************************************************
* Include
****************************************************************************/
#include <Core/RtxCore.h>
#include <Ros/RosCfg.h> 
#include <portdef.h>
#include <ProjCfg.h>
#include <Ulp/ulpcfg.h>


/****************************************************************************
* Macro Definitions
****************************************************************************/

/****************************************************************************
* Types
****************************************************************************/

typedef void (*ApiPpUlpHalKeybIntFcnType)(void); 

typedef enum
{
 API_PP_ULP_HAL_GPIO_INP,           
 API_PP_ULP_HAL_GPIO_INP_PULLUP,    
 API_PP_ULP_HAL_GPIO_INP_PULLDOWN,  
 API_PP_ULP_HAL_GPIO_OUT,           

} ApiPpUlpHalGpioDir_t;

typedef enum
{
  API_PP_ULP_HAL_CP_LEVEL_2V5,
  API_PP_ULP_HAL_CP_LEVEL_3V0,
  API_PP_ULP_HAL_CP_LEVEL_4V0,
  API_PP_ULP_HAL_CP_LEVEL_4V5,

} ApiPpUlpHalCpLevel_t;


/****************************************************************************
*                            Global variables/const
****************************************************************************/

/****************************************************************************
*                                Implementation
****************************************************************************/

/*************************************************************************
* FUNCTION: ApiPpUlpHalGetDirP32
* INPUTS  : None           
* OUTPUTS : P32 dir
*
* DESCRIPTION: Get P3 bit 2 dir:    Input, no resistors selected
*                                   Input, pull-up selected
*                                   Input, Pull-down selected
*                                   Output, no resistors selected
*
**************************************************************************/
extern ApiPpUlpHalGpioDir_t ApiPpUlpHalGetDirP32(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalGetDirP33
* INPUTS  : None           
* OUTPUTS : P33 dir
*
* DESCRIPTION: Get P3 bit 3 dir:    Input, no resistors selected
*                                   Input, pull-up selected
*                                   Input, Pull-down selected
*                                   Output, no resistors selected
*
**************************************************************************/
extern ApiPpUlpHalGpioDir_t ApiPpUlpHalGetDirP33(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalGetDirP34
* INPUTS  : None           
* OUTPUTS : P34 dir
*
* DESCRIPTION: Get P3 bit 4 dir:    Input, no resistors selected
*                                   Input, pull-up selected
*                                   Input, Pull-down selected
*                                   Output, no resistors selected
*
**************************************************************************/
extern ApiPpUlpHalGpioDir_t ApiPpUlpHalGetDirP34(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalGetDirP35
* INPUTS  : None           
* OUTPUTS : P35 Dir
*
* DESCRIPTION: Get P3 bit 5 dir:    Input, no resistors selected
*                                   Input, pull-up selected
*                                   Input, Pull-down selected
*                                   Output, no resistors selected
*
**************************************************************************/
extern ApiPpUlpHalGpioDir_t ApiPpUlpHalGetDirP35(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalGetDirP36
* INPUTS  : None
* OUTPUTS : P36 dir
*
* DESCRIPTION: Get P3 bit 6 dir:    Input, no resistors selected
*                                   Input, pull-up selected
*                                   Input, Pull-down selected
*                                   Output, no resistors selected
*
**************************************************************************/
extern ApiPpUlpHalGpioDir_t ApiPpUlpHalGetDirP36(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalGetDirP37
* INPUTS  : None           
* OUTPUTS : P37 mode
*
* DESCRIPTION: get P3 bit 7 dir:    Input, no resistors selected
*                                   Input, pull-up selected
*                                   Input, Pull-down selected
*                                   Output, no resistors selected
*
**************************************************************************/
extern ApiPpUlpHalGpioDir_t ApiPpUlpHalGetDirP37(void);


/*************************************************************************
* FUNCTION: ApiPpUlpHalSetDirP32
* INPUTS  : P32 dir
* OUTPUTS : None
*
* DESCRIPTION: Set P3 bit 2 dir :   Input, no resistors selected
*                                   Input, pull-up selected
*                                   Input, Pull-down selected
*                                   Output, no resistors selected
*
**************************************************************************/
extern void ApiPpUlpHalSetDirP32(ApiPpUlpHalGpioDir_t mode);

/*************************************************************************
* FUNCTION: ApiPpUlpHalSetDirP33
* INPUTS  : P33 dir
* OUTPUTS : None
*
* DESCRIPTION: Set P3 bit 3 dir :   Input, no resistors selected
*                                   Input, pull-up selected
*                                   Input, Pull-down selected
*                                   Output, no resistors selected
*
**************************************************************************/
extern void ApiPpUlpHalSetDirP33(ApiPpUlpHalGpioDir_t mode);


/*************************************************************************
* FUNCTION: ApiPpUlpHalSetDirP34
* INPUTS  : P34 dir
* OUTPUTS : None
*
* DESCRIPTION: Set P3 bit 4 dir:    Input, no resistors selected
*                                   Input, pull-up selected
*                                   Input, Pull-down selected
*                                   Output, no resistors selected
*
**************************************************************************/
extern void ApiPpUlpHalSetDirP34(ApiPpUlpHalGpioDir_t mode);

/*************************************************************************
* FUNCTION: ApiPpUlpHalSetDirP35
* INPUTS  : P35 dir                      
* OUTPUTS : None
*
* DESCRIPTION: Set P3 bit 5 dir:    Input, no resistors selected
*                                   Input, pull-up selected
*                                   Input, Pull-down selected
*                                   Output, no resistors selected
*
**************************************************************************/
extern void ApiPpUlpHalSetDirP35(ApiPpUlpHalGpioDir_t mode);

/*************************************************************************
* FUNCTION: ApiPpUlpHalSetDirP36
* INPUTS  : P36 dir           
* OUTPUTS : None
*
* DESCRIPTION: Set P3 bit 6 dir:    Input, no resistors selected
*                                   Input, pull-up selected
*                                   Input, Pull-down selected
*                                   Output, no resistors selected
*  
**************************************************************************/
extern void ApiPpUlpHalSetDirP36(ApiPpUlpHalGpioDir_t mode);

/*************************************************************************
* FUNCTION: ApiPpUlpHalSetDirP37
* INPUTS  : P37 dir
* OUTPUTS : None
*
* DESCRIPTION: Set P3 bit 7 dir:    Input, no resistors selected
*                                   Input, pull-up selected
*                                   Input, Pull-down selected
*                                   Output, no resistors selected
*
**************************************************************************/
extern void ApiPpUlpHalSetDirP37(ApiPpUlpHalGpioDir_t mode);

/*************************************************************************
* FUNCTION: ApiPpUlpHalGetP32
* INPUTS  : None           
* OUTPUTS : P32 bit value
*
* DESCRIPTION: Get P3 bit2 value
*  
**************************************************************************/
extern rsuint16 ApiPpUlpHalGetP32(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalGetP33
* INPUTS  : None           
* OUTPUTS : P33 bit value
*
* DESCRIPTION: Get P3 bit3 value
*  
**************************************************************************/
extern rsuint16 ApiPpUlpHalGetP33(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalGetP34
* INPUTS  : None           
* OUTPUTS : P34 bit value
*
* DESCRIPTION: Get P3 bit4 value
*  
**************************************************************************/
extern rsuint16 ApiPpUlpHalGetP34(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalGetP35
* INPUTS  : None
* OUTPUTS : P35 bit value
*
* DESCRIPTION: Get P3 bit5 value
*  
*
**************************************************************************/
extern rsuint16 ApiPpUlpHalGetP35(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalGetP36
* INPUTS  : None           
* OUTPUTS : P36 bit value
*
* DESCRIPTION: Get P3 bit6 value
*  
**************************************************************************/
extern rsuint16 ApiPpUlpHalGetP36(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalGetP37
* INPUTS  : None           
* OUTPUTS : P37 bit value
*
* DESCRIPTION: Get P3 bit7 value
*  
**************************************************************************/
extern rsuint16 ApiPpUlpHalGetP37(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalSetP30
* INPUTS  : None
* OUTPUTS : None
*
* DESCRIPTION: Set P3 bit0
*  
**************************************************************************/
extern void ApiPpUlpHalSetP30(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalSetP31
* INPUTS  : None
* OUTPUTS : None
*
* DESCRIPTION: Set P3 bit1
*  
**************************************************************************/
extern void ApiPpUlpHalSetP31(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalSetP32
* INPUTS  : None
* OUTPUTS : None
*
* DESCRIPTION: Set P3 bit2
*  
**************************************************************************/
extern void ApiPpUlpHalSetP32(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalSetP33
* INPUTS  : None
* OUTPUTS : None
*
* DESCRIPTION: Set P3 bit3
*  
**************************************************************************/
extern void ApiPpUlpHalSetP33(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalSetP34
* INPUTS  : None
* OUTPUTS : None
*
* DESCRIPTION: Set P3 bit4
*  
**************************************************************************/
extern void ApiPpUlpHalSetP34(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalSetP35
* INPUTS  : None
* OUTPUTS : None
*
* DESCRIPTION: Set P3 bit5
*  
**************************************************************************/
extern void ApiPpUlpHalSetP35(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalSetP36
* INPUTS  : None
* OUTPUTS : None
*
* DESCRIPTION: Set P3 bit6
*  
**************************************************************************/
extern void ApiPpUlpHalSetP36(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalSetP37
* INPUTS  : None
* OUTPUTS : None
*
* DESCRIPTION: Set P3 bit7 
*  
**************************************************************************/
extern void ApiPpUlpHalSetP37(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalResetP30
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Reset P3 bit0 
*  
**************************************************************************/
extern void ApiPpUlpHalResetP30(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalResetP31
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Reset P3 bit1 
*  
**************************************************************************/
extern void ApiPpUlpHalResetP31(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalResetP32
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Reset P3 bit2 
*  
**************************************************************************/
extern void ApiPpUlpHalResetP32(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalResetP33
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Reset P3 bit3 
*  
**************************************************************************/
extern void ApiPpUlpHalResetP33(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalResetP34
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Reset P3 bit4 
*  
**************************************************************************/
extern void ApiPpUlpHalResetP34(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalResetP35
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION: Reset P3 bit5 
*  
**************************************************************************/
extern void ApiPpUlpHalResetP35(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalResetP36
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION: Reset P3 bit6 
*  
**************************************************************************/
extern void ApiPpUlpHalResetP36(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalResetP37
* INPUTS  : None
* OUTPUTS : None
*
* DESCRIPTION: Reset P3 bit7 
*  
**************************************************************************/
extern void ApiPpUlpHalResetP37(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalCpVout1Level
* INPUTS  : Voltage level selector 
* OUTPUTS : None
*
* DESCRIPTION:  Set CP VOUT1 level (2.5 V, 3.0 V, 4.0 V or 4.5 V) 
*
*      ( After start-up, it may take up-to 500 us before the charge
*        pump has reached its programmed output voltage)
*
**************************************************************************/
extern void ApiPpUlpHalCpVout1Level(ApiPpUlpHalCpLevel_t level);

/*************************************************************************
* FUNCTION: ApiPpUlpHalCpVout2Level
* INPUTS  : Voltage level selector           
* OUTPUTS : None
*
* DESCRIPTION: Set CP VOUT2 level (2.5 V, 3.0 V, 4.0 V or 4.5 V) 
*
*      ( After start-up, it may take up-to 500 us before the charge
*        pump has reached its programmed output voltage)
*
**************************************************************************/
extern void ApiPpUlpHalCpVout2Level(ApiPpUlpHalCpLevel_t level);

/*************************************************************************
* FUNCTION: ApiPpUlpHalCpVout1On
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Star Charge pump on Vout1
*      
**************************************************************************/
extern void ApiPpUlpHalCpVout1On(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalCpVout2On
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION: Star Charge pump on Vout2
*      
**************************************************************************/
extern void ApiPpUlpHalCpVout2On(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalCpVout1Off
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION: Stop Charge pump on Vout1
*      
**************************************************************************/
extern void ApiPpUlpHalCpVout1Off(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalCpVout1Off
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION: Stop Charge pump on Vout1
*      
**************************************************************************/
extern void ApiPpUlpHalCpVout2Off(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalLed34MaxCurrentMode
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Set LED3 and LED4 (D7,D6) to change between 5 mA and 
*      10 mA depending on LED3_CUR and LED4_CUR values
*
**************************************************************************/
extern void ApiPpUlpHalLed34MaxCurrentMode(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalLed34MinCurrentMode
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Set LED3 and LED4 (D7,D6) to change between 2.5 mA and 
*      5 mA depending on LED3_CUR and LED4_CUR values

**************************************************************************/
extern void ApiPpUlpHalLed34MinCurrentMode(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalLed3HighCurrentMode
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Set LED3 to high current mode, 5 mA or 10 mA depending
*      on the LED34_C_MODE value
*
**************************************************************************/
extern void ApiPpUlpHalLed3HighCurrentMode(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalLed4HighCurrentMode
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Set LED4 to high current mode, 5 mA or 10 mA depending
*      on the LED34_C_MODE value
*
**************************************************************************/
extern void ApiPpUlpHalLed4HighCurrentMode(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalLed3LowCurrentMode
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Set LED3 to Low current mode, 2.5 mA or 5 mA depending
*      on the LED34_C_MODE value
*
**************************************************************************/
extern void ApiPpUlpHalLed3LowCurrentMode(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalLed4LowCurrentMode
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Set LED4 to Low current mode, 2.5 mA or 5 mA depending
*      on the LED34_C_MODE value
*
**************************************************************************/
extern void ApiPpUlpHalLed4LowCurrentMode(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalLed3On  (D7)
* INPUTS  : None            
* OUTPUTS : None
*
* DESCRIPTION:  Set LED3 on 
*      
**************************************************************************/
extern void ApiPpUlpHalLed3On(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalLed4On (D6)
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Set LED4 on
*      
**************************************************************************/
extern void ApiPpUlpHalLed4On(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalLed3Off (D7)
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION: Set LED3 off 
*      
**************************************************************************/
extern void ApiPpUlpHalLed3Off(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalLed4Off (D6)
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Set LED4 off 
*      
**************************************************************************/
extern void ApiPpUlpHalLed4Off(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalLed3Toggle (D7)
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Toggel LED3 
*      
**************************************************************************/
extern void ApiPpUlpHalLed3Toggle(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalLed4Toggle (D6)
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION: Toggle LED4
*      
**************************************************************************/
extern void ApiPpUlpHalLed4Toggle(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalAdc0ModeOn
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION: Enables ADC0 mode on P3[3] 
*      
**************************************************************************/
extern void ApiPpUlpHalAdc0ModeOn(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalAdc0ModeOff
* INPUTS  : None         
* OUTPUTS : None
*
* DESCRIPTION: Disables ADC0 mode and sets P3[3] to output mode  
*      
**************************************************************************/
extern void ApiPpUlpHalAdc0ModeOff(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalAdc0InpProtectionEnable
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION: Enables ADC0 Input protection
*      
*    OBS! this will limit the ADC range,  see Sc1441
*
**************************************************************************/
extern void ApiPpUlpHalAdc0InpProtectionEnable(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalAdc1InpProtectionEnable
* INPUTS  : None*           
* OUTPUTS : None
*
* DESCRIPTION: Enables ADC1 Input protection
*              
*    OBS! this will limit the ADC range,  see Sc1441
*      
**************************************************************************/
extern void ApiPpUlpHalAdc1InpProtectionEnable(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalAdc0InpProtectionDisable
* INPUTS  : None          
* OUTPUTS : None
*
* DESCRIPTION:  Disables ADC0 input protection
*
*     OBS Protection must be enabled if ADC0 input is ADC-NTC, that is 
*         when jumper j10 is mounted
*      
**************************************************************************/
extern void ApiPpUlpHalAdc0InpProtectionDisable(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalAdc1InpProtectionDisable
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION: Disables ADC1 input protection
*    
*     OBS Protection must be enabled if ADC1 input is ADC-POT, that is
*         when jumper j9 is mounted      
*
**************************************************************************/
extern void ApiPpUlpHalAdc1InpProtectionDisable(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalAdc0Read
* INPUTS  : None
*           
* OUTPUTS : ADC0 sample value (ADC-NTC)
*
* DESCRIPTION:  This function used to read an ADC value form ADC0.
*     
*     The input is taken from P1 bit 0, if a jumper is mounted on j10 
*     this port is connected to ADC-NTC and the input protection must be
*     enabled in order to get the correct range ...
*
*     OBS! Interrupt is disabled during the conversion
*      
**************************************************************************/
extern rsuint16 ApiPpUlpHalAdc0Read(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalAdc1Read
* INPUTS  : None
*           
* OUTPUTS : ADC1 sample value (ADC_POT))
*
* DESCRIPTION:  This function used to read an ADC value form ADC1.
*     
*     The input is taken from P1 bit 0, if a jumper is mounted on j9 
*     this port is connected to ADC-POT and the input  protection must be
*     enabled in order to get the correct range ...
*
*     OBS! Interrupt is disabled during the conversion
*      
**************************************************************************/
extern rsuint16 ApiPpUlpHalAdc1Read(void);

/*************************************************************************
* FUNCTION: ApiPpUlpHalSw2InterruptEnable
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION: 
*    
*  
*
**************************************************************************/
extern void ApiPpUlpHalKeybIntEnable(ApiPpUlpHalKeybIntFcnType KeybFcn);

/*************************************************************************
* FUNCTION: ApiPpUlpHalKeybIntSetup
* INPUTS  : None           
* OUTPUTS : None
*
* DESCRIPTION:  Enable interrupt on SW2 and setups the callback function 
*    to call when the switch is pressed...
*         
**************************************************************************/
extern void ApiPpUlpHalKeybIntSetup(ApiPpUlpHalKeybIntFcnType KeybFcn);
