
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
//#include <dos.h>

//#include <interface.h>
//#include <graphics.h>
//#include <ibmstuf.h>
#include "pasoaux.h"

#define HBASE	7
#define IZQ	0
#define	DER	1

int n_velocidad(long n);
long ciclos_delay(int vel,int ax,int ay);

void textoxy(int x,int y,char *cadena);
long decimas();
void punto_tray(int it,int ib,int *xt,int *yt,int *ut,int *vt,
		int *xe,int *ye,int *ue,int *ve);
void calculo_tray_perfil(int cuerda_e,int cuerda_m,int g,int f,
			int alturaxy,int alturauv,int *xt,int *yt,int *ut,int *vt,
			float *xb,float *yb,int num_b,int id_ba,int *ini,int *num_t,int tipo_salida,
			int semiala,float ase,float asi,float chapa);
int lectura_perfil(char *acceso,char *nombre,int *num_b,int *id_ba,float *xb,float *yb);
void corte(FILE *file, int ini,int num_t,int vel_desp,int tiempo,int *xc,int *yc,int *uc,int*vc);
void calculo_carros(int ini,int num_t,int b,int env,int *xd,int *yd,int *ud,int*vd,
					int *xc,int *yc,int *uc,int*vc);
void calculo_desplaz(int ini,int num_t,float rel,float distxy,float distuv,
		int *xt,int *yt,int *ut,int*vt,int *xd,int *yd,int *ud,int*vd,int lado);
void calculo_enchap(int num_e,float distxy,float distuv,
		int *xt,int *yt,int *ut,int*vt,int *xd,int *yd,int *ud,int*vd,int lado);
void radio_quemado(int material,float rel_vel,float *distxy,float *distuv);
void grafico_tray(int ini,int num_t,int *xt,int *yt,int *ut,int*vt);
void grafico_planta(int b,int env);

void linea_hilo(int x,int y,int u,int v);

void cargarGeometria(char *acceso_datos,char *acceso,int *env,int *cuerda_m,int *cuerda_e,
	int *f,int *b,int *g,int *alturaxy,int *alturauv);
void setMaterial(int material,int *mat,int *velocidad,float *intensidad);
void simetria(int semiala,int *ini,int *num_t,int *xc,int *yc,int *uc,int *vc);


int getint(int min, int max,int col,int row) {
    int value;
    scanf("%d", &value);
    return  value;
}  /* Obtiene un entero desde la entrada */

void outtextxy(int x,int y, char *txt) {
    printf("%s\n", txt);
};

	int xact,yact,uact,vact;
	int xgraf,ygraf,ugraf,vgraf;
	int lng;
	float coef_A=0.001216,coef_B=6.900e-6;

