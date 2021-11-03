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
/**
 * @brief 获取磁编码器数据
 * 
 * @param cnt 
 */
void get_magnetic_encoder(unsigned int* cnt1, unsigned int* cnt2)
{
    int data1, data2;
    uint8_t spi_data1[2], spi_data2[2];

    data1 = 0x3fff;	//寄存器地址
    data2 = 0x3fff;	//寄存器地址

    HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&data1, spi_data1, 1, 0xffff);
    HAL_GPIO_WritePin(CS1_GPIO_Port, CS1_Pin, GPIO_PIN_SET);
    *cnt1 = ((((spi_data1[1] & 0x3f) << 8) | spi_data1[0]) + 0)%16284;

    HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&data2, spi_data2, 1, 0xffff);
    HAL_GPIO_WritePin(CS2_GPIO_Port, CS2_Pin, GPIO_PIN_SET);
    *cnt2 = ((((spi_data2[1] & 0x3f) << 8) | spi_data2[0]) + 7226)%16284;
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
 * 获取反馈量
 */
void get_feedback(int32_t adc[], feedback_typedef *fb1, feedback_typedef *fb2)
{
	static angle1_last, angle2_last;
	static speed1_last, speed2_last;

	get_phase_current(adc, &fb1->current, &fb2->current);
	get_magnetic_encoder(&fb1->motion_state.cnt, &fb2->motion_state.cnt);

	angle1_last = fb1->motion_state.angle;
	speed1_last = fb1->motion_state.speed;
	fb1->motion_state.angle = fb1->motion_state.cnt/16384.0*6.28;
	fb1->motion_state.phase = (fb1->motion_state.cnt%4096)/4096.0*6.28;
	fb1->motion_state.speed += (((fb1->motion_state.angle - angle1_last)/0.0001)-speed1_last)/1;

	angle2_last = fb2->motion_state.angle;
	speed2_last = fb2->motion_state.speed;
	fb2->motion_state.angle = fb2->motion_state.cnt/16384.0*6.28;
	fb2->motion_state.phase = (fb2->motion_state.cnt%4096)/4096.0*6.28;
	fb2->motion_state.speed += (((fb2->motion_state.angle - angle2_last)/0.0001)-speed2_last)/1;
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

