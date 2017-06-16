#include "LCD.h"
#include "font.h"

//10us@30MHz
void timer2Init() {
	AUXR |= 0x04;
	T2L = 0xD4;
	T2H = 0xFE;
	IE2 |= (1 << 2);
	EA = 1;
	AUXR |= 0x10;
}

void waitBusy() {
	LCD_E = 0;
	LCD_RS = 0;
	delayMicroseconds(10);
	LCD_RW = 1;
	delayMicroseconds(10);
	LCD_DATA = 0xFF;
	delayMicroseconds(10);
	LCD_E = 1;
	while (LCD_DATA & 0x80);
	LCD_E = 0;
}

void writeByte(uint8_t value, uint8_t rs) {
	waitBusy();
	LCD_RS = rs;
	delayMicroseconds(10);
	LCD_RW = 0;
	delayMicroseconds(10);
	LCD_E = 0;
	LCD_DATA = value;
	delayMicroseconds(10);
	LCD_E = 1;
	delayMicroseconds(10);
	LCD_E = 0;
}

void writeCmd(uint8_t value) { writeByte(value, 0); }

void writeData(uint8_t value) { writeByte(value, 1); }

void lcdInit() {
	P0M0 = P0M1 = 0;
	P1M0 = P1M1 = 0;
	P5M0 = P5M1 = 0;
	
	timer2Init();
	
	LCD_CONTRAST_SET = 0;
	LCD_BACKLIGHT_SET = 0;
	LCD_CONTRAST_VALUE = 0;
	LCD_BACKLIGHT_VALUE = 0;
	
	writeCmd(0x38);
	writeCmd(0x08);
	writeCmd(0x06);
	writeCmd(0x01);
	writeCmd(0x0C);
	writeCmd(0x80);
}

void lcdSetBright(uint8_t value) {
	if (value <= LCD_BACKLIGHT_MAX)
		LCD_BACKLIGHT_SET = LCD_BACKLIGHT_MAX - value;
	else
		LCD_BACKLIGHT_SET = 0;
}

void lcdSetContrast(uint8_t value) {
	if (value <= LCD_CONTRAST_MAX)
		LCD_CONTRAST_SET = LCD_CONTRAST_MAX - value;
	else
		LCD_CONTRAST_SET = 0;
}

void lcdDraw(uint8_t x, uint8_t y, char c) {
	writeCmd(0x80 + ((y > 0) ? 0x40 : 0) + x);
	writeData(c);
}

void lcdCusDraw(uint8_t x, uint8_t y, char c) {
	uint8_t i;
	writeCmd(LCD_CUSCMD_1);
	for (i = 1; i < 6; i++) writeData(font[c - 32][i]);
	writeCmd(0x80 + ((y > 0) ? 0x40 : 0) + x);
	writeData(LCD_CUSADD_1);
}

void lcdPrint(uint8_t x, uint8_t y, char* str) {
	uint8_t i; uint8_t tx = x, ty = y;
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] == '\n') {
			tx = x;
			ty = 1 - ty;
		} else {
			lcdDraw(tx + i, ty, str[i]);
		}
	}
}

void lcdCusPrint(uint8_t x, uint8_t y, char* str) {
	uint8_t i; uint8_t tx = x, ty = y;
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] == '\n') {
			tx = x;
			ty = 1 - ty;
		} else {
			lcdCusDraw(tx + i, ty, str[i]);
		}
	}
}

void lcdClear() {
	writeCmd(0x01);
	delay(1);
}

void timer2Interrupt() interrupt 12 {
	T2L = 0xD4;
	T2H = 0xFE;
	
	if (LCD_CONTRAST_VALUE <= LCD_CONTRAST_SET) LCD_CONTRAST = 1;
	else if (LCD_CONTRAST_VALUE <= LCD_CONTRAST_MAX) LCD_CONTRAST = 0;
	else LCD_CONTRAST_VALUE = 0;
	LCD_CONTRAST_VALUE += 1;
	
	if (LCD_BACKLIGHT_VALUE <= LCD_BACKLIGHT_SET) LCD_BACKLIGHT = 1;
	else if (LCD_BACKLIGHT_VALUE <= LCD_BACKLIGHT_MAX) LCD_BACKLIGHT = 0;
	else LCD_BACKLIGHT_VALUE = 0;
	LCD_BACKLIGHT_VALUE += 1;
}