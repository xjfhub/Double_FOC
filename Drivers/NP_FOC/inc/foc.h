/*
 * @Author: xjf
 * @brief: Do not edit
 * @Date: 2021-07-16 15:58:41
 * @Version: 
 */

#ifndef NP_FOC_H
#define NP_FOC_H
#include "foc_config.h"
#include "foc_math.h"
#include "foc_pid.h"

/* NP_FOC控制输入量 */
typedef struct
{
	int mode;	  //工作模式
	float angle;  //输入角度	电机输出轴角度	单位：弧度
	float speed;  //输入速度	电机输出轴转速	单位：弧度每秒	不是rpm
	float torque; //输入扭矩	电机输出扭矩	单位：Nm
} input_typedef;

/* 运动状态 */
typedef struct
{
	int cnt;	//编码器值
	float angle;	//输出轴角度
	float speed;	//角速度
	float phase;	//相位
} motion_state_typedef;
/* NP_FOC控制反馈量 */
typedef struct
{
	motion_state_typedef motion_state;	//运动状态
	triphase_typedef current; //反馈电流
} feedback_typedef;

/* NP_FOC控制输出量 */
typedef struct
{
	triphase_typedef pwm; //输出PWM
} output_typedef;

/* 电机相关参数 */
typedef struct
{
	int pole_num;	//电机极对数
	int kv;			//电机kv值
	float voltage;	//额定电压
	float current;	//额定电流
	float resistor; //相电阻
	float inductor; //相电感
	float inertia;	//转子转动惯量
} motor_typedef;

/* 编码器相关参数 */
typedef struct
{
	int resolution; //分辨率
	/* 电机安装方向
		定义为电机轴向旋转一周
		编码器旋转周数 */
	int direction;	
	/* 偏置 = 电机转到零点时的读取值 */
	int bias; 
} encoder_typedef;

/**
 * @brief FOC控制变量，参数如无特殊说明，默认采用国际标准单位
 * 			一个结构体包含了一路电机控制所需要的所有参数
 */
typedef struct
{
	/* 电机参数 */
	motor_typedef motor;
	/* 编码器参数 */
	encoder_typedef encoder;
	/* 输入信号 */
	input_typedef input;
	/* 反馈信号 */
	feedback_typedef feedback;
	/* NP_FOC控制PID参数 */
	triphase_PID_typedef 	PID_current; //电流环PID
	PID_typedef 			PID_speed;	 //速度环PID
	PID_typedef 			PID_phase;	 //角度环PID
	/* NP_FOC控制中间量 */
	float expect_phase;			  //期望相位
	float expect_speed;			  //期望速度
	float expect_torque;		  //期望力矩
	triphase_typedef expect_current; //期望电流
	triphase_typedef expect_voltage; //期望电压
	triphase_typedef output_pwm;
} NP_FOC_typedef;

/* 控制模式 */
enum MODE
{
	OPEN_LOOP = 0, //开环控制
	TORQUE_MODE,   //扭矩控制
	SPEED_MODE,	   //速度控制
	ANGLE_MODE,	   //角度控制
	POWER_MODE	   //功率控制
};

void foc_control(int mode, float set, NP_FOC_typedef *np);

#endif
