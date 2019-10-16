#include <stdio.h>
#include <dos.h>

void espera();

main()
{
	union REGS inregs,outregs;
	unsigned int outlo,outhi;
	int registro,entrada;
	int espera;

/*	N§ purto serie: DX= 0 ¢ 1
	configuracion( AL ):
	velocidad:	000=110 bps
	paridad:        00=ninguna
	stop bits:	0=1 bit
	longitud:       11= 8 bits
	AL=00000011=0x03
*/
	clrscr();
	printf("espera:");
	scanf("%d",&espera);

	inregs.h.ah=0x00;
	inregs.x.dx=0x0001;
	inregs.h.al=0x003;
	 int86(0x014,&inregs,&outregs);
	outlo=outregs.h.al;
	outhi=outregs.h.ah;
/*
	printf("al=%i , ah=%i\n",outlo,outhi);
*/

	registro=0;
	while(!kbhit())
	{
		printf("salida=%d, ",registro);
		inregs.h.ah=0x01;
		inregs.x.dx=0x0001;
		inregs.h.al=registro;
		 int86(0x014,&inregs,&outregs);

		outregs.h.al=0;
		delay(1000);
		inregs.h.ah=0x02;
		inregs.x.dx=0x0001;
		 int86(0x014,&inregs,&outregs);
		entrada=outregs.h.al;
		printf("entrada=%d\n",entrada);
		registro++;
		if(registro==16) registro=0;
		delay(espera);
	}
}

void espera()
{
	int i,j;

	for(i=0;i<=60000;i++);
}

