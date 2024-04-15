#ifndef LED_H_ 
#define LED_H_

#define LED_STATE_OFF 0
#define LED_STATE_ON 1

#define LED_CONNECTION_FORWARD 0
#define LED_CONNECTION_REVERSED 1



typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct 
{
    void *port;
    u32 pin ;
    u8 connection;
    u8 state; 
}LED_Config_t;


typedef enum{
    LED_OK,
    LED_NOK,
}Led_RetenumerrorStatuse;



Led_RetenumerrorStatuse Led_Init(void);

Led_RetenumerrorStatuse Led_State(u32 Copy_led, u8 Copy_State );






#endif