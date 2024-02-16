#ifndef RCC_H_
#define RCC_H_


typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

#define RCC_BASE_ADDRESS 0x40023800


/**********************************Clock typs***************************************************************************/
#define RCC_HSI 0
#define RCC_HSE 1
#define RCC_PLL 2

/*clocks on */
#define MASK_HSION 0
#define MASK_HSEON 16
#define MASK_PLLON 24

/**SW****/

#define  MASK_SW                 0x00000003
#define  MASK_GET_SWS            0x0000000C


/******System clock switch status****************/
#define	SysClk_CLR_MASK		0xFFFFFFFC
#define MASK_SWS_HSI 			 0x00000000
#define MASK_SWS_HSE 			 0x00000004
#define MASK_SWS_PLL 			 0x00000008


/**********CLOCK_READY and ON***************/
#define  MASK_HSI_ON             0x00000001
#define  MASK_HSI_RDY            0x00000002
#define  MASK_HSE_ON             0x00010000
#define  MASK_HSE_RDY            0x00020000
#define  MASK_PLL_ON             0x01000000
#define  MASK_PLL_RDY            0x02000000

//PL_M , PLL_N , PLL_Q ,PLL_P
#define PLL_CONFIG_CLR_MASK 0XF0FC8000
#define PLL_SOURCE_CLR_MASK 0xFFBFFFFF
#define PLLSRC_OFFSET 	22
#define  OFFSET_PLL_M	0
#define  OFFSET_PLL_N	6
#define  OFFSET_PLL_P	16
#define  OFFSET_PLL_Q	24

//start and end Pll bits
#define PLL_M_START	2
#define PLL_M_END	63
#define PLL_N_START	192
#define PLL_N_END	432
#define PLL_P_START	0
#define PLL_P_END	3
#define PLL_Q_START	2
#define PLL_Q_END	15

/*periphral bits in AHP and ABP*/

#define CLEAR_BIT 0
#define SET_BIT 1

//AHP1
#define	MASk_AHB1ENR_GPIOA	0
#define	MASk_AHB1ENR_GPIOB	1
#define	MASk_AHB1ENR_GPIOC	2
#define	MASk_AHB1ENR_GPIOD	3
#define	MASk_AHB1ENR_GPIOE	4
#define	MASk_AHB1ENR_GPIOH	7
#define	MASk_AHB1ENR_CRCEN	12
#define	MASk_AHB1ENR_DMA1EN	21
#define	MASk_AHB1ENR_DMA2EN	22
//AHP2
#define	MASk_AHB2ENR_OTGFSEN 7
//ABP1
#define	MASk_APB1ENR_TIM2		0
#define	MASk_APB1ENR_TIM3		1
#define	MASk_APB1ENR_TIM4		2
#define	MASk_APB1ENR_TIM5		3
#define	MASk_APB1ENR_WWDG		11
#define	MASk_APB1ENR_SPI2		14
#define	MASk_APB1ENR_SPI3		15
#define	MASk_APB1ENR_USART2		17
#define	MASk_APB1ENR_I2C1		21
#define	MASk_APB1ENR_I2C2		22
#define	MASk_APB1ENR_I2C3		23
#define	MASk_APB1ENR_PWR		28

//ABP2
#define	MASk_APB2ENR_TIM1		0
#define	MASk_APB2ENR_USART1		4
#define	MASk_APB2ENR_USART6		5
#define	MASk_APB2ENR_ADC1		8
#define	MASk_APB2ENR_SDIO		11
#define	MASk_APB2ENR_SPI1		12
#define	MASk_APB2ENR_SPI4		13
#define	MASk_APB2ENR_SYSCFG 	14
#define	MASk_APB2ENR_TIM9		16
#define	MASk_APB2ENR_TIM10		17
#define	MASk_APB2ENR_TIM11		18

/***************Macros for AHP prescaler***************/
#define AHBPRE_CLEARMASK 0x000000F0
#define MASK_AHP_OFFSET	4
#define AHP_PRE_1 	0
#define AHP_PRE_2 	8
#define AHP_PRE_4 	9
#define AHP_PRE_8 	10
#define AHP_PRE_16 	11
#define AHP_PRE_64 	12
#define AHP_PRE_128 13
#define AHP_PRE_256 14
#define AHP_PRE_512 15


