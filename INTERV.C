/* INTERV.C
CALCULA INTERVALOS DE TIEMPO Y FRECUENCIAS, PARA
ACEL. LINEALES DEL PaP
*/

#include <stdio.h>
#include <math.h>

main()
{
	int m,k,q;
	float f1,fs,b,time,interval,freq;
	int divisor;
	float sq,a;
	char ch;
	FILE *file_ptr;
	int elec,toc;

	divisor=16;

while(ch!=' ')
{
	clrscr();

	printf("pantalla(0) ¢ fichero(1)?:");
	scanf("%d",&elec);
	printf("\ntabla(0) ¢ codigo(1)?:");
	scanf("%d",&toc);
	printf("Frec.inicial:");
	scanf("%fd",&f1);
	printf("\nFrec.maxima:");
	scanf("%f",&fs);
	printf("\nNumero de pasos para aceleraci¢n:");
	scanf("%d",&m);
	a=((2*(float)m-3)*(2*(float)m-3)+(fs/f1)*(fs/f1)-1);
	sq=sqrt(a);
	b=2*(fs*fs-f1*f1)/(sq+(2*m-3));
	clrscr();
	if(elec==1)
	{
	file_ptr=fopen("a:\interv3.dat","wt");
	fprintf(file_ptr,"\nFrec.inicial=%4.0f, Frec.maxima=%4.0f",f1,fs);
	fprintf(file_ptr,"\nAceleraci¢n=%4.2f pasos/s2",b);
	fprintf(file_ptr,"\nNumrero de pasos para aceleraci¢n m=%d",m);
	fprintf(file_ptr,"\n\nm	Tm(ms)		Intervalo(ms)	Freq(Hz)	Qm");
	for(k=1;k<=m;k++)
	{
		time=2*(k-1)/(sqrt(fs*fs-2*(m-k)*b)+sqrt(fs*fs-2*(m-1)*b));
		interval=2/(sqrt(fs*fs-2*(m-k-1)*b)+sqrt(fs*fs-2*(m-k)*b));
		if(k==m) interval=1/fs;
		freq=1/interval;
		q=(int)((interval*1000000-30)/divisor);

		if(toc==0)
		{
		fprintf(file_ptr,"\n%d	%4.3f		%4.4f		%4.0f		%d",k,time*1000,interval*1000,freq,q);
		}
		else fprintf(file_ptr,"\n	RETLW	D'%d'	;%d",q,k-1);
	}
	fclose(file_ptr);
	}
	else
	{
	printf("\nFrec.inicial=%4.0f, Frec.maxima=%4.0f",f1,fs);
	printf("\nAceleraci¢n=%4.2f pasos/s2",b);
	printf("\nNumrero de pasos para aceleraci¢n m=%d",m);
	getch();
	printf("\n\nm	Tm(ms)		Intervalo(ms)	Freq(Hz)	Qm");
	for(k=1;k<=m;k++)
	{
		time=2*(k-1)/(sqrt(fs*fs-2*(m-k)*b)+sqrt(fs*fs-2*(m-1)*b));
		interval=2/(sqrt(fs*fs-2*(m-k-1)*b)+sqrt(fs*fs-2*(m-k)*b));
		if(k==m) interval=1/fs;
		freq=1/interval;
		q=(int)((interval*1000000-30)/divisor);
		if(toc==0)
		{
		printf("\n%d	%4.3f		%4.4f		%4.2f		%d",k,time*1000,interval*1000,freq,q);
		}
		else printf("\n	RETLW	D'%d'	;%d",q,k-1);
	}
        ch=getch();
	}

}
}
