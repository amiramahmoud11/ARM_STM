#include "../../../HAL/include/SWITCH/SWITCH_CFG.h"
#include "../../../HAL/include/SWITCH/SWITCH.h"
#include "../../../MCAL/include/GPIO.h"

const SWITCH_Config_t SWITCHS[_Switch_Num]={
    [Switch_One]={.port=GPIO_PORT_A,.pin=GPIO_PIN_0,.connection=SWITCH_CONNECTION_PULLDOWEN}
    ,[Switch_Tow]={.port=GPIO_PORT_A,.pin=GPIO_PIN_1,.connection=SWITCH_CONNECTION_PULLUP} 
};