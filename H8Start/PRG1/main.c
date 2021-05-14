/****************************************************************
KPIT Cummins Infosystems Ltd, Pune, India. - 10-Mar-2003.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*****************************************************************/

/*****************************************************************
program testowy, zadawanie czestotliwosci z potencjometry 100Hz - 5kHz z dokladnoscia do 10 Hz
ustawianie wypelnienia 5-95 z klawiatury, podobnie z klawiatury start i stop ukladu

*****************************************************************/

#include "iodefine.h"
#include "lcd.h"
#include "inline.h"
#define	 klawiatura_Obszar 0x20000
#define  klawiatura_Bufor (*(volatile unsigned char*)(klawiatura_Obszar+1)) 


//deklaracje funkcji z main

void Ekran_startowy();

void init_ITU2(void);
void init_ITU0(void);



void odczyt_klawiaure(void);

void startPWM();
void changePWM();
void stopPWM(void);

void int_ready_changePWM(void);


short count=0;
short licznik0=0,licznik1=0;




char stan_pracy=0;

short wypelnienie=5;
short Fzadane=10;
short Tryb_Pracy=1;
short Stala_Pracy=8;

short time=0;

long takty=800;


//------------ wlasciwy program -----------------------------------

int main (void)
{
	stopPWM();
	IniLCD();
	init_ITU0();
	init_ITU2();
	
				
	while(1)						//petla glowna
	{
		
		if(ITU2.TSR.BIT.IMFB==1)
		{
			
			ITU2.TSR.BIT.IMFB=0;
			
			count++;
			if(!(count%100))odczyt_klawiaure();
			if(stan_pracy==1)
			{
				if(!(count%50))
				{

					Ekran_startowy();
				}
		
			}
			else
			{
				if(!(count%50))
				{	
					Ekran_startowy();
				
				}
				
			}		
		}
			
		
	}
}
	
void odczyt_klawiaure()
{
	unsigned char temp = klawiatura_Bufor&0x7f;	
	switch(temp)
	{
		case 0x7e: //start
		{
			stan_pracy=1;
			startPWM();
			break;	
		}
		case 0x7d: //stop
		{
			stan_pracy=0;
			stopPWM();
			break;	
		}
		case 0x7b: //
		{
			if(Tryb_Pracy<5)Tryb_Pracy++;
			else Tryb_Pracy=1;
			changePWM();
			
			break;	
		}
		case 0x77: //
		{
			
			break;	
		}								
	}
	
}
void startPWM()
{
	ITU.TSTR.BIT.STR4=0;
	ITU4.TCR.BYTE=0xA3;	
	
	switch(Tryb_Pracy)
	{
		case 1: 
		{
			ITU4.GRA=200 ;
			
			break;	
		}
		case 2: 
		{	
			ITU4.GRA=250 ;

			break;	
		}
		case 3: 
		{
				ITU4.GRA=333 ;
	
			break;	
		}
		case 4: 
		{
			
				ITU4.GRA=500 ;
	
			break;	
		}	
		case 5: 
		{
				ITU4.GRA=1000 ;
	
			break;	
		}											
		
	}
	
	ITU4.TIOR.BYTE=0xF8;
	ITU4.TIER.BYTE=0xF8;
	ITU.TMDR.BYTE=0x90;
	
	ITU.TSTR.BIT.STR4=1;
}
void changePWM()
{
	switch(Tryb_Pracy)
	{
		case 1: 
		{
			ITU4.GRA=200 ;
			
			break;	
		}
		case 2: 
		{	
			ITU4.GRA=250 ;

			break;	
		}
		case 3: 
		{
			ITU4.GRA=333 ;
	
			break;	
		}
		case 4: 
		{
			
			ITU4.GRA=500 ;
	
			break;	
		}	
		case 5: 
		{
			ITU4.GRA=1000 ;
	
			break;	
		}											
		
	}
}
void stopPWM(void)
{
	ITU.TSTR.BIT.STR4=0;
	//ITU.TSTR.BIT.STR4=1;
}

void init_ITU0(void)
{
	ITU.TSTR.BIT.STR0=0;
	ITU0.TCNT=0;
	ITU0.TIOR.BYTE=0x8C;
	ITU0.TCR.BYTE=0xA3;
	ITU0.TIER.BYTE=0xFD;
	ITU.TSTR.BIT.STR0=1;	
}
void odczyt_zew()
{
	takty=time*65536+ITU0.GRA;
	long pre =20000000;
	takty=pre/takty;
	if(takty<2)
	{
		takty = 1;
		ITU4.GRB =ITU4.GRA*2/100 ;	
	}
	else if(takty>800)
	{
		takty = 800;
		ITU4.GRB =ITU4.GRA*98/100 ;	
	}
	else
	{
		ITU4.GRB =ITU4.GRA*takty/800 ;		
	}
	
	ITU0.TSR.BIT.IMFA=0;
	time=0;
}
void incre()
{
	time++;	
	ITU0.TSR.BIT.OVF=0;
}

void init_ITU2(void)
{
	ITU.TSTR.BIT.STR2=0;
	
	ITU2.TCR.BYTE=0xC3;
	
	ITU2.GRB=1999;
	
	ITU.TSTR.BIT.STR2=1;
}

//------- ekran startowy po wlaczeniu ukladu

void Ekran_startowy()
{
	if(stan_pracy)Put_S("START");
	else Put_S("STOP ");
	
    GotoXY(1,7);
	Put_S("ITUC=");
	Put_4N(takty*10);
	GotoXY(2,0);
	Put_S("F=");
	switch(Tryb_Pracy)
	{
		case 1: 
		{
		Put_4N(10*100);
			break;	
		}
		case 2: 
		{	
		Put_4N(8*100);
			break;	
		}
		case 3: 
		{
			Put_4N(6*100);
			break;	
		}
		case 4: 
		{
			Put_4N(4*100);
			break;	
		}	
		case 5: 
		{
			Put_4N(2*100);
			break;	
		}								
		
	}
	Put_S("KHz ");
	
	if(takty==800)
	{
		Put_S("MAX");
	}
	else if(takty<9)
	{
		Put_S("MIN");
	}
	else
	{
		Put_S("   ");
	}
	
	GotoXY(1,1);	
}

void Put_S(char*x)
{
	do
	{
		putchar(*x);
		x++;
	}
	while(*x);	
}
void Put_N(short x)
{
	putchar('0'+x);		
}
void Put_4N(short x)
{
	if(x<1000)
	{
		putchar(' ');		
	}
	else
	{		
		Put_N(x/1000);
	}
	
	Put_N((x/100)%10);
	putchar('.');
	Put_N((x/10)%10);
	Put_N(x%10);
}

