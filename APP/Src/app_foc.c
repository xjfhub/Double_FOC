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
	return 0;
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
	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3, output1.A);
	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2, output1.B);
	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, output1.C);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, output2.A);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, output2.B);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, output2.C);
}
/**
 * @brief 
 * 
 */
void np_foc_init(NP_FOC_typedef *np1, NP_FOC_typedef *np2)
{
    mcosine = projection;
    /* 电流环参数 */
    np1->PID_current.kp = 20;
    np1->PID_current.ki = 2;
    np1->PID_current.kd = 0;
    np1->PID_current.dt = 0.01;
    np1->PID_current.out_max =  1.8;
    np1->PID_current.out_min = -1.8;
}


