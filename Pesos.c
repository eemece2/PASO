/* pesos.c */
/* calcula pesos de un ala de foam y fibra */

#include <stdio.h>
#include <math.h>

char acceso[]={"s4083.dat"};
char acceso_v[]={"s4083_p.dat"};
char nombre[30];

float xb[500],yb[500];
int i,num_b,fin;
FILE *fptr;

int num_c;
float env;
float cuerda[10];
float d_foam;
float d_fibra;
float rel_rf;

float perimetro;
float area[10],volumen[10],peso[10];
float area_perfil[10];
float volumen_t,peso_t;
float sup_fibra;
float  peso_foam,peso_fibra,peso_resina;


main()
{
	clrscr();

	num_c=2;
	d_foam=30.0;
	d_fibra=50.0;
	rel_rf=2.0;
	cuerda[0]=180;
	cuerda[1]=170;
	env=200;

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

/* calculo */

	perimetro=0.0;
	area[0]=0.0;
	for(i=0;i<=num_b-2;i++)
	{
		area[0]+=(xb[i+1]-xb[i])*(yb[i+1]+yb[i])/2;
	/*	perimetro+=abs(xb[i+1]-xb[i]); */
		perimetro+=sqrt((xb[i+1]-xb[i])*(xb[i+1]-xb[i])+
				(yb[i+1]-yb[i])*(yb[i+1]-yb[i]));
		    i=i;
	}
	area_perfil[0]=-(area[0]*cuerda[0]*cuerda[0])/100.0;
	perimetro=perimetro*cuerda[0]/10.0;
	volumen_t=area_perfil[0]*env/10.0;
	peso_foam=volumen_t*d_foam/1000.0;
	sup_fibra=env*perimetro/10.0;
	peso_fibra=sup_fibra*d_fibra/10000.0;
	peso_resina=peso_fibra*rel_rf;
	peso_t=peso_foam+peso_fibra+peso_resina;

	printf("Perfil = %s \n",nombre);
	printf("Envergadura = %#0.1f mm \n",env);
	printf("Cuerda = %#0.1f mm \n",cuerda[0]);
	printf("Densidad fibra = %#0.1f g/m2 \n",d_fibra);
	printf("Rel. resina/fibra = %#0.2f \n\n",rel_rf);

	printf("area perfil= %#0.2f cm2\n",area_perfil[0]);
	printf("perimetro perfil= %#5.2f cm\n",perimetro);
	printf("volumen = %#0.2f cm3 ( %#0.2f dm3 )\n",volumen_t,volumen_t/1000.0);
	printf("area fibra= %#0.2f cm2 ( %#0.2f dm2 )\n",sup_fibra,sup_fibra/100.0);
	printf("peso foam = %0.2f gr\n",peso_foam);
	printf("peso fibra = %0.2f gr\n",peso_fibra);
	printf("peso resina = %0.2f gr\n",peso_resina);
	printf("peso total = %0.2f gr\n",peso_t);
	getch();

/*  escritura fichero */
/*	if((fptr=fopen(acceso_v,"wt"))!=NULL)
	{
		fprintf(fptr,"%s_s\n",nombre);
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
*/
}

