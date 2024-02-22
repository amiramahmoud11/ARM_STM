#include "../include/GPIO.h"

#define GPIO_MODE_MASK 0x00000018
#define GPIO_SHIFT_MODE_MASK 0x00000003
#define GPIO_TYPE_MASK 0x00000004
#define GPIO_SHIFT_TYPE_MASK 0x00000002
#define GPIO_PUPD_MASK 0x00000003
#define SHIFT_CLEAR_MASK 0x00000003
#define SHIFT_2BIT__MASK 0x00000002
#define SHIFT_CLEAR_TYPE_MASK 0x00000001
#define CLEAR_AF_MASK 0x0000000F
#define AFL_4BIT_OFFSET 4
#define AFH_8BIT_OFFSET 8





typedef struct 
{
 u32   MODER;
 u32  OTYPER;
 u32 OSPEEDR ;
 u32   PUPDR;
 u32    IDR;
 u32    ODR; 
 u32   BSRR ;
 u32   LCKR ;
 u32   AFRL ;
 u32   AFRH ;

    
}GPIO_MEMMAP_t;

Ret_enumerrorStatuse GPIO_Init(GPIO_pin_t *Copy_GPIO_elements)
{
 
    Ret_enumerrorStatuse Loc_Ret_errorState=GPIO_NOk;

    if (Copy_GPIO_elements==NULL)
    {
        Loc_Ret_errorState=Invalid_inputs;
    }
    else if ((Copy_GPIO_elements->port >GPIOC_BASE_ADDRESS)||(Copy_GPIO_elements->pin > GPIO_PIN_15))
    {
        Loc_Ret_errorState=Invalid_inputs;
    }
    else if ((Copy_GPIO_elements->mode > GPIO_MODE_AF_OD_PD)||(Copy_GPIO_elements->speed> GPIO_VERY_HIGH_SPEED))
    {
        Loc_Ret_errorState=Invalid_inputs;
    }
    else
    {
        /* code */
        Loc_Ret_errorState=GPIO_OK;
        u32 Loc_Mode_Value=(Copy_GPIO_elements->mode&GPIO_MODE_MASK)>>GPIO_SHIFT_MODE_MASK;
        u32 Loc_Type_Value=(Copy_GPIO_elements->mode&GPIO_TYPE_MASK)>>GPIO_SHIFT_TYPE_MASK;
        u32 Loc_PuPd_Value=(Copy_GPIO_elements->mode&GPIO_PUPD_MASK);  
        
        u32 Loc_MODE_Value=((GPIO_MEMMAP_t* )Copy_GPIO_elements->port)->MODER;
        u32 Loc_TYPE_Value=((GPIO_MEMMAP_t* )Copy_GPIO_elements->port)->OTYPER;
        u32 Loc_SPEAD_Value=((GPIO_MEMMAP_t* )Copy_GPIO_elements->port)->OSPEEDR;
        u32 Loc_PUPD_Value=((GPIO_MEMMAP_t* )Copy_GPIO_elements->port)->PUPDR;  

        Loc_MODE_Value&=~(SHIFT_CLEAR_MASK<<( SHIFT_2BIT__MASK * Copy_GPIO_elements->pin ));
        Loc_TYPE_Value&=~(SHIFT_CLEAR_TYPE_MASK<<(  Copy_GPIO_elements->pin ));
        Loc_SPEAD_Value&=~(SHIFT_CLEAR_MASK<<( SHIFT_2BIT__MASK * Copy_GPIO_elements->pin ));
        Loc_PUPD_Value&=~(SHIFT_CLEAR_MASK<<( SHIFT_2BIT__MASK * Copy_GPIO_elements->pin ));

        Loc_MODE_Value|=(Loc_Mode_Value<<( SHIFT_2BIT__MASK * Copy_GPIO_elements->pin ));  
        Loc_TYPE_Value|=(Loc_Type_Value<<(  Copy_GPIO_elements->pin ));  
        Loc_SPEAD_Value|=((Copy_GPIO_elements->speed)<<( SHIFT_2BIT__MASK * Copy_GPIO_elements->pin ));
        Loc_PUPD_Value|=(Loc_PuPd_Value<<( SHIFT_2BIT__MASK * Copy_GPIO_elements->pin ));
    
        ((GPIO_MEMMAP_t* )Copy_GPIO_elements->port)->MODER =  Loc_MODE_Value;
        ((GPIO_MEMMAP_t* )Copy_GPIO_elements->port)->OTYPER=  Loc_TYPE_Value;
        ((GPIO_MEMMAP_t* )Copy_GPIO_elements->port)->OSPEEDR= Loc_SPEAD_Value;
        ((GPIO_MEMMAP_t* )Copy_GPIO_elements->port)->PUPDR=   Loc_PUPD_Value;  

    
    
    }   

 
return Loc_Ret_errorState;
}