int main()
{
	int i,j,k,ib,it;
	int t,d,dist;
	long ldist;
	int acel;
	unsigned char ch;
	unsigned int cport;
	float rad;
	int modo;
	long tiempo,tiempo_desp;
	int velocidad,vel_desp,velocidadxy;
	FILE *fptr;
	char acceso[20]={"hd800.dat"};
	char acceso_datos[20]={"musc-1.gma"};
	char nombre[30];
	char cadena[30];
	int fin=0;
	float xb[500],yb[500];
	int xt[500],yt[500],ut[500],vt[500];
	int xd[500],yd[500],ud[500],vd[500];
	int xc[500],yc[500],uc[500],vc[500];


	float distxy,distuv;
	int num_b,id_ba,num_t[10];
	long e,exy,euv,dx,dy,du,dv;
	int salir;
	int cuerda;
	int numtotal;
	int homeA,homeB,homeC,homeD;
	int deltax,deltay;
	int alturaxy,alturauv;
	int alturabloque;
	int env,cuerda_e,cuerda_m,f,b,g;
	int cxy;

	int semiala;
	int tipo_salida;
	int material;
	float intensidad;
	float dist100,diametro,quemado[6];
	float rel_vel,quemadouv;
	float ftemp;
	int ancho,alto;
	int ini[10];
	int seg;
	long dec_i,dec_f;
	int decpnt,sgn;
	char *fstr;
	char *buf;
	long ltemp,li,lj,lk;
	int vel;
	long t0,tn,n;
	float c_A,c_B;
	float angulo;

	int radioa,radiob,altura;
	float ase,asi;
	float chapa;

	char opciones[40][30]={
        "0=salir",
        "1=circulo",
        "2=manual",
        "3=perfil",
        "4=angulos",
        "5=paso a paso",
        "6=ent/sal",
        "7=trayectorias",
        "8=home",
        "9=arriba",
        "10=abajo",
        "11=desplaza en corte",
        "12=desactiva",
        "13=nombre perfil",
        "14=param. ala",
        "15=posici¢n",
        "16=velocidad",
        "17=altura de inicio",
        "18=salvar",
        "19=cargar",
        "20=Espesor de foam",
        "21=Calibrar velocidad",
        "22=Comprobar velocidad",
        "28=material",
        "29=calib. mat.",
        "30=bisel",
        "31=Sierra calibre vel.maxima",
        "32=semiala",
        "33=Tipo de salida",
        "34=Desplaz.",
        "35=Angulo de tang. en B.A.",
        "36=Espesor enchapado",
        "modo:"
    };
	char materiales[5][30]={"Foam azul","Foam blanco 10Kg/m3",
		"Foam rosa;foam ROOFMATE","Foam Blanco (20 Kg/m3)",
		"Styrodur (verde): 34.5 kg/m3)"};

	//COUT(CONTROLPORT,137);

	//initialize();
	//setbkcolor(WHITE);

	lng=1020;
	vel_desp=300;	/* mm/min */
	alturabloque=25;
	semiala=IZQ;
	tipo_salida=1;
	ase=35*PI2/360.0;
	asi=35*PI2/360.0;
	chapa=0.6;
	cargarGeometria(acceso_datos,acceso,&env,&cuerda_m,&cuerda_e,
			&f,&b,&g,&alturaxy,&alturauv);
	setMaterial(4,&material,&velocidad,&intensidad);
	textoxy(10,200,"Material:");
	textoxy(100,200,materiales[material-1]);
    //ltoa(velocidad,cadena,10);
    sprintf(cadena, "%i", velocidad);
	textoxy(10,220,"Velocidad:");
	textoxy(100,220,cadena);
    //printf("int: %f\n", intensidad);
	//gcvt(intensidad,2,&buf);
    sprintf(cadena, "%f", intensidad);
	textoxy(10,230,"Fije la intensidad a:");
	textoxy(220,230,cadena);
	getchar();

	salir=0;
	while(salir==0)
	{
	//cleardevice();
	//settextstyle(0,0,1);
	//setcolor(BLUE);
	for(i=0;i<33;i++)
		{
		textoxy(10,10+i*10,opciones[i]);
	}

	modo=getint(0,40,50,10+(i-1)*10);

    printf("modo: %i\n", modo);
	//cleardevice();
	//transline(1,1,XMAX-1,1,BLACK);
	//transline(XMAX-1,1,XMAX-1,YMAX-1,BLACK);
	//transline(XMAX-1,YMAX-1,1,YMAX-1,BLACK);
	//transline(1,YMAX-1,1,1,BLACK);
	//gotoxy(0,0);
	switch(modo)
	{
	case 0:
		salir=1;
		desactivamotor();
		break;

    //"1=circulo",
	case 1:
		activamotor();
		radioa=28;
		radiob=20;
		altura=40-HBASE;
		linea_to((100-radioa)*RPL,(altura+10)*RPL,(100)*RPL,(altura+10)*RPL,vel_desp);
		getchar();
		linea_to((100-radioa)*RPL,altura*RPL,(100)*RPL,altura*RPL,velocidad);
		for(i=1;i<=180;i++)
		{
			rad=i*6.2832/360;
			linea_to((100-radioa*cos(rad))*RPL,(altura-radiob*sin(rad))*RPL,
				100*RPL,altura*RPL,velocidad);
		}
		linea_to((100+radioa)*RPL,(altura+10)*RPL,(100)*RPL,(altura+10)*RPL,velocidad);
		desactivamotor();
		getchar();
		break;

    //"2=manual",
	case 2:
/*		printf("velocidad:");
		scanf("%i",&velocidad);
		activamotor();
		while(!kbhit())
		{
			pausa(velocidad);
			cport=CIN(CPORT);
			if((cport & 1)==0)
			{
				pasomotor(MA,1);
			}
			else if((cport & 2)==0)
			{
				pasomotor(MA,-1);
			}

			if((cport & 4)==0)
			{
				pasomotor(MB,1);
			}
			else if((cport & 8)==0)
			{
				pasomotor(MB,-1);
			}
		}
		desactivamotor();
*/
		break;
    //"3=perfil",
	case 3:
		//ltoa(material,cadena,10);
        sprintf(cadena, "%i", material);
		textoxy(20,200,"Material:");
        textoxy(100,200,materiales[material-1]);
/*		textoxy(100,200,cadena); */
		//gcvt(intensidad,2,&buf);
		textoxy(20,210,"Fije la intensidad a:");
        printf("%f\n", intensidad);
		//textoxy(220,210, buf);
		getchar();

		if(lectura_perfil(acceso,nombre,&num_b,&id_ba,xb,yb)==1) break;

		calculo_tray_perfil(cuerda_e,cuerda_m,g,f,alturaxy,alturauv,
					xt,yt,ut,vt,xb,yb,num_b,id_ba,ini,num_t,tipo_salida,
					semiala,ase,asi,chapa);

        // Escribir a fichero
		if((fptr=fopen("perfil.gcode","wt"))!=NULL)
        {
            printf("GCODE");
        }
		for(seg=0;seg<=1;seg++)
		{
			grafico_tray(ini[seg],num_t[seg],xt,yt,ut,vt);
			rel_vel=(float)cuerda_m/cuerda_e;
			radio_quemado(material,rel_vel,&distxy,&distuv);
			calculo_desplaz(ini[seg],num_t[seg],rel_vel,
				 distxy,distuv,xt,yt,ut,vt,xd,yd,ud,vd,-semiala);
			grafico_tray(ini[seg],num_t[seg],xd,yd,ud,vd);
			calculo_carros(ini[seg],num_t[seg],b,env,xd,yd,ud,vd,
							xc,yc,uc,vc);
			grafico_tray(ini[seg],num_t[seg],xc,yc,uc,vc);
			grafico_planta(b,env);
			cxy=cuerda_m+(float)(cuerda_e-cuerda_m)*(env+b)/(float)env;
			velocidadxy=(float)velocidad*cxy/(float)cuerda_e;
			corte(fptr, ini[seg],num_t[seg],vel_desp,velocidadxy,xc,yc,uc,vc);
			getchar();
		}
        if(fclose(fptr)!=0)
        {
            outtextxy(10,40,"no se pudo cerrar");
            getchar();
        }
		break;

    //"4=angulos",
	case  4:
		//ltoa(velocidad,cadena,10);
        sprintf(cadena, "%i", velocidad);
		textoxy(20,10,"velocidad:");
		textoxy(100,10,cadena);
		activamotor();
		alto=10;
		ancho=20;
/*		linea_to(RPL*20,RPL*10,RPL*20,RPL*10,vel_desp); */
		textoxy(20,30,"Pulse una tecla.");
                getchar();
		linea_to_rel( RPL*ancho, 0       , RPL*ancho, 0        ,velocidad);
/*		pausa(100000); */
		linea_to_rel( 0        , RPL*alto, 0        , RPL*alto ,velocidad);
		linea_to_rel(-RPL*ancho, 0       ,-RPL*ancho, 0        ,velocidad);
		linea_to_rel( 0        ,RPL*alto, 0        ,RPL*alto ,velocidad);
		desactivamotor();
		getchar();
		break;

    //"5=paso a paso",
	case 5:
		activamotor();
		fin=0;
		while(fin==0)
		{
			ch=getchar();
			if(ch=='\x1B') fin=1;
			pasomotor(MA,1);
			pasomotor(MB,1);
			pasomotor(MC,1);
			pasomotor(MD,1);
		}
		desactivamotor();
		break;

    //"6=ent/sal",
	case 6:
/*		printf("velocidad:");
		scanf("%i",&velocidad);
		activamotor();
		linea_to_rel(2000,0,2000,0,velocidad);
		linea_to_rel(0,1000,0,1000,velocidad);
		linea_to_rel(-2000,0,-2000,0,velocidad);
		desactivamotor();
		getchar(); */
		break;

    //"7=trayectorias",
	case 7:
		if(lectura_perfil(acceso,nombre,&num_b,&id_ba,xb,yb)==1) break;

		calculo_tray_perfil(cuerda_e,cuerda_m,g,f,alturaxy,alturauv,
					xt,yt,ut,vt,xb,yb,num_b,id_ba,ini,num_t,tipo_salida,semiala,ase,asi,chapa);

		//transline(0,RPL*(alturaxy),XMAX,RPL*(alturaxy),BLUE);

		//transline(0,RPL*(alturabloque-HBASE),XMAX,RPL*(alturabloque-HBASE),RED);
		//transline(0,YMAX-RPL*HBASE,XMAX,YMAX-RPL*HBASE,BLUE);
		//transline(0,0-RPL*HBASE,XMAX,0-RPL*HBASE,BLUE);
		for(seg=0;seg<=1;seg++)
		{
			grafico_tray(ini[seg],num_t[seg],xt,yt,ut,vt);
			rel_vel=(float)cuerda_m/cuerda_e;
			radio_quemado(material,rel_vel,&distxy,&distuv);
			calculo_desplaz(ini[seg],num_t[seg],rel_vel,
				 distxy,distuv,xt,yt,ut,vt,xd,yd,ud,vd,-semiala);
			grafico_tray(ini[seg],num_t[seg],xd,yd,ud,vd);
			calculo_carros(ini[seg],num_t[seg],b,env,xd,yd,ud,vd,
							xc,yc,uc,vc);

			grafico_tray(ini[seg],num_t[seg],xc,yc,uc,vc);
			grafico_planta(b,env);
/*			corte(ini[seg],num_t[seg],vel_desp,velocidad,xc,yc,uc,vc); */
			//linea_planta(xc[ini[seg]],0,uc[ini[seg]],(long)RPL*lng,BLUE);
			//linea_planta(xc[ini[seg]+1],0,uc[ini[seg]+1],(long)RPL*lng,BLUE);
			getchar();
		}
		break;

    //"8=home",
	case 8:
		ltemp=200;
/*		textoxy(10,10,"tiempo:");
		tiempo=getint(0,2000,150,10);
		ltemp=(long)tiempo;          */
		activamotor();
		homeA=0;
		homeB=0;
		homeC=0;
		homeD=0;
		while(!((homeA==1) & (homeB==1) & (homeC==1) & (homeD==1)))
		{
			//cport=CIN(CPORT);
			pausa(ltemp);
			if((cport & 1)!=0) pasomotor(MA,-1);
			if((cport & 4)!=0) pasomotor(MB,-1);
			if((cport & 16)!=0) pasomotor(MC,-1);
			if((cport & 64)!=0) pasomotor(MD,-1);

			if((cport & 1)==0) homeA=1;
			if((cport & 4)==0) homeB=1;
			if((cport & 16)==0) homeC=1;
			if((cport & 64)==0) homeD=1;
		}
		desactivamotor();
		xact=0;
		yact=0;
		uact=0;
		vact=0;
		break;

    //"9=arriba",
	case 9:
		printf("velocidad:");
		scanf("%i",&velocidad);
		activamotor();
		linea_to_rel(0,5000,0,5000,velocidad);
		desactivamotor();
		getchar();
		break;

    //"10=abajo",
	case 10:
		printf("velocidad:");
		scanf("%i",&velocidad);
		activamotor();
		linea_to_rel(0,-5000,0,-5000,velocidad);
		desactivamotor();
		getchar();
		break;

    //"11=desplaza en corte",
	case 11:
		textoxy(10,20,"Deltax:");
		deltax=getint(-280,280,150,20);
		textoxy(10,30,"Deltay:");
		deltay=getint(-280,280,150,30);

		activamotor();
		linea_to_rel(RPL*deltax,RPL*deltay,RPL*deltax,RPL*deltay,velocidad);
		desactivamotor();
		getchar();
		break;

    //"12=desactiva",
	case 12:
		desactivamotor();
		break;

    //"13=nombre perfil",
	case 13:
		textoxy(10,100,"Fichero del perfil:");
		//getline(12,acceso,200,100);
		break;
    //"14=param. ala",
	case 14:
		textoxy(10,10,"Envergadura:");
		env=getint(1,2000,150,10);
		textoxy(10,20,"Cuerda encastre:");
		cuerda_e=getint(1,2000,150,20);
		textoxy(10,30,"Cuerda marginal:");
		cuerda_m=getint(1,2000,150,30);
		textoxy(10,40,"flecha:");
		f=getint(-2000,2000,150,40);
		break;

    //"15=posici¢n",
	case 15:
		textoxy(10,10,"dist. al carro (B):");
		b=getint(0,10000,190,10);
		textoxy(10,20,"dist.al eje y=0 (G):");
		g=getint(-2000,2000,190,20);
		break;

    //"16=velocidad",
	case 16:
		textoxy(10,10,"velocidad de corte(mm/min):");
		velocidad=getint(0,500,250,10);
		textoxy(10,20,"velocidad de despl.(mm/min):");
		vel_desp=getint(0,500,250,20);
		break;
    //"17=altura de inicio",
	case 17:
		textoxy(10,20,"altura de inicio en xy:");
		alturaxy=getint(0,120,210,20)-HBASE;
		textoxy(10,30,"altura de inicio en uv:");
		alturauv=getint(0,120,210,30)-HBASE;
		break;
    //"18=salvar",
	case 18:
		textoxy(10,20,"Nombre del fichero:");
		//getline(12,acceso_datos,200,20);
		if((fptr=fopen(acceso_datos,"wt"))!=NULL)
		{
			fprintf(fptr,"Perfil= %s\n",acceso);
			fprintf(fptr,"Envergadura= %i\n",env);
			fprintf(fptr,"Cuerda_encastre= %i\n",cuerda_e);
			fprintf(fptr,"Cuerda_marginal= %i\n",cuerda_m);
			fprintf(fptr,"Flecha= %i\n",f);
			fprintf(fptr,"G= %i\n",g);
			fprintf(fptr,"B= %i\n",b);
			fprintf(fptr,"Altura_encastre= %i\n",alturaxy+HBASE);
			fprintf(fptr,"Altura_marginal= %i\n",alturauv+HBASE);
			if(fclose(fptr)!=0)
			{
                outtextxy(10,40,"no se pudo cerrar");
				getchar();
			}
		}
		else
		{
			textoxy(20,40,"no se pudo habrir");
			getchar();
		}
		break;

    //"19=cargar",
	case 19:
		textoxy(10,20,"Nombre del fichero a cargar:");
		//getline(12,acceso_datos,250,20);
		cargarGeometria(acceso_datos,acceso,&env,&cuerda_m,&cuerda_e,
			&f,&b,&g,&alturaxy,&alturauv);
		break;

    //"20=Espesor de foam",
	case 20:
		textoxy(10,20,"Espesor de foam:");
		//getline(10,cadena,170,20);
		alturabloque=atoi(cadena);
		break;

    //"21=Calibrar velocidad",
	case 21:
		dist=-100;
		lk=0;
		vel=1200;
		textoxy(10,10,"velocidad:");
		vel=getint(0,10000,170,20);
		textoxy(10,20,"Pulse una tecla para empezar.");
		getchar();
		for(i=0;i<5;i++)
		{
			dist=-dist;
			dec_i=decimas();
/*			linea_to_rel(RPL*dist/1.41,RPL*dist/1.41,RPL*dist/1.41,RPL*dist/1.41,vel);*/
			linea_to_rel(0,RPL*dist,0,RPL*dist,vel);
			dec_f=decimas();
			lk=lk+(dec_f-dec_i);
		}
		lk=lk/5;
		//ltoa(lk,cadena,10);
		textoxy(10,40,"tiempo medio:");
		textoxy(150,40,cadena);
		textoxy(10,50,"Velocidad media:");
		//gcvt((float)abs(dist)*6000/lk,2,&buf);
		outtextxy(150,50, buf);
		getchar();

		break;

    //"22=Comprobar velocidad",
	case 22:
		textoxy(10,10,"Velocidad(mm/min):");
		i=getint(0,20000,180,10);
		outtextxy(10,20,"Pulse una tecla para empezar.");
		getchar();
		dist=-100;
		//while(!kbhit())
		while(0)
		{
			dist=-dist;
			dec_i=decimas();
/*			linea_to_rel(RPL*dist,RPL*dist,RPL*dist,RPL*dist,i); */
			linea_to_rel(0,RPL*dist,0,RPL*dist,i);
			dec_f=decimas();
			k=i;
			//itoa(k,cadena,10);
			textoxy(10,40,"Velocidad:");
			outtextxy(150,40,cadena);
			k=dist;
			//itoa(k,cadena,10);
			textoxy(10,50,"Distancia(mm):");
			textoxy(150,50,cadena);
			k=dec_f-dec_i;
			//itoa(k,cadena,10);
			textoxy(10,60,"Tiempo(decimas):");
			textoxy(150,60,cadena);
			ftemp=(float)dist*6000/(dec_f-dec_i);
			//fstr=gcvt(ftemp,5,buf);
			textoxy(10,70,"Velocidad(mm/min):");
			textoxy(150,70,fstr);
		}
		getchar();

		break;

	case 23:
/*		textoxy(10,10,"n:");
		k=getint(0,10000,220,10); */
		for(lk=0;lk<50;lk++)
		{
			//ltoa(lk*1000,cadena,10);
			textoxy(10,lk*10+10,"n:");
			textoxy(150,lk*10+10,cadena);
			lj=n_velocidad(lk*1000);
			//ltoa(lj,cadena,10);
			textoxy(200,lk*10+10,"velocidad:");
			textoxy(350,lk*10+10,cadena);
		}
		getchar();
		break;

	case 24:
/*		textoxy(10,10,"velocidad:");
		k=getint(0,10000,220,10); */
		for(lk=1;lk<50;lk++)
		{
			//ltoa(lk*20,cadena,10);
			textoxy(10,lk*10+10,"velocidad:");
			textoxy(150,lk*10+10,cadena);
			lj=ciclos_delay(lk*20,1,0);
			//ltoa(lj,cadena,10);
			textoxy(200,lk*10+10,"n:");
			textoxy(350,lk*10+10,cadena);
		}
		getchar();
		break;

	case 25:
		textoxy(10,10,"n:");
		lk=getint(0,10000,220,10);
		//ltoa(lk,cadena,10);
		textoxy(10,30,"n:");
		textoxy(150,30,cadena);
		lj=n_velocidad(lk);
		//ltoa(lj,cadena,10);
		textoxy(200,30,"velocidad:");
		textoxy(350,30,cadena);
		getchar();
		break;

	case 26:
		textoxy(10,10,"velocidad:");
		lk=getint(0,10000,220,10);
		//ltoa(lk,cadena,10);
		textoxy(10,30,"velocidad:");
		textoxy(150,30,cadena);
		lj=ciclos_delay(lk,1,0);
		//ltoa(lj,cadena,10);
		textoxy(200,30,"n:");
		textoxy(350,30,cadena);
		getchar();
		break;

	case 27:
		textoxy(10,10,"Calibrado.");
		textoxy(10,20,"ciclos n:");
		n=getint(0,10000,220,10);
		ldist=250;

		vel=n_velocidad(0);
		linea_to(200,500,200,200,vel);
                dec_i=decimas();
/*		linea_to_rel(RPL*ldist/1.38,RPL*ldist/1.41,RPL*ldist/1.38,RPL*ldist/1.41,vel); */
		linea_to_rel(RPL*ldist,0,RPL*ldist,0,vel);
		dec_f=decimas();
		t0=dec_f-dec_i;
		c_A=(float)t0/(100*(ldist)*RPL);
		//fstr=gcvt(c_A,4,&buf);
		textoxy(10,30,"c_A:");
		textoxy(150,30,fstr);

/*		vel=n_velocidad(n);
                dec_i=decimas();
		linea_to_rel(-RPL*ldist/1.38,-RPL*ldist/1.41,-RPL*ldist/1.38,-RPL*ldist/1.41,vel);
		linea_to_rel(-RPL*ldist,0,-RPL*ldist,0,vel);
		dec_f=decimas();
		tn=dec_f-dec_i;
		c_B=((float)tn/(100*(ldist)*RPL)-c_A)/n;
		fstr=gcvt(c_B,4,&buf);
		textoxy(10,40,"c_B:");
		textoxy(150,40,fstr);     */
		coef_A=c_A;
		coef_B=c_B;
		getchar();
		break;
    //"28=material",
	case 28:
		textoxy(10,10,"1=foam azul.");
		textoxy(10,20,"2=foam blanco (10 Kg/m3).");
		textoxy(10,30,"3=foam rosa. y foam azul ROOFMATE");
		textoxy(10,40,"4=foam blanco (20 Kg/m3).");
		textoxy(10,50,"5=Styrodur (verde) (34.5 Kg/m3).");

		textoxy(10,60,"material:");
		material=getint(0,9,150,60);
		setMaterial(material,&material,&velocidad,&intensidad);
                //ltoa(velocidad,cadena,10);
		textoxy(20,80,"Velocidad:");
		textoxy(100,80,cadena);
		//gcvt(intensidad,2,&buf);
		textoxy(20,90,"Fije la intensidad a:");
		textoxy(220,90, buf);
		getchar();
		break;
    //"29=calib. mat.",
	case 29:
            //ltoa(velocidad,cadena,10);
		textoxy(20,10,"velocidad:");
		textoxy(100,10,cadena);
		activamotor();
		alto=10;
		ancho=20;
/*		linea_to(RPL*20,RPL*10,RPL*20,RPL*10,vel_desp); */
		textoxy(20,30,"Pulse una tecla.");
		for(i=0;i<5;i++)
		{
		vel=velocidad*(1-(double)i/5);
		//ltoa(vel,cadena,10);
		textoxy(20,60,"Velocidad:");
		textoxy(100,60,cadena);
		textoxy(20,70,"Pulse una tecla.");

                getchar();
		linea_to_rel( RPL*ancho, 0       , RPL*ancho, 0        ,vel);
		getchar();
		linea_to_rel(-RPL*ancho, 0       ,-RPL*ancho, 0        ,velocidad);
		linea_to_rel( 0        ,RPL*alto, 0        ,RPL*alto ,velocidad);
		}
		desactivamotor();
		getchar();
		break;

    //"30=bisel",
	case 30:
		textoxy(10,10,"altura base:");
		k=getint(0,100,150,10);
		textoxy(10,20,"espesor:");
		i=getint(0,100,150,20);
		textoxy(10,30,"angulo (resp. vertical):");
		//getline(10,cadena,210,30);
		angulo=atof(cadena);
		angulo=angulo*PI2/360;
		activamotor();
		linea_to(RPL*20,RPL*k,RPL*20,RPL*k,vel_desp);
		textoxy(20,40,"Coloque el borde inferior junto al hilo.");
		getchar();
		linea_to(RPL*15,RPL*k,RPL*15,RPL*k,vel_desp);
		linea_to(RPL*15,RPL*(k+(i+6)*cos(angulo)),
			RPL*15,RPL*(k+(i+6)*cos(angulo)),vel_desp);
		linea_to(RPL*(20+(i+6)*sin(angulo)),RPL*(k+(i+6)*cos(angulo)),
			RPL*(20+(i+6)*sin(angulo)),RPL*(k+(i+6)*cos(angulo)),vel_desp);
		textoxy(20,50,"Conecte el hilo. Pulse una tecla.");
                getchar();
		linea_to(RPL*20,RPL*k,RPL*20,RPL*k,velocidad);
		linea_to(RPL*20,RPL*0,RPL*20,RPL*0,velocidad);
		desactivamotor();
		getchar();
		break;

    //"31=Sierra calibre vel.maxima",
	case  31:
		velocidad=240;
		//ltoa(velocidad,cadena,10);
		textoxy(20,10,"velocidad:");
		textoxy(100,10,cadena);
		activamotor();
		alto=6;
		ancho=6;
/*		linea_to(RPL*20,RPL*10,RPL*20,RPL*10,vel_desp); */
		textoxy(20,30,"Pulse una tecla.");
		getchar();
		for(velocidad=200;velocidad<=301;velocidad+=20)
		{
		linea_to_rel( RPL*ancho, 0       , RPL*ancho, 0        ,velocidad);
		linea_to_rel( 0        ,-RPL*alto, 0        ,-RPL*alto ,velocidad);
		linea_to_rel( RPL*ancho, 0       , RPL*ancho, 0        ,velocidad);
		linea_to_rel( 0        , RPL*alto, 0        , RPL*alto ,velocidad);
		}
		linea_to_rel(2*RPL*ancho, 0       ,2*RPL*ancho, 0        ,velocidad);
		desactivamotor();
		getchar();
		break;

    //"32=semiala",
	case 32:
		textoxy(10,20,"Semiala( 0=Izq.,1=Der.):");
		//getline(10,cadena,200,20);
		semiala=atoi(cadena);
		break;

    //"33=Tipo de salida",
	case 33:
		textoxy(10,20,"Tipo de salida:");
		textoxy(10,30,"0 = sin tangencias.");
		textoxy(10,40,"1 = con tangencias hasta el eje.");
		textoxy(10,50,"2 = con tangencias hasta el final.");
		//getline(10,cadena,200,20);
		tipo_salida=atoi(cadena);
		break;
    //"34=Desplaz.",
	case 34:
		textoxy(10,20,"Deltax:");
		deltax=getint(-280,280,150,20);
		textoxy(10,30,"Deltay:");
		deltay=getint(-280,280,150,30);

		activamotor();
		linea_to_rel(RPL*deltax,RPL*deltay,RPL*deltax,RPL*deltay,vel_desp);
		desactivamotor();
		getchar();
		break;
    //"35=Angulo de tang. en B.A.",
	case 35:
		textoxy(10,20,"Angulo de tang. en B.A.(extrados):");
		//getline(10,cadena,330,20);
		ase=atoi(cadena)*PI2/360.0;
		textoxy(10,30,"Angulo de tang. en B.A.(intrados):");
		//getline(10,cadena,330,30);
		asi=atoi(cadena)*PI2/360.0;
		break;
    //"36=Espesor enchapado",
	case 36:
		textoxy(10,20,"Espesor enchap.(x0.1mm):");
		//getline(10,cadena,230,20);
		chapa=(float)atoi(cadena)/10.0;
		break;

	}
	}

	//closegraph();

    return 0;
}

