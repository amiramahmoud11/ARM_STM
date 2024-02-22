
#include "RCC.h"

// HSI Clock

RCC_enuRet_errorStatus RCC_HSION_SystemClock(void)
{
    RCC_enuRet_errorStatus RetErrorStatuse=RCC_NOK;
    /**HSE_ON******/
    if (((RCC->CR) & (MASK_HSI_ON))!=MASK_HSI_ON)

    {
        /**HSE_READY*/
        if (((RCC->CR) & ( MASK_HSI_RDY))==MASK_HSI_RDY)
        {
            /*SELECT_SW*/

            u32 LocRcc_CR_Reg=RCC->CFGR;
            LocRcc_CR_Reg &=(~MASK_SW);
            LocRcc_CR_Reg |=(RCC_HSI<<0);
            RCC->CFGR=LocRcc_CR_Reg;

            u32 Loc_Time_Out=0;

            while ((((RCC->CFGR & MASK_GET_SWS)!=MASK_SWS_HSI))&&(Loc_Time_Out<600))
            {
                Loc_Time_Out++;
            }
            if (Loc_Time_Out>=600)
            {
                RetErrorStatuse=RCC_NOK;
            }
            else
            {
                RetErrorStatuse=RCC_NOK;
            }


        }
        else
        {
            RetErrorStatuse=RCC_NOK;
        }


    }
    else
    {
        RetErrorStatuse=RCC_NOK;
    }


return RetErrorStatuse;
}

//HSE Clock

RCC_enuRet_errorStatus RCC_HSEON_SystemClock(void)
{
    RCC_enuRet_errorStatus RetErrorStatuse=RCC_NOK;
    /**HSE_ON******/
    if (((RCC->CR) & (MASK_HSE_ON))!=MASK_HSE_ON)

    {
        /**HSE_READY*/
        if (((RCC->CR) & ( MASK_HSE_RDY))==MASK_HSE_RDY)
        {
            /*SELECT_SW*/

            u32 LocRcc_CR_Reg=RCC->CFGR;
            LocRcc_CR_Reg&=(~MASK_SW);
            LocRcc_CR_Reg|=(RCC_HSE<<0);
            RCC->CFGR=LocRcc_CR_Reg;

            u32 Loc_Time_Out=0;

            while ((((RCC->CFGR &MASK_SWS_HSE)!=MASK_SWS_HSE))&&(Loc_Time_Out<600))
            {
                Loc_Time_Out++;
            }
            if (Loc_Time_Out>=600)
            {
                RetErrorStatuse=RCC_NOK;
            }
            else
            {
                RetErrorStatuse=RCC_NOK;
            }


        }
        else
        {
            RetErrorStatuse=RCC_NOK;
        }


    }
    else
    {
        RetErrorStatuse=RCC_NOK;
    }


return RetErrorStatuse;
}


//PLL Clock

RCC_enuRet_errorStatus RCC_PLLON_SystemClock(void)
{
    RCC_enuRet_errorStatus RetErrorStatuse=RCC_NOK;
    /**HSE_ON******/
    if (((RCC->CR) & (MASK_PLL_ON))!=MASK_PLL_ON)

    {
        /**HSE_READY*/
        if (((RCC->CR) & ( MASK_PLL_RDY))==MASK_PLL_RDY)
        {
            /*SELECT_SW*/

            u32 LocRcc_CR_Reg=RCC->CFGR;
            LocRcc_CR_Reg&=(~MASK_SW);
            LocRcc_CR_Reg|=(RCC_PLL<<0);
            RCC->CFGR=LocRcc_CR_Reg;

            u32 Loc_Time_Out=0;

            while ((((RCC->CFGR &MASK_GET_SWS)!=MASK_SWS_PLL))&&(Loc_Time_Out<10000))
            {
                Loc_Time_Out++;
            }
            if (Loc_Time_Out>=10000)
            {
                RetErrorStatuse=RCC_NOK;
            }
            else
            {
                RetErrorStatuse=RCC_NOK;
            }


        }
        else
        {
            RetErrorStatuse=RCC_NOK;
        }


    }
    else
    {
        RetErrorStatuse=RCC_NOK;
    }


return RetErrorStatuse;
}

RCC_enuRet_errorStatus RCC_HSI_OFF_SystemClock(void)
{
    RCC_enuRet_errorStatus RetErrorStatuse=RCC_NOK;
    /**HSI_OFF******/
        u32 Loc_RCC_HSI_Cleear=RCC->CR;
        Loc_RCC_HSI_Cleear&=SysClk_CLR_MASK;
        RCC->CR =Loc_RCC_HSI_Cleear;


return RetErrorStatuse;
}
RCC_enuRet_errorStatus RCC_HSE_OFF_SystemClock(void)
{
    RCC_enuRet_errorStatus RetErrorStatuse=RCC_NOK;
    /**HSE_OFF******/

        u32 Loc_RCC_HSE_Cleear=RCC->CR;
        Loc_RCC_HSE_Cleear&=SysClk_CLR_MASK;
        RCC->CR =Loc_RCC_HSE_Cleear;


return RetErrorStatuse;
}

