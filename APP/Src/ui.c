/*
 * @Description: 
 * @Version: 
 * @Autor: Xjf
 * @Date: 2021-06-23 20:53:57
 * @LastEditors: Xjf
 * @LastEditTime: 2021-07-03 00:30:10
 */
#include "ui.h"
#include "lcd.h"
#include "app_input.h"

#define FONT 16

void main_ui(int32_t adc[])
{
	uint8_t str[24] = {0};
    uint8_t line;

    line = 0;
    
    LCD_ShowString(0,(line++)*FONT,"Double FOC",WHITE,BLACK,16,0);

    sprintf(str, "cnt:%5d", g_pulley.cnt);
    LCD_ShowString(0, (line++)*FONT, str, WHITE,BLACK, FONT, 0);

    sprintf(str, "IA1:%5.2fA", (adc[0]-1988.0)*0.0015625);
    LCD_ShowString(0, (line++)*FONT, str, WHITE,BLACK, FONT, 0);

    sprintf(str, "IB1:%5.2fA", (adc[1]-1988.0)*0.0015625);
    LCD_ShowString(0, (line++)*FONT, str, WHITE,BLACK, FONT, 0);

    sprintf(str, "IC1:%5.2fA", (adc[2]-1988.0)*0.0015625);
    LCD_ShowString(0, (line++)*FONT, str, WHITE,BLACK, FONT, 0);

    sprintf(str, "IA2:%5.2fA", (adc[3]-1988.0)*0.0015625);
    LCD_ShowString(0, (line++)*FONT, str, WHITE,BLACK, FONT, 0);

    sprintf(str, "IB2:%5.2fA", (adc[4]-1988.0)*0.0015625);
    LCD_ShowString(0, (line++)*FONT, str, WHITE,BLACK, FONT, 0);

    sprintf(str, "IC2:%5.2fA", (adc[5]-1988.0)*0.0015625);
    LCD_ShowString(0, (line++)*FONT, str, WHITE,BLACK, FONT, 0);

    sprintf(str, "VBUS:%4.1fV", (adc[6]/4096.0)*3.2*11);
    LCD_ShowString(0, (line++)*FONT, str, WHITE,BLACK, FONT, 0);
}