void radio_quemado(int material,float rel_vel,float *distxy,float *distuv)
{
	float quemado[6];
	float quemadouv;

	switch(material)
	{
	case 1:
		quemado[0]=.25;
		quemado[1]=.275;
		quemado[2]=.325;
		quemado[3]=.500;
		quemado[4]=.83;
		quemado[5]=1.75;
		break;
	case 2:
		quemado[0]=.4;
		quemado[1]=.4;
		quemado[2]=.5;
		quemado[3]=.85;
		quemado[4]=1.30;
		quemado[5]=1.80;
		break;
	case 3:
		quemado[0]=.25;
		quemado[1]=.32;
		quemado[2]=.40;
		quemado[3]=.70;
		quemado[4]=1.1;
		quemado[5]=2.0;
		break;
	case 4:
		quemado[0]=.25;
		quemado[1]=.40;
		quemado[2]=.5;
		quemado[3]=.65;
		quemado[4]=1.0;
		quemado[5]=1.7;
		break;
	case 5:
		quemado[0]=.25;
		quemado[1]=.35;
		quemado[2]=.5;
		quemado[3]=.9;
		quemado[4]=1.25;
		quemado[5]=1.8;
		break;
	}

	*distxy=94*(quemado[0]);

	if(rel_vel>.8)
		quemadouv=quemado[0]+((1-rel_vel)*(quemado[1]-quemado[0]))/.2;
	else if(rel_vel>.6)
		quemadouv=quemado[1]+((.8-rel_vel)*(quemado[2]-quemado[1]))/.2;
	else if(rel_vel>.4)
		quemadouv=quemado[2]+((.6-rel_vel)*(quemado[3]-quemado[2]))/.2;
	else if(rel_vel>.2)
		quemadouv=quemado[3]+((.4-rel_vel)*(quemado[4]-quemado[3]))/.2;
	else if(rel_vel>.0)
		quemadouv=quemado[4]+((.2-rel_vel)*(quemado[5]-quemado[4]))/.2;
	*distuv=94*(quemadouv);
/*	*distxy+=200;
	*distuv+=200; */
}

