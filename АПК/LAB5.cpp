#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <windows.h>

unsigned int countMilliseconds = 0;
void _interrupt _far(*oldVector)(...);

void _interrupt _far newVector(...); 
void interrupt(*int_old_alarm) (...);

void resetAlarm() {

	if (int_old_alarm == NULL) {
		return;
	}

	disable();

	setvect(0x4A, int_old_alarm); 
	outp(0xA1, (inp(0xA0) | 0x01));

	int i = 0;
	outp(0x70, 0x0A);
	for (; (inp(0x71) & 0x80) && i < 30000; i++) {
		outp(0x70, 0x0A);
	}
	if (i >= 30000){
		printf("Alarm error!");
		enable();
		return;
	}

	outp(0x70, 0x05);
	outp(0x71, 0x00);

	outp(0x70, 0x03);
	outp(0x71, 0x00);

	outp(0x70, 0x01);
	outp(0x71, 0x00);

	outp(0x70, 0xB);
	outp(0x71, (inp(0x71) & 0xDF)); 

	enable();
}


int bcd_to_dec (int bcd_number) {
	return ((bcd_number / 16 * 10) + (bcd_number % 16));
}


int dec_to_bcd (int dec_number) {
	return ((dec_number / 10 * 16) + (dec_number % 10));
}

void getTime() {

	system("cls");
	outp(0x70, 0x00);
	char second = inp(0x71);
	outp(0x70, 0x02);
	char minutes = inp(0x71);
	outp(0x70, 0x04);
	char hour = inp(0x71);
	printf(" HH:%02d MM:%02d SS:%02d\n", bcd_to_dec(hour), bcd_to_dec(minutes), bcd_to_dec(second));

	outp(0x70, 0x07);
	char day = inp(0x71);
	outp(0x70, 0x08);
	char month = inp(0x71);
	outp(0x70, 0x32);
	char century = inp(0x71);
	outp(0x70, 0x09);
	char year = inp(0x71);
	printf("DD:%02d MM:%02d YY:%d\n", bcd_to_dec(day), bcd_to_dec(month), bcd_to_dec(year) + bcd_to_dec(century) * 100);

}

void setTime() {	
	printf("Input please:\n");
	int hours;
	do {
		fflush(stdin);
		printf("Hours: "); 
		scanf("%i", &hours);
	} while ((hours > 23 || hours < 0));

	int minutes;
	do {
		fflush(stdin);
		printf("Minutes: ");  
		scanf("%i", &minutes);
	} while (minutes > 59 || minutes < 0);

	int seconds;
	do {
		fflush(stdin);
		printf("Seconds: ");
		scanf("%i", &seconds);
	} while (seconds > 59 || seconds < 0);

	disable();

	int i = 0;
	outp(0x70, 0x0A);
	for (; (inp(0x71) & 0x80) && i < 30000; i++) {
		outp(0x70, 0x0A);
	}
	if (i >= 30000){
		printf("Alarm error!");
		enable();
		return;
	}
	
	outp(0x70, 0xB);
	outp(0x71, inp(0x71) | 0x80); 
	
	outp(0x70, 0x04);
	outp(0x71, dec_to_bcd(hours));
	outp(0x70, 0x02);
	outp(0x71, dec_to_bcd(minutes));
	outp(0x70, 0x00);
	outp(0x71, dec_to_bcd(seconds));

	outp(0x70, 0xB);
	outp(0x71, inp(0x71) & 0x7F);

	enable();

	system("cls");
}

void delay(unsigned int ms) {

	disable();

	oldVector = _dos_getvect(0x70);
	_dos_setvect(0x70, newVector); 
	
	enable(); 

	outp(0xA1, inp(0xA1) & 0xFE); 

	outp(0x70, 0xB);
	outp(0x71, inp(0x71) | 0x40);  

	countMilliseconds = 0;

	while (countMilliseconds <= ms);

	disavle();

	_dos_setvect(0x70, oldVector); 

	enable();

	return;
}

void _interrupt _far newVector(...) {
	countMilliseconds++;
	
	outp(0x70, 0x0C);
	inp(0x71);
	
	outp(0x20, 0x20);
	outp(0xA0, 0x20);
}

void interrupt int_new_alarm(...) {
	write(1, "\nALARM!", 7);
	int_old_alarm();
	resetAlarm();
}

void setAlarm() {

	printf("Input please:\n");

	int hour;
	do {
		fflush(stdin);
		printf("Hours: ");
		scanf ("%i", &hour);
	} while (hour > 23 || hour < 0);
	
	int minute;
	do {
		fflush(stdin);
		printf("Minutes: ");
		scanf ("%i", &minute);
	} while (minute > 59 || minute < 0);
	
	int second;
	do {
		fflush(stdin);
		printf("Seconds : ");
		scanf ("%i", &second);
	} while (second > 59 || second < 0);

	disable();
	
	int i = 0;
	outp(0x70, 0x0A);
	for (; (inp(0x71) & 0x80) && i < 30000; i++) {
		outp(0x70, 0x0A);
	}
	if (i >= 30000) {
		printf("Alarm error!");
		return;
	}

	outp(0x70, 0x05);
	outp(0x71, dec_to_bcd(hour));
	outp(0x70, 0x03);
	outp(0x71, dec_to_bcd(minute));
	outp(0x70, 0x01);
	outp(0x71, dec_to_bcd(second));

	outp(0x70, 0xB);
	outp(0x71, (inp(0x71) | 0x20));
	
	int_old_alarm = getvect(0x4A);	
	setvect(0x4A, int_new_alarm);		
	outp(0xA1, (inp(0xA0) & 0xFE));

	enable();

	printf("OK\n");
}

int main()
{
	int ms;
	
	while(1) {

		 printf("1. Show Time\n");
		 printf("2. Set Time\n");
		 printf("3. Set Alarm\n");
		 printf("4. Sleep\n");
		 printf("q. Quit\n\n");

		switch(getch()) {
		case '1': 
			getTime(); 
			break;
			
		 case '2': 
		 	setTime();
		 	break;
		 
		 case '3':
			setAlarm();
		 	break;

		 case '4': 

			do {
				fflush(stdin);
				printf("Input ms: ");
				scanf("%d", &ms);
			} while (ms < 0 || !ms);

		 	printf("Sleeping... \n");
		 	delay(ms); 
			printf("Thats all! \n");
		 	break;
			 
		 case 'q':
			resetAlarm();
		 	return 0;
		}
	}

}