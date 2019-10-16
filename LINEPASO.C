/* linepaso.c */

#include <math.h>
#include <graphics.h>
#include <pasoaux.h>

extern int xact,yact,uact,vact;
extern int xgraf,ygraf,ugraf,vgraf;
extern int lng;
extern float coef_A,coef_B;

long ciclos_delay(int vel,int ax,int ay);
int n_velocidad(long n);

void linea_to(int x2,int y2,int u2,int v2,int velocidad)
{
	long d_x,d_y,d_u,d_v,dx,dy,du,dv;
	long Aincr_x,Aincr_y,Aincr_u,Aincr_v;
	long Bincr_x,Bincr_y,Bincr_u,Bincr_v;
	long yincr,xincr,uincr,vincr;
	int x1,y1,u1,v1;
	int x,y,u,v,null,unull;
	long ax,ay,au,av;
	long delay;
	long lxy,luv;

	x1=xact;
	y1=yact;
	u1=uact;
	v1=vact;
	ax=abs(x2-x1);
	ay=abs(y2-y1);
	au=abs(u2-u1);
	av=abs(v2-v1);

	if((ax==0)  && (ay==0) && (au==0) &&  (av==0)) return(0);

	lxy=sqrt(ax*ax+ay*ay);
	luv=sqrt(au*au+av*av);

	if((ax>=ay) && (ax>=au) && (ax>=av))
	{
		if(lxy > luv) delay=ciclos_delay(velocidad,ax,ay);
		else delay=ciclos_delay(velocidad*lxy/luv,ax,ay);

/*		delay=time*(lxy/ax); */

                if(y2 > y1)
			yincr=1;
		else
			yincr=-1;
		if(u2 > u1)
			uincr=1;
		else
			uincr=-1;
		if(v2 > v1)
			vincr=1;
		else
			vincr=-1;

		if(x1 < x2 )
		{
			dx=x2-x1;
			dy=abs(y2-y1);
			du=abs(u2-u1);
			dv=abs(v2-v1);
			d_y=2*dy-dx;
			d_u=2*du-dx;
			d_v=2*dv-dx;

			Aincr_y=2*(dy-dx);
			Bincr_y=2*dy;
			Aincr_u=2*(du-dx);
			Bincr_u=2*du;
			Aincr_v=2*(dv-dx);
			Bincr_v=2*dv;

			x=x1;
			y=y1;
			u=u1;
			v=v1;
			unull=u;

			transpixel(x,y,col_iz);
			transpixel(u,v,col_der);

			for(x=x1+1;x<=x2;x++)
			{
				pausa(delay);
				pasomotor(MA,1);
				if(d_y>=0)
				{
					pasomotor(MB,yincr);
					y+=yincr;
					d_y+=Aincr_y;
				}
				else
				{
					pasomotor(MNULL,yincr);
					null+=yincr;
					d_y+=Bincr_y;
				}

				if(d_u>=0)
				{
					pasomotor(MC,uincr);
					u+=uincr;
					d_u+=Aincr_u;
				}
				else
				{
					pasomotor(MNULL,uincr);
					unull+=uincr;
					d_u+=Bincr_u;
				}

				if(d_v>=0)
				{
					pasomotor(MD,vincr);
					v+=vincr;
					d_v+=Aincr_v;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_v+=Bincr_v;
				}

				transpixel(x,y,col_iz);
				transpixel(u,v,col_der);
			}
		}
		else
		{
			dx=x1-x2;
			dy=abs(y2-y1);
			du=abs(u2-u1);
			dv=abs(v2-v1);
			d_y=2*dy-dx;
			d_u=2*du-dx;
			d_v=2*dv-dx;

			Aincr_y=2*(dy-dx);
			Bincr_y=2*dy;
			Aincr_u=2*(du-dx);
			Bincr_u=2*du;
			Aincr_v=2*(dv-dx);
			Bincr_v=2*dv;

			x=x1;
			y=y1;
			u=u1;
			v=v1;

			transpixel(x,y,col_iz);
			transpixel(u,v,col_der);

			for(x=x1-1;x>=x2;x--)
			{
				pausa(delay);
				pasomotor(MA,-1);
				if(d_y>=0)
				{
					pasomotor(MB,yincr);
					y+=yincr;
					d_y+=Aincr_y;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_y+=Bincr_y;
				}

				if(d_u>=0)
				{
					pasomotor(MC,uincr);
					u+=uincr;
					d_u+=Aincr_u;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_u+=Bincr_u;
				}

				if(d_v>=0)
				{
					pasomotor(MD,vincr);
					v+=vincr;
					d_v+=Aincr_v;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_v+=Bincr_v;
				}

				transpixel(x,y,col_iz);
				transpixel(u,v,col_der);
			}
		}
	}
	else if((ay>=ax) && (ay>=au) && (ay>=av))
	{
		if(lxy > luv) delay=ciclos_delay(velocidad,ay,ax);
		else delay=ciclos_delay(velocidad*lxy/luv,ay,ax);

/*		delay=time*(lxy/ay); */

		if(x2 > x1)
			xincr=1;
		else
			xincr=-1;
		if(u2 > u1)
			uincr=1;
		else
			uincr=-1;
		if(v2 > v1)
			vincr=1;
		else
			vincr=-1;

		if(y1 < y2 )
		{
			dy=y2-y1;
			dx=abs(x2-x1);
			du=abs(u2-u1);
			dv=abs(v2-v1);
			d_x=2*dx-dy;
			d_u=2*du-dy;
			d_v=2*dv-dy;

			Aincr_x=2*(dx-dy);
			Bincr_x=2*dx;
			Aincr_u=2*(du-dy);
			Bincr_u=2*du;
			Aincr_v=2*(dv-dy);
			Bincr_v=2*dv;

			x=x1;
			y=y1;
			u=u1;
			v=v1;

			transpixel(x,y,col_iz);
			transpixel(u,v,col_der);

			for(y=y1+1;y<=y2;y++)
			{
				pausa(delay);
				pasomotor(MB,1);
				if(d_x>=0)
				{
					pasomotor(MA,xincr);
					x+=xincr;
					d_x+=Aincr_x;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_x+=Bincr_x;
				}

				if(d_u>=0)
				{
					pasomotor(MC,uincr);
					u+=uincr;
					d_u+=Aincr_u;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_u+=Bincr_u;
				}

				if(d_v>=0)
				{
					pasomotor(MD,vincr);
					v+=vincr;
					d_v+=Aincr_v;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_v+=Bincr_v;
				}

				transpixel(x,y,col_iz);
				transpixel(u,v,col_der);
			}
		}
		else
		{
			dy=y1-y2;
			dx=abs(x2-x1);
			du=abs(u2-u1);
			dv=abs(v2-v1);
			d_x=2*dx-dy;
			d_u=2*du-dy;
			d_v=2*dv-dy;

			Aincr_x=2*(dx-dy);
			Bincr_x=2*dx;
			Aincr_u=2*(du-dy);
			Bincr_u=2*du;
			Aincr_v=2*(dv-dy);
			Bincr_v=2*dv;

			x=x1;
			y=y1;
			u=u1;
			v=v1;

			transpixel(x,y,col_iz);
			transpixel(u,v,col_der);

			for(y=y1-1;y>=y2;y--)
			{
				pausa(delay);
				pasomotor(MB,-1);
				if(d_x>=0)
				{
					pasomotor(MA,xincr);
					x+=xincr;
					d_x+=Aincr_x;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_x+=Bincr_x;
				}

				if(d_u>=0)
				{
					pasomotor(MC,uincr);
					u+=uincr;
					d_u+=Aincr_u;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_u+=Bincr_u;
				}

				if(d_v>=0)
				{
					pasomotor(MD,vincr);
					v+=vincr;
					d_v+=Aincr_v;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_v+=Bincr_v;
				}

				transpixel(x,y,col_iz);
				transpixel(u,v,col_der);
			}
		}
	}
	else if((au>=ax) && (au>=ay) && (au>=av))
	{
		if(luv > lxy) delay=ciclos_delay(velocidad,au,av);
		else delay=ciclos_delay(velocidad*luv/lxy,au,av);

/*		delay=time*(sqrt(ax*ax+ay*ay)/au); */

		if(x2 > x1)
			xincr=1;
		else
			xincr=-1;
		if(y2 > y1)
			yincr=1;
		else
			yincr=-1;
		if(v2 > v1)
			vincr=1;
		else
			vincr=-1;

		if(u1 < u2 )
		{
			du=u2-u1;
			dx=abs(x2-x1);
			dy=abs(y2-y1);
			dv=abs(v2-v1);
			d_x=2*dx-du;
			d_y=2*dy-du;
			d_v=2*dv-du;

			Aincr_x=2*(dx-du);
			Bincr_x=2*dx;
			Aincr_y=2*(dy-du);
			Bincr_y=2*dy;
			Aincr_v=2*(dv-du);
			Bincr_v=2*dv;

			x=x1;
			y=y1;
			u=u1;
			v=v1;

			transpixel(x,y,col_iz);
			transpixel(u,v,col_der);

			for(u=u1+1;u<=u2;u++)
			{
				pausa(delay);
				pasomotor(MC,1);
				if(d_x>=0)
				{
					pasomotor(MA,xincr);
					x+=xincr;
					d_x+=Aincr_x;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_x+=Bincr_x;
				}

				if(d_y>=0)
				{
					pasomotor(MB,yincr);
					y+=yincr;
					d_y+=Aincr_y;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_y+=Bincr_y;
				}

				if(d_v>=0)
				{
					pasomotor(MD,vincr);
					v+=vincr;
					d_v+=Aincr_v;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_v+=Bincr_v;
				}

				transpixel(x,y,col_iz);
				transpixel(u,v,col_der);
			}
		}
		else
		{
			du=u1-u2;
			dx=abs(x2-x1);
			dy=abs(y2-y1);
			dv=abs(v2-v1);
			d_x=2*dx-du;
			d_y=2*dy-du;
			d_v=2*dv-du;

			Aincr_x=2*(dx-du);
			Bincr_x=2*dx;
			Aincr_y=2*(dy-du);
			Bincr_y=2*dy;
			Aincr_v=2*(dv-du);
			Bincr_v=2*dv;

			x=x1;
			y=y1;
			u=u1;
			v=v1;

			transpixel(x,y,col_iz);
			transpixel(u,v,col_der);

			for(u=u1-1;u>=u2;u--)
			{
				pausa(delay);
				pasomotor(MC,-1);
				if(d_x>=0)
				{
					pasomotor(MA,xincr);
					x+=xincr;
					d_x+=Aincr_x;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_x+=Bincr_x;
				}

				if(d_y>=0)
				{
					pasomotor(MB,yincr);
					y+=yincr;
					d_y+=Aincr_y;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_y+=Bincr_y;
				}

				if(d_v>=0)
				{
					pasomotor(MD,vincr);
					v+=vincr;
					d_v+=Aincr_v;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_v+=Bincr_v;
				}

				transpixel(x,y,col_iz);
				transpixel(u,v,col_der);
			}
		}
	}
	else if((av>=ax) && (av>=ay) && (av>=au))
	{
		if(luv > lxy) delay=ciclos_delay(velocidad,av,au);
		else delay=ciclos_delay(velocidad*luv/lxy,av,au);

/*		delay=time*(sqrt(ax*ax+ay*ay)/av); */

		if(x2 > x1)
			xincr=1;
		else
			xincr=-1;
		if(y2 > y1)
			yincr=1;
		else
			yincr=-1;
		if(u2 > u1)
			uincr=1;
		else
			uincr=-1;

		if(v1 < v2 )
		{
			dv=v2-v1;
			dx=abs(x2-x1);
			dy=abs(y2-y1);
			du=abs(u2-u1);
			d_x=2*dx-dv;
			d_y=2*dy-dv;
			d_u=2*du-dv;

			Aincr_x=2*(dx-dv);
			Bincr_x=2*dx;
			Aincr_y=2*(dy-dv);
			Bincr_y=2*dy;
			Aincr_u=2*(du-dv);
			Bincr_u=2*du;

			x=x1;
			y=y1;
			u=u1;
			v=v1;

			transpixel(x,y,col_iz);
			transpixel(u,v,col_der);

			for(v=v1+1;v<=v2;v++)
			{
				pausa(delay);
				pasomotor(MD,1);
				if(d_x>=0)
				{
					pasomotor(MA,xincr);
					x+=xincr;
					d_x+=Aincr_x;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_x+=Bincr_x;
				}

				if(d_y>=0)
				{
					pasomotor(MB,yincr);
					y+=yincr;
					d_y+=Aincr_y;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_y+=Bincr_y;
				}

				if(d_u>=0)
				{
					pasomotor(MC,uincr);
					u+=uincr;
					d_u+=Aincr_u;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_u+=Bincr_u;
				}

				transpixel(x,y,col_iz);
				transpixel(u,v,col_der);
			}
		}
		else
		{
			dv=v1-v2;
			dx=abs(x2-x1);
			dy=abs(y2-y1);
			du=abs(u2-u1);
			d_x=2*dx-dv;
			d_y=2*dy-dv;
			d_u=2*du-dv;

			Aincr_x=2*(dx-dv);
			Bincr_x=2*dx;
			Aincr_y=2*(dy-dv);
			Bincr_y=2*dy;
			Aincr_u=2*(du-dv);
			Bincr_u=2*du;

			x=x1;
			y=y1;
			u=u1;
			v=v1;

			transpixel(x,y,col_iz);
			transpixel(u,v,col_der);

			for(v=v1-1;v>=v2;v--)
			{
				pausa(delay);
				pasomotor(MD,-1);
				if(d_x>=0)
				{
					pasomotor(MA,xincr);
					x+=xincr;
					d_x+=Aincr_x;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_x+=Bincr_x;
				}

				if(d_y>=0)
				{
					pasomotor(MB,yincr);
					y+=yincr;
					d_y+=Aincr_y;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_y+=Bincr_y;
				}

				if(d_u>=0)
				{
					pasomotor(MC,uincr);
					u+=uincr;
					d_u+=Aincr_u;
				}
				else
				{
                                	pasomotor(MNULL,yincr);
					null+=yincr;
					d_u+=Bincr_u;
				}

				transpixel(x,y,col_iz);
				transpixel(u,v,col_der);
			}
		}
	}
	xact=x2;
	yact=y2;
	uact=u2;
	vact=v2;
}

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

int n_velocidad(long n)
{
	return(60*(1/((coef_B*n+coef_A)*RPL))); /*return  mm/min */
}