RCC_enuRet_errorStatus RCC_PLL_OFF_SystemClock(void)
{
    RCC_enuRet_errorStatus RetErrorStatuse=RCC_NOK;
    /**PLL_OFF******/

        u32 Loc_RCC_PllCleear=RCC->CR;
        Loc_RCC_PllCleear&=SysClk_CLR_MASK;
        RCC->CR =Loc_RCC_PllCleear;


return RetErrorStatuse;
}

//PLL_Source (HSE OR HSI )
RCC_enuRet_errorStatus RCC_Source_PllClock(RCC_enuPll Source_ClK_Pll)
{
    u32 Loc_RCC_PLLSource=RCC->PLLCFGR;
    RCC_enuRet_errorStatus RetErrorStatuse=RCC_NOK;

    if (Source_ClK_Pll>=HSI && Source_ClK_Pll<=HSE  )
    {
        RetErrorStatuse=RCC_OK;

        Loc_RCC_PLLSource&=PLL_SOURCE_CLR_MASK;
        Loc_RCC_PLLSource|=Source_ClK_Pll;
        RCC->PLLCFGR=Loc_RCC_PLLSource;

    }
    else
    {
        RetErrorStatuse=RCC_NOK;
    }

return RetErrorStatuse;
}



//PLL_CONFIGRATION_CLOCK

RCC_enuRet_errorStatus RCC_Cfg_PllClock(u8 Pll_M , u16 Pll_N , u8 Pll_P ,u8 Pll_Q)
{
    u32 Loc_RCC_PLLCFGR=RCC->PLLCFGR;
    RCC_enuRet_errorStatus RetErrorStatuse=RCC_NOK;
    if(Pll_M<PLL_M_START || Pll_M>PLL_M_END)
    {
        RetErrorStatuse=RCC_NOK;
    }
    else if (Pll_N<PLL_N_START || Pll_N>PLL_N_END)
    {
        RetErrorStatuse=RCC_NOK;
    }
    else if ( Pll_P>=PLL_P_END)
    {
        RetErrorStatuse=RCC_NOK;
    }
    else if (Pll_Q<PLL_Q_START || Pll_Q>PLL_Q_END)
    {
        RetErrorStatuse=RCC_NOK;
    }
    else
    {
        RetErrorStatuse=RCC_OK;

        Loc_RCC_PLLCFGR&=PLL_CONFIG_CLR_MASK;
        Loc_RCC_PLLCFGR|=(Pll_M<< OFFSET_PLL_M);
        Loc_RCC_PLLCFGR|=(Pll_N<< OFFSET_PLL_N);
        Loc_RCC_PLLCFGR|=(Pll_P<< OFFSET_PLL_P);
        Loc_RCC_PLLCFGR|=(Pll_Q<< OFFSET_PLL_Q);
        RCC->PLLCFGR=Loc_RCC_PLLCFGR;

    }



return RetErrorStatuse;
}


RCC_enuRet_errorStatus RCC_PeripheralEnableClock(RCC_enuPeripheralName Copy_Path_ID ,u8 Copy_Peripheral )
{
    u32 Loc_RCC_PriEnaClk;
    RCC_enuRet_errorStatus RetErrorStatuse=RCC_NOK;
    switch (Copy_Path_ID)
    {
    case AHP1:
        Loc_RCC_PriEnaClk=RCC->AHB1ENR;
        Loc_RCC_PriEnaClk|=(SET_BIT<<Copy_Peripheral);
        RCC->AHB1ENR=Loc_RCC_PriEnaClk;
        RetErrorStatuse=RCC_OK;
        break;
    case AHP2:
        Loc_RCC_PriEnaClk=RCC->AHB2ENR;
        Loc_RCC_PriEnaClk|=(SET_BIT<<Copy_Peripheral);
        RCC->AHB2ENR=Loc_RCC_PriEnaClk;
        RetErrorStatuse=RCC_OK;
        break;
    case APB1:
        Loc_RCC_PriEnaClk=RCC->APB1ENR;
        Loc_RCC_PriEnaClk|=(SET_BIT<<Copy_Peripheral);
        RCC->APB1ENR=Loc_RCC_PriEnaClk;
        RetErrorStatuse=RCC_OK;
        break;
    case APB2:
        Loc_RCC_PriEnaClk=RCC->APB2ENR;
        Loc_RCC_PriEnaClk|=(SET_BIT<<Copy_Peripheral);
        RCC->APB2ENR=Loc_RCC_PriEnaClk;
        RetErrorStatuse=RCC_OK;
        break;
    default:
        RetErrorStatuse=Rong_Path_Num;
        break;
    }


return RetErrorStatuse;
}