Ret_enumerrorStatuse GPIO_SetPin_Value(  void *GPIO_port , u32 GPIO_pin , u32 GPIO_Value_State)
{
 
    Ret_enumerrorStatuse Loc_Ret_errorState=GPIO_NOk;
    if(GPIO_port ==NULL)
    {
        Loc_Ret_errorState=Invalid_inputs;
    }
    else if(GPIO_pin>GPIO_PIN_15)
    {
        Loc_Ret_errorState=Invalid_inputs;
    }
    else
    {
        
        if(GPIO_Value_State==SET_BIT)
        {
            Loc_Ret_errorState=GPIO_OK;
            ((GPIO_MEMMAP_t *)GPIO_port)->BSRR=(SET_BIT<<GPIO_pin);
        }
        else if(GPIO_Value_State==REST_BIT)
        {
            Loc_Ret_errorState=GPIO_OK;
            ((GPIO_MEMMAP_t *)GPIO_port)->BSRR=BSRR_SHIFT_MASK<<(SET_BIT<<GPIO_pin);
        }
        else 
        {
            Loc_Ret_errorState=Invalid_inputs;
        }
        
    }


return Loc_Ret_errorState;}   


Ret_enumerrorStatuse GPIO_GetPin_Value(  void *GPIO_port , u32 GPIO_pin , u8 *GPIO_Value_State)
{
 
    Ret_enumerrorStatuse Loc_Ret_errorState=GPIO_NOk;
    if(GPIO_port ==NULL)
    {
        Loc_Ret_errorState=Invalid_inputs;
    }
    else if(GPIO_pin>GPIO_PIN_15)
    {
        Loc_Ret_errorState=Invalid_inputs;
    }
    else
    {
        
        
        Loc_Ret_errorState=GPIO_OK;
        *GPIO_Value_State=((((GPIO_MEMMAP_t *)GPIO_port)->IDR )>>GPIO_pin)|1;
       
        
    }


return Loc_Ret_errorState;}


Ret_enumerrorStatuse GPIO_AlternateFunction(  void *GPIO_port , u32 GPIO_pin , u32 GPIO_AltFun)
{
 
    Ret_enumerrorStatuse Loc_Ret_errorState=GPIO_NOk;
    if(GPIO_port ==NULL)
    {
        Loc_Ret_errorState=Invalid_inputs;
    }
    else if(GPIO_pin>GPIO_PIN_15)
    {
        Loc_Ret_errorState=Invalid_inputs;
    }
    else if(GPIO_AltFun>GPIO_ALTERNAT_FUNC_15)
    {
        Loc_Ret_errorState=Invalid_inputs;
    }

    else
    {
        
        if(GPIO_pin <GPIO_PIN_8)
        {
            Loc_Ret_errorState=GPIO_OK;
            u32 Loc_AlterFun_Low=((GPIO_MEMMAP_t *)GPIO_port)->AFRL;
            Loc_AlterFun_Low&=~(CLEAR_AF_MASK<<(GPIO_pin*AFL_4BIT_OFFSET));
            Loc_AlterFun_Low|=(GPIO_AltFun<<(GPIO_pin*AFL_4BIT_OFFSET));
            ((GPIO_MEMMAP_t *)GPIO_port)->AFRL=Loc_AlterFun_Low;
        
        }
        else
        {
            Loc_Ret_errorState=GPIO_OK;

            u32 Loc_AlterFun_High=((GPIO_MEMMAP_t *)GPIO_port)->AFRH;
            Loc_AlterFun_High&=~(CLEAR_AF_MASK<<((GPIO_pin-AFH_8BIT_OFFSET)*AFL_4BIT_OFFSET));
            Loc_AlterFun_High|=(GPIO_AltFun<<((GPIO_pin-AFH_8BIT_OFFSET)*AFL_4BIT_OFFSET));
            ((GPIO_MEMMAP_t *)GPIO_port)->AFRH=Loc_AlterFun_High;
        
        }
        
       
        
    }


return Loc_Ret_errorState;}
