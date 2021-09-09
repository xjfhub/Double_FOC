/*
 * @Description: 
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-07-01 00:18:44
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-03 00:31:44
 */
#ifndef APP_INPUT_H
#define APP_INPUT_H
#include "main.h"

enum KEY_STATE{OFF, PRESS, RELEASE, ON};
enum PULLEY_STATE{MINUS = -1, IDLE, PLUS};


typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t state;              //按键状态  b00,
    uint8_t last_state;         //上一次按键状态
    uint32_t press_time;        //
    uint32_t last_press_time;   //
    uint32_t continual_time;    //按下持续时间  用来判断长按
    uint32_t gap_time;          //两次按下间隔时间 用来判断连按
}key_typedef;

typedef struct
{
    /* 端口定义 */
    GPIO_TypeDef *port_a;
    uint16_t pin_a;
    GPIO_TypeDef *port_b;
    uint16_t pin_b;
    /* 状态记录 */
    uint8_t state_a;              
    uint8_t last_state_a;         
    uint8_t state_b;              
    uint8_t last_state_b;        
    /* 输出参数 */ 
    uint16_t cnt_max;
    uint16_t cnt;
    int8_t direction;
}pulley_typedef;

extern key_typedef g_key;
extern pulley_typedef g_pulley;

void input_init(void);
void get_key(key_typedef *key);
void get_pulley(pulley_typedef *pulley);

#endif
