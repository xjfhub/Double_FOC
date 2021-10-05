/**
 * @file led_rgb.h
 * @author xjf (2545500530@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef LED_RGB_H
#define LED_RGB_H
#include "main.h"

typedef struct 
{
    uint8_t G;
    uint8_t R;
    uint8_t B;
}color_typedef;
void led_set(int32_t *adc);

#endif
