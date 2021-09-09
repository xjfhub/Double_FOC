/**
 * @file encoder.h
 * @author xjf (2545500530@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef ENCODER_H
#define ENCODER_H
#include "main.h"

typedef struct 
{
    GPIO_TypeDef ssck_gpio;
    uint16_t ssck_pin;
    GPIO_TypeDef ssd_gpio;
    uint16_t ssd_pin;
}ssi_typedef;


#endif