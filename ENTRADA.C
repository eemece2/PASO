
#include <stdio.h>
#include <graphics.h>
#include <package.h>
#include <interfac.h>

void drawbyte(unsigned int);
void time(int i);
void COUT(unsigned int port,unsigned int data);
unsigned int CIN(unsigned int port);
unsigned int read_adc();

main()
{
	int i;
	int k,byte;
	unsigned int entrada;
	char ch;
	int g_driver,g_modo;

	g_driver=VGA;
	g_modo=VGAHI;
	initgraph(&g_driver,&g_modo,"");
/*
	CONTROLPORT:    A OUT, B OUT, C IN

	bit 7:	activo:		1
	bit 6:	modo 0:		0
	bit 5:	modo 0:		0
	bit 4:	A OUT:		0
	bit 3:	CH IN:		1
	bit 2:	modo 0:		0
	bit 1:	B OUT:		0
	bit 0:	CL IN:		1

	CONTROLPORT = 10001001 = 137d
*/

	COUT(CONTROLPORT,137);

	cleardevice();
	setcolor(8);
	for (k=0;k<=28;k=k+1)
			{
				line(145,93+k,210,93+k);
			}

	while(!kbhit())
	{
/*		entrada=CIN(CPORT);
		drawbyte(entrada);
		printf("entrada=%i \n",entrada);
		time(20000);
*/
		entrada=read_adc();
		drawbyte(entrada);
		sound();
		time(1000);
		nosound();
	}
	nosound();

	getch();
}

/* lecctura CAD TLC 549
APORT,0 CS  (OUT)
BPORT,0 CLK (OUT)
CPORT,0 DTA (IN)
*/
unsigned int read_adc()
{
	unsigned int byte,in;
	int i;

	in=0;
	time(100);
	COUT(BPORT,0);
	time(100);
	COUT(APORT,0);
	time(100);
	for(i=0;i<7;i++)
	{
		time(100);
		COUT(BPORT,255);
		time(100);
		COUT(BPORT,0);
		time(100);
		byte=CIN(CPORT);
		in*=2;
		byte=byte & 1;
		in+=byte;
	}
	COUT(APORT,255);

	return(in);
}



void drawbyte(unsigned int byte)
{
	int k,b,i,j=0;

	for (i=1;i<=128;i=i*2)
	{
		b=byte&i;
		if(b!=0)
		{
			setcolor(12);
			for (k=0;k<=14;k=k+1)
			{
				line(150+7*j,100+k,155+7*j,100+k);
			}
		}
		else
		{
			setcolor(7);
			for (k=0;k<=14;k=k+1)
			{
				line(150+7*j,100+k,155+7*j,100+k);
			}
		}

		j=j+1;
	}
}

void time(int i)
{
	int k;

	for (k=1;k<=i;k=k+1);
}




