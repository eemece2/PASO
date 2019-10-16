#include <stdio.h>
#include <dos.h>


main()
{
	union REGS inregs,outregs;
	unsigned int outlo,outhi;

/*	N§ purto serie: DX= 0 ¢ 1
	configuracion( AL ):
	velocidad:	000=110 bps
	paridad:        00=ninguna
	stop bits:	0=1 bit
	longitud:       11= 8 bits
	AL=00000011=0x003
*/
	clrscr();

{
	inregs.h.ah=0x00;
	inregs.x.dx=0x0001;
	inregs.h.al=0x003;
	 int86(0x014,&inregs,&outregs);
	outlo=outregs.h.al;
	outhi=outregs.h.ah;

	printf("al=%i , ah=%i\n",outlo,outhi);

	inregs.h.ah=0x01;
	inregs.x.dx=0x0001;
	inregs.h.al=0x0AA;
	 int86(0x014,&inregs,&outregs);
	outlo=outregs.h.al;
	outhi=outregs.h.ah;

	printf("ah=%i\n",outhi);

}
getch();
}