void grafico_tray(int ini,int num_t,int *xt,int *yt,int *ut,int*vt)
{
	int i,k;
			k=ini;
			move_graf_to(xt[k],yt[k],ut[k],vt[k]);
			for(i=1;i<num_t;i++)
			{
				k=ini+i;
				linea_graf_to(xt[k],yt[k],ut[k],vt[k]);
			}
}

void calculo_desplaz(int ini,int num_t,float rel,float distxy,float distuv,
		int *xt,int *yt,int *ut,int*vt,int *xd,int *yd,int *ud,int*vd,int lado)
{
	int i,j,k;
	int ax1,ay1,ax2,ay2;
	int au1,av1,au2,av2;
	float betaxy1,betaxy2;
	float betauv1,betauv2;
	float betaxym,betauvm;
	float dpxy,dpuv;

        if(lado==1) lado=-1;
	if(lado==0) lado=1;

	k=ini;
	xd[k]=xt[k]+lado*distxy*cos(PID2+atan2(yt[k+1]-yt[k],xt[k+1]-xt[k]));
	yd[k]=yt[k]+lado*distxy*sin(PID2+atan2(yt[k+1]-yt[k],xt[k+1]-xt[k]));
	ud[k]=ut[k]+lado*distuv*cos(PID2+atan2(vt[k+1]-vt[k],ut[k+1]-ut[k]));
	vd[k]=vt[k]+lado*distuv*sin(PID2+atan2(vt[k+1]-vt[k],ut[k+1]-ut[k]));

	for(i=1;i<num_t-1;i++)
	{
		k=ini+i;
		ax1=xt[k]-xt[k-1];
		ax2=xt[k+1]-xt[k];
		ay1=yt[k]-yt[k-1];
		ay2=yt[k+1]-yt[k];
		au1=ut[k]-ut[k-1];
		au2=ut[k+1]-ut[k];
		av1=vt[k]-vt[k-1];
		av2=vt[k+1]-vt[k];
		betaxy1=atan2(ay1,ax1);
		betaxy2=atan2(ay2,ax2);
		betaxym=PID2+(betaxy1+betaxy2)/2;
		dpxy=distxy/cos((betaxy1-betaxy2)/2);
		betauv1=atan2(av1,au1);
		betauv2=atan2(av2,au2);
		betauvm=PID2+(betauv1+betauv2)/2;
		dpuv=distuv/cos((betauv1-betauv2)/2);

		dpxy=lado*dpxy;
		dpuv=lado*dpuv;
		xd[k]=xt[k]+dpxy*cos(betaxym);
		yd[k]=yt[k]+dpxy*sin(betaxym);
		ud[k]=ut[k]+dpuv*cos(betauvm);
		vd[k]=vt[k]+dpuv*sin(betauvm);
	}
	j=ini+num_t-1;
	xd[j]=xt[j]+lado*distxy*cos(PID2+atan2(yt[j]-yt[j-1],xt[j]-xt[j-1]));
	yd[j]=yt[j]+lado*distxy*sin(PID2+atan2(yt[j]-yt[j-1],xt[j]-xt[j-1]));
	ud[j]=ut[j]+lado*distuv*cos(PID2+atan2(vt[j]-vt[j-1],ut[j]-ut[j-1]));
	vd[j]=vt[j]+lado*distuv*sin(PID2+atan2(vt[j]-vt[j-1],ut[j]-ut[j-1]));
}

