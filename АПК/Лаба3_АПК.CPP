#include <dos.h>

struct VIDEO
{
	unsigned char symb;
	unsigned char attr;
};

void get_reg();         	//get data from registres
void print(int, int x,unsigned char attr);    //fill in the screen

//IRQ0-15
void interrupt (*int8) (...);
void interrupt (*int9) (...);
void interrupt (*int10) (...);
void interrupt (*int11) (...);
void interrupt (*int12) (...);
void interrupt (*int13) (...);
void interrupt (*int14) (...);
void interrupt (*int15) (...);

void interrupt (*int70) (...);
void interrupt (*int71) (...);
void interrupt (*int72) (...);
void interrupt (*int73) (...);
void interrupt (*int74) (...);
void interrupt (*int75) (...);
void interrupt (*int76) (...);
void interrupt (*int77) (...);

// new interrupt handlers
void interrupt  new_90(...) { get_reg(); int8(); }
void interrupt  new_91(...) { get_reg(); int9(); }
void interrupt  new_92(...) { get_reg(); int10(); }
void interrupt  new_93(...) { get_reg(); int11(); }
void interrupt  new_94(...) { get_reg(); int12(); }
void interrupt  new_95(...) { get_reg(); int13(); }
void interrupt  new_96(...) { get_reg(); int14(); }
void interrupt  new_97(...) { get_reg(); int15(); }

void interrupt  new_08(...) { get_reg(); int70(); }
void interrupt  new_09(...) { get_reg(); int71(); }
void interrupt  new_10(...) { get_reg(); int72(); }
void interrupt  new_11(...) { get_reg(); int73(); }
void interrupt  new_12(...) { get_reg(); int74(); }
void interrupt  new_13(...) { get_reg(); int75(); }
void interrupt  new_14(...) { get_reg(); int76(); }
void interrupt  new_15(...) { get_reg(); int77(); }

void print(int val, int x,unsigned char attr)
{
	char temp;
	int i=0;
	VIDEO far* screen = (VIDEO far *)MK_FP(0xB800, 0);
	while((x*9)>i)
	{
		screen++;
		i++;
	}

	for(i=7;i>=0;i--)        //find bits
	{
		temp=val%2;
		val/=2;         //fill the screen
		screen->symb=temp+'0';
		screen->attr=attr;
		screen++;
	}
		screen->symb='0';
		screen->attr=0x01;
		screen++;
}

// get data from registers
void get_reg()
{
	//master
	outp(0x20, 0x0B);// Interrupt Service Register
	print(inp(0x20),0,0x6E);
	print(inp(0x21),1,0x6E);// Interrupt Mask Register
	outp(0x20, 0x0A);// Interrupt Request Register
	print(inp(0x20),2,0x6E);
	
	//slave
	outp(0xA0, 0x0B);// Interrupt Service Register
	print(inp(0xA0),3,0x1E);
	print(inp(0xA1),4,0x1E);// Interrupt Mask Register
	outp(0xA0,0x0A);// Interrupt Request Register
	print(inp(0xA0),5,0x1E);
	
}

void init()
{
	int8 = getvect(0x8);      // IRQ0 прерывание таймера.
	int9 = getvect(0x9);      // IRQ1 прерывание от клавиатуры.
	int10 = getvect(0xA);     // IRQ2 используется для каскадирования аппаратных прерываний
	int11 = getvect(0xB);     // IRQ3 прерывание асинхронного порта COM2.
	int12 = getvect(0xC);     // IRQ4 прерывание асинхронного порта COM1.
	int13 = getvect(0xD);     // IRQ5 прерывание от контроллера жесткого диска для XT.
	int14 = getvect(0xE);     // IRQ6 прерывание генерируется контроллером флоппи диска после завершения операции
	int15 = getvect(0xF);     //IRQ7 прерывание принтера.

	int70 = getvect(0x70);    //IRQ8 прерывание от часов реального времени.
	int71 = getvect(0x71);    //IRQ9 прерывание от контроллера EGA.
	int72 = getvect(0x72);    //IRQ10 зарезервировано.
	int73 = getvect(0x73);    //IRQ11 зарезервировано.
	int74 = getvect(0x74);    //IRQ12 зарезервировано.
	int75 = getvect(0x75);    //IRQ13 прерывание от математического сопроцессора.
	int76 = getvect(0x76);    //IRQ14 прерывание от контроллера жесткого диска.
	int77 = getvect(0x77);    //IRQ15 зарезервировано.

 
	setvect(0xA0, new_90);//A0-A7
	setvect(0xA1, new_91);
	setvect(0xA2, new_92); 
	setvect(0xA3, new_93);
	setvect(0xA4, new_94); 
	setvect(0xA5, new_95);
	setvect(0xA6, new_96); 
	setvect(0xA7, new_97);
	
	setvect(0x08, new_08);//08-0F
	setvect(0x09, new_09);
	setvect(0x0A, new_10);
	setvect(0x0B, new_11);
	setvect(0x0C, new_12);
	setvect(0x0D, new_13);
	setvect(0x0E, new_14);
	setvect(0x0F, new_15);

	_disable(); // disable interrupts handling (cli)

	/* MASTER */
	outp(0x20, 0x11);	//ICW1
	outp(0x21, 0xA0);   //ICW2
	outp(0x21, 0x04);	//ICW3
	outp(0x21, 0x01);	//ICW4

	/* SLAVE */
	outp(0xA0, 0x11);	//ICW1
	outp(0xA1, 0x08);   //ICW2
	outp(0xA1, 0x02);	//ICW3
	outp(0xA1, 0x01);	//ICW4

	_enable(); // enable interrupt handling (sti)
}

int main()
{
	unsigned far *fp;
	init();

	FP_SEG (fp) = _psp; // segment
	FP_OFF (fp) = 0x2c; // offset
	_dos_freemem(*fp);

	_dos_keep(0,(_DS -_CS)+(_SP/16)+1);//TSR
	return 0;
}


