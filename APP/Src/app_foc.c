/**
 * @file app_foc.c
 * @author xjf (2545500530@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "app_foc.h"
#include "spi.h"
#include "arm_math.h"
#include "tim.h"

/* 定义两个电机对象 */
NP_FOC_typedef np1;
NP_FOC_typedef np2;

/**
 * @brief 取模的投影函数
 * 
 * @param modulus 模长
 * @param angle 模相位
 * @return float 模的投影
 */
float projection(float modulus, float angle)
{
    return modulus*arm_cos_f32(angle);
}
/**
 * @brief 获取磁编码器数据
 * 
 * @param cnt 
 */
void get_magnetic_encoder(unsigned int* cnt1, unsigned int* cnt2)
{
    int data1, data2;
    uint8_t spi_data1[2], spi_data2[2];

    data1 = 0x3fff;
    data2 = 0x3fff;
    HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&data1, spi_data1, 1, 0xffff);
    HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_SET);
    *cnt1 = ((spi_data1[1] & 0x3f) << 8) | spi_data1[0];

    HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&data2, spi_data2, 1, 0xffff);
    HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_SET);
    *cnt2 = ((spi_data2[1] & 0x3f) << 8) | spi_data2[0];

//    int i;
//    *cnt1 = 0;
//    *cnt2 = 0;
//    HAL_GPIO_WritePin(SSCK_GPIO_Port, SSCK_Pin, GPIO_PIN_SET);
//    HAL_GPIO_WritePin(SSCK_GPIO_Port, SSCK_Pin, GPIO_PIN_RESET);
//
//    for (i = 0; i < 16; i++)
//    {
//        HAL_GPIO_WritePin(SSCK_GPIO_Port, SSCK_Pin, GPIO_PIN_SET);
//        HAL_GPIO_WritePin(SSCK_GPIO_Port, SSCK_Pin, GPIO_PIN_RESET);
//        *cnt1 |= HAL_GPIO_ReadPin(SSD1_GPIO_Port, SSD1_Pin) << (15-i);
//        *cnt2 |= HAL_GPIO_ReadPin(SSD2_GPIO_Port, SSD2_Pin) << (15-i);
//    }
}
/**
 * @brief 计算角度
 * 
 * @param cnt 
 * @return float 
 */
float calculator_angle(int cnt)
{
    ;
}
/**
 * @brief 计算速度
 * 
 * @param cnt 
 * @return float 
 */
float calculator_speed(int cnt)
{
    ;
}
/**
 * @brief 获取相电流
 * 
 */
void get_phase_current(int32_t adc[], triphase_typedef *current1, triphase_typedef *current2)
{
    current1->A = (adc[0]*2 - adc[1] - adc[2])*3.2/4096;
    current1->B = (adc[1]*2 - adc[2] - adc[0])*3.2/4096;
    current1->C = (adc[2]*2 - adc[0] - adc[1])*3.2/4096;
    current2->A = (adc[3]*2 - adc[4] - adc[5])*3.2/4096;
    current2->B = (adc[4]*2 - adc[5] - adc[3])*3.2/4096;
    current2->C = (adc[5]*2 - adc[3] - adc[4])*3.2/4096;
}
/**
 * @brief 
 * 
 * @param htim 
 * @param basis 
 */
void pwm_output(triphase_typedef output1,  triphase_typedef output2)
{
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, output1.A);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, output1.B);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, output1.C);
	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, output2.A);
	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2, output2.B);
	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3, output2.C);
}
/**
 * @brief 
 * 
 */
void np_foc_init(NP_FOC_typedef *np1, NP_FOC_typedef *np2)
{
    mcosine = projection;
    /* 电流环参数 */
    np1->PID_current.kp = 30;
    np1->PID_current.ki = 30;
    np1->PID_current.kd = 0;
    np1->PID_current.dt = 0.0001;
    np1->PID_current.out_max =  1.8;
    np1->PID_current.out_min = -1.8;

    np2->PID_current.kp = 30;
    np2->PID_current.ki = 30;
    np2->PID_current.kd = 0;
    np2->PID_current.dt = 0.0001;
    np2->PID_current.out_max =  1.8;
    np2->PID_current.out_min = -1.8;
}