void calculo_enchap(int num_e,float distxy,float distuv,
		int *xt,int *yt,int *ut,int*vt,int *xd,int *yd,int *ud,int*vd,int lado)
{
	int i,j,k;
	int ax1,ay1,ax2,ay2;
	int au1,av1,au2,av2;
	float betaxy1,betaxy2;
	float betauv1,betauv2;
	float betaxym,betauvm;
	float dpxy,dpuv;

        if(lado==1) lado=-1;
	if(lado==0) lado=1;

	k=0;
	xd[k]=xt[k]+lado*distxy*cos(PID2+atan2(yt[k+1]-yt[k],xt[k+1]-xt[k]));
	yd[k]=yt[k]+lado*distxy*sin(PID2+atan2(yt[k+1]-yt[k],xt[k+1]-xt[k]));
	ud[k]=ut[k]+lado*distuv*cos(PID2+atan2(vt[k+1]-vt[k],ut[k+1]-ut[k]));
	vd[k]=vt[k]+lado*distuv*sin(PID2+atan2(vt[k+1]-vt[k],ut[k+1]-ut[k]));

	for(i=1;i<num_e-1;i++)
	{
		k=i;
		ax1=xt[k]-xt[k-1];
		ax2=xt[k+1]-xt[k];
		ay1=yt[k]-yt[k-1];
		ay2=yt[k+1]-yt[k];
		au1=ut[k]-ut[k-1];
		au2=ut[k+1]-ut[k];
		av1=vt[k]-vt[k-1];
		av2=vt[k+1]-vt[k];
		betaxy1=atan2(ay1,ax1);
		betaxy2=atan2(ay2,ax2);
		betaxym=PID2+(betaxy1+betaxy2)/2;
		dpxy=distxy/cos((betaxy1-betaxy2)/2);
		betauv1=atan2(av1,au1);
		betauv2=atan2(av2,au2);
		betauvm=PID2+(betauv1+betauv2)/2;
		dpuv=distuv/cos((betauv1-betauv2)/2);

		dpxy=lado*dpxy;
		dpuv=lado*dpuv;
		xd[k]=xt[k]+dpxy*cos(betaxym);
		yd[k]=yt[k]+dpxy*sin(betaxym);
		ud[k]=ut[k]+dpuv*cos(betauvm);
		vd[k]=vt[k]+dpuv*sin(betauvm);
	}
	j=num_e-1;
	xd[j]=xt[j]+lado*distxy*cos(PID2+atan2(yt[j]-yt[j-1],xt[j]-xt[j-1]));
	yd[j]=yt[j]+lado*distxy*sin(PID2+atan2(yt[j]-yt[j-1],xt[j]-xt[j-1]));
	ud[j]=ut[j]+lado*distuv*cos(PID2+atan2(vt[j]-vt[j-1],ut[j]-ut[j-1]));
	vd[j]=vt[j]+lado*distuv*sin(PID2+atan2(vt[j]-vt[j-1],ut[j]-ut[j-1]));
}