/***************Macros for APB1(Low speed) prescaler***************/
#define APB1_PRE_CLEARMASK 0x00001C00
#define MASK_APB1_OFFSET	10

#define APB1_PRE_2 	4
#define APB1_PRE_4 	5
#define APB1_PRE_8 	6
#define APB1_PRE_16 7

/***************Macros for APB2(high speed) prescaler***************/
#define APB2_PRE_CLEARMASK 0x0000E000
#define MASK_APB2_OFFSET	13

#define APB2_PRE_2 	4
#define APB2_PRE_4 	5
#define APB2_PRE_8 	6
#define APB2_PRE_16 7





/***********TYPS********************************************************
 **********************************************************************
 *****************************************************************
*/



typedef struct{

	u32	CR;
	u32	PLLCFGR;
	u32	CFGR;
	u32	CIR;
	u32	AHB1RSTR;
	u32	AHB2RSTR;
	u32	Reserved_1;
	u32	Reserved_2;
	u32	APB1RSTR;
	u32	APB2RSTR;
	u32	Reserved_3;
	u32	Reserved_4;
	u32	AHB1ENR;
	u32	AHB2ENR;
	u32	Reserved_5;
	u32	Reserved_6;
	u32	APB1ENR;
	u32	APB2ENR;
	u32	Reserved_7;
	u32	Reserved_8;
	u32	AHB1LPENR;
	u32	AHB2LPENR;
	u32	Reserved_9;
	u32	Reserved_10;
	u32	APB1LPENR;
	u32 APB2LPENR;
	u32	Reserved_11;
	u32	Reserved_12;
	u32	BDCR;
	u32 CSR;
	u32	Reserved_13;
	u32	Reserved_14;
	u32	SSCGR;
	u32	PLLI2SCFGR;
	u32 DCKCFGR;

}RCC_MemMap_t;

#define	RCC	((volatile RCC_MemMap_t*)(RCC_BASE_ADDRESS))

typedef enum{
    HSI,
    HSE
}RCC_enuPll;

typedef enum {
    OFF,
    ON
}RCC_enuON_OFF;

typedef enum{
    RCC_OK,
    RCC_NOK,
	Rong_Path_Num,
	Rong_Statuse
}RCC_enuRet_errorStatus;

typedef enum{
    Ready,
    Not_Ready
}RCC_enuReadyStatus;

typedef enum{
    AHP1,
	AHP2,
	APB1,
	APB2
}RCC_enuPeripheralName;


/****************************************APIS*******************************************************************************
 * **************************************************************************************
*/
RCC_enuRet_errorStatus RCC_HSION_SystemClock(void);
RCC_enuRet_errorStatus RCC_HSEON_SystemClock(void);
RCC_enuRet_errorStatus RCC_PLLON_SystemClock(void);
RCC_enuRet_errorStatus RCC_PLLOFF_SystemClock(void);
RCC_enuRet_errorStatus RCC_HSI_OFF_SystemClock(void);
RCC_enuRet_errorStatus RCC_HSE_OFF_SystemClock(void);
RCC_enuRet_errorStatus RCC_PLL_OFF_SystemClock(void);
RCC_enuRet_errorStatus RCC_Source_PllClock(RCC_enuPll Source_ClK_Pll);
RCC_enuRet_errorStatus RCC_Cfg_PllClock(u8 Pll_M , u16 Pll_N , u8 Pll_P ,u8 Pll_Q);
RCC_enuRet_errorStatus RCC_PeripheralEnableClock(RCC_enuPeripheralName Copy_Path_ID ,u8 Copy_Peripheral );
RCC_enuRet_errorStatus RCC_PeripheralDisableClock(RCC_enuPeripheralName Copy_Path_ID ,u8 Copy_Peripheral );
RCC_enuRet_errorStatus RCC_AHP_Prescaler(u8 Copy_AHP_Prescaler);
RCC_enuRet_errorStatus RCC_APB2_Prescaler(u8 Copy_APB2_Prescaler);
RCC_enuRet_errorStatus RCC_APB1_Prescaler(u8 Copy_APB1_Prescaler);




#endif

