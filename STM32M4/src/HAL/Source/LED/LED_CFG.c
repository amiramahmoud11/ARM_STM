#include "../../../HAL/include/LED/LED_CFG.h"
#include "../../../HAL/include/LED/LED.h"
#include "../../../MCAL/include/GPIO.h"

const LED_Config_t LEDS[_Led_Num]={
    [Led_One]={.port=GPIO_PORT_A,.pin=GPIO_PIN_0,.connection=LED_CONNECTION_FORWARD,.state=LED_STATE_ON}
    ,[Led_Tow]={.port=GPIO_PORT_A,.pin=GPIO_PIN_1,.connection=LED_CONNECTION_REVERSED,.state=LED_STATE_ON} 
};