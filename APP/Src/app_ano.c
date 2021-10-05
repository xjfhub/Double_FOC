/**
 * @file app_ano.c
 * @author xjf (2545500530@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "app_ano.h"
#include "usart.h"

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

void ano_send(float *data, uint8_t num)
{
    uint8_t data_to_send[128];	//发送数据缓存
    uint8_t _cnt = 0;           
    uint8_t sum = 0;
    uint8_t i;

    /* 帧头 */
    data_to_send[_cnt++] = 0xAA;
    data_to_send[_cnt++] = 0xAA;
    /* 功能帧 */
    data_to_send[_cnt++] = 0xF1;
    /* 长度 */
    data_to_send[_cnt++] = num*4;
    /* 有效数据 */
    for(i=0; i<num; i++)
    {
        data_to_send[_cnt++] = BYTE3(data[i]);
        data_to_send[_cnt++] = BYTE2(data[i]);
        data_to_send[_cnt++] = BYTE1(data[i]);
        data_to_send[_cnt++] = BYTE0(data[i]);
    }
    for(i=0; i<num*4+4; i++)
    {
        sum += data_to_send[i];
    }
    data_to_send[_cnt++] = sum;

    HAL_UART_Transmit(&huart2, (uint8_t *)data_to_send, num*4+5, 0xFFFF);
}
