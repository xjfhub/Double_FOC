/**
 * @file app_cordic.c
 * @author xjf (2545500530@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "app_cordic.h"
#include "cordic.h"

// void cordic_set(uint32_t Function, 
//                 uint32_t Size, 
//                 uint32_t OutSize, 
//                 uint32_t NbWrite, 
//                 uint32_t NbRead, 
//                 uint32_t Precision)
void cordic_set(void)
{
    CORDIC_ConfigTypeDef CORDIC_ConfigStruct = {0};

    CORDIC_ConfigStruct.Function = CORDIC_FUNCTION_COSINE;
    CORDIC_ConfigStruct.Scale = CORDIC_SCALE_0;
    CORDIC_ConfigStruct.InSize = CORDIC_INSIZE_16BITS;
    CORDIC_ConfigStruct.OutSize = CORDIC_OUTSIZE_16BITS;
    CORDIC_ConfigStruct.NbWrite = CORDIC_NBREAD_1;
    CORDIC_ConfigStruct.NbRead = CORDIC_NBWRITE_1;
    CORDIC_ConfigStruct.Precision = CORDIC_PRECISION_3CYCLES;
    
    HAL_CORDIC_Configure(&hcordic, &CORDIC_ConfigStruct);
}

float cordic_cosine_f32(float modulus, float phase)
{
    uint32_t InBuff;
    uint32_t OutBuff;

    InBuff = ( ((int32_t)(modulus*32768.0))<<16 ) | ((int32_t)(phase*10430.38));

    WRITE_REG(hcordic.Instance->WDATA, InBuff);
    OutBuff = (int32_t)READ_REG(hcordic.Instance->RDATA);

    return ((int16_t)(OutBuff&0x0000FFFF))/32768.0;
}
