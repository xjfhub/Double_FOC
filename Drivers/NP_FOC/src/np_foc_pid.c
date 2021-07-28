/*
 * @Author: xjf
 * @brief: Do not edit
 * @Date: 2021-07-19 10:20:37
 * @Version: 
 */
#include "np_foc_pid.h"

float np_foc_pid(float input, float feedback, PID_typedef *PID)
{
    /* PID输入 */
    PID->input = input;
    PID->feedback = feedback;

    PID->err_last_last  = PID->err_last;
    PID->err_last       = PID->err;
    PID->err            = PID->input - PID->feedback;
    
    PID->output = PID->output 
                + PID->ki*(PID->err*PID->dt)
                + PID->kp*(PID->err - PID->err_last) 
                + PID->kd*((PID->err - 2*PID->err_last + PID->err_last_last)/PID->dt);
    PID->output = LIMIT(PID->output, PID->out_min, PID->out_max);
    /* PID输出 */
    return PID->output;
}
