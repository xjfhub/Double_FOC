/*
 * @Description: 
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-07-01 00:20:40
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-03 01:02:15
 */
#include "app_input.h"

#define QUADRUPLE 0 //AB上升下降都采集 四倍频

key_typedef g_key;          //按键结构体
pulley_typedef g_pulley;    //滚轮结构体

/**
 * @brief 输入端口初始化
 * 
 */
void input_init(void)
{
    g_key.port = KEY_EN_GPIO_Port;
    g_key.pin = KEY_EN_Pin;
    g_pulley.port_a = ENC_A_GPIO_Port;
    g_pulley.pin_a = ENC_A_Pin;
    g_pulley.port_b = ENC_B_GPIO_Port;
    g_pulley.pin_b = ENC_B_Pin;
    g_pulley.cnt_max = 10;
}
/**
 * @description: 获取按键状态
 * @param {KEY} num  按键序号 一共四个按键
 * @return {*}按键状态，长按时间，间隔时间
 */
void get_key(key_typedef *key)
{
    //更新按键状态
    key->last_state = key->state;

    key->state = !HAL_GPIO_ReadPin(key->port, key->pin);
    //储存按键状态
    key->state = (key->last_state<<1) | key->state;
    switch (key->state)
    {
        case PRESS:         //按下
        {
            key->last_press_time = key->press_time;     //记录上次按下时间
            key->press_time = HAL_GetTick();            //更新本次按下时间
            key->continual_time = 0;                     //开始计算长按时间
            key->gap_time = key->press_time - key->last_press_time;  //计算两次按下间隔时间
            break;
        }
        case ON:            //打开
        {
            key->continual_time = HAL_GetTick() - key->press_time;
            break;
        }
        case RELEASE:       //释放
        {
            break;
        }
        case OFF:           //关闭
        {
            break;
        }
        default:
        {
            break;
        }
    }
}
/**
 * @brief Get the pulley object
 * 
 * @param pulley 
 */
void get_pulley(pulley_typedef *pulley) 
{
    pulley->last_state_a = pulley->state_a;
    pulley->last_state_b = pulley->state_b;

    pulley->state_a = HAL_GPIO_ReadPin(pulley->port_a, pulley->pin_a);
    pulley->state_b = HAL_GPIO_ReadPin(pulley->port_b, pulley->pin_b);

    if((pulley->state_a == GPIO_PIN_RESET) && (pulley->state_b == GPIO_PIN_RESET))
    {
        if ((pulley->last_state_a == GPIO_PIN_RESET) && (pulley->last_state_b == GPIO_PIN_SET))
        {
            pulley->direction = MINUS;
            pulley->cnt = (pulley->cnt + pulley->cnt_max + pulley->direction)%pulley->cnt_max;
        }
        if ((pulley->last_state_a == GPIO_PIN_SET) && (pulley->last_state_b == GPIO_PIN_RESET))
        {
            pulley->direction = PLUS;
            pulley->cnt = (pulley->cnt + pulley->cnt_max + pulley->direction)%pulley->cnt_max;
        }
    }
}
