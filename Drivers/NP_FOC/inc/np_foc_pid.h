/**
 * @file np_foc_pid.h
 * @author xjf (2545500530@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef NP_FOC_PID_H
#define NP_FOC_PID_H

/* 宏函数限幅 */
#define LIMIT(input,min,max)    input>min?(input<max?input:max):min  
/* 单输入单输出PID控制结构体 */
typedef struct
{
    float input;         //输入值
    float feedback;      //反馈值
    float err;           //误差
    float err_last;      //上次误差
    float err_last_last; //上上次误差
    float output;        //输出值
    float dt;            //控制时间
    float kp;            //P参数
    float ki;            //I参数
    float kd;            //D参数
    float out_min;       //输出最小值
    float out_max;       //输出最大值
} PID_typedef;

float np_foc_pid(float input, float feedback, PID_typedef *PID);

#endif