void calculo_carros(int ini,int num_t,int b,int env,
		int *xd,int *yd,int *ud,int*vd,int *xc,int *yc,int *uc,int*vc)
{
	int i,k;

	for(i=0;i<=num_t;i++)
	{
		k=ini+i;
		xc[k]=xd[k]-((float)b*(ud[k]-xd[k]))/env;
		uc[k]=ud[k]+((float)(lng-env-b)*(ud[k]-xd[k]))/env;
		yc[k]=yd[k]-((float)b*(vd[k]-yd[k]))/env;
		vc[k]=vd[k]+((float)(lng-env-b)*(vd[k]-yd[k]))/env;
	}
}

void corte(FILE *file, int ini,int num_t,int vel_desp,int velocidad,int *xc,int *yc,int *uc,int*vc)
{
	int i,k;

	activamotor();


	k=ini;
	linea_to(xc[k],yc[k],uc[k],vc[k],vel_desp);
	//linea_planta(xc[k],0,uc[k],(long)RPL*lng,BLUE);
	//setcolor(BLUE);
	outtextxy(10,30,"Pulse una tecla para comenzar.");
	getchar();
	for(i=1;i<num_t;i++)
	{
		k=ini+i;
        printf("corte %i: %i %i %i %i\n", i, xc[k],yc[k],uc[k],vc[k]);
        fprintf(file, "%i: %i %i %i %i\n", i, xc[k],yc[k],uc[k],vc[k]);
		linea_to(xc[k],yc[k],uc[k],vc[k],velocidad);
/*		linea_planta(xc[k],0,uc[k],(long)RPL*lng,LIGHTGRAY); */
	}
/*	k=ini+i;
	linea_to(xc[k],yc[k],uc[k],vc[k],velocidad); */
	//linea_planta(xc[k],0,uc[k],(long)RPL*lng,BLUE);
	desactivamotor();
}

void grafico_planta(int b,int env)
{
	//linea_planta(0,0,0,(long)RPL*(long)lng,LIGHTGRAY);
	//linea_planta(XMAX,0,XMAX,(long)RPL*(long)lng,LIGHTGRAY);
	//linea_planta(0,0,XMAX,0,col_iz);
	//linea_planta(0,(long)RPL*lng,XMAX,(long)RPL*lng,col_der);
	//linea_planta(0,(long)RPL*b,XMAX,(long)RPL*(long)b,col_tray_iz);
	//linea_planta(0,(long)RPL*(long)(b+env),XMAX,(long)RPL*(long)(b+env),col_tray_der);
}

