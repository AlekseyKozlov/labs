#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
/* 9.	F(x) = x / (|sin(x)| + 2) */
void main(void)
{
	double a = -100, b = 100, step = 0.001, x,f;
	int two=2;
	//clock_t start,end;

    LARGE_INTEGER t1, t2, f1;
    QueryPerformanceCounter(&t1);

	x=a;
	f=0;
	
	//start=clock();
	_asm{
		finit
			fld b
			fld x
loop_start:
	        fcom
			fstsw ax
			and ah, 01000101b
			jz loop_end

	
			fld x
			
		
			fld x
			fsin 
			fabs  
			fiadd two
            
			
        	fdiv

			fadd f
			fstp f

			fadd step
			fst x
			jmp loop_start
loop_end:
			fwait
	}
	//end=clock();
    QueryPerformanceCounter(&t2);
    QueryPerformanceFrequency(&f1);
    double sec = double(t2.QuadPart - t1.QuadPart) / f1.QuadPart;
	printf("%f\n", f);
	//printf("\ntime ASM(clock) %f\n", (double)(end-start)/CLK_TCK);
	
	printf("\ntime ASM(Querty) %f\n", sec);


	x=a;
	f=0;
//	start=clock();
	 QueryPerformanceCounter(&t1);
	while(x<=b)
	{
		f +=x/(abs(sin(x))+2);
		x +=step;
	};
	//end =clock();
	 QueryPerformanceCounter(&t2);
    QueryPerformanceFrequency(&f1);
    sec = double(t2.QuadPart - t1.QuadPart) / f1.QuadPart;
	printf("%f\n",f);
	//printf("time CI(clock) %f\n",(double)(end-start)/CLK_TCK);
	printf("time CI(Querty) %f\n",sec);

	getch();
}
//#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <conio.h>
//#include <windows.h>
//#include <iostream>
//
//// 27.F(x) = (cos(x) + 1) / (sin(x) + 4)
//
//int main()
//{
//double a, b, step, x, f;
//int four=4, one=1, i=0;
//LARGE_INTEGER timerFrequency, timerStart, timerStop;
//
//while(i==0)
//{
//printf("Input lower limit:\n");
//scanf("%lf", &a);
//printf("Input upper limit:\n");
//scanf("%lf", &b);
//printf("Input step:\n");
//scanf("%lf", &step);
//
//x=a;
//f=0;
//
////QueryPerformanceFrequency(&timerFrequency);
//QueryPerformanceCounter(&timerStart);
//
//while(x<=b)
//{
//f+=(cos(x) + 1) / (sin(x) + 4);
//x+=step;
//};
//
//
//QueryPerformanceCounter(&timerStop);
//QueryPerformanceFrequency(&timerFrequency);
// double t1 = double(timerStop.QuadPart - timerStart.QuadPart) / timerFrequency.QuadPart;
////double const t1( static_cast<double>( timerStop.QuadPart -timerStart.QuadPart ) / timerFrequency.QuadPart );
//
//printf("C:\n");
//printf("Result: %f\n", f);
//printf("Time C: %f\n", t1);
//
//x=a;
//f=0;
//
////QueryPerformanceFrequency(&timerFrequency);
//QueryPerformanceCounter(&timerStart);
//
//_asm
//{
//finit
//fld b
//fld x
//loop_start:
//fcom
//fstsw ax
//and ah, 01000101b
//jz loop_end
//
//
//fld x
//fcos
//fiadd one
//
//fld x
//fsin
//fiadd four
//
//fdiv
//fadd f
//fstp f
//
//fadd step
//fst x
//jmp loop_start
//loop_end:
//fwait
//}
//
//QueryPerformanceCounter(&timerStop);
//QueryPerformanceFrequency(&timerFrequency);
//double t = double(timerStop.QuadPart - timerStart.QuadPart) / timerFrequency.QuadPart;
////double const t( static_cast<double>( timerStop.QuadPart -timerStart.QuadPart ) / timerFrequency.QuadPart );
//
//printf("\nASM:\n");
//printf("Result: %f\n", f);
//printf("Time asm: %f\n", t);
//
//printf ("\nDo you want to continue?(0-yes, 1-no)");
//scanf("%d", &i);
//system ("cls");
//}
//getch();
//return 0;
//}