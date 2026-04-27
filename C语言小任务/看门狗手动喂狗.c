#include <reg52.h>

sbit BEEP=P1^0;
sbit LED1=P2^4;
sbit LED2=P2^5;
sbit LED3=P2^6;
sbit LED4=P2^7;
sbit KEY1=P3^2;

sfr WDT_CONTR=0xE1;

static void DelayNms(int nms)
{
  unsigned int i,j;
  for(i=0;i<nms;i++)
  {
    for(j=0;j<123;j++)
    {
      
    }
  }
}


static void InitInterrupt()
{
  IT0=1;
  EX0=1;
  EA=1;
}

void main()
{
  unsigned char i;
  
  /*BEEP=0;
  DelayNms(100);
  BEEP=1;*/
  
  InitInterrupt();
  WDT_CONTR=0x33;
  while(1)
  {
    //流水灯
    P2=0xEF;
    for(i=0;i<4;i++)
    {
      DelayNms(500);
      P2=P2<<1;
    }
    DelayNms(250);
  }
}

void External0_Handler() interrupt 0
{
  WDT_CONTR|=0x10;
}
