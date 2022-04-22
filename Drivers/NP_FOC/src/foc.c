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
#include "foc.h"
#include "foc_pid.h"


/**
 * @brief 
 * 
 * @param np 
 */
void foc_control(int mode, float set, NP_FOC_typedef *np)
{
    np->input.mode = mode;

    /* 根据控制模式控制 */
    switch (np->input.mode)
    {
    /* 开环控制模式，直接控制电流为最大相电流 */
    case OPEN_LOOP:     
    {
        np->expect_phase = set;
        np->expect_torque = 0.8;
        np->expect_current = polar_to_triphase(np->expect_torque,np->expect_phase);
        break;
    }
    /* 力矩控制模式 */
    case TORQUE_MODE:
    {
        np->expect_torque = set;
        np->expect_phase = np->feedback.motion_state.phase+PI/2;
        np->expect_current = polar_to_triphase(np->expect_torque,np->expect_phase);
        break;
    }
    /* 速度控制模式 */
    case SPEED_MODE:
    {
        np->expect_phase = np->feedback.motion_state.phase+PI/2;
        np->expect_torque = pid(np->input.speed, np->feedback.motion_state.speed, &(np->PID_phase));//补充速度计算函数
        np->expect_current = polar_to_triphase(np->expect_torque,np->expect_phase);
        break;
    }
    case ANGLE_MODE:    //角度控制模式
    {
    	np->input.angle = set;
        np->expect_phase = np->feedback.motion_state.phase+PI/2;
        if((np->input.angle - np->feedback.motion_state.angle) > PI)
        {
        	np->input.angle -= 2*PI;
        }
        if((np->input.angle - np->feedback.motion_state.angle) < -PI)
        {
        	np->input.angle += 2*PI;
        }
        np->expect_torque = pid(np->input.angle, np->feedback.motion_state.angle, &(np->PID_phase));
        np->expect_current = polar_to_triphase(np->expect_torque,np->expect_phase);
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

    np->expect_voltage = triphase_pid(np->expect_current,np->feedback.current,&(np->PID_current));

    np->output_pwm.A = 4000+np->expect_voltage.A*2000;
    np->output_pwm.B = 4000+np->expect_voltage.B*2000;
    np->output_pwm.C = 4000+np->expect_voltage.C*2000;
}