int lectura_perfil(char *acceso,char *nombre,int *num_b,int *id_ba,float *xb,float *yb)
{
	FILE *fptr;
	int i,fin;
	int nada;

	if((fptr=fopen(acceso,"rt"))!=NULL)
	{
		fscanf(fptr,"%[^\n]\n",nombre);
		//setcolor(BLUE);
		outtextxy(10,10,nombre);

		i=0;
		fin=1;
		while(fin==1)
		{
			if(i==50)
			{
				nada=0;
			}

			fscanf(fptr,"%f",&xb[i]);
			fin=fscanf(fptr,"%f",&yb[i]);
			if((xb[i]<0.001)&(fin==1)) *id_ba=i;
			i++;
		}
		*num_b=i-1;
                if(fclose(fptr)!=0) printf("  no se pudo cerrar");
		return(0);
	}
        else
	{
		//setcolor(RED);
		outtextxy(100,100,"no se pudo abrir");
		getchar();
		return(1);
	}

}
void punto_tray(int it,int ie,int *xt,int *yt,int *ut,int *vt,
		int *xe,int *ye,int *ue,int *ve)
{
	xt[it]=xe[ie];
	yt[it]=ye[ie];
	ut[it]=ue[ie];
	vt[it]=ve[ie];
}

void calculo_tray_perfil(int cuerda_e,int cuerda_m,int g,int f,
			int alturaxy,int alturauv,int *xt,int *yt,int *ut,int *vt,
			float *xb,float *yb,int num_b,int id_ba,int *ini,int *num_t,int tipo_salida,
			int semiala,float ase,float asi,float chapa)
{
	int xp[500],yp[500],up[500],vp[500];
	int xe[500],ye[500],ue[500],ve[500];
	int num_e,id_bae;
	int i,it,ib,ie;
	long exy,euv,dx,dy,du,dv;
	FILE *fptr;
	float ai; /*angulo del segmento de la iteracion */
	float afixy,afexy;
	float afiuv,afeuv; /*angulos de tang. en el B.F. en intrad. y extrad. */

	num_e=num_b;
	id_bae=id_ba;


	exy=RPL*cuerda_e;
	euv=RPL*cuerda_m;
	dx=RPL*g;
	du=RPL*(g-f);
	dy=RPL*alturaxy;
	dv=RPL*alturauv;

/* Calculo de perfiles en la cuerda encastre y marginal */
	for(ib=0;ib<num_b;ib++)
	{
		xp[ib]=dx+exy*(1.0-xb[ib]);
		yp[ib]=dy+exy*yb[ib];
		up[ib]=du+euv*(1.0-xb[ib]);
		vp[ib]=dv+euv*yb[ib];
	}

	num_e=num_b;
	id_bae=id_ba;

/* Calculo de perfiles descontando enchapado */
	calculo_enchap(num_e,RPL*chapa,RPL*chapa,
			xp,yp,up,vp,xe,ye,ue,ve,1);

	switch(tipo_salida)
	{
	case 0: /* sin tangencias */
        /* estrados */
		it=0;
		ini[0]=it;
		ie=0;

		xt[it]=xe[ie]-exy*0.10;
		yt[it]=ye[ie];
		ut[it]=ue[ie]-euv*0.10;
		vt[it]=ve[ie];
		it++;

		do
		{
			punto_tray(it++,ie,xt,yt,ut,vt,xe,ye,ue,ve);
		} while(ie++<id_bae);
		ie--;
		xt[it]=xt[it-1]+exy*0.10;
		yt[it]=yt[it-1];
		ut[it]=ut[it-1]+euv*0.10;
		vt[it]=vt[it-1];
		num_t[0] =it+1;


	/* intrados */
		it++;
		ini[1]=it;
		xt[it]=xt[it-1];
		yt[it]=yt[it-1];
		ut[it]=ut[it-1];
		vt[it]=vt[it-1];
		it++;
		do
		{
			punto_tray(it++,ie,xt,yt,ut,vt,xe,ye,ue,ve);
		} while(ie++<num_e-1);
		xt[it]=xt[it-1]-exy*.10;
		yt[it]=yt[it-1];
		ut[it]=ut[it-1]-euv*.10;
		vt[it]=vt[it-1];
		num_t[1]=it-num_t[0]+1;
		break;

	case 1:  /* con tangencias hasta el eje */
	/* extrados */

        	it=0;
		ini[0]=it;

		/* calculamos el 2§ punto, para calcular un previo del 1§
			para que no falle el atan2 */
		ie=0;
		it=1;
		punto_tray(it,ie,xt,yt,ut,vt,xe,ye,ue,ve);
		it=0;
		punto_tray(it,ie,xt,yt,ut,vt,xe,ye,ue,ve);
		xt[it]-=exy*0.10;
		ut[it]-=euv*0.10;
		it++;
		ie=0;
		do
		{
			punto_tray(it,ie,xt,yt,ut,vt,xe,ye,ue,ve);
			ai=atan2((ye[ie+1]-ye[ie]),(xe[ie+1]-xe[ie]));
			it++;
			ie++;
		} while(ai>-ase);
		ie--;

		/* primer punto (recalculado despues del intrados)*/

		afexy=atan2((yt[2]-yt[1]),(xt[2]-xt[1]));
		afeuv=atan2((vt[2]-vt[1]),(ut[2]-ut[1]));
                xt[0]=xt[1]-exy*0.1;
		yt[0]=yt[1]-exy*0.1*tan(afexy);
		ut[0]=ut[1]-euv*0.1;
		vt[0]=vt[1]-euv*0.1*tan(afeuv);


		/* anteultimo punto extrados: corte tang. - eje */
		xt[it]=xt[it-1]+(yt[it-1]-dy)/tan(ase);
		yt[it]=dy;          /* corte con el eje (y==dy) */
		ut[it]=ut[it-1]+(vt[it-1]-dv)/tan(ase);
		vt[it]=dv;
		it++;

		/* ultimo punto el extrados */

		xt[it]=dx+exy*(1.0+0.1);   /* un 10% mas de la cuerda sobre el B.A. */
/*		xt[it]=xt[it-1]+exy*0.02; */
		yt[it]=yt[it-1];
		ut[it]=du+euv*(1.0+0.1);
/*		ut[it]=ut[it-1]+euv*0.02; */
		vt[it]=vt[it-1];
		num_t[0]=it+1;

		do
		{
			ai=atan2((ye[ie+1]-ye[ie]),(xe[ie+1]-xe[ie]));
			ie++;
		} while(ai>-PI+asi);
		ie--;


	/* intrados */
		it++;
		ini[1]=it;
		xt[it]=xt[it-1];
		yt[it]=yt[it-1];
		ut[it]=ut[it-1];
		vt[it]=vt[it-1];
		it++;
			punto_tray(it+1,ie,xt,yt,ut,vt,xe,ye,ue,ve);
		xt[it]=xt[it+1]+(dy-yt[it+1])/tan(asi);
		yt[it]=dy;
		ut[it]=ut[it+1]+(dv-vt[it+1])/tan(asi);
		vt[it]=dv;
		it++;
		it++;
		ie++;
		do
		{
			punto_tray(it,ie,xt,yt,ut,vt,xe,ye,ue,ve);
			it++;
		} while(ie++<num_e-1);

		/* recalculo el primer punto del extrados */
                afexy=atan2((yt[2]-yt[1]),(xt[2]-xt[1]));
		afeuv=atan2((vt[2]-vt[1]),(ut[2]-ut[1]));
		xt[0]=dx-exy*0.1;   /* menos 10%cuerda sobre el B.S. */
		yt[0]=yt[1]-(xt[1]-(dx-exy*0.1))*tan(afexy);
		ut[0]=du-euv*0.1;
		vt[0]=vt[1]-(ut[1]-(du-euv*0.1))*tan(afeuv);

/*		xt[0]=xt[1]-exy*0.1;
		yt[0]=yt[1]-exy*0.1*tan(afexy);
		ut[0]=ut[1]-euv*0.1;
		vt[0]=vt[1]-euv*0.1*tan(afeuv); */

		/* ultimo punto:  tangencia en B.F. */
		afixy=atan2((yt[it-2]-yt[it-1]),(xt[it-2]-xt[it-1]));
		afiuv=atan2((vt[it-2]-vt[it-1]),(ut[it-2]-ut[it-1]));
		xt[it]=xt[it-1]-exy*0.1;
		yt[it]=yt[it-1]-exy*0.1*tan((afixy+afexy)/2);
		ut[it]=ut[it-1]-euv*0.1;
		vt[it]=vt[it-1]-euv*0.1*tan((afiuv+afeuv)/2);

                /* recalculo el primer punto del extrados */
                xt[0]=xt[1]-exy*0.1;
		yt[0]=yt[1]-exy*0.1*tan((afexy+afixy)/2);
		ut[0]=ut[1]-euv*0.1;
		vt[0]=vt[1]-euv*0.1*tan((afeuv+afiuv)/2);

		num_t[1]=it-num_t[0]+1;
		break;

	}

	if(semiala==DER)
	{
		for(it=0;it<num_t[0];it++)
		{
			xt[it]=RPL*270-xt[it];
			ut[it]=RPL*270-ut[it];
		}
		for(it=ini[1];it<ini[1]+num_t[1];it++)
		{
			xt[it]=RPL*270-xt[it];
			ut[it]=RPL*270-ut[it];
		}
	}

	fptr=fopen("puntos.dat","wt");
	fprintf(fptr,"Extrados (num=%i):\n",num_t[0]);
	for(it=0;it<num_t[0];it++)
	{
		fprintf(fptr,"xt[%i]=%f yt[%i]=%f\n",it,xt[it]/RPL,it,yt[it]/RPL);
	}
	fprintf(fptr,"Intrados (num=%i):\n",num_t[1]);
	for(it=ini[1];it<ini[1]+num_t[1];it++)
	{
		fprintf(fptr,"xt[%i]=%f yt[%i]=%f\n",it,xt[it]/RPL,it,yt[it]/RPL);
	}

	fclose(fptr);

}

