#include<dos.h>
#include<stdio.h>
#include<stdlib.h>

void printToVideoMemory(char* str, int x, int y, unsigned char attribute);
void byteToString(unsigned char temp, char *str);
void print();
void swap();
unsigned char colorMaster1 =  0x4E;
unsigned char colorSlave1 = 0x2E;

unsigned char colorMaster2 = 0x4B;
unsigned char colorSlave2 = 0x2B;
void interrupt new_0(...);
void interrupt new_1(...);
void interrupt new_2(...);
void interrupt new_3(...);							
void interrupt new_4(...);	
void interrupt new_5(...);
void interrupt new_6(...);
void interrupt new_7(...);
void interrupt new_8(...);
void interrupt new_9(...);
void interrupt new_10(...);
void interrupt new_11(...);
void interrupt new_12(...);
void interrupt new_13(...);
void interrupt new_14(...);
void interrupt new_15(...);


void interrupt(*old_0)(...);
void interrupt(*old_1)(...);
void interrupt(*old_2)(...);
void interrupt(*old_3)(...);
void interrupt(*old_4)(...);
void interrupt(*old_5)(...);
void interrupt(*old_6)(...);
void interrupt(*old_7)(...);
void interrupt(*old_8)(...);
void interrupt(*old_9)(...);
void interrupt(*old_10)(...);
void interrupt(*old_11)(...);
void interrupt(*old_12)(...);
void interrupt(*old_13)(...);
void interrupt(*old_14)(...);
void interrupt(*old_15)(...);


void main()
{
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	old_0 = getvect(0x08);
	old_1 = getvect(0x09);
	old_2 = getvect(0x0A);
	old_3 = getvect(0x0B);				
	old_4 = getvect(0x0C);
	old_5 = getvect(0x0D);				
	old_6 = getvect(0x0E);
	old_7 = getvect(0x0F);				
	old_8 = getvect(0x70);
	old_9 = getvect(0x71);				

	old_10 = getvect(0x72);
	old_11 = getvect(0x73);				
	old_12 = getvect(0x74);
	old_13 = getvect(0x75);				
	old_14 = getvect(0x76);
	old_15 = getvect(0x77);				
	

	setvect(0xB0, new_0);
	setvect(0xB1, new_1);				// installing the base vector
	setvect(0xB2, new_2);
	setvect(0xB3, new_3);				// installing the base vector
	setvect(0xB4, new_4);
	setvect(0xB5, new_5);				// installing the base vector
	setvect(0xB6, new_6);
	setvect(0xB7, new_7);	
	
	setvect(0x08, new_8);
	setvect(0x09, new_9);				// installing the base vector
	setvect(0x0A, new_10);
	setvect(0x0B, new_11);				// installing the base vector
	setvect(0x0C, new_12);
	setvect(0x0D, new_13);				// installing the base vector
	setvect(0x0E, new_14);
	setvect(0x0F, new_15);				// installing the base vector
	

	outp(0x20, 0x11);	// ICW1 особенности последовательности,инициализация ICW4 		   
	outp(0x21, 0xB0);	// ICW2
	outp(0x21, 0x04);	// ICW3	0-7, где ведомый?							код индетефикации номера входа, к которму подключен ведомый
	outp(0x21, 0x01);	// ICW4 дополнительные параметры					тип микр, особенности обработки  конца, ведущий или ведомый

	outp(0xA0, 0x11);   // ICW1
	outp(0xA1, 0x08);   // ICW2
	outp(0xA1, 0x02);	// ICW3
	outp(0xA1, 0x01);	

	unsigned far *fp;	//объявляем указатель
	FP_SEG(fp) = _psp;	// получаем сегмент
	FP_OFF(fp) = 0x2c;	// и смещение сегмента данных с переменными среды
	_dos_freemem(*fp);

	_dos_keep(0, (_DS - _CS) + (_SP / 16) + 1); 
}

void byteToString(unsigned char temp, char *str)
{
	int i;
	str[8] = 0;
	i = 7;
	while (temp)
	{
		str[i] = '0' + temp % 2;
		temp = temp / 2;
		i--;
	}
	for (; i>-1; i--)
		str[i] = '0';
}

void printToVideoMemory(char* str, int x, int y, unsigned char attribute)
{
	char far* start = (char far*)0xb8000000;	// начальный адрес видеопамяти
	start += x + 160 * y;

	int i = 0;
	while (str[i] != 0)
	{
		*start = str[i];
		start++;
		*start = attribute;
		start++;
		i++;
	}
}



void print()
{
	unsigned char isr_master, isr_slave; 
	unsigned char irr_master, irr_slave; 
	unsigned char imr_master, imr_slave; 

	imr_master = inp(0x21);
	imr_slave = inp(0xA1);

	outp(0x20, 0x0A);
	irr_master = inp(0x20);
	outp(0x20, 0x0B);
	isr_master = inp(0x20);

	outp(0xA0, 0x0A);
	irr_slave = inp(0xA0);
	outp(0xA0, 0x0B);
	isr_slave = inp(0xA0);

	char str[9];
	printToVideoMemory("MASTER PIC  ->>  ISR: ", 0, 0, colorMaster1);
	byteToString(isr_master, str);
	printToVideoMemory(str, 44, 0, colorMaster1);

	printToVideoMemory("  |  IRR: ", 60, 0, colorMaster1);
	byteToString(irr_master, str);
	printToVideoMemory(str, 80, 0, colorMaster1);

	printToVideoMemory("  |  IMR: ", 96, 0, colorMaster1);
	byteToString(imr_master, str);
	printToVideoMemory(str, 116, 0, colorMaster1);

	printToVideoMemory("SLAVE  PIC  ->>  ISR: ", 0, 1, colorMaster1);
	byteToString(isr_slave, str);
	printToVideoMemory(str, 44, 1, colorMaster1);

	printToVideoMemory("  |  IRR: ", 60, 1, colorMaster1);
	byteToString(irr_slave, str);
	printToVideoMemory(str, 80, 1, colorMaster1);

	printToVideoMemory("  |  IMR: ", 96, 1, colorMaster1);
	byteToString(imr_slave, str);
	printToVideoMemory(str, 116, 1, colorMaster1);

}

void swap()
{
	unsigned char temp;
	temp = colorMaster1;
	colorMaster1 = colorMaster2;
	colorMaster2 = temp;

	temp = colorSlave1;
	colorSlave1 = colorSlave2;
	colorSlave2 = temp;

}

void interrupt new_0(...)
{
	
	print();
	(*old_0)();
}
void interrupt new_1(...)
{
	swap();
	print();
	(*old_1)();
}
void interrupt new_2(...)
{
	print();
	(*old_2)();
}
void interrupt new_3(...)
{
	print();
	(*old_3)();
}
void interrupt new_4(...)
{
	print();
	(*old_4)();
}
void interrupt new_5(...)
{
	print();
	(*old_5)();
}
void interrupt new_6(...)
{
	print();
	(*old_8)();
}
void interrupt new_7(...)
{
	print();
	(*old_8)();
}
void interrupt new_8(...)
{
	print();
	(*old_8)();
}

void interrupt new_9(...)
{
	print();
	(*old_9)();
}

void interrupt new_10(...)
{
	print();
	(*old_10)();
}

void interrupt new_11(...)
{
	print();
	(*old_11)();
}

void interrupt new_12(...)
{
	print();
	(*old_12)();
}

void interrupt new_13(...)
{
	print();
	(*old_13)();
}

void interrupt new_14(...)
{
	print();
	(*old_14)();
}

void interrupt new_15(...)
{
	print();
	(*old_15)();
}

