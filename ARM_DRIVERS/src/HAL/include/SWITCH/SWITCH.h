#ifndef SWITCH_H_ 
#define SWITCH_H_

#define SWITCH_CONNECTION_PULLDOWEN 0x00000010
#define SWITCH_CONNECTION_PULLUP 0x00000008
#define OFFSET_4BIT_MASK 4

#define SWITCH_STATE_NOTPRESSED 0
#define SWITCH_STATE_PRESSED 1



typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

typedef struct 
{
    void *port;
    u32 pin ;
    u8 connection;
    
}SWITCH_Config_t;


typedef enum{
   SWITCH_OK,
   SWITCH_NOK,
   NULL_POINTR,
}SWITCH_RetenumerrorStatuse;



SWITCH_RetenumerrorStatuse Switch_Init(void);

SWITCH_RetenumerrorStatuse Switch_Get_State(u32 Copy_Switch,u8 * Switch_Value_State);






#endif