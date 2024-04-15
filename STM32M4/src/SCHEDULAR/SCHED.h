#ifndef _SCHED_H_
#define _SCHED_H_

#define NULL ((void *)0)
typedef void (*runnableCb_t)(void);


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SCHED
{
    char *runnable_name;
    u32 periodicityMS;
    u32 periority;
    runnableCb_t cb;
    u32 delay_ms; 


}runnable_t;

typedef struct 
{
    const runnable_t * Runnable;
    u32 remainTime_ms ;

}runnable_info_t;



typedef enum{
   
    Status_OK,
    Status_NOK,
    Invalid_Inputs,
    Statuse_Null

}ErrorStatuse;



ErrorStatuse Sched_Init(void);
static void Sched(void);
ErrorStatuse Sched_Start(void);
static void SCHED_TicksPending(void);



#endif