/* spline.c */

#include <stdio.h>
#include <math.h>

float x_spline(float t,int num);
float y_spline(float t,int num);

char acceso[]={"s4083.dat"};
char acceso_s[]={"s4083_s.dat"};
char nombre[30];

float xb[500],yb[500];
float xs[500],ys[500];
float xf[1000],yf[1000];
float xt,yt;
int i,num_b,num_s,fin;
FILE *fptr;

int j,t,num_f;
float par_t;

main()
{
	clrscr();

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
/* puntos iniciales */
	xs[0]=2*xb[0]-xb[1];
	ys[0]=2*yb[0]-yb[1];
	for(i=1;i<=num_b;i++)
	{
		xs[i]=xb[i-1];
		ys[i]=yb[i-1];
	}
	xs[i]=2*xb[i-2]-xb[i-3];
	ys[i]=2*yb[i-2]-yb[i-3];
	num_s=i+1;

/* interpolaci¢n */

	j=0;

	for(i=3;i<=num_s-1;i++)
	{
		for(t=0;t<=3;t++)
		{
			par_t=((float)t)/4.0;
			xf[j]=x_spline(par_t,i);
			yf[j]=y_spline(par_t,i);
			j++;
		}
	}
	num_f=j;

/*  escritura fichero */
	if((fptr=fopen(acceso_s,"wt"))!=NULL)
	{
		fprintf(fptr,"%s_s\n",nombre);
		for(i=0;i<num_f;i++)
		{
			fprintf(fptr,"%f ",xf[i]);
			fprintf(fptr,"%f\n",yf[i]);
		}
		if(fclose(fptr)!=0) printf("  no se pudo cerrar (s)");
	}
	else
	{
		printf("no se pudo habrir (s)");
	}

	getch();
}

float x_spline(float t,int num)
{
	float x;
	float m11=-1,m21= 2,m31=-1,m41=0;
	float m12= 3,m22=-5,m32= 0,m42=2;
	float m13=-3,m23= 4,m33= 1,m43=0;
	float m14= 1,m24=-1,m34= 0,m44=0;

	float bt=1,gm=1;

	m11=-bt;  m12=4-gm;  m13=-4+bt;  m14=gm;
	m21=2*bt; m22=-6+gm; m23=6-2*bt; m24=-gm;
	m31=-bt;  m32=0;     m33=bt;     m34=0;
	m41=0;    m42=2;     m43=0;      m44=0;

	x=0.5*((t*(t*(t*m11+m21)+m31)+m41)*xs[num-3] +
	       (t*(t*(t*m12+m22)+m32)+m42)*xs[num-2] +
	       (t*(t*(t*m13+m23)+m33)+m43)*xs[num-1] +
	       (t*(t*(t*m14+m24)+m34)+m44)*xs[num]);
	return(x);
}

float y_spline(float t,int num)
{
	float y;
	float m11=-1,m21= 2,m31=-1,m41=0;
	float m12= 3,m22=-5,m32= 0,m42=2;
	float m13=-3,m23= 4,m33= 1,m43=0;
	float m14= 1,m24=-1,m34= 0,m44=0;

		float bt=1,gm=1;

	m11=-bt;  m12=4-gm;  m13=-4+bt;  m14=gm;
	m21=2*bt; m22=-6+gm; m23=6-2*bt; m24=-gm;
	m31=-bt;  m32=0;     m33=bt;     m34=0;
	m41=0;    m42=2;     m43=0;      m44=0;

	y=0.5*((t*(t*(t*m11+m21)+m31)+m41)*ys[num-3] +
	       (t*(t*(t*m12+m22)+m32)+m42)*ys[num-2] +
	       (t*(t*(t*m13+m23)+m33)+m43)*ys[num-1] +
	       (t*(t*(t*m14+m24)+m34)+m44)*ys[num]);
	return(y);
}