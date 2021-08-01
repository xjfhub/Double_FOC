#include "lcd_init.h"

void LCD_Writ_Bus(uint8_t dat)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		LCD_SCLK_Clr();
		if (dat & 0x80)
		{
			LCD_MOSI_Set();
		}
		else
		{
			LCD_MOSI_Clr();
		}
		LCD_SCLK_Set();
		dat <<= 1;
	}
}

void LCD_WR_DATA8(uint8_t dat)
{
	LCD_Writ_Bus(dat);
}

void LCD_WR_DATA(uint16_t dat)
{
	LCD_Writ_Bus(dat >> 8);
	LCD_Writ_Bus(dat);
}

void LCD_WR_REG(uint8_t dat)
{
	LCD_DC_Clr();
	LCD_Writ_Bus(dat);
	LCD_DC_Set();
}

void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	if (USE_HORIZONTAL == 0)
	{
		LCD_WR_REG(0x2a);
		LCD_WR_DATA(x1 + 26);
		LCD_WR_DATA(x2 + 26);
		LCD_WR_REG(0x2b);
		LCD_WR_DATA(y1 + 1);
		LCD_WR_DATA(y2 + 1);
		LCD_WR_REG(0x2c);
	}
	else if (USE_HORIZONTAL == 1)
	{
		LCD_WR_REG(0x2a);
		LCD_WR_DATA(x1 + 26);
		LCD_WR_DATA(x2 + 26);
		LCD_WR_REG(0x2b);
		LCD_WR_DATA(y1 + 1);
		LCD_WR_DATA(y2 + 1);
		LCD_WR_REG(0x2c);
	}
	else if (USE_HORIZONTAL == 2)
	{
		LCD_WR_REG(0x2a);
		LCD_WR_DATA(x1 + 1);
		LCD_WR_DATA(x2 + 1);
		LCD_WR_REG(0x2b);
		LCD_WR_DATA(y1 + 26);
		LCD_WR_DATA(y2 + 26);
		LCD_WR_REG(0x2c);
	}
	else
	{
		LCD_WR_REG(0x2a);
		LCD_WR_DATA(x1 + 1);
		LCD_WR_DATA(x2 + 1);
		LCD_WR_REG(0x2b);
		LCD_WR_DATA(y1 + 26);
		LCD_WR_DATA(y2 + 26);
		LCD_WR_REG(0x2c);
	}
}

void LCD_Init(void)
{

	LCD_WR_REG(0x11); //Sleep out
	HAL_Delay(120);	  //Delay 120ms
	LCD_WR_REG(0xB1); //Normal mode
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x3C);
	LCD_WR_REG(0xB2); //Idle mode
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x3C);
	LCD_WR_REG(0xB3); //Partial mode
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x3C);
	LCD_WR_REG(0xB4); //Dot inversion
	LCD_WR_DATA8(0x03);
	LCD_WR_REG(0xC0); //AVDD GVDD
	LCD_WR_DATA8(0xAB);
	LCD_WR_DATA8(0x0B);
	LCD_WR_DATA8(0x04);
	LCD_WR_REG(0xC1);	//VGH VGL
	LCD_WR_DATA8(0xC5); //C0
	LCD_WR_REG(0xC2);	//Normal Mode
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x00);
	LCD_WR_REG(0xC3); //Idle
	LCD_WR_DATA8(0x8D);
	LCD_WR_DATA8(0x6A);
	LCD_WR_REG(0xC4); //Partial+Full
	LCD_WR_DATA8(0x8D);
	LCD_WR_DATA8(0xEE);
	LCD_WR_REG(0xC5); //VCOM
	LCD_WR_DATA8(0x0F);
	LCD_WR_REG(0xE0); //positive gamma
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x0E);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x02);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x25);
	LCD_WR_DATA8(0x36);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x10);
	LCD_WR_REG(0xE1); //negative gamma
	LCD_WR_DATA8(0x0A);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x02);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x25);
	LCD_WR_DATA8(0x35);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x10);

	LCD_WR_REG(0xFC);
	LCD_WR_DATA8(0x80);

	LCD_WR_REG(0x3A);
	LCD_WR_DATA8(0x05);
	LCD_WR_REG(0x36);
	if (USE_HORIZONTAL == 0)
		LCD_WR_DATA8(0x08);
	else if (USE_HORIZONTAL == 1)
		LCD_WR_DATA8(0xC8);
	else if (USE_HORIZONTAL == 2)
		LCD_WR_DATA8(0x78);
	else
		LCD_WR_DATA8(0xA8);
	LCD_WR_REG(0x21); //Display inversion
	LCD_WR_REG(0x29); //Display on
	LCD_WR_REG(0x2A); //Set Column Address
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x1A); //26
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x69); //105
	LCD_WR_REG(0x2B);	//Set Page Address
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x01); //1
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0xA0); //160
	LCD_WR_REG(0x2C);
}
