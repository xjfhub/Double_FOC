/*
 * @Author: xjf
 * @brief: FOC控制所需的数学运算
 * @Date: 2021-07-17 18:04:20
 * @Version: 
 */
#include "foc_math.h"

float (*msine)(float, float);
float (*mcosine)(float, float);

/**
 * @brief: 把极坐标转化为三相基底表示
 *          无极控制只用到这一个坐标变换
 * @param {polar_typedef} polar
 * @param {triphase_typedef} basis
 * @return {*}
 */
triphase_typedef polar_to_triphase(float amplitude, float phase)
{
    triphase_typedef basis;
    basis.A = mcosine(amplitude, phase+PHASE_A);
    basis.B = mcosine(amplitude, phase+PHASE_B);
    basis.C = mcosine(amplitude, phase+PHASE_C);
    return basis;
}
