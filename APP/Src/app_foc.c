/**
 * @file app_foc.c
 * @author xjf (2545500530@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "app_foc.h"
#include "arm_math.h"

/**
 * @brief 取模的投影函数
 * 
 * @param modulus 模长
 * @param phase 模相位
 * @return float 模的投影
 */
float projection(float modulus, float phase)
{
    return modulus*arm_cos_f32(phase);
}

/**
 * @brief 初始化电机和控制参数
 *        声明接口变量和函数
 * 
 * @param np 
 */
void np_foc_config(NP_FOC_typedef *des, NP_FOC_typedef )
{
    mcosine = projection;
    ;
}
/**
 * @brief 
 * 
 */
void np_foc_init(void)
{
    mcosine = projection;
    np_foc_config(&np1);
    np_foc_config(&np2);
}