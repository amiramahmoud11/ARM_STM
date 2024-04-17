#ifndef UART_H_
#define UART_H_
#define USART_1 0
#define USART_2 1
#define USART_6 2
#define USART_OVER_8  0x00008000
#define USART_PARITY_ENABLE 0x00000400
#define USART_PARITY_ODD 0x00000200
#define USART_9_DATABIT 0x00001000
#define USART_2_STOP_BIT 0x00002000
#define USART_STATE_BUSY 1
#define USART_STATE_READY 0
#define UART_TXE_MASK 0x00000020
#define UART_TXEIE_ENABLE_FLAG 0x00000080
#define USART_RXNEIE_ENABLE_FLAG 0x00000020
#define USART_RX_DONE_IRQ  0x00000020
#define USART_LBD_ENABLE ((u32)(1<<8))
#define USART_TXE_ENABLE_FLAG ((u32)(1<<7))
#define USART_RXE_ENABLE_FLAG ((u32)(1<<5))
#define NULL ((void *)0)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

// Callback function pointer type
typedef void (*CallBack_t)(void);
typedef void (*LBD_CallBack_t)(void);
// Structure for UART configuration
typedef struct 
{
    u32 address;
    u32 baudrate;
    u32 paritycontrol;
    u32 parityselect;
    u32 overSampling;
    u32 stopBit;
    u32 WordLength;

}uart_configuration;

// Structure for USART Request
typedef struct
{
    u8 USART_Peri;
    u8 *buffer;
    u16 length;
    CallBack_t CB;
} USART_Req_t;

// Enumeration for Error Status
typedef enum {

    Statuse_Ok,
    Statuse_Nok,
    Invalid_Inputs,
    State_busy,
    Status_NULL_Pointer,
    Status_usart_timeout
 
}Error_tatuse;





/********************************APIS*************************************************
*************************************************************************************
*************************************************************************************/
/*
 * Initialize the USART peripheral with provided configuration.
 * Parameters:
 *  - uart_config: Configuration parameters for USART.
 * Return:
 *  - Error status indicating success or failure.
 */
Error_tatuse uart_int(uart_configuration uart_config);

/*
 * Send a single byte via USART.
 * Parameters:
 *  - Usart_Req: Structure containing USART request details.
 * Return:
 *  - Error status indicating success or failure.
 */

Error_tatuse UASART_SendByte(USART_Req_t Usart_Req);

/*
 * Receive a single byte via USART.
 * Parameters:
 *  - Usart_Req: Structure containing USART request details.
 * Return:
 *  - Error status indicating success or failure.
 */

Error_tatuse UASART_GetByte(USART_Req_t Usart_Req);

/*
 * Send a buffer of data via USART.
 * Parameters:
 *  - Usart_Req: Structure containing USART request details.
 * Return:
 *  - Error status indicating success or failure.
 */
Error_tatuse UASART_SendBufferAsyncZeroCopy(USART_Req_t Usart_Req);

/*
 * Receive a buffer of data via USART.
 * Parameters:
 *  - Usart_Req: Structure containing USART request details.
 * Return:
 *  - Error status indicating success or failure.
 */

Error_tatuse UASART_ReciveBufferAsyncZeroCopy(USART_Req_t Usart_Req);

#endif