RCC_enuRet_errorStatus RCC_PeripheralDisableClock(RCC_enuPeripheralName Copy_Path_ID ,u8 Copy_Peripheral )
{
    u32 Loc_RCC_PriDisable_Clk;
    RCC_enuRet_errorStatus RetErrorStatuse=RCC_NOK;
    switch (Copy_Path_ID)
    {
    case AHP1:
        RetErrorStatuse=RCC_OK;
        Loc_RCC_PriDisable_Clk=RCC->AHB1ENR;
        Loc_RCC_PriDisable_Clk&=(CLEAR_BIT<<Copy_Peripheral);
        RCC->AHB1ENR=Loc_RCC_PriDisable_Clk;
        break;

    case AHP2:
        RetErrorStatuse=RCC_OK;
        Loc_RCC_PriDisable_Clk=RCC->AHB2ENR;
        Loc_RCC_PriDisable_Clk&=(CLEAR_BIT<<Copy_Peripheral);
        RCC->AHB2ENR=Loc_RCC_PriDisable_Clk;
        break;

    case APB1:
        RetErrorStatuse=RCC_OK;
        Loc_RCC_PriDisable_Clk=RCC->APB1ENR;
        Loc_RCC_PriDisable_Clk&=(CLEAR_BIT<<Copy_Peripheral);
        RCC->APB1ENR=Loc_RCC_PriDisable_Clk;
        break;
    case APB2:
        RetErrorStatuse=RCC_OK;
        Loc_RCC_PriDisable_Clk=RCC->APB2ENR;
        Loc_RCC_PriDisable_Clk&=(CLEAR_BIT<<Copy_Peripheral);
        RCC->APB2ENR=Loc_RCC_PriDisable_Clk;
        break;
    default:
        RetErrorStatuse=Rong_Path_Num;
        break;
    }


return RetErrorStatuse;
}

RCC_enuRet_errorStatus RCC_AHP_Prescaler(u8 Copy_AHP_Prescaler)
{
    u32 Loc_AHP_Prescaler=RCC->CFGR;
    RCC_enuRet_errorStatus RetErrorStatuse=RCC_NOK;

    if (Copy_AHP_Prescaler>AHP_PRE_512)
    {
        RetErrorStatuse=Rong_Statuse;
    }
    else
    {
        RetErrorStatuse=RCC_OK;
        Loc_AHP_Prescaler&=~(AHBPRE_CLEARMASK);
        Loc_AHP_Prescaler|=(Copy_AHP_Prescaler<<MASK_AHP_OFFSET);
        RCC->CFGR=Loc_AHP_Prescaler;
    }

return RetErrorStatuse;
}

RCC_enuRet_errorStatus RCC_APB2_Prescaler(u8 Copy_APB2_Prescaler)
{
    u32 Loc_APB2_Prescaler=RCC->CFGR;
    RCC_enuRet_errorStatus RetErrorStatuse=RCC_NOK;

    if (Copy_APB2_Prescaler>APB2_PRE_16)
    {
        RetErrorStatuse=Rong_Statuse;
    }
    else
    {
        RetErrorStatuse=RCC_OK;
        Loc_APB2_Prescaler&=~(APB1_PRE_CLEARMASK);
        Loc_APB2_Prescaler|=(Copy_APB2_Prescaler<<MASK_APB2_OFFSET);
        RCC->CFGR=Loc_APB2_Prescaler;
    }

return RetErrorStatuse;
}

RCC_enuRet_errorStatus RCC_APB1_Prescaler(u8 Copy_APB1_Prescaler)
{
    u32 Loc_APB1_Prescaler=RCC->CFGR;
    RCC_enuRet_errorStatus RetErrorStatuse=RCC_NOK;

    if (Copy_APB1_Prescaler>APB1_PRE_16)
    {
        RetErrorStatuse=Rong_Statuse;
    }
    else
    {
        RetErrorStatuse=RCC_OK;
        Loc_APB1_Prescaler&=~(APB1_PRE_CLEARMASK);
        Loc_APB1_Prescaler|=(Copy_APB1_Prescaler<<MASK_APB1_OFFSET);
        RCC->CFGR=Loc_APB1_Prescaler;
    }

return RetErrorStatuse;
}










