/*
 * SYSTICK.c
 *
 *  Created on: Mar 7, 2024
 *  Author: Amira Mahmoud
 */


#include "SYSTICK.h"
#include "SYSTICK_CFG.h"

#define SYSTICK_ENABLE 0x00000001
#define MAX_NUM_TICKS 0xFFFFFF

/* Configure the Processor clock speed in HZ */
#define SYSTICK_AHB_CLOCK   25000000
#define SYSTICK_INT_MASK  0X00000002
/*Enables the counter. When ENABLE is set to 1, the counter loads the RELOAD value from the 
LOAD register and then counts down. On reaching 0*/ 
#define SYSTICK_TIME_START  0X00000001  

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


void SysTick_ClockSource(u8 clock_source)       // if Systick_Intrrupt AHB =0 if AHB_DIV_8 =4;
{
   
    u32 Loc_Systick_CLKS=STK->CTRL;
    Loc_Systick_CLKS&=~SYSTICK_CLEAR_CLK_FLAG;
    Loc_Systick_CLKS|=clock_source;
    STK->CTRL=Loc_Systick_CLKS;

}

Error_Statuse SysTick_SetTicks(u32 Num_Ticks )       
{
   Error_Statuse Loc_Error_Statuse=Status_STK_OK;
    if(Num_Ticks>MAX_NUM_TICKS)
    {
       Loc_Error_Statuse=Status_STK_NOK;
    }
    else
    {
       
       STK->LOAD=Num_Ticks;
    }
    
    
    
return Loc_Error_Statuse; }

Error_Statuse SysTick_SetTime_ms(u32 time_ms )      
{
    Error_Statuse Loc_Error_Statuse=Status_STK_OK;
    u32 loc_load;
    u32 FPU;
    if((STK->CTRL & SYSTICK_CLEAR_CLK_FLAG)==SYSTICK_CLEAR_CLK_FLAG)
    {
        FPU=SYSTICK_AHB_CLOCK;
    }
    else
    {
        FPU=SYSTICK_AHB_CLOCK_DIV8;
    }
    
    loc_load=((FPU/(1000))*time_ms)-1;
    Loc_Error_Statuse=SysTick_SetTicks(loc_load); 
    
return Loc_Error_Statuse;}

Error_Statuse SysTick_Start( u32 Systick_moad ) 
{
    Error_Statuse Loc_Error_Statuse=Status_STK_OK;
    if((Systick_moad != ONE_TIME) || (Systick_moad !=PERIODIC))
    {
        Loc_Error_Statuse=Status_STK_NOK;
    }
    else 
    {
        /*clear value in val reg */
        STK->VAL=0;
        /*if Systick_moad(one time ) 0: Counting down to zero does not assert the SysTick exception request
        if Systick_moad(periodic )   1: Counting down to zero to asserts the SysTick exception request.*/
        
        STK->CTRL&=SYSTICK_INT_MASK;
        /*
        *COUNTFLAG bit needs to be cleared explicitly by software. 
        Typically, this is done by writing any value to certain registers associated with the SysTick timer
        ,writing any value clears the COUNTFLAG bit to 0.
        */
        STK->CTRL=(SYSTICK_TIME_START|Systick_moad);   
    }
return Loc_Error_Statuse;   
}

Error_Statuse Systick_SET_Current_Value(u32 currunt_value)
{
   
    Error_Statuse Loc_Ret_Statuse=Status_STK_NOK;
    if (currunt_value>0x00FFFFFF)
    {
        Loc_Ret_Statuse=Invalid_STK_Inputs;
    }
    else
    {
       Loc_Ret_Statuse=Status_STK_OK;
       STK->VAL=currunt_value;
    }
return Loc_Ret_Statuse;}


Error_Statuse Systick_Remainig_Value(u32 *Remainig_Value)
{
   
    Error_Statuse Loc_Ret_Statuse=Status_STK_NOK;
    if (Remainig_Value==NULL)
    {
        Loc_Ret_Statuse=Statuse_STK_Null;
    }
    else
    {
        Loc_Ret_Statuse=Status_STK_NOK;
       *Remainig_Value=STK->VAL;
    }
return Loc_Ret_Statuse;}


/*  return he last counts or time from starting count in Systick */
u32 Systick_ElaPsed_Value(void)
{
   u32 Loc_ElaPsed_Value;
   Loc_ElaPsed_Value=STK->LOAD-STK->VAL;
    
return Loc_ElaPsed_Value;}

Error_Statuse Systick_Call_back(Systick_Cbf_t Cbf)
{
    Error_Statuse Loc_Ret_Statuse=Status_STK_NOK;
    if (Cbf==NULL)
    {
        Loc_Ret_Statuse=Statuse_STK_Null;
    }
    else
    {
        Loc_Ret_Statuse=Status_STK_OK;
        APPCBF=Cbf;
    }
return Loc_Ret_Statuse;}


Error_Statuse Systick_Handler(void)
{
    Error_Statuse Loc_Ret_Statuse=Status_STK_NOK;

    if(APPCBF!=NULL)
    {
        Loc_Ret_Statuse=Status_STK_OK;

        APPCBF();
    }
    else
    {
        Loc_Ret_Statuse=Invalid_STK_Inputs;
    }
return Loc_Ret_Statuse;}

 
