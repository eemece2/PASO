/* pasoaux.c  */

//#include <graphics.h>
//#include <interface.h>
#include "pasoaux.h"
#include <math.h>

extern int xact,yact,uact,vact;
extern int xgraf,ygraf,ugraf,vgraf;
extern int lng;
int GraphDriver,GraphMode,ErrorCode;

extern float coef_A,coef_B;

// linea_to estaba definida en LINEPASO.C
void linea_to(int x2,int y2,int u2,int v2,int velocidad) {}
// n_velocidad estaba definida en LINEPASO.C
int n_velocidad(long n)
{
	return(60*(1/((coef_B*n+coef_A)*RPL))); /*return  mm/min */
}
// ciclos_delay estaba definida en LINEPASO.C
long ciclos_delay(int vel,int ax,int ay)
{
	long n;
	float raiz;
	float velocidad;

	velocidad=(float)vel/60.0;	/* mm/s */
	raiz=sqrt(1+(float)ay*ay/((float)ax*ax));
	n=(raiz/(RPL*velocidad)-coef_A)/coef_B;
	return(n);
}


void activamotor()
{
	//COUT(APORT,3+16*3);
	//COUT(BPORT,3+16*3);
}

void desactivamotor()
{
	//COUT(APORT,0);
	//COUT(BPORT,0);
}

void pasomotor(int motor,int sentido)
{
    /*
	static int posicA=0;
	static int posicB=0;
	static int posicC=0;
	static int posicD=0;
	static int posicNULL=0;
	int secuencia[8]={3,2,10,8,12,4,5,1};
	int cport;

	if(motor==MA)
	{
		if(sentido==1)
		{
			if((cport=CIN(CPORT) & 2) != 0)
			{
				posicA++;
				if(posicA==8) posicA=0;
			}
		}
		else
		{
			if((cport=CIN(CPORT) & 1) != 0)
			{
				posicA--;
				if(posicA==-1) posicA=7;
			}
		}
		//COUT(APORT,16*secuencia[posicB]+secuencia[posicA]);
		//COUT(BPORT,16*secuencia[posicD]+secuencia[posicC]);
	}

	if(motor==MB)
	{
		if(sentido==1)
		{
			if((cport=CIN(CPORT) & 8) != 0)
			{
				posicB++;
				if(posicB==8) posicB=0;
			}
		}
		else
		{
			if((cport=CIN(CPORT) & 4) != 0)
			{
				posicB--;
				if(posicB==-1) posicB=7;
			}
		}
		//COUT(APORT,16*secuencia[posicB]+secuencia[posicA]);
		//COUT(BPORT,16*secuencia[posicD]+secuencia[posicC]);
	}

	if(motor==MC)
	{
		if(sentido==1)
		{
			if((cport=CIN(CPORT) & 32) != 0)
			{
				posicC++;
				if(posicC==8) posicC=0;
			}
		}
		else
		{
			if((cport=CIN(CPORT) & 16) != 0)
			{
				posicC--;
				if(posicC==-1) posicC=7;
			}
		}
		//COUT(APORT,16*secuencia[posicB]+secuencia[posicA]);
		//COUT(BPORT,16*secuencia[posicD]+secuencia[posicC]);
	}

	if(motor==MD)
	{
		if(sentido==1)
		{
			if((cport=CIN(CPORT) & 128) != 0)
			{
				posicD++;
				if(posicD==8) posicD=0;
			}
		}
		else
		{
			if((cport=CIN(CPORT) & 64) != 0)
			{
				posicD--;
				if(posicD==-1) posicD=7;
			}
		}
		//COUT(APORT,16*secuencia[posicB]+secuencia[posicA]);
		//COUT(BPORT,16*secuencia[posicD]+secuencia[posicC]);
	}

	if(motor==MNULL)
	{
		if(sentido==1)
		{
			if((cport=CIN(CPORT) & 128) != 0)
			{
				posicNULL++;
				if(posicNULL==8) posicNULL=0;
			}
		}
		else
		{
			if((cport=CIN(CPORT) & 64) != 0)
			{
				posicNULL--;
				if(posicNULL==-1) posicNULL=7;
			}
		}
		//COUT(APORT,16*secuencia[posicB]+secuencia[posicA]);
		//COUT(BPORT,16*secuencia[posicD]+secuencia[posicC]);
	}
    */
}



void transline(int x1,int y1,int x2,int y2,int col)
{
	int xx1,yy1,xx2,yy2;
	long mul;

	mul=(long)x1*640;
	xx1=(int)(mul/XMAX);
	mul=(long)y1*640;
	yy1=(int)(mul/XMAX);
	mul=(long)x2*640;
	xx2=(int)(mul/XMAX);
	mul=(long)y2*640;
	yy2=(int)(mul/XMAX);
	//setcolor(col);
	//line(xx1,479-20-yy1,xx2,479-20-yy2);
}

void transpixel(int x,int y,int col)
{
	int xx,yy;
	long mul;

	mul=(long)x*640;
	xx=(int)(mul/XMAX);
	mul=(long)y*640;
	yy=(int)(mul/XMAX);
/*	setcolor(col); */
	//putpixel(xx,479-20-yy,col);
}

void linea_planta(long x1,long z1,long x2,long z2,int col)
{
	long xx1,yy1,xx2,yy2,zz1,zz2;
	long mul;
	long relpl=94;

/*	mul=(long)x1*100;
	xx1=(int)(mul/XMAX);
	mul=(long)x2*100;
	xx2=(int)(mul/XMAX);

	mul=(long)z1*100;
	zz1=(int)(mul/lng);
	mul=(long)z2*100;
	zz2=(int)(mul/lng); */

	xx1=x1*400/((long)RPL*lng);
	xx2=x2*400/((long)RPL*lng);
	zz1=z1*400/((long)RPL*lng);
	zz2=z2*400/((long)RPL*lng);;
	//setcolor(col);
	//line(200+zz1,60+xx1,200+zz2,60+xx2);
/*	line(320,60+xx1,320+300,60+xx2);      */
}

void move_to(int x,int y,int u,int v)
{
	xact=x;
	yact=y;
	uact=u;
	vact=v;
}


void linea_to_rel(int x2,int y2,int u2,int v2,int time)
{
	linea_to(xact+x2,yact+y2,uact+u2,vact+v2,time);
}

void move_graf_to(int x,int y,int u,int v)
{
	xgraf=x;
	ygraf=y;
	ugraf=u;
	vgraf=v;
}

void linea_graf_to(int x,int y,int u,int v)
{
	transline(xgraf,ygraf,x,y,col_tray_iz);
	transline(ugraf,vgraf,u,v,col_tray_der);
	xgraf=x;
	ygraf=y;
	ugraf=u;
	vgraf=v;
}



void pausa(long t)
{
	long i;

	for(i=1;i<=t;i++);

}

void initialize(void)
{
	int xasp,yasp;

    /*
	GraphDriver = DETECT;
	initgraph( &GraphDriver,&GraphMode,"");
	ErrorCode=graphresult();
	if(ErrorCode != grOk)
	{
		printf("Graphics System Error: %s ¦n",grapherrormsg(ErrorCode));
	exit(1);
	}
    */
/*	getpalette(&palette);
	MaxColors= getmaxcolor()+1;
*/
}

