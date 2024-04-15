#ifndef NVIC_H_
#define NVIC_H_
#include "STM32f401CC_IRQ.h"


#define NULL ((void *)0)

//Reset value (AIRCR): 0xFA050000 
#define RESET_VALUE_AIRCR 0xFA050000 
#define OFFSET_VALUE_AIRCR 8 
#define GROUP_PERIORITY_OFFSET 2
#define PERIORITY_OFFSET 4
/////////////////////////
#define PEND_SV -6
#define SYSTICK -5
////////////////////////////
#define SV_CALL -4
/////////////////////////
#define MEMORY_MANAGE -3
#define BUS_FAULT -2
#define USAGE_FAULT -1
/////////////////////////



#define NVIC_BASE_ADDRESS   0xE000E100
#define SCB_BASE_ADDRESS    0xE000E008

#define NVIC_ISER_OFFFSET 0x00000001
#define NVIC_ICER_OFFFSET 0x00000001
#define NVIC_ISPR_OFFFSET 0x00000001
#define NVIC_ICPR_OFFFSET 0x00000001
#define NVIC_IABR_OFFFSET 0x00000001
#define NVIC_CLEARFLAG_OFFST 0x000000FF
#define NVIC_REG_THRESHOLD 32
#define NVIC_4BIT_THRESHOLD 4
#define NVIC_8BIT_THRESHOLD 8


#define NUMBER_OF_GROUP_BITS 4

//periority options in (AIRCR)
#define GROUP_4BITS 0b011
#define GROUP_3BITS 0b100
#define GROUP_2BITS 0b101
#define GROUP_1BITS 0b110
#define GROUP_0BITS 0b111



typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/*NVIC_Registers*/

typedef struct
{
    /* data */
    volatile u32  NVIC_ISER[8];
    volatile u32  RESERVED_1[24];
    volatile u32  NVIC_ICER[8];
    volatile u32  RESERVED_2[24];
    volatile u32  NVIC_ISPR[8];
    volatile u32  RESERVED_3[24];
    volatile u32  NVIC_ICPR[8];
    volatile u32  RESERVED_4[24];
    volatile u32  NVIC_IABR[8];
    volatile u32  RESERVED_5[56];
    volatile u32  NVIC_IPR[8];
    volatile u32  RESERVED_6[580];
    volatile u32  NVIC_STIR[15]; 
    
} NVIC_t;

typedef struct
{
    volatile u32 ACTLR;
    volatile u32 Reserved1[829];
    volatile u32 CPUID;
    volatile u32 ICSR;
    volatile u32 VTOR;
    volatile u32 AIRCR;
    volatile u32 SCR;
    volatile u32 CCR;
    volatile u32 SHPR[3];
    volatile u32 SHCSR;
    volatile u32 CFSR;
    volatile u32 HFSR;
    volatile u32 Reserved2;
    volatile u32 MMAR;
    volatile u32 BFAR;
    volatile u32 AFSR;

} SCB_t;


typedef enum{
   
    Status_OK,
    Status_NOK,
    Invalid_Inputs

}Ret_errorStatuse;


/***************************APIS************************/
/*********************************************************************************************
 * ***************************************************************************************
*/

/*
 * use this function to  set-enable register x (NVIC_ISER) X[0->7]
 * parameters:
 * NVIC_IRQ -> the ID of the requested interrupt from the target IRQ_ID list
 * return:
 * Status_NOK, Status_OK, Status_Null_Pointer, Status_Invalid_Input
 */
Ret_errorStatuse NVIC_EnableIRQ(IRQn_t IRQn);
Ret_errorStatuse NVIC_DisableIRQ(IRQn_t IRQn);
Ret_errorStatuse NVIC_SetPendingIRQ (IRQn_t IRQn);
Ret_errorStatuse NVIC_ClearPendingIRQ (IRQn_t IRQn);
Ret_errorStatuse NVIC_AciveIRQ(IRQn_t IRQn);
Ret_errorStatuse NVIC_CNFG_Priority ( u32 Priority_Option);
Ret_errorStatuse NVIC_SetPriority (IRQn_t IRQn, u8 Subgroup_priority, u8 Group_priority, u8 SubGroup_periorty_Bits);
Ret_errorStatuse NVIC_GetPriority (IRQn_t IRQn, u32 *GetPriority_Value);
Ret_errorStatuse NVIC_SetPriorityGrouping(u32 priority_grouping);

/*
 * Function: NVIC_EnableIRQ
 * ------------------------
 * Enables the specified interrupt identified by the IRQn parameter in the NVIC_ISER register.
 *
 * IRQn: The ID of the interrupt to be enabled from the target IRQ_ID list.
 *
 * returns: 
 *      Status_NOK: An error occurred during the operation.
 *      Status_OK: The interrupt was successfully enabled.
 *      Status_Null_Pointer: The input pointer is null.
 *      Status_Invalid_Input: The input IRQn is not a valid interrupt ID.
 */
Ret_errorStatuse NVIC_EnableIRQ(IRQn_t IRQn);

