b#include                                                                                              <stdio.h>
#include <dos.h>

void inicializa();
void transmite(int caracter);
int trnsmt_cmd(int id,int cmd,int data);
int recive();

#define	CMD_INICIALIZ	0
#define CMD_DESACTIVA	1
#define	CMD_ACTIVA	2
#define	CMD_INICIOMOV	3
#define	CMD_PASOSL	4
#define	CMD_PASOSH	5
#define	CMD_RAMPA	6
#define	CMD_SENTIDO	7
#define	CMD_PASO_I	8
#define	CMD_PASO_D	9
#define	CMD_POSICL	128
#define	CMD_POSICH	129
#define	CMD_ESTADO	130

main()
{
	union REGS inregs,outregs;
	unsigned int outlo,outhi;
	int i;
	int pasosh,pasosl,time,rampa,sentido;
	int id;
	char ch;
	int elec;


	clrscr();
while(ch!=' ')
{
	id=1;
	inicializa();

	printf("autonomo(0) o no(1):");
	scanf("%d",&elec);
	if(elec==0)
	{
	printf("pasosh:");
	scanf("%d",&pasosh);
	printf("pasosl:");
	scanf("%d",&pasosl);
	printf("rampa:");
	scanf("%d",&rampa  );
	printf("sentido:");
	scanf("%d",&sentido);

	trnsmt_cmd(id,CMD_INICIALIZ,	0    );
	trnsmt_cmd(id,CMD_PASOSL,	pasosl);
	trnsmt_cmd(id,CMD_PASOSH,	pasosh);
	trnsmt_cmd(id,CMD_RAMPA,	rampa);
	trnsmt_cmd(id,CMD_SENTIDO,	sentido);
/*	trnsmt_cmd(id,CMD_ACTIVA,	0    );
*/
	trnsmt_cmd(id,CMD_INICIOMOV,	0    );
	}
	else
	{
	printf("pasos:");
	scanf("%d",&pasosl);
	printf("delay:");
	scanf("%d",&time  );
        trnsmt_cmd(id,CMD_INICIALIZ,	0    );
	trnsmt_cmd(id,CMD_ACTIVA,	0    );
	for(i=0;i<pasosl;i++)
	{
		delay(time);
		trnsmt_cmd(id,CMD_PASO_I,0);
	}
	for(i=0;i<pasosl;i++)
	{
		delay(time);
		trnsmt_cmd(id,CMD_PASO_D,0);
	}
	}

	ch=getch();
}
trnsmt_cmd(id,CMD_DESACTIVA,	0    );
}

void inicializa()
{
	union REGS inregs,outregs;

        /*	N§ purto serie: DX= 0 ¢ 1
	configuracion( AL ):
	velocidad:	110=4800 bps
	paridad:        00=ninguna
	stop bits:	0=1 bit
	longitud:       11= 8 bits
	AL=11000011=0x0C3
*/

	inregs.h.ah=0x00;
	inregs.x.dx=0x0001;
	inregs.h.al=0x0C3;
	 int86(0x014,&inregs,&outregs);
}


void transmite(int caracter)
{
	union REGS inregs,outregs;

	inregs.h.ah=0x01;
	inregs.x.dx=0x0001;
	inregs.h.al=caracter;
	 int86(0x014,&inregs,&outregs);
}
int recive()
{
	union REGS inregs,outregs;

	inregs.h.ah=0x02;
	inregs.x.dx=0x0001;
	 int86(0x014,&inregs,&outregs);
	return(outregs.h.al);
}

int trnsmt_cmd(int id,int cmd,int data)
{
	transmite(id);
	transmite(cmd);
	transmite(data);
}