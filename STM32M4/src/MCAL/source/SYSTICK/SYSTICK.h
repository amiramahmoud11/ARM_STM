#ifndef SYSTICK_H_
#define SYSTICK_H_



#define NULL ((void *)0)


#define SYSTICK_BASE_ADDRESS  0xE000E010

#define SYSTICK_CLEAR_INT_FLAG 0x00000002
#define SYSTICK_ENABLE_INT_FLAG 0x00000002 
#define SYSTICK_CLEAR_CLK_FLAG 0x00000004


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int   u32;


typedef struct SYSTICK
{
    volatile u32 CTRL;
    volatile u32 LOAD;
    volatile u32 VAL;
    volatile u32 CALIB;
}SysTick_t;


typedef enum
{
    Status_STK_OK,
    Status_STK_NOK,
    Invalid_STK_Inputs,
    Statuse_STK_Null
}Error_Statuse;



typedef void (*Systick_Cbf_t) (void);

/***********APIS*****************************************************************************
 * **************************************************************************************************
 * **********************************************************************************************
*/

/*enable counter in systick , the counter loads the RELOAD value from the 
LOAD register and then counts down. On reaching 0*/

void SysTick_CTRL_StartTimer(void);



void SysTick_CTRL_Itrrupt(u32 Systick_Intrrupt);

/**
 *@brief sets clock source 
*@param if  Selects the clock source.
 0: AHB/8
 1: Processor clock (AHB)
*@return return ok if valid inputs and not ok if not valid 
*@note 
*/
void SysTick_ClockSource(u8 clock_source);


/**
 *@brief sets number of ticks  
*@param take number of ticks and set it in load reg 
*@return return ok if valid inputs and not ok if not valid 
*@note 
*/

Error_Statuse SysTick_SetTicks(u32 Num_Ticks ) ;




/**
 *@brief sets time in ms 
*@param take time ms
*@note convert time_ms to ticks in load reg then start count dowen 
*/
Error_Statuse SysTick_SetTime_ms(u32 time_ms ) ;


/**
 *@brief sets mode (one_time or periodic )
*@param take mode 
*@return return ok if valid inputs and not ok if not valid 
*@note 
*/
Error_Statuse SysTick_Start( u32 Systick_moad ) ;


Error_Statuse Systick_SET_Current_Value(u32 currunt_value);


Error_Statuse Systick_Remainig_Value(u32 *Remainig_Value);


u32 Systick_ElaPsed_Value(void);


Error_Statuse Systick_Call_back(Systick_Cbf_t Cbf);


Error_Statuse Systick_Handler(void);


#endif