/*
 * Function: NVIC_DisableIRQ
 * -------------------------
 * Disables the specified interrupt identified by the IRQn parameter in the NVIC_ISER register.
 *
 * IRQn: The ID of the interrupt to be disabled from the target IRQ_ID list.
 *
 * returns:
 *      Status_NOK: An error occurred during the operation.
 *      Status_OK: The interrupt was successfully disabled.
 *      Status_Null_Pointer: The input pointer is null.
 *      Status_Invalid_Input: The input IRQn is not a valid interrupt ID.
 */
Ret_errorStatuse NVIC_DisableIRQ(IRQn_t IRQn);

/*
 * Function: NVIC_SetPendingIRQ
 * -----------------------------
 * Sets the pending status of the specified interrupt identified by the IRQn parameter.
 *
 * IRQn: The ID of the interrupt to set as pending from the target IRQ_ID list.
 *
 * returns:
 *      Status_NOK: An error occurred during the operation.
 *      Status_OK: The pending status of the interrupt was successfully set.
 *      Status_Null_Pointer: The input pointer is null.
 *      Status_Invalid_Input: The input IRQn is not a valid interrupt ID.
 */
Ret_errorStatuse NVIC_SetPendingIRQ (IRQn_t IRQn);

/*
 * Function: NVIC_ClearPendingIRQ
 * ------------------------------
 * Clears the pending status of the specified interrupt identified by the IRQn parameter.
 *
 * IRQn: The ID of the interrupt to clear its pending status from the target IRQ_ID list.
 *
 * returns:
 *      Status_NOK: An error occurred during the operation.
 *      Status_OK: The pending status of the interrupt was successfully cleared.
 *      Status_Null_Pointer: The input pointer is null.
 *      Status_Invalid_Input: The input IRQn is not a valid interrupt ID.
 */
Ret_errorStatuse NVIC_ClearPendingIRQ (IRQn_t IRQn);

/*
 * Function: NVIC_AciveIRQ
 * ------------------------
 * Checks if the specified interrupt identified by the IRQn parameter is active.
 *
 * IRQn: The ID of the interrupt to check its active status from the target IRQ_ID list.
 *
 * returns:
 *      Status_NOK: An error occurred during the operation.
 *      Status_OK: The active status of the interrupt was successfully checked.
 *      Status_Null_Pointer: The input pointer is null.
 *      Status_Invalid_Input: The input IRQn is not a valid interrupt ID.
 */
Ret_errorStatuse NVIC_AciveIRQ(IRQn_t IRQn);

/*
 * Function: NVIC_CNFG_Priority
 * -----------------------------
 * Configures the priority options for interrupt handling.
 *
 * Priority_Option: The priority configuration options to be set.
 *
 * returns:
 *      Status_NOK: An error occurred during the operation.
 *      Status_OK: The priority configuration was successfully set.
 *      Status_Null_Pointer: The input pointer is null.
 *      Status_Invalid_Input: The input priority option is invalid.
 */
Ret_errorStatuse NVIC_CNFG_Priority ( u32 Priority_Option);

/*
 * Function: NVIC_SetPriority
 * ---------------------------
 * Sets the priority for the specified interrupt identified by the IRQn parameter.
 *
 * IRQn: The ID of the interrupt to set its priority from the target IRQ_ID list.
 * Subgroup_priority: The subgroup priority value.
 * Group_priority: The group priority value.
 * SubGroup_periorty_Bits: The number of bits used for subgroup priority.
 *
 * returns:
 *      Status_NOK: An error occurred during the operation.
 *      Status_OK: The priority for the interrupt was successfully set.
 *      Status_Null_Pointer: The input pointer is null.
 *      Status_Invalid_Input: The input IRQn is not a valid interrupt ID.
 */
Ret_errorStatuse NVIC_SetPriority (IRQn_t IRQn, u8 Subgroup_priority, u8 Group_priority, u8 SubGroup_periorty_Bits);

/*
 * Function: NVIC_GetPriority
 * ---------------------------
 * Retrieves the priority for the specified interrupt identified by the IRQn parameter.
 *
 * IRQn: The ID of the interrupt to retrieve its priority from the target IRQ_ID list.
 * GetPriority_Value: Pointer to store the retrieved priority value.
 *
 * returns:
 *      Status_NOK: An error occurred during the operation.
 *      Status_OK: The priority for the interrupt was successfully retrieved.
 *      Status_Null_Pointer: The input pointer is null.
 *      Status_Invalid_Input: The input IRQn is not a valid interrupt ID.
 */
Ret_errorStatuse NVIC_GetPriority (IRQn_t IRQn, u32 *GetPriority_Value);

/*
 * Function: NVIC_SetPriorityGrouping
 * -----------------------------------
 * Sets the priority grouping for the interrupt priority.
 *
 * priority_grouping: The priority grouping value to be set.
 *
 * returns:
 *      Status_NOK: An error occurred during the operation.
 *      Status_OK: The priority grouping was successfully set.
 *      Status_Null_Pointer: The input pointer is null.
 *      Status_Invalid_Input: The input priority grouping value is invalid.
 */
Ret_errorStatuse NVIC_SetPriorityGrouping(u32 priority_grouping);


#endif
