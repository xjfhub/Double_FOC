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
#include "foc_pid.h"

/**
 * @brief 增量式pid
 * 
 * @param input 
 * @param feedback 
 * @param PID 
 * @return float 
 */
float pid(float input, float feedback, PID_typedef *PID)
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
                        ((PID->output-PID->out_min)/(PID->out_max-PID->out_min))    )
                + PID->kp*(PID->err - PID->err_last) 
                + PID->kd*((PID->err - 2*PID->err_last + PID->err_last_last)/PID->dt);
    PID->output = LIMIT(PID->output, PID->out_min, PID->out_max);
    /* PID输出 */
    return PID->output;
}
/**
 * @brief 三相PID函数
 * 
 * @param input 
 * @param feedback 
 * @param PID 
 * @return triphase_typedef 
 */
triphase_typedef triphase_pid(triphase_typedef input, triphase_typedef feedback, triphase_PID_typedef *PID)
{
    float bias;
    /* PID输入 */
    PID->input = input;
    PID->feedback = feedback;
    /* 记录最近两次的误差值，用于微分运算 */
    PID->err_last_last  = PID->err_last;
    PID->err_last       = PID->err;
    PID->err.A            = PID->input.A - PID->feedback.A;
    PID->err.B            = PID->input.B - PID->feedback.B;
    PID->err.C            = PID->input.C - PID->feedback.C;
    
    PID->output.A = PID->output.A 
                + PID->ki*(PID->err.A*PID->dt)*   \
                    (   (PID->err.A>0)?  \
                        ((PID->out_max-PID->output.A)/(PID->out_max-PID->out_min)):   \
                        ((PID->output.A-PID->out_min)/(PID->out_max-PID->out_min))    );
                + PID->kp*(PID->err.A - PID->err_last.A) 
                + PID->kd*((PID->err.A - 2*PID->err_last.A + PID->err_last_last.A)/PID->dt);
    PID->output.B = PID->output.B 
                + PID->ki*(PID->err.B*PID->dt)*   \
                    (   (PID->err.B>0)?  \
                        ((PID->out_max-PID->output.B)/(PID->out_max-PID->out_min)):   \
                        ((PID->output.B-PID->out_min)/(PID->out_max-PID->out_min))    );
                + PID->kp*(PID->err.B - PID->err_last.B) 
                + PID->kd*((PID->err.B - 2*PID->err_last.B + PID->err_last_last.B)/PID->dt);
    PID->output.C = PID->output.C 
                + PID->ki*(PID->err.C*PID->dt)*   \
                    (   (PID->err.C>0)?  \
                        ((PID->out_max-PID->output.C)/(PID->out_max-PID->out_min)):   \
                        ((PID->output.C-PID->out_min)/(PID->out_max-PID->out_min))    );
                + PID->kp*(PID->err.C - PID->err_last.C) 
                + PID->kd*((PID->err.C - 2*PID->err_last.C + PID->err_last_last.C)/PID->dt);
    /* 计算共模干扰 */
    bias = (PID->output.A + PID->output.B + PID->output.C)/3;
    /* 消除共模干扰并限幅 */
    PID->output.A = LIMIT(PID->output.A-bias, PID->out_min, PID->out_max);
    PID->output.B = LIMIT(PID->output.B-bias, PID->out_min, PID->out_max);
    PID->output.C = LIMIT(PID->output.C-bias, PID->out_min, PID->out_max);
    /* PID输出 */
    return PID->output;
}
