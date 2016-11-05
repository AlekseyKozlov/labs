#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <malloc.h>
#include <ctime>
#define N 8
#define OPERATION 1000000

void main(void)
{
	LARGE_INTEGER freq;
	LARGE_INTEGER start, end;

	srand(time(0));
	int a[N][N];
	
	int res[N]={};
	
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)	
			a[i][j] = rand() % 5;
				
	}

	printf_s("\nArray 1\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf_s("%d  ", a[i][j]);
		}
		puts("\n");
	}

	
	QueryPerformanceCounter(&start);
	QueryPerformanceFrequency(&freq);
	for (int k=0; k < OPERATION; k++)
	{
		_asm
		{
		    	push eax
				push ebx
				push ecx
				push esi
				mov ecx, 8
				xor eax, eax
				xor ebx, ebx
				xor esi, esi
		first_asm :
			    push ecx
				mov ecx, 8
			 second_asm :
				add eax, a[ebx]
				add ebx, 32
				dec ecx
				cmp ecx, 0
			jne second_asm
				pop ecx
				mov res[esi], eax
				add esi, 4
				mov ebx, esi
				xor eax, eax
				dec ecx
				cmp ecx, 0
		jne first_asm
				pop esi
				pop ecx
				pop ebx
				pop eax
		}

	}
	QueryPerformanceCounter(&end);
	for (int i = 0; i < N; i++)
	{
		printf_s("%d ", res[i]);

	}
		printf("\nTime asm is %f\n", (double)(end.QuadPart - start.QuadPart) / freq.QuadPart);
		puts("\n\n\n");


	QueryPerformanceCounter(&start);
	QueryPerformanceFrequency(&freq);
		for (int k=0; k < OPERATION; k++)
	{
		_asm
		{
			push eax
				push ebx
				push ecx
				push esi
				xor eax, eax
				xor ebx, ebx
				xor esi, esi
				mov ecx, 4
			first_MMX:
			    push ecx
				mov ecx, 7
				mov esi, ebx
				movq MM0, a[esi]
			second_MMX:
				add esi, 32
				movq MM1, a[esi]
				paddw MM0, MM1
				dec ecx
				cmp ecx, 0
				jne second_MMX
				pop ecx
				movq res[ebx], mm0
				add ebx, 8
				xor eax, eax
				dec ecx
				cmp ecx, 0
				jne first_MMX
				emms
				pop esi
				pop ecx
				pop ebx
				pop eax
		}
	}
	QueryPerformanceCounter(&end);
	for (int i = 0; i < N; i++)
	{
		printf_s("%d ", res[i]);

	}
		printf("\nTime MMX is %f\n", (double)(end.QuadPart - start.QuadPart) / freq.QuadPart);
		puts("\n\n\n");


	QueryPerformanceCounter(&start);
	QueryPerformanceFrequency(&freq);

	for (int k = 0; k < OPERATION; k++)
	{
		for (int i = 0; i < N; i++)
		{
			res[i] = 0;
			for (int j = 0; j < N; j++)	
				res[i] += a[j][i];
		}
	}

	QueryPerformanceCounter(&end);
	
	for (int i = 0; i < N; i++)
			printf_s("%d ", res[i]);
		
	printf("\nTime C is %f\n", (double)(end.QuadPart - start.QuadPart) / freq.QuadPart);

	_getch();
}








