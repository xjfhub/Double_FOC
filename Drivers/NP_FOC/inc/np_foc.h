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

/* NP_FOC控制输入量 */
typedef struct
{
	int mode;	  //工作模式
	float angle;  //输入角度	电机输出轴角度	单位：弧度
	float speed;  //输入速度	电机输出轴转速	单位：弧度每秒	不是rpm
	float torque; //输入扭矩	电机输出扭矩	单位：Nm
} input_typedef;

/* NP_FOC控制反馈量 */
typedef struct
{
	int encoder_cnt;
	float angle;		   //角度	范围：0-2π
	float speed;		   //角速度
	float phase;		   //电角度	范围：0-2π
	int adc[3];
	basis_typedef current; //反馈电流
} feedback_typedef;

/* NP_FOC控制输出量 */
typedef struct
{
	basis_typedef pwm; //输出PWM
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
	int resolution; //分辨率 = 2^编码器位数
	int direction;	//安装方向
		//电机正转一圈 编码器旋转的圈数
		//正值为正转 负值为反转
	int bias; //偏置值 应由读取值减去偏置再计算角度
} encoder_typedef;

/**
 * @brief FOC控制变量，默认采用国际标准单位
 * 电机和编码器参数单独设置，可支持不同电机
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
	PID_typedef PID_current_A; //A相电流环PID
	PID_typedef PID_current_B; //B相电流环PID
	PID_typedef PID_current_C; //C相电流环PID
	PID_typedef PID_speed;	   //速度环PID
	PID_typedef PID_phase;	   //角度环PID
	/* NP_FOC控制中间量 */
	float expect_phase;			  //期望相位
	float expect_speed;			  //期望速度
	float expect_torque;		  //期望力矩
	basis_typedef expect_current; //期望电流
	basis_typedef expect_voltage; //期望电压
	output_typedef output;

	void (*collect_current)(basis_typedef*); //采集电流
	void (*collect_phase)(float*);			 //采集相位
	void (*collect_speed)(float*);			 //采集相位
	void (*svpwm_out)(output_typedef);			 //SVPWM输出
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
extern NP_FOC_typedef np1;
extern NP_FOC_typedef np2;

#endif
