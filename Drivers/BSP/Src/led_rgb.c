/**
 * @file led_rgb.c
 * @author xjf (2545500530@qq.com)
 * @brief TX1812驱动程序
 *          信号类型：归零码
 *          信号时间：1,600ns; 0,300ns;
 *          信号格式：GRB888
 * @version 0.1
 * @date 2021-07-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "led_rgb.h"


void led_set(int32_t *adc)
{
    int8_t i;
    color_typedef led1, led2;

	led1.G = (adc[0]>2048)?((adc[0]-2048)/256):0;
	led1.R = (adc[1]>2048)?((adc[1]-2048)/256):0;
	led1.B = (adc[2]>2048)?((adc[2]-2048)/256):0;
	led2.G = (adc[3]>2048)?((adc[3]-2048)/256):0;
	led2.R = (adc[4]>2048)?((adc[4]-2048)/256):0;
	led2.B = (adc[5]>2048)?((adc[5]-2048)/256):0;

    for(i=7; i>=0; i--)
    {
        HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_SET);
        if((led1.G>>i)&0x01)
        {
            HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_RESET);
        }
        HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_RESET);
    }
    for(i=7; i>=0; i--)
    {
        HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_SET);
        if((led1.R>>i)&0x01)
        {
            HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_RESET);
        }
        HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_RESET);
    }
    for(i=7; i>=0; i--)
    {
        HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_SET);
        if((led1.B>>i)&0x01)
        {
            HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_RESET);
        }
        HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_RESET);
    }
    for(i=7; i>=0; i--)
    {
        HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_SET);
        if((led2.G>>i)&0x01)
        {
            HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_RESET);
        }
        HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_RESET);
    }
    for(i=7; i>=0; i--)
    {
        HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_SET);
        if((led2.R>>i)&0x01)
        {
            HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_RESET);
        }
        HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_RESET);
    }
    for(i=7; i>=0; i--)
    {
        HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_SET);
        if((led2.B>>i)&0x01)
        {
            HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_RESET);
        }
        HAL_GPIO_WritePin(LED_RZ_GPIO_Port, LED_RZ_Pin, GPIO_PIN_RESET);
    }

}
