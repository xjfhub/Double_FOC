/**
 * @file foc_config.h
 * @author xjf (2545500530@qq.com)
 * @brief 参数配置头文件，所有驱动电路(软件&硬件)相关的参数均由宏定义配置
 *          电机，编码器相关的参数包含在控制结构体中
 * @version 0.1
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef FOC_CONFIG_H
#define FOC_CONFIG_H

/* 控制参数 */
#define SYS_CLK_FREQ 160000000                   //系统时钟频率
#define CONTROL_FREQ 10000                       //控制频率
#define SVPWM_FREQ 10000                         //SVPWM频率
#define PWM_DUTY_MIN 0.1f                        //PWM占空比最小值
#define PWM_DUTY_MAX 0.9f                        //PWM占空比最大值
#define PWM_WIDTH (SYS_CLK_FREQ / SVPWM_FREQ)    //PWM宽度
#define PWM_WIDTH_MIN (PWM_DUTY_MIN * PWM_WIDTH) //PWM最小宽度
#define PWM_WIDTH_MAX (PWM_DUTY_MAX * PWM_WIDTH) //PWM最大宽度
#define DEAD_WIDTH 32                            //死区宽度
#define BUS_VOLTAGE_MAX 24.0f                    //母线电压最大值
#define BUS_VOLTAGE_MIN 5.0f                     //母线电压最小值

/* 采样参数 */
#define ADC_VREF 3.3f
#define ADC_MAX 4096 //ADC采样最大值
#define SAMPLE_RESISTOR 0.01f
#define AMPLIFY 50

#endif

