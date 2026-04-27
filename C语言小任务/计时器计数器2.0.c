#include<reg52.h>

sbit LED1=P2^4;
sbit KEY1=P3^2;
sbit SegmentG1=P2^3;
sbit SegmentG2=P2^2;
sbit SegmentG3=P2^1;
sbit SegmentG4=P2^0;

static unsigned char s_arrNumber[]=
{0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x09};

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
  ET0=1;
  
  IT0=1;
  EX0=1;
  
  EA=1;
}

static void InitTimer0()
{
  TMOD=0x01;
  TH0=0xFC;
  TL0=0x18;
  TR0=1;
}

static unsigned int s_iCounter=0;
static unsigned int key=0;

static void count()
{
  static unsigned int s2;
  static unsigned int s3;
  static unsigned int s4;
  
  while(1)
  {
  if (10 <= s_iCounter )
	{
		if (10 <=s2)
		{
			if (10 <= s3)
			{
				if (10 <= s4)
				{
					s_iCounter = 0;
				}
				else
				{
					s4++;
				}
				s3 = 0;
			}
			else
			{
				s3++;
			}
			s2 = 0;
		}
		else
		{
			s2++;
		}
		s_iCounter = 0;
	}
	else
	{
		s_iCounter++;
	}
  
  
    P0=s_arrNumber[s4];
    SegmentG1=0;
    DelayNms(5);
    SegmentG1=1;
  
    P0=s_arrNumber[s3];
    SegmentG2=0;
    DelayNms(5);
    SegmentG2=1;
  
    P0=s_arrNumber[s2];
    SegmentG3=0;
    DelayNms(5);
    SegmentG3=1;
  
    P0=s_arrNumber[s_iCounter];
    SegmentG4=0;
    DelayNms(5);
    SegmentG4=1;
  }
}  

void main()
{
  InitInterrupt();
  InitTimer0();
  
  if(1==KEY1)
  {
    key=0;
  }
   while(1)
   {
     
   }
}

void Timer0_Handler() interrupt 1
{
  TH0=0xFC;
  TL0=0x18;
  
  if(key==1)
  {
  s_iCounter++;
    count();
  }
  
  if(key==0)
  {
    
  }
}

void External0_Handler() interrupt 0
{
  key=1;
}
