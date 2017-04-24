#include "STC15.h"

/*
	P36 P37 P41 P42 P44 P20 P21 P22
*/

#define CLK P36
#define setPos(v) P37 = (v >> 1) & 0x1; P41 = v & 0x1;
#define setData(v) P42 = (v >> 4) & 0x1; P44 = (v >> 3) & 0x1; P20 = (v >> 2) & 0x1; P21 = (v >> 1) & 0x1; P22 = v & 0x1;
#define show(p, v) setPos(p); setData(v); CLK = 1; CLK = 0; CLK = 1;

void print(unsigned short v) {
	char i;
	
	if (v > 9999) {
		for (i = 0; i < 4; i++)
			show(i, (v >> ((3 - i) * 4)) & 0xF);
	} else {
		show(0, v / 1000);
		show(1, (v % 1000) / 100);
		show(2, (v % 100) / 10);
		show(3, (v % 10));
	}
}



void main() {
	unsigned short time = 0;
	
	P0M0 = 0; P0M1 = 0xFF;
	P1M0 = 0; P1M1 = 0xFF;
	
	P2M0 = 0; P2M1 = 0;
	P3M0 = 0; P3M1 = 0;
	P4M0 = 0; P4M1 = 0;
	
	while (1) {
		print(time);
		time += 1;
		delay(100);
	}
}