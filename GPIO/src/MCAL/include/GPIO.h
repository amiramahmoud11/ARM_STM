#ifndef GPIO_H_
#define GPIO_H_


#define NULL ((void *)0)

/*GPIO A,B,C,.... base address*/

#define GPIOA_BASE_ADDRESS   0x40020000
#define GPIOB_BASE_ADDRESS   0x40020400 
#define GPIOC_BASE_ADDRESS   0x40020800

/******** gpio pins ***********/

#define GPIO_PIN_0  0x00000000
#define GPIO_PIN_1  0x00000001
#define GPIO_PIN_2  0x00000002
#define GPIO_PIN_3  0x00000003
#define GPIO_PIN_4  0x00000004
#define GPIO_PIN_5  0x00000005
#define GPIO_PIN_6  0x00000006
#define GPIO_PIN_7  0x00000007
#define GPIO_PIN_8  0x00000008
#define GPIO_PIN_9  0x00000009
#define GPIO_PIN_10 0x0000000A
#define GPIO_PIN_11 0x0000000B
#define GPIO_PIN_12 0x0000000C
#define GPIO_PIN_13 0x0000000D
#define GPIO_PIN_14 0x0000000E
#define GPIO_PIN_15 0x0000000F

/****************************************************************/
#define GPIOA   (volatile GPIO_MEMMAP_t *(GPIOA_BASE_ADDRESS ))
#define GPIOB   (volatile GPIO_MEMMBP_t *(GPIOB_BASE_ADDRESS ))
#define GPIOC   (volatile GPIO_MEMMAP_t *(GPIOC_BASE_ADDRESS ))

/********************/

/*Parameter to be used for function:
 * @ Gpio_PinModeConfiguration
 *
 * ---> To set the Pin Mode
 */

#define GPIO_MODE_OP_PP 0b01000
#define GPIO_MODE_OP_PP_PU 0b01001
#define GPIO_MODE_OP_PP_PD 0b01010
#define GPIO_MODE_OP_OD 0b01100
#define GPIO_MODE_OP_OD_PU 0b01101
#define GPIO_MODE_OP_OD_PD 0b01110


#define GPIO_MODE_AF_PP 0b10000
#define GPIO_MODE_AF_PP_PU 0b10001
#define GPIO_MODE_AF_PP_PD 0b10010
#define GPIO_MODE_AF_OD 0b10100
#define GPIO_MODE_AF_OD_PU 0b10101
#define GPIO_MODE_AF_OD_PD 0b10110


#define GPIO_MODE_IN_FLOATING 0b00000
#define GPIO_MODE_IN_PU 0b00001
#define GPIO_MODE_IN_PD 0b00010

#define GPIO_MODE_AN 0b11000

/*
* ***GPIO port output speed register
***
**/

#define GPIO_LOW_SPEED 0X00000000
#define GPIO_MEDIUM_SPEED 0X00000001
#define GPIO_HIGH_SPEED 0X00000002
#define GPIO_VERY_HIGH_SPEED 0X00000003


/****
 * 
 * /*
 * Alternative function
 * */

#define GPIO_ALTERNAT_FUNC_0 0x00000000
#define GPIO_ALTERNAT_FUNC_1 0x00000001
#define GPIO_ALTERNAT_FUNC_2 0x00000002
#define GPIO_ALTERNAT_FUNC_3 0x00000003
#define GPIO_ALTERNAT_FUNC_4 0x00000004
#define GPIO_ALTERNAT_FUNC_5 0x00000005
#define GPIO_ALTERNAT_FUNC_6 0x00000006
#define GPIO_ALTERNAT_FUNC_7 0x00000007
#define GPIO_ALTERNAT_FUNC_8 0x00000008
#define GPIO_ALTERNAT_FUNC_9 0x00000009
#define GPIO_ALTERNAT_FUNC_10 0x0000000A
#define GPIO_ALTERNAT_FUNC_11 0x0000000B
#define GPIO_ALTERNAT_FUNC_12 0x0000000C
#define GPIO_ALTERNAT_FUNC_13 0x0000000D
#define GPIO_ALTERNAT_FUNC_14 0x0000000E
#define GPIO_ALTERNAT_FUNC_15 0x0000000F


/* BIT_SET_RESET Rgister*/
#define SET_BIT 0x00000001
#define REST_BIT 0x00000000
#define BSRR_SHIFT_MASK 16





typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;



typedef struct GPIO
{
    u32  pin;
   void *port;
    u32 speed;
    u32 mode;

}GPIO_pin_t;
/***************return error statuse **************/
typedef enum{
    GPIO_OK,
    GPIO_NOk,
    Invalid_inputs
}Ret_enumerrorStatuse;


/***********************************************************************************************
*****************************************APIS****************************************************
**********************************************************************************************/


Ret_enumerrorStatuse GPIO_Init(GPIO_pin_t *Copy_pin_elements);
Ret_enumerrorStatuse GPIO_SetPin_Value(  void *GPIO_port , u32 GPIO_pin , u32 GPIO_Value_State);
Ret_enumerrorStatuse GPIO_GetPin_Value(   void *GPIO_port , u32 GPIO_pin , u32 GPIO_Value_State);
Ret_enumerrorStatuse GPIO_AlternateFunction(  void  *GPIO_port , u32 GPIO_pin , u32 GPIO_AltFun);













#endif