#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

void interrupt newInt9(...); 
void interrupt (*oldInt9)(...); 
void indicator(unsigned char mask); 
void blink (void); 
int resend = 1; 
int quitFlag = 0; 
int blinkON = 0; 

void main()
{
	oldInt9 = getvect(9); 
	setvect(9, newInt9); 
	while(!quitFlag)
	{
		if(blinkON)
		{
			blink(); 
		}
	}
	setvect(9, oldInt9);
	return;
}

void interrupt newInt9(...)
{
	unsigned char value = 0;
	value = inp(0x60); 
	if(value == 0x01) 
		quitFlag = 1; 
	if (value >= 0x10 && value <= 0x32 && blinkON == 0)
		blinkON = 1; 
	else if (value >= 0x10 && value <= 0x32 && blinkON == 1) 
			blinkON = 0;
	if (value != 0xFA && blinkON == 1) 
		resend = 1; 
	else 
		resend = 0;
	printf("\t%x", value);
	oldInt9();
}

void indicator(unsigned char mask)
{
	int counter=0;
	resend = 1;
	while (resend) 
	{
		while(((inp(0x64) & 0x02) != 0x00));
		if(counter!=3)
		{
			outp(0x60, 0xED);
		}
		else
		{
			printf("exit");
			exit(1);
		}
		counter++;
			delay(50);
	}
	resend = 1;
	counter=0;
	while (resend)
	{
		while((inp(0x64) & 0x02) != 0x00); 
		if(counter!=3)
		{
			outp(0x60, mask); 
		}
		else
		{
			printf("exit");
			exit(1);
		}
		counter++;
			delay(50);
	}
}

void blink ()
{
	indicator(0x6); 
	delay(1000);
	indicator(0x00); 
	delay(1000);
}