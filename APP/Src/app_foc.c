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

/**
 * @brief 取模的投影函数
 * 
 * @param modulus 模长
 * @param phase 模相位
 * @return float 模的投影
 */
float projection(float modulus, float phase)
{
    return modulus*arm_cos_f32(phase);
}
/**
 *
 */
void get_magnetic_encoder(unsigned int* cnt)
{
	return 0;
}
/**
 * @brief 
 * 
 * @param htim 
 * @param basis 
 */
void pwm_output(TIM_HandleTypeDef *htim, output_typedef output)
{
	__HAL_TIM_SetCompare(htim, TIM_CHANNEL_1, output.pwm.A);
	__HAL_TIM_SetCompare(htim, TIM_CHANNEL_2, output.pwm.B);
	__HAL_TIM_SetCompare(htim, TIM_CHANNEL_3, output.pwm.C);
}
/**
 * @brief 
 * 
 */
void np_foc_init(void)
{
    mcosine = projection;
    np_foc_config(&np1);
    np_foc_config(&np2);
}


/** 获取转子相位
 *  注意：非电机输出轴的角度，需考虑电机极对数
 */
//    np->collect_phase(&(np->feedback.phase));
/* 获取相电流 */
//    collect_current(&(np->feedback.current));
//    np->svpwm_out(np->output);
