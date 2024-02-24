#include "../../../HAL/include/LED/LED_CFG.h"
#include "../../../HAL/include/LED/LED.h"
#include "../../../MCAL/include/GPIO.h"

extern const LED_Config_t LEDS[_Led_Num];

Led_RetenumerrorStatuse Led_Init(void)
{
    Led_RetenumerrorStatuse RetLed_errorStatuse=LED_OK;
    GPIO_pin_t Loc_Led;
    Loc_Led.mode=GPIO_MODE_OP_PP;
    Loc_Led.speed=GPIO_HIGH_SPEED;
    for (u8 led_number = 0; led_number < _Led_Num; led_number++)
    {
        Loc_Led.port=LEDS[led_number].port;
        Loc_Led.pin=LEDS[led_number].pin;
        RetLed_errorStatuse=GPIO_Init(&Loc_Led);
    }
    
    
return RetLed_errorStatuse;}




Led_RetenumerrorStatuse Led_State(u32 Copy_led, u8 Copy_State )
{
    Led_RetenumerrorStatuse RetLed_errorStatuse=LED_OK;
    RetLed_errorStatuse=GPIO_SetPin_Value(  LEDS[Copy_led].port ,  LEDS[Copy_led].pin,  LEDS[Copy_led].connection^Copy_State);

return RetLed_errorStatuse;}

