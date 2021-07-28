/*
 * @Author: xjf
 * @brief: Do not edit
 * @Date: 2021-07-16 15:58:41
 * @Version: 
 */

#ifndef NP_FOC_H
#define NP_FOC_H
#include "foc_config.h"
#include "np_foc_pid.h"
#include "np_foc_math.h"

/* FOC控制变量，默认采用国际标准单位 */
typedef struct
{
	/* NP_FOC控制输入量 */
	unsigned char mode;	//工作模式
	float input_angle;	//输入角度	电机输出轴角度	单位：弧度
	float input_speed;	//输入速度	电机输出轴转速	单位：弧度每秒	不是rpm
	float input_torque;	//输入扭矩	电机输出扭矩	单位：Nm
	/* NP_FOC控制反馈量 */
	float feedback_phase;	//电角度	标量	范围：0-2π
	basis_typedef feedback_current; //反馈电流
	/* NP_FOC控制PID参数 */
	PID_typedef PID_current_A;	//A相电流环PID
	PID_typedef PID_current_B;	//B相电流环PID
	PID_typedef PID_current_C;	//C相电流环PID
	PID_typedef PID_speed;		//速度环PID
	PID_typedef PID_phase;		//角度环PID
	/* NP_FOC控制中间量 */
	float expect_phase;	//期望相位
	float expect_speed;	//期望速度
	float expect_torque;	//期望力矩
	basis_typedef expect_current;	//期望电流
	basis_typedef expect_voltage;	//期望电压
	/* NP_FOC控制输出量 */
	basis_typedef output_pwm;	//输出电压
	/* 需要驱动层提供的接口函数 */
} NP_FOC_typedef;

/* 控制模式 */
enum MODE{OPEN_LOOP, TORQUE_MODE, SPEED_MODE, ANGLE_MODE, POWER_MODE};
extern void (*collect_current)(basis_typedef *current);	//采集电流
extern void (*collect_phase)(float *phase);				//采集相位
extern void (*svpwm_out)(basis_typedef *pwm);			//SVPWM输出

#endif
