#include "stdio.h"
#include <string.h>
#include <locale.h>
int powers[5]={1,2,4,8,16};
char calculateControlBit(char * s,int bit){

    int currentPosition = bit;
    int ones=0;
    while (currentPosition < 22)
    {
        for (int i=0;i<bit && currentPosition < 22;i++){
            if (s[currentPosition+i]== '1' && ((currentPosition+i) != bit))
                ones++;
        }
        currentPosition += (2*bit);
    }
    if (ones % 2) return '1';
    else return '0';
}

int isPow2(int a) {
  return !(a&(a-1));
}

char flip(char a)
{
    if (a == '0')
        return '1';
    else return '0' ;
}

int getCorruptedBitNumber(char * a,char * b){
    int i = 0;
    int number = 0;
    while (a[i]){
        if (a[i]!=b[i]){
            number += powers[i];
        }
        i++;
    }
    return number;
}

int main(int argc, char *argv[])
{
char c = 'a';
while(c!='n' && c!='N' ) {
    char packet[3];
    char bits[2][10];
    char coded[23]="                      ";
    puts("введите пакет (2 символа)\n");
    scanf("%s",packet);
    puts("\n");
    for (int i=0;i<2;i++)
    {
        bits[i][9]=0;
        bits[i][0]=' ';
        for (int j=8;j>0;j--)
        {
            int ost = packet[i] % 2;
            packet[i] /= 2;
            if (ost)
                bits[i][j]= '1';
            else
                bits[i][j]= '0';
        }
    }
    puts(bits[0]);
    puts(bits[1]);
    char packetBits[18]="                 ";
    for (int i=0;i<2;i++)
        for (int j=1;j<=8;j++){
            packetBits[j+(i*8)]=bits[i][j];
        }
    int codedPosition=1;
    int bitPosition=1;
    while (codedPosition <22 ){
        if (isPow2(codedPosition)){
            codedPosition++;
        } else {
            coded[codedPosition] = packetBits[bitPosition];
            codedPosition++;
            bitPosition++;
        }
    }
    coded[1] = calculateControlBit(coded,1);
    coded[2] = calculateControlBit(coded,2);
    coded[4] = calculateControlBit(coded,4);
    coded[8] = calculateControlBit(coded,8);
    coded[16] = calculateControlBit(coded,16);
    puts("закодированный пакет:\n");
    puts(coded);

    puts("выберите, в каком бите допустить ошибку: (1-21)\n");
    int corrupted;
    scanf("%d", &corrupted);
    coded[corrupted] = flip(coded[corrupted]);
    puts("сообщение с ошибкой:\n");
    puts(coded);
    char receivedControl[6]="     ";
    char calculatedControl[6]="     ";

    receivedControl[0]=coded[1];
    receivedControl[1]=coded[2];
    receivedControl[2]=coded[4];
    receivedControl[3]=coded[8];
    receivedControl[4]=coded[16];

    calculatedControl[0]=calculateControlBit(coded,1);
    calculatedControl[1]=calculateControlBit(coded,2);
    calculatedControl[2]=calculateControlBit(coded,4);
    calculatedControl[3]=calculateControlBit(coded,8);
    calculatedControl[4]=calculateControlBit(coded,16);
    puts("полученные контр. биты:\n");
    puts(receivedControl);
    puts("вычисленные контр. биты:\n");
    puts(calculatedControl);
    corrupted = getCorruptedBitNumber(receivedControl,calculatedControl);
    printf("номер бита с ошибкой: %d \n",corrupted);
    coded[corrupted] = flip(coded[corrupted]);
    puts("ошибка исправлена:\n");
    puts(coded);
    memmove(coded+1,coded+3,20);
    memmove(coded+2,coded+3,20);
    memmove(coded+5,coded+6,15);
    memmove(coded+12,coded+13,8);
    puts("исходное сообщение в двоичном представлении\n");
    puts(coded);
    puts("закодировать еще один пакет? Y/N?\n");
    fflush(stdin);
    c=getchar();
}
    return 0;
}

