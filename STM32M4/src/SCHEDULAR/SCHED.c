/*
 * SCHED.c
 *
 * Created on: Mar 18, 2024
 *  Author: Amira Mahmoud
 */



#include "SCHED.h"
#include "SCHED_CFG.h"
#include "../MCAL/source/SYSTICK/SYSTICK.h"
#include "../MCAL/source/SYSTICK/SYSTICK_CFG.h"



extern runnable_t Runnables[_NUM_RUNNABLES] ;


static runnable_info_t RInfo[_NUM_RUNNABLES] ;


static volatile u32 Ticks_Pending=1;

static void SCHED_TicksPending(void);

ErrorStatuse Sched_Init(void)
{

   ErrorStatuse Loc_Ret_errorStatuse=Status_OK;

   u32 curr_Runnable;
    for (curr_Runnable = 0; curr_Runnable < _NUM_RUNNABLES; curr_Runnable++)
    {
        
            RInfo[curr_Runnable].Runnable=&Runnables;
            RInfo[curr_Runnable].remainTime_ms=Runnables[curr_Runnable].delay_ms;
            SysTick_ClockSource(SYSTICK_CLKSOURCE);
            Loc_Ret_errorStatuse= Systick_Call_back(SCHED_TicksPending);
            Loc_Ret_errorStatuse= SysTick_SetTime_ms(SCHED_TICK_MS);

       RInfo[curr_Runnable].remainTime_ms-=SCHED_TICK_MS; 
    }
  

return Loc_Ret_errorStatuse;
}


static void Sched(void)
{
    u32 curr_Runnable;
    for (curr_Runnable = 0; curr_Runnable < _NUM_RUNNABLES; curr_Runnable++)
    {
        if((RInfo[curr_Runnable].Runnable->cb)&&(RInfo[curr_Runnable].remainTime_ms==0))
        {
            RInfo[curr_Runnable].Runnable->cb();
            RInfo[curr_Runnable].remainTime_ms=Runnables[curr_Runnable].periority;

        }
       RInfo[curr_Runnable].remainTime_ms-=SCHED_TICK_MS; 
    }
    
}

ErrorStatuse Sched_Start(void)
{
    ErrorStatuse Loc_errorStatuse=Status_OK;

    Loc_errorStatuse=SysTick_Start( SYSTICK_MODE );
    while (1)
    {
        if(Ticks_Pending!=0)
        {
            Ticks_Pending--;
            Sched();
        }
    }
    

return Loc_errorStatuse;}

static void SCHED_TicksPending(void)
{
    Ticks_Pending++;
}