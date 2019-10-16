/* perfil.c */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <dos.h>


int lectura_perfil(char *acceso,char *nombre,int *num_b,float *xb,float *yb);
int escritura_perfil(char *acceso_salida,char *nombre,int num_b,float *xb,float *yb);

	float escala;

main()
{
	char nombre[30];
	char acceso_entrada[20]="rg15.dat";
	char acceso_salida[20]="rg15-75.dat";
	float xb[200],yb[200];
	float xs[200],ys[200];
	int num_b;
	int i;


	clrscr();

	lectura_perfil(acceso_entrada,nombre,&num_b,xb,yb);
	printf("\nRelaci¢n de escala en eje y:");
	scanf("%f",&escala);
	for(i=0;i<num_b;i++)
	{
		xs[i]=xb[i];
		ys[i]=yb[i]*escala;
	}
	escritura_perfil(acceso_salida,nombre,num_b,xs,ys);
	getch();

}



int lectura_perfil(char *acceso,char *nombre,int *num_b,float *xb,float *yb)
{
	FILE *fptr;
	int i,fin;

	if((fptr=fopen(acceso,"rt"))!=NULL)
	{
		fscanf(fptr,"%[^\n]\n",nombre);
		printf(nombre);

		i=0;
		fin=1;
		while(fin==1)
		{
			fscanf(fptr,"%f",&xb[i]);
			fin=fscanf(fptr,"%f",&yb[i]);
			i++;
		}
		*num_b=i-1;
                if(fclose(fptr)!=0) printf("  no se pudo cerrar");
		return(0);
	}
        else
	{
		printf("no se pudo abrir");
		getch();
		return(1);
	}

}

int escritura_perfil(char *acceso_salida,char *nombre,int num_b,float *xs,float *ys)
{
	FILE *fptr;
	int i,fin;

	if((fptr=fopen(acceso_salida,"wt"))!=NULL)
	{
		fprintf(fptr,nombre);
		fprintf(fptr," (escala=%f)\n",escala);
		for(i=0;i<num_b;i++)
		{
			fprintf(fptr,"%f %f\n",xs[i],ys[i]);
		}
		printf(nombre);
		printf(" (escala=%f)\n",escala);


                if(fclose(fptr)!=0) printf("  no se pudo cerrar");
		return(0);
	}
        else
	{
		outtextxy(100,100,"no se pudo abrir");
		getch();
		return(1);
	}

}