#include "../../../HAL/include/SWITCH/SWITCH_CFG.h"
#include "../../../HAL/include/SWITCH/SWITCH.h"
#include "../../../MCAL/include/GPIO.h"

extern const SWITCH_Config_t SWITCHS[_Switch_Num];

SWITCH_RetenumerrorStatuse Switch_Init(void)
{
    SWITCH_RetenumerrorStatuse RetSwitch_errorStatuse=SWITCH_OK;
    GPIO_pin_t Loc_Switch;
   
    for (u8 Switch_number = 0; Switch_number < _Switch_Num; Switch_number++)
    {
        Loc_Switch.port=SWITCHS[Switch_number].port;
        Loc_Switch.pin=SWITCHS[Switch_number].pin;
        Loc_Switch.mode=SWITCHS[Switch_number].connection;
        RetSwitch_errorStatuse=GPIO_Init(&Loc_Switch);
    }
    
    
return RetSwitch_errorStatuse;}




SWITCH_RetenumerrorStatuse Switch_Get_State(u32 Copy_Switch,u8 * Switch_Value_State)
{
    SWITCH_RetenumerrorStatuse RetSwitch_errorStatuse=SWITCH_NOK;
    u8 Loc_SW_Value;
    if (Switch_Value_State==NULL)
    {
        RetSwitch_errorStatuse=NULL_POINTR;
    }
    else
    {
        
        RetSwitch_errorStatuse=GPIO_GetPin_Value(  SWITCHS[Copy_Switch].port ,  SWITCHS[Copy_Switch].pin, &Loc_SW_Value);
        *Switch_Value_State=~(Loc_SW_Value^((SWITCHS[Copy_Switch].connection)>>OFFSET_4BIT_MASK));
    }
    

return RetSwitch_errorStatuse;}

