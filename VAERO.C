/* vaero.c */

#include <stdio.h>
#include <math.h>

char acceso[]={"s4083.dat"};
char acceso_v[]={"s4083_v.dat"};
char nombre[30];

float xb[500],yb[500];
float xv[500],yv[500];
int i,num_b,fin;
FILE *fptr;
float cm0,alfa0;
float espesor,c_espesor;
float flecha,c_flecha;


main()
{
	clrscr();
	printf("Nombre del fichero formato Selig (Entrada):");
	gets(acceso);
	printf("\nNombre del fichero formato Visuaero (Salida):");
	gets(acceso_v);
	printf("\nCoeficiente de momento (Cm0):");
	scanf("%f",&cm0);
	printf("\nAngulo sustentaci¢n nula (Alfa0):");
	scanf("%f",&alfa0);
	alfa0=-2.5;
	cm0=-.4;
	espesor=8;
	c_espesor=40;
	flecha=2;
	c_flecha=50;


	if((fptr=fopen(acceso,"rt"))!=NULL)
	{

/* lectura del perfil */
		fscanf(fptr,"%[^\n]\n",nombre);
		i=0;
		fin=1;
		while(fin==1)
		{
			fscanf(fptr,"%f",&xb[i]);
			fin=fscanf(fptr,"%f",&yb[i]);
			i++;
		}
		num_b=i-1;
		if(fclose(fptr)!=0) printf("  no se pudo cerrar");
	}
	else
	{
		printf("no se pudo abrir");
	}

/* modificacion */

	for(i=0;i<=num_b;i++)
	{
		xv[i]=100.0*xb[i];
		yv[i]=100.0*yb[i];
	}


/*  escritura fichero */
	if((fptr=fopen(acceso_v,"wt"))!=NULL)
	{
		fprintf(fptr,"%s\n",nombre);
		fprintf(fptr,"%f %f\n",espesor,c_espesor);
		fprintf(fptr,"%f %f\n",flecha,c_flecha);
		fprintf(fptr,"%f %f\n",cm0,alfa0);
		for(i=0;i<num_b;i++)
		{
			fprintf(fptr,"%f ",xv[i]);
			fprintf(fptr,"%f\n",yv[i]);
		}
		if(fclose(fptr)!=0) printf("  no se pudo cerrar (s)");
	}
	else
	{
		printf("no se pudo habrir (s)");
	}

}

