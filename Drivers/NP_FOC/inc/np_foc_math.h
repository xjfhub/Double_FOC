/*
 * @Author: xjf
 * @brief: Do not edit
 * @Date: 2021-07-17 18:05:46
 * @Version: foc相关数学算法头文件
 */
#ifndef NP_FOC_MATH_H
#define NP_FOC_MATH_H

#ifndef NULL
    #define NULL 0
#endif

#ifndef PI
    #define PI 3.1415926f
#endif
#define PHASE_A (PI*0/3)
#define PHASE_B (PI*2/3)
#define PHASE_C (PI*4/3)

/* 相位基量表示法 */
typedef struct
{
	float A; //0
	float B; //2π/3
	float C; //4π/3
} basis_typedef;

/* 角度表示法 */
typedef struct
{
	float modulus;
	float phase;
} polar_typedef;

extern float (*msine)(float modulus, float phase);			//正弦函数
extern float (*mcosine)(float modulus, float phase);		//余弦函数

basis_typedef polar_to_basis(float modulus, float phase);

#endif
