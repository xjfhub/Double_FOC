/**
 * @file np_foc_pid.c
 * @author xjf (2545500530@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "np_foc_pid.h"

/**
 * @brief 
 * 
 * @param input 
 * @param feedback 
 * @param PID 
 * @return float 
 */
float np_foc_pid(float input, float feedback, PID_typedef *PID)
{
    /* PID输入 */
    PID->input = input;
    PID->feedback = feedback;
    /* 记录最近两次的误差值，用于微分运算 */
    PID->err_last_last  = PID->err_last;
    PID->err_last       = PID->err;
    PID->err            = PID->input - PID->feedback;
    
    PID->output = PID->output 
                + PID->ki*(PID->err*PID->dt)*   \
                    (   (PID->err>0)?  \
                        ((PID->out_max-PID->output)/(PID->out_max-PID->out_min)):   \
                        ((PID->output-PID->out_min)/(PID->out_max-PID->out_min))    );
                + PID->kp*(PID->err - PID->err_last) 
                + PID->kd*((PID->err - 2*PID->err_last + PID->err_last_last)/PID->dt);
    PID->output = LIMIT(PID->output, PID->out_min, PID->out_max);
    /* PID输出 */
    return PID->output;
}
