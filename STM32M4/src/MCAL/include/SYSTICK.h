#ifndef SYSTICK_H_
#define SYSTICK_H_

#define NULL ((void *)0)


#define SYSTICK_BASE_ADDRESS  0xE000E010
#define SYSTICK_ENABLE 0x00000001
#define SYSTICK_CLEAR_INT_FLAG 0x00000002
#define SYSTICK_ENABLE_INT_FLAG 0x00000002 
#define SYSTICK_CLEAR_CLK_FLAG 0x00000004

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

typedef struct SYSTICK
{
    volatile u32 CTRL;
    volatile u32 LOAD;
    volatile u32 VAL;
    volatile u32 CALIB;
}SysTick_t;




typedef enum{
   
    Status_OK,
    Status_NOK,
    Invalid_Inputs,
    Statuse_Null

}Ret_errorStatuse;

typedef void (*Systick_Cbf_t) (void);

/***********APIS*****************************************************************************
 * **************************************************************************************************
 * **********************************************************************************************
*/

/*enable counter in systick , the counter loads the RELOAD value from the 
LOAD register and then counts down. On reaching 0*/

void SysTick_CTRL_StartTimer(void);
void SysTick_CTRL_Itrrupt(u32 Systick_Intrrupt);
void SysTick_CTRL_ClockSource(u32 Systick_CLKSource);
void SysTick_SetTime_ms(u32 Reload_Value);
Ret_errorStatuse Systick_SET_Current_Value(u32 currunt_value);
Ret_errorStatuse Systick_Remainig_Value(u32 *Remainig_Value);
u32 Systick_ElaPsed_Value(void);
Ret_errorStatuse Systick_Call_back(Systick_Cbf_t Cbf);
Ret_errorStatuse Systick_Handler(void);

#endif