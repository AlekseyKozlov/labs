#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int melody[] = {  //here we can type any melody, because we have a table which
//connects notes and frequency
 392, 392, 293, 196, 196, 392, 392, 293, 196
};

void get_random(long bound){

	long base = 1193180, j, kd, kdLow, kdHigh, kdNew;

		outp(0x43, 0xb4);

		outp(0x42, bound % 256);
		bound /= 256;
		outp(0x42, bound);

		outp(0x61, inp(0x61) | 1);

		while(getch()!=27){

		outp(0x43, 0x86);

		kdLow = inp(0x42);
		kdHigh = inp(0x42);
		kdNew = kdHigh * 256 + kdLow;

		printf("%ld\n", kdNew);
		}
		outp(0x61, inp(0x61) & 0xFC);
}

void printKd(){

 long i, j, kdLow, kdHigh, kd, kdMax;

    for(i = 0; i < 3; i++){
	kdMax = 0;

	for(j = 0; j < 60000; j++){

	    if(i == 0){
		outp(0x43, 0x0);
		kdLow = inp(0x40);
		kdHigh = inp(0x40);
	    }

	    if (i == 1){
		outp(0x43, 0x40);
		kdLow = inp(0x41);
		kdHigh = inp(0x41);
	    }

	    if(i == 2){
		outp(0x43, 0x80);
		kdLow = inp(0x42);
		kdHigh = inp(0x42);
	    }

	    kd = kdHigh * 256 + kdLow;

	    if (kdMax < kd)
	      kdMax = kd;
	}
      if(i == 0) printf("KD for zero channel: ");
      if(i == 1) printf("KD for first channel: ");
      if(i == 2) printf("KD for second channel: ");
      printf("%X\n", kdMax);
    }
}

void printWords(){

    int i, iChannel, state;
    char temp;

    for(iChannel = 0; iChannel < 3; iChannel++){

	if(iChannel == 0){
	  outp(0x43, 0xe2);
	  state = inp(0x40);
	  printf("Word of zero channel: \t");
	}

	if(iChannel == 1){
	  outp(0x43,0xe4);
	  state = inp(0x41);
	  printf("Word of first channel: \t");
	}

	if(iChannel == 2){
	  outp(0x43, 0xe8);
	  state = inp(0x42);
	  printf("Word of second channel: \t");
	}

	for(i = 7; i >= 0; i--){
	    temp = state % 2;
	    printf("%d", temp);
	    state /= 2;
	}

	printf("\n\n");
    }
}

void Speaker(int a){

    if(a){
      outp(0x61, inp(0x61) | 3);
    }

    else{
      outp(0x61, inp(0x61) & 0xfc);
    }
}

void setFrequency(unsigned int freq){

   long base = 1193180, kd;

   outp(0x43, 0xB6);

   kd = base / freq;

   outp(0x42, kd % 256);
   kd /= 256;
   outp(0x42, kd);
}

void playMelody(){

  int i;

    for(i = 0; melody[i] != 0; i++){

      setFrequency(melody[i]);

      Speaker(1);

      delay(800);

      Speaker(0);

    }
}

int main(){

  int i;
  long randAboveRange;
  char control;

     while(1){

	printf("1: Play Melody\n");
	printf("2: Print KD\n");
	printf("3: Print condition words\n");
	printf("4: Generate random numbers\n\n");

	control = getch();

	switch(control){

	  case '1':
	    playMelody();
	    break;

	  case '2':
	    system("cls");
	    printKd();
	    getch();
	    break;

	  case '3':
	    system("cls");
	    printWords();
	    getch();
	    break;

	  case '4':
	     system("cls");
	     printf("Enter the above range of random: ");
	     scanf("%ld", &randAboveRange);
	     get_random(randAboveRange);
	     break;

	  case 'q':
	    printf("Bye - bye");
	    return 0;

	  default:
	    printf("Error key! Please try again\n");
	    break;
	}
     }
}