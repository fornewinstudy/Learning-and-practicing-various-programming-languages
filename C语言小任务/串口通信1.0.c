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
  ES=1;
  EA=1;
  IT0=1;
  EX0=1;
}

void External0_Handler() interrupt 0
{
  
}

static unsigned int key=0;

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
static unsigned char s_iCounter=0;
void UART_Handler() interrupt 4
{
  static unsigned char arrBuffer[100];
  /*unsigned char i;*/
  //数据接收
  if(1==RI)
  {
    arrBuffer[s_iCounter]=SBUF;
    RI=0;
    
    /*switch(arrBuffer[100])
    {
      case "LED1":LED1=0;break;
      case "LED2":LED2=0;break;
      case "LED3":LED3=0;break;
      case "LED4":LED4=0;break;
      case '1':LED1=1;break;
      case '2':LED2=1;break;
      case '3':LED3=1;break;
      case '4':LED4=1;break;
      default:break;
    }*/
    if(arrBuffer[s_iCounter-3]=='L'&&arrBuffer[s_iCounter-2]=='E'&&arrBuffer[s_iCounter-1]=='D'&&arrBuffer[s_iCounter]=='1')
    {
      LED1=1;
    }
    /*if(arrBuffer[100]=="LED2")
    {
      LED2=1;
    }
    if(arrBuffer[100]=="LED3")
    {
      LED3=1;
    }
    if(arrBuffer[100]=="LED4")
    {
      LED4=1;
    }*/
    if(arrBuffer[s_iCounter-3]=='L'&&arrBuffer[s_iCounter-2]=='E'&&arrBuffer[s_iCounter-1]=='D'&&arrBuffer[s_iCounter]=='O')
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
    
    if(arrBuffer[s_iCounter]>='0'&&arrBuffer[s_iCounter]<='z')
    {
      s_iCounter++;
    }
  }
  //数据发送
  /*for(i=0; i<11; i++)
  {
    SBUF=arrBuffer[i];
    while(!TI)
    {
    
    }
    TI=0;
  }*/
}

void External1_Handler() interrupt 2
{
  
}
