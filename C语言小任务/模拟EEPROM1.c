#include <reg52.h>
sbit LED1=P2^4;
sbit LED2=P2^5;
sbit LED3=P2^6;
sbit LED4=P2^7;
sbit KEY1=P3^2;
sbit KEY2=P3^3;
sbit KEY3=P3^4;
sbit SegmentG1=P2^3;
sbit SegmentG2=P2^2;
sbit SegmentG3=P2^1;
sbit SegmentG4=P2^0;

static unsigned char s_arrNumber[]=
{0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x09,0x0c};

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

static void InitUART()
{
  SCON=0X50;
  TMOD=0X20;
  PCON=0X80;
  TL1=0XF3;
  TH1=TL1;
  TR1=1;
}

static void InitInterrupt()
{
  ES=0;
  EA=1;
  IT0=1;
  EX0=1;
}

void External0_Handler() interrupt 0
{
  ES=1;
}

void main()
{
  InitInterrupt();
  InitUART();
  
  while(1)
  {
    
  }
}

/*void UART_Handler() interrupt 4
{
  static unsigned char s_iBuffer;
  s_iBuffer=SBUF;
  RI=0;
  
  SBUF=s_iBuffer;
  while(!TI)
  {
    
  }
  TI=0;
}*/
void UART_Handler() interrupt 4
{
  /*static unsigned char s_iCounter=0;
  static unsigned char arrBuffer[11];
  static unsigned char s_iBuffer;*/
  unsigned char i;
  unsigned char arrStr[]="Hello World";
  
  /*if(1==RI)
  {
    arrBuffer[s_iCounter]=SBUF;
    RI=0;
    
    if(arrBuffer[s_iCounter]=='1')
    {
      LED1=0;
    }
    if(arrBuffer[s_iCounter]=='2')
    {
      LED2=0;
    }
    if(arrBuffer[s_iCounter]=='3')
    {
      LED3=0;
    }
    if(arrBuffer[s_iCounter]=='4')
    {
      LED4=0;
    }
    if(arrBuffer[s_iCounter]=='')
    {
      LED1=1;
    }
    if(arrBuffer[s_iCounter]=='1')
    {
      LED2=1;
    }
    if(arrBuffer[s_iCounter]=='1')
    {
      LED3=1;
    }
    if(arrBuffer[s_iCounter]=='1')
    {
      LED4=1;
    }
    
    
    if(arrBuffer[s_iCounter]>='0'&&arrBuffer[s_iCounter]<='z')
    {
      s_iCounter++;
    }
    
  }*/
  
 /* SBUF=s_iBuffer;
  while(!TI)
  {
    
  }
  TI=0;*/
  
  /*if(KEY1==0) 
 {
   DelayNms(20);
   if(KEY1==0)
 {
  for(i=0; i<10; i++)
  {
    SBUF=arrStr[i];
    while(!TI)
    {
      
    }
    TI=0;
  }
 }
 }*/
 
  for(i=0; i<11; i++)
  {
    SBUF=arrStr[i];
    while(!TI)
    {
    
    }
    TI=0;
  }
  ES=0;
}

void External1_Handler() interrupt 2
{
  
}
