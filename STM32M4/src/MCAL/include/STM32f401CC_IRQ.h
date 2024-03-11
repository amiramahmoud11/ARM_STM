#ifndef STM32f401CC_IRQ_
#define STM32f401CC_IRQ_

/********intrrupt Requst number*****************/

typedef enum {
    NVIC_IRQ_WWDG =0,
    NVIC_IRQ_PVD,
    NVIC_IRQ_TAMP_STAMP,
    NVIC_IRQ_RTC_WKUP,
    NVIC_IRQ_FLASH,
    NVIC_IRQ_RCC,
    NVIC_IRQ_EXTI0,
    NVIC_IRQ_EXTI1,
    NVIC_IRQ_EXTI2,
    NVIC_IRQ_EXTI3,
    NVIC_IRQ_EXTI4,
    NVIC_IRQ_DMA1_Stream0,
    NVIC_IRQ_DMA1_Stream1,
    NVIC_IRQ_DMA1_Stream2,
    NVIC_IRQ_DMA1_Stream3,
    NVIC_IRQ_DMA1_Stream4,
    NVIC_IRQ_DMA1_Stream5,
    NVIC_IRQ_DMA1_Stream6,
    NVIC_IRQ_ADC,
    NVIC_IRQ_CAN1_TX,
    NVIC_IRQ_CAN1_RX0,
    NVIC_IRQ_CAN1_RX1,
    NVIC_IRQ_CAN1_SCE,
    NVIC_IRQ_EXTI9_5,
    NVIC_IRQ_TIM1_BRK_TIM9,
    NVIC_IRQ_TIM1_UP_TIM10,
    NVIC_IRQ_TIM1_TRG_COM_TIM11,
    NVIC_IRQ_TIM1_CC,
    NVIC_IRQ_TIM2,
    NVIC_IRQ_TIM3,
    NVIC_IRQ_TIM4,
    NVIC_IRQ_I2C1_EV,
    NVIC_IRQ_I2C1_ER,
    NVIC_IRQ_I2C2_EV,
    NVIC_IRQ_I2C2_ER,
    NVIC_IRQ_SPI1,
    NVIC_IRQ_SPI2,
    NVIC_IRQ_USART1,
    NVIC_IRQ_USART2,
    NVIC_IRQ_USART3,
    NVIC_IRQ_EXTI15_10,
    NVIC_IRQ_RTC_Alarm,
    NVIC_IRQ_OTG_FS_WKUP,
    NVIC_IRQ_TIM8_BRK_TIM12,
    NVIC_IRQ_TIM8_UP_TIM13,
    NVIC_IRQ_TIM8_TRG_COM_TIM14,
    NVIC_IRQ_TIM8_CC,
    NVIC_IRQ_DMA1_Stream7,
    NVIC_IRQ_FSMC,
    NVIC_IRQ_SDIO,
    NVIC_IRQ_TIM5,
    NVIC_IRQ_SPI3,
    NVIC_IRQ_UART4,
    NVIC_IRQ_UART5,
    NVIC_IRQ_TIM6_DAC,
    NVIC_IRQ_TIM7,
    NVIC_IRQ_DMA2_Stream0,
    NVIC_IRQ_DMA2_Stream1,
    NVIC_IRQ_DMA2_Stream2,
    NVIC_IRQ_DMA2_Stream3,
    NVIC_IRQ_DMA2_Stream4,
    NVIC_IRQ_ETH,
    NVIC_IRQ_ETH_WKUP,
    NVIC_IRQ_CAN2_TX,
    NVIC_IRQ_CAN2_RX0,
    NVIC_IRQ_CAN2_RX1,
    NVIC_IRQ_CAN2_SCE,
    NVIC_IRQ_OTG_FS,
    NVIC_IRQ_DMA2_Stream5,
    NVIC_IRQ_DMA2_Stream6,
    NVIC_IRQ_DMA2_Stream7,
    NVIC_IRQ_USART6,
    NVIC_IRQ_I2C3_EV,
    NVIC_IRQ_I2C3_ER,
    NVIC_IRQ_OTG_HS_EP1_OUT,
    NVIC_IRQ_OTG_HS_EP1_IN,
    NVIC_IRQ_OTG_HS_WKUP,
    NVIC_IRQ_OTG_HS,
    NVIC_IRQ_DCMI,
    NVIC_IRQ_CRYP,
    NVIC_IRQ_HASH_RNG,
    NVIC_IRQ_FPU,
    NVIC_IRQ_SPI4=84,
    _NVIC_IRQ_NUM
}IRQn_t;

#endif