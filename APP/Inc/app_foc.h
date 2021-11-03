/**
 * @file app_foc.h
 * @author xjf (2545500530@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef APP_FOC_H
#define APP_FOC_H
#include "main.h"
#include "foc.h"

extern NP_FOC_typedef np1;
extern NP_FOC_typedef np2;

//void get_phase_current(int32_t adc[], triphase_typedef *current1, triphase_typedef *current2);
//void get_magnetic_encoder(unsigned int* cnt1, unsigned int* cnt2);
void np_foc_init(NP_FOC_typedef *np1, NP_FOC_typedef *np2);
void get_feedback(int32_t adc[], feedback_typedef *fb1, feedback_typedef *fb2);
void pwm_output(triphase_typedef output1,  triphase_typedef output2);


#endif
