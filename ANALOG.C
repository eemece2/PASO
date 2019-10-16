
#include <stdio.h>
#include <graphics.h>
#include <package.h>
#include <math.h>
#include <dos.h>

void drawbyte(unsigned int);
void time(int i);
void COUT(unsigned int port,unsigned int data);
unsigned int CIN(unsigned int port);

#define APORT 816
#define BPORT 817
#define CPORT 818
#define CONTROLPORT 819

main()
{
	union REGS inregs,outregs;
	int alo,ahi;
	int caracter,entrada;
	char tec='a';

	int eoc;
	int i,iold;
	int k,byte;
	unsigned int j;
	char ch;
	int g_driver,g_modo;

	int c1,c2,c3,c4;
	int c1o,c2o,c3o,c4o;
	int h,ah,p;
	int in[640];
	int tim;

	g_driver=VGA;
	g_modo=VGAHI;
	initgraph(&g_driver,&g_modo,"c:\\lenguage\\turboc");


	COUT(CONTROLPORT,146);   /* A IN, B IN, C OUT  */

while(tec!=' ')
{
	cleardevice();
	setcolor(4);
	tim=200;
/*	printf("time=");
	scanf("%d",&tim);*/
	printf("caracter=");
	scanf("%d",&caracter);

	k=0;
	i=0;
	h=150;
	ah=70;
	p=40;

	line(0,h     ,630,h     );
	line(0,h+ah  ,630,h+ah  );
/*	line(0,h+ah*2,630,h+ah*2);
	line(0,h+ah*3,630,h+ah*3);
*/

/*	while(i&1==0)
	{
		i=CIN(APORT);
	}
*/

/*	velocidad: 000=110 bps;
	paridad: 00=ninguna
	n§ de bits finales: 0= 1 bits;
	longitud: 11=8 bits;
	00000011=0x07
*/

	inregs.h.ah=0x00;
	inregs.x.dx=0x0001;
	inregs.h.al=0x03;
	int86(0x014,&inregs,&outregs);

	inregs.h.ah=0x01;
	inregs.x.dx=0x0001;
	inregs.h.al=caracter;

	int86(0x014,&inregs,&outregs);

/*	int86(0x014,&inregs,&outregs);
*/
	for(k=0;k<=630;k++)
	{
		in[k]=CIN(APORT);
		time(tim);
	}
	outregs.h.al=0;
	inregs.h.ah=0x02;
	inregs.x.dx=0x0001;
	int86(0x014,&inregs,&outregs);
	entrada=outregs.h.al;
	printf("entrada=%d",entrada);

	for(k=0;k<=630;k++)
	{
		c1=in[k]&1;
		c2=in[k]&2;c2=c2/2;
		c3=in[k]&4;c3=c3/4;
		c4=in[k]&8;c4=c4/8;
		setcolor(15);
		putpixel(k,h     -c1*p,15);
		putpixel(k,h+ah  -c2*p,15);
/*		putpixel(k,h+ah*2-c3*p,15);
		putpixel(k,h+ah*3-c4*p,15); */

		line(k-1,h     -c1o*p,k,h     -c1*p);
		line(k-1,h+ah  -c2o*p,k,h+ah  -c2*p);
/*		line(k-1,h+ah*2-c3o*p,k,h+ah*2-c3*p);
		line(k-1,h+ah*3-c4o*p,k,h+ah*3-c4*p); */
		c1o=c1;
		c2o=c2;
		c3o=c3;
		c4o=c4;
	}
	drawbyte(caracter);
	tec=getch();
}

/*	COUT(CONTROLPORT,128); */

}

void drawbyte(unsigned int byte)
{
	int k,b,i,j=0;
	int anch=8;
	int alt=20;

	for (i=1;i<=128;i=i*2)
	{
		b=byte&i;
		if(b!=0)
		{
			setcolor(15);
			for (k=0;k<=alt;k=k+1)
			{
				line(150+anch*j,50+k,150+anch*j+anch,50+k);
			}
		}
		else
		{
			setcolor(0);
			for (k=0;k<=alt;k=k+1)
			{
				line(150+anch*j,50+k,155+anch*j+anch,50+k);
			}
		}
		setcolor(15);
		line(150+anch*j     ,50    ,150+anch*j     ,50+alt);
		line(150+anch*j+anch,50    ,150+anch*j+anch,50+alt);
		line(150+anch*j     ,50    ,150+anch*j+anch,50    );
		line(150+anch*j     ,50+alt,150+anch*j+anch,50+alt);

		j=j+1;
	}
}

void time(int i)
{
	int k;

	for (k=1;k<=i;k++);
}




