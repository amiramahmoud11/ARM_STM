#include "../../include/SYSTICK.h"


/* Configure the Processor clock speed in HZ */
#define SYSTICK_AHB_CLOCK     25000000


/* Configure the External refrence clock speed in HZ if it exists */
#define SYSTICK_AHB_CLOCK_DIV8      3125000  /* AHB/8 */

SysTick_t *const STK =(SysTick_t*) SYSTICK_BASE_ADDRESS;
static Systick_Cbf_t APPCBF;


void SysTick_CTRL_StartTimer(void)
{
   
    u32 Loc_Systick=STK->CTRL;
    Loc_Systick|=SYSTICK_ENABLE;
    STK->CTRL=Loc_Systick;

}

  /* Clear the Interrupt bit then set it according to mode
   if mode is periodic Int bit will be set if moode one time it will stay cleared */
void SysTick_CTRL_Itrrupt(u32 Systick_Intrrupt)       // if Systick_Intrrupt enable =2 if disable =0;
{
   
    u32 Loc_Systick_Int=STK->CTRL;
    Loc_Systick_Int&=~SYSTICK_CLEAR_INT_FLAG;
    Loc_Systick_Int|=Systick_Intrrupt;
    STK->CTRL=Loc_Systick_Int;

}

void SysTick_CTRL_ClockSource(u32 Systick_CLKSource)       // if Systick_Intrrupt AHB =0 if AHB_DIV_8 =4;
{
   
    u32 Loc_Systick_CLKS=STK->CTRL;
    Loc_Systick_CLKS&=~SYSTICK_CLEAR_CLK_FLAG;
    Loc_Systick_CLKS|=Systick_CLKSource;
    STK->CTRL=Loc_Systick_CLKS;

}

void SysTick_SetTime_ms(u32 Reload_Value)       // if Systick_Intrrupt AHB =0 if AHB_DIV_8 =4;
{
    u32 FPU;
    if((STK->CTRL & SYSTICK_CLEAR_CLK_FLAG)==SYSTICK_CLEAR_CLK_FLAG)
    {
        FPU=SYSTICK_AHB_CLOCK;
    }
    else
    {
        FPU=SYSTICK_AHB_CLOCK_DIV8;
    }
    STK->LOAD=((FPU/(1000))*Reload_Value)-1;
    
}

Ret_errorStatuse Systick_SET_Current_Value(u32 currunt_value)
{
   
    Ret_errorStatuse Loc_Ret_Statuse=Status_NOK;
    if (currunt_value>0x00FFFFFF)
    {
        Loc_Ret_Statuse=Invalid_Inputs;
    }
    else
    {
       Loc_Ret_Statuse=Status_OK;
       STK->VAL=currunt_value;
    }
return Loc_Ret_Statuse;}


Ret_errorStatuse Systick_Remainig_Value(u32 *Remainig_Value)
{
   
    Ret_errorStatuse Loc_Ret_Statuse=Status_NOK;
    if (Remainig_Value==NULL)
    {
        Loc_Ret_Statuse=Statuse_Null;
    }
    else
    {
        Loc_Ret_Statuse=Status_NOK;
       *Remainig_Value=STK->VAL;
    }
return Loc_Ret_Statuse;}


/*  return he last counts or time from starting count in Systick */
u32 Systick_ElaPsed_Value(void)
{
   u32 Loc_ElaPsed_Value;
   Loc_ElaPsed_Value=STK->LOAD-STK->VAL;
    
return Loc_ElaPsed_Value;}

Ret_errorStatuse Systick_Call_back(Systick_Cbf_t Cbf)
{
    Ret_errorStatuse Loc_Ret_Statuse=Status_NOK;
    if (Cbf==NULL)
    {
        Loc_Ret_Statuse=Statuse_Null;
    }
    else
    {
        Loc_Ret_Statuse=Status_OK;
        APPCBF=Cbf;
    }
return Loc_Ret_Statuse;}


Ret_errorStatuse Systick_Handler(void)
{
    Ret_errorStatuse Loc_Ret_Statuse=Status_NOK;

    if(APPCBF!=NULL)
    {
        Loc_Ret_Statuse=Status_OK;

        APPCBF();
    }
    else
    {
        Loc_Ret_Statuse=Invalid_Inputs;
    }
return Loc_Ret_Statuse;}

 
