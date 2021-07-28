/**
 * @file np_foc.c
 * @author xjf (2545500530@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "np_foc.h"

/**
 * @brief 
 * 
 * @param np 
 */
void np_foc_control(NP_FOC_typedef *np)
{
    /** 获取转子相位
     *  注意：非电机输出轴的角度，需考虑电机极对数
     */
    collect_phase(&(np->feedback_phase));
    /* 获取相电流 */
    collect_current(&(np->feedback_current));
    /* 根据控制模式控制 */
    switch (np->mode)
    {
    /* 开环控制模式，直接控制电流为最大相电流 */
    case OPEN_LOOP:     
    {
        np->expect_current.A = mcosine(PHASE_CURRENT_MAX, np->expect_phase+PHASE_A);
        np->expect_current.B = mcosine(PHASE_CURRENT_MAX, np->expect_phase+PHASE_B);
        np->expect_current.C = mcosine(PHASE_CURRENT_MAX, np->expect_phase+PHASE_C);
        np->expect_voltage.A = np_foc_pid(np->expect_current.A, np->feedback_current.A, &(np->PID_current_A));
        np->expect_voltage.B = np_foc_pid(np->expect_current.B, np->feedback_current.B, &(np->PID_current_B));
        np->expect_voltage.C = np_foc_pid(np->expect_current.C, np->feedback_current.C, &(np->PID_current_C));
        break;
    }
    /* 力矩控制模式 */
    case TORQUE_MODE:
    {
        /* 计算期望电流，精确模型需考虑转动惯量、转矩脉动和摩擦力 */
        np->expect_current.A = msine(np->input_torque, np->feedback_phase+PHASE_A);
        np->expect_current.B = msine(np->input_torque, np->feedback_phase+PHASE_B);
        np->expect_current.C = msine(np->input_torque, np->feedback_phase+PHASE_C);
        np->expect_voltage.A = np_foc_pid(np->expect_current.A, np->feedback_current.A, &(np->PID_current_A));
        np->expect_voltage.B = np_foc_pid(np->expect_current.B, np->feedback_current.B, &(np->PID_current_B));
        np->expect_voltage.C = np_foc_pid(np->expect_current.C, np->feedback_current.C, &(np->PID_current_C));
        break;
    }
    /* 速度控制模式 */
    case SPEED_MODE:
    {
        // np->expect_torque = np_foc_pid(np->input_speed, np->feedback_speed, &(np->PID_phase));//补充速度计算函数
        np->expect_current.A = msine(np->expect_torque, np->feedback_phase+PHASE_A);
        np->expect_current.B = msine(np->expect_torque, np->feedback_phase+PHASE_B);
        np->expect_current.C = msine(np->expect_torque, np->feedback_phase+PHASE_C);
        np->expect_voltage.A = np_foc_pid(np->expect_current.A, np->feedback_current.A, &(np->PID_current_A));
        np->expect_voltage.B = np_foc_pid(np->expect_current.B, np->feedback_current.B, &(np->PID_current_B));
        np->expect_voltage.C = np_foc_pid(np->expect_current.C, np->feedback_current.C, &(np->PID_current_C));
        break;
    }
    case ANGLE_MODE:    //角度控制模式
    {
        np->expect_torque = np_foc_pid(np->expect_phase, np->feedback_phase, &(np->PID_phase));
        np->expect_current.A = msine(np->expect_torque, np->feedback_phase+PHASE_A);
        np->expect_current.B = msine(np->expect_torque, np->feedback_phase+PHASE_B);
        np->expect_current.C = msine(np->expect_torque, np->feedback_phase+PHASE_C);
        np->expect_voltage.A = np_foc_pid(np->expect_current.A, np->feedback_current.A, &(np->PID_current_A));
        np->expect_voltage.B = np_foc_pid(np->expect_current.B, np->feedback_current.B, &(np->PID_current_B));
        np->expect_voltage.C = np_foc_pid(np->expect_current.C, np->feedback_current.C, &(np->PID_current_C));
        break;
    }
    case POWER_MODE:    //恒功率控制模式
    {
        break;
    }
    default:            //其它模式
    {
        break;
    }
    }
    svpwm_out(&(np->output_pwm));
}

/**
 * @brief foc控制编码器校准函数
 * 
 */
void np_foc_adjust(NP_FOC_typedef *np)
{

}

/**
 * @brief FOC控制初始化
 * 
 * @param np 
 */
void np_foc_init(NP_FOC_typedef *np)
{

}