#include "../../include/NVIC.h"
#include "../../include/STM32f401CC_IRQ.h"



NVIC_t *NVIC= (NVIC_t *)NVIC_BASE_ADDRESS;
SCB_t *SCB= (SCB_t *) SCB_BASE_ADDRESS ;

Ret_errorStatuse NVIC_EnableIRQ(IRQn_t IRQn)
{
    Ret_errorStatuse Loc_error_status=Status_NOK;
    if (IRQn>_NVIC_IRQ_NUM)
    {
        Loc_error_status=Status_NOK;
    }
    else
    {
        Loc_error_status=Status_OK;
        NVIC->NVIC_ISER[IRQn/NVIC_REG_THRESHOLD]=NVIC_ISER_OFFFSET<<(IRQn%NVIC_REG_THRESHOLD);
    }
    
return Loc_error_status;}


Ret_errorStatuse NVIC_DisableIRQ(IRQn_t IRQn)
{
    Ret_errorStatuse Loc_error_status=Status_NOK;
    if (IRQn>_NVIC_IRQ_NUM)
    { 
        Loc_error_status=Status_NOK;
    }
    else
    {
        Loc_error_status=Status_OK;
        NVIC->NVIC_ICER[IRQn/NVIC_REG_THRESHOLD]=NVIC_ICER_OFFFSET<<(IRQn%NVIC_REG_THRESHOLD);
    }
    
return Loc_error_status;}

Ret_errorStatuse NVIC_SetPendingIRQ(IRQn_t IRQn)
{
    Ret_errorStatuse Loc_error_status=Status_NOK;
    if (IRQn>_NVIC_IRQ_NUM)
    {
        Loc_error_status=Status_NOK;
    }
    else
    {
        Loc_error_status=Status_OK;
        NVIC->NVIC_ISPR[IRQn/NVIC_REG_THRESHOLD]=NVIC_ISPR_OFFFSET<<(IRQn%NVIC_REG_THRESHOLD);
    }
    
return Loc_error_status;}


Ret_errorStatuse NVIC_ClearPendingIRQ(IRQn_t IRQn)
{
    Ret_errorStatuse Loc_error_status=Status_NOK;
    if (IRQn>_NVIC_IRQ_NUM)
    {
        Loc_error_status=Status_NOK;
    }
    else
    {
        Loc_error_status=Status_OK;
        NVIC->NVIC_ICPR[IRQn/NVIC_REG_THRESHOLD]=NVIC_ICPR_OFFFSET<<(IRQn%NVIC_REG_THRESHOLD);
    }
    
return Loc_error_status;}

Ret_errorStatuse NVIC_AciveIRQ(IRQn_t IRQn)
{
    Ret_errorStatuse Loc_error_status=Status_NOK;
    if (IRQn>_NVIC_IRQ_NUM)
    {
        Loc_error_status=Status_NOK;
    }
    else
    {
        Loc_error_status=Status_OK;
        NVIC->NVIC_IABR[IRQn/NVIC_REG_THRESHOLD]=NVIC_IABR_OFFFSET<<(IRQn%NVIC_REG_THRESHOLD);
    }
    
return Loc_error_status;}

/*configration of interrupt*/


Ret_errorStatuse NVIC_CNFG_Priority ( u32 Priority_Option)
{
    Ret_errorStatuse Loc_error_status=Status_NOK;
    if ((Priority_Option<GROUP_4BITS )|| (Priority_Option>GROUP_0BITS))
    {
        Loc_error_status=Status_NOK;
    }
    else
    {
        Loc_error_status=Status_OK;
        SCB->AIRCR=RESET_VALUE_AIRCR|(Priority_Option<<OFFSET_VALUE_AIRCR);
    }
    
return Loc_error_status;}

/**
 * @brief  		 Function to Set Priority Bit for Any Interrupt in the System
 *
 * @param   	 1) IRQn(Interrupt Number)
 *                  - MACRO Begins with NVIC_
 *                  - Options listed in STM32F401xx.h
 *              
 *               2) PreemptLevel
 *                  - Takes preemtion level, number must less than 2^(preemption bits)
 *                  - Preemtion bits is (Priority bits - Subgroup Bits)
 * 
 *               3) SubGroupLevel
 *                  - Takes Subgroup level, number must less than 2^(subgroup bits)
 * 
 *               4) SubGroupBitsMask
 *                  - Takes Number of Subgroup bits configuration, choose options from:
 *                          * SUBPRIORITY_BITS_NONE
 *                          * SUBPRIORITY_BITS_ONE
 *                          * SUBPRIORITY_BITS_TWO
 *                          * SUBPRIORITY_BITS_THREE
 *                          * SUBPRIORITY_BITS_FOUR
 *
 * @return		  Error Status
 *         		 - Returns Error if:
 *                          * Interrupt Number is out of range 
 *                          * Preemtion bits >= 2^(preemption bits)
 *                          * SubGroupLevel >= 2^(subgroup bits)
 *             
*/

Ret_errorStatuse NVIC_SetPriority (IRQn_t IRQn, u8 Subgroup_priority, u8 Group_priority, u8 SubGroup_periorty_Bits)
{
    Ret_errorStatuse Loc_error_status=Status_NOK;
    u32 periorty_index;
   
    u32 Loc_IPR=NVIC->NVIC_IPR[IRQn/NVIC_REG_THRESHOLD];
    periorty_index=(IRQn%NVIC_4BIT_THRESHOLD)*NVIC_8BIT_THRESHOLD;
   
    if (IRQn>=_NVIC_IRQ_NUM || SubGroup_periorty_Bits>NUMBER_OF_GROUP_BITS)
    {
        Loc_error_status=Invalid_Inputs;
    }
    else if ((Subgroup_priority+Group_priority)>SubGroup_periorty_Bits)    //(power(2,Subgroup_priority)+power(2,Group_priority))>power(2,SubGroup_periorty_Bits)
    {
        Loc_error_status=Invalid_Inputs;
    }
    else
    {
       Loc_IPR&=~(NVIC_CLEARFLAG_OFFST<<periorty_index);
       Loc_IPR|=(Group_priority<<(periorty_index+(NVIC_4BIT_THRESHOLD+Subgroup_priority)) | (Group_priority<<(NVIC_4BIT_THRESHOLD+Subgroup_priority)));
       NVIC->NVIC_IPR[IRQn/NVIC_REG_THRESHOLD]=Loc_IPR;
    }
    
     
    
return Loc_error_status;
}

Ret_errorStatuse NVIC_GetPriority (IRQn_t IRQn, u32 *GetPriority_Value)
{
    Ret_errorStatuse Loc_error_status=Status_NOK;
    u32 periorty_index;
   
    periorty_index=(IRQn%NVIC_4BIT_THRESHOLD)*NVIC_8BIT_THRESHOLD;
   
    if (IRQn>=_NVIC_IRQ_NUM && GetPriority_Value==NULL)
    {
        Loc_error_status=Invalid_Inputs;
    }
    else
    {
        periorty_index=(IRQn%NVIC_4BIT_THRESHOLD)*NVIC_8BIT_THRESHOLD;
        *GetPriority_Value= NVIC->NVIC_IPR[IRQn/NVIC_REG_THRESHOLD]>>periorty_index;
    }   
    
     
    
return Loc_error_status;
}

