
#include <stdio.h>
#include <graphics.h>
#include <package.h>

void drawbyte(unsigned int);
void time(int i);
void COUT(unsigned int port,unsigned int data);
unsigned int CIN(unsigned int port);

main()
{
	int i;
	int k,byte;
	unsigned int j;
	char ch;
	int g_driver,g_modo;

	g_driver=VGA;
	g_modo=VGAHI;
	initgraph(&g_driver,&g_modo,"");


	COUT(819,128);

	cleardevice();
	setcolor(8);
	for (k=0;k<=28;k=k+1)
			{
				line(145,93+k,210,93+k);
			}

	while(!kbhit())
	{
		COUT(816,i);
		drawbyte(i);
		time(20000);
		i=i+1;
	}

	getch();
	COUT(816,0);

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