long decimas()
{
	//union REGS inregs,outregs;
	//long horas,minutos,segundos,decimas;

	//inregs.h.ah=0x2C;
	//intdos(&inregs,&outregs);
	//horas=outregs.h.ch;
	//minutos=outregs.h.cl;
	//segundos=outregs.h.dh;
	//decimas=outregs.h.dl;
	//return(horas*360000+minutos*6000+segundos*100+decimas);
    return 1;
}

void textoxy(int x,int y,char *cadena)
{
    //printf("%s\n", cadena);
	//setcolor(WHITE);
	//outtextxy(x,y,"ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ");
	//setcolor(BLUE);
	outtextxy(x,y,cadena);
}

void cargarGeometria(char *acceso_datos,char *acceso,int *env,int *cuerda_m,int *cuerda_e,
	int *f,int *b,int *g,int *alturaxy,int *alturauv)
{
/*	char nombre[30]; */
	char cadena[30];
	FILE *fptr;

	//setcolor(BLUE);
	if((fptr=fopen(acceso_datos,"rt"))!=NULL)
	{
		fscanf(fptr,"%s %s\n",cadena,acceso);
		printf("Perfil: %s\n", acceso);

		fscanf(fptr,"%s %i\n",cadena,&env);
		printf("Envergadura: %i\n", env);

		fscanf(fptr,"%s %i\n",cadena, &cuerda_e);
		printf("C.encastre: %i\n", cuerda_e);

		fscanf(fptr,"%s %i\n",cadena, &cuerda_m);
		printf("C.marginal: %i\n", cuerda_m);

		fscanf(fptr,"%s %i\n",cadena, &f);
		printf("Flecha: %i\n", f);

		fscanf(fptr,"%s %i\n",cadena, &g);
		printf("G: %i\n", g);

		fscanf(fptr,"%s %i\n",cadena, &b);
		printf("B: %i\n", b);

		fscanf(fptr,"%s %i\n",cadena, &alturaxy);
		printf("Altura encastre: %i\n", alturaxy);
		alturaxy-=HBASE;

		fscanf(fptr,"%s %i\n",cadena, &alturauv);
		printf("Altura marginal: %i\n", alturauv);
		alturauv-=HBASE;

		if(fclose(fptr)!=0)
		{
			outtextxy(10,40,"no se pudo cerrar");
			getchar();
		}
		getchar();
	}
	else
	{
		outtextxy(10,40,"no se pudo habrir");
		getchar();
	}
}

void setMaterial(int material,int *mat,int *velocidad,float *intensidad)
{
	*mat=material;
	switch(material)
        {
	case 1:	/* azul */
		*velocidad=300;
		*intensidad=0.45;
		break;
	case 2:	/* blanco baja dens. */
		*velocidad=300;
		*intensidad=0.30;
		break;
	case 3:	/* rosa y azul ROOFMATE */
		*velocidad=220;
		*intensidad=0.45;
		break;
	case 4:	/* blanco 20 Kg/m3. */
		*velocidad=260;
		*intensidad=0.35;
		break;
	case 5:	/* Styrodur (verde) 34.5 Kg/m3. */
		*velocidad=220;
		*intensidad=0.45;
		break;

	}
}

void simetria(int semiala,int *ini,int *num_t,int *xc,int *yc,int *uc,int *vc)
{
	int it;
	if(semiala==DER)
	{
		for(it=0;it<num_t[0];it++)
		{
			xc[it]=RPL*270-xc[it];
			uc[it]=RPL*270-uc[it];
		}
		for(it=ini[1];it<ini[1]+num_t[1];it++)
		{
			xc[it]=RPL*270-xc[it];
			uc[it]=RPL*270-uc[it];
		}
	}
}

