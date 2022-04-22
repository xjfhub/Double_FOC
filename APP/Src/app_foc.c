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
 * @param amplitude 模长
 * @param angle 模相位
 * @return float 模的投影
 */
float projection(float amplitude, float angle)
{
    return amplitude*arm_cos_f32(angle);
}
/**
 * @brief
 *
 */
void np_foc_init(NP_FOC_typedef *np1, NP_FOC_typedef *np2)
{
    mcosine = projection;
    /* 电流环参数 */
    np1->PID_current.kp = 200;
    np1->PID_current.ki = 200;
    np1->PID_current.kd = 0;
    np1->PID_current.dt = 0.0001;
    np1->PID_current.out_max =  1.8;
    np1->PID_current.out_min = -1.8;

    np2->PID_current.kp = 200;
    np2->PID_current.ki = 200;
    np2->PID_current.kd = 0;
    np2->PID_current.dt = 0.0001;
    np2->PID_current.out_max =  1.8;
    np2->PID_current.out_min = -1.8;
    /* 速度环参数 */
    np1->PID_speed.kp = 200;
    np1->PID_speed.ki = 0;
    np1->PID_speed.kd = 0;
    np1->PID_speed.dt = 0.0001;
    np1->PID_speed.out_max =  1.8;
    np1->PID_speed.out_min = -1.8;

    np2->PID_speed.kp = 200;
    np2->PID_speed.ki = 0;
    np2->PID_speed.kd = 0;
    np2->PID_speed.dt = 0.0001;
    np2->PID_speed.out_max =  1.8;
    np2->PID_speed.out_min = -1.8;
    /* 位置环参数 */
    np1->PID_phase.kp = 5;
    np1->PID_phase.ki = 50;
    np1->PID_phase.kd = 0;
    np1->PID_phase.dt = 0.0001;
    np1->PID_phase.out_max =  1.8;
    np1->PID_phase.out_min = -1.8;

    np2->PID_phase.kp = 5;
    np2->PID_phase.ki = 50;
    np2->PID_phase.kd = 0;
    np2->PID_phase.dt = 0.0001;
    np2->PID_phase.out_max =  1.8;
    np2->PID_phase.out_min = -1.8;
}
/**
 * @brief 获取磁编码器数据
 * 
 * @param cnt 
 */
void get_magnetic_encoder(int* cnt1, int* cnt2)
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
 * @brief 获取相电流,并进行差分和取模运算
 * 
 */
void get_phase_current(int32_t adc[], triphase_typedef *current1, triphase_typedef *current2)
{
    current1->A = (adc[0]*2 - adc[1] - adc[2])*3.2/6144;
    current1->B = (adc[1]*2 - adc[2] - adc[0])*3.2/6144;
    current1->C = (adc[2]*2 - adc[0] - adc[1])*3.2/6144;
//    arm_sqrt_f32(	(current1->A*current1->A
//                 	 +current1->B*current1->B
//					 +current1->C*current1->C)*2/3,
//    					&current1->modulus);
    current2->A = (adc[3]*2 - adc[4] - adc[5])*3.2/6144;
    current2->B = (adc[4]*2 - adc[5] - adc[3])*3.2/6144;
    current2->C = (adc[5]*2 - adc[3] - adc[4])*3.2/6144;
//    arm_sqrt_f32(	(current2->A*current2->A
//				 	 +current2->B*current2->B
//					 +current2->C*current2->C)*2/3,
//						&current2->modulus);
}
/**
 * 获取反馈量
 */
void get_feedback(int32_t adc[], feedback_typedef *fb1, feedback_typedef *fb2)
{
	static int cnt1_last, cnt2_last;
	static float speed1_last, speed2_last;

	/* 读取相电流和编码器数据 */
	get_phase_current(adc, &fb1->current, &fb2->current);
	get_magnetic_encoder(&fb1->motion_state.cnt, &fb2->motion_state.cnt);
	/* 计算电机机械角度，电角度，和角速度*/
	fb1->motion_state.angle = fb1->motion_state.cnt/16384.0*6.28;
	fb1->motion_state.phase = (fb1->motion_state.cnt%4096)/4096.0*6.28;
	fb1->motion_state.speed += ( ( ((int)(fb1->motion_state.cnt + 24576- cnt1_last)%16384 - 8192)/16384.0*(6.28/0.0001) )
								-speed1_last) /128;
	cnt1_last = fb1->motion_state.cnt;
	speed1_last = fb1->motion_state.speed;
//	fb1->motion_state.speed = (fb1->motion_state.angle - angle1_last)/0.0001;

	fb2->motion_state.angle = fb2->motion_state.cnt/16384.0*6.28;
	fb2->motion_state.phase = (fb2->motion_state.cnt%4096)/4096.0*6.28;
	fb2->motion_state.speed += ( ( ((int)(fb2->motion_state.cnt + 24576- cnt2_last)%16384 - 8192)/16384.0*(6.28/0.0001) )
								-speed2_last) /128;
	cnt2_last = fb2->motion_state.cnt;
	speed2_last = fb2->motion_state.speed;
//	fb2->motion_state.speed = (fb2->motion_state.angle - angle2_last)/0.0001;
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

