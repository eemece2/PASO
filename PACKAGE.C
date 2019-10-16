
/*  SIMPLE GRAPHICS PACKAGE  Lec.6 del NEWMAN  ( PACKAGE.C )  */

#include <STDIO.H>
#include <MATH.H>
#include <GRAPHICS.H>
#include <package.h>

float WVxm  ,WVxa  ,WVym  ,WVya  ;
float Wxl=0   ,Wxr=1   ,Wyb=0   ,Wyt=1   ;
int	  Vxl=0   ,Vxr=1   ,Vyb=0   ,Vyt=1   ;
int   Clipxl,Clipxr,Clipyb,Clipyt;
int   cx,cy;

void p_initialice()
		{
		int g_driver=VGA,g_mode=VGAHI;
		initgraph(&g_driver,&g_mode,"a:\\");
	/*  clrscr(); */
		}

void p_close()
		{
		closegraph();
		}
void p_setwindowviewport()

		{
		WVxm = (Vxr-Vxl)/(Wxr-Wxl);
		WVxa = Vxl-Wxl*WVxm;
		WVym = (Vyt-Vyb)/(Wyt-Wyb);
		WVya = Vyb-Wyb*WVym;
		}

void p_worldtoscreen(float x,float y,int*sx,int*sy)

		{
		*sx = WVxm*x+WVxa;
		*sy = WVym*y+WVya;
		}

void p_setwindow(float x1,float y1,float x2,float y2)

		{
		Wxl = x1;
		Wxr = x2;
		Wyb = y1;
		Wyt = y2;
		p_setwindowviewport();
		}

void p_setviewport(int x1,int y1,int x2,int y2)

		{
		Vxl = x1;
		Vxr = x2;
		Vyb = y1;
		Vyt = y2;
		p_setwindowviewport();
		Clipxl = x1;
		Clipxr = x2;
		Clipyb = y1;
		Clipyt = y2;
		}

void p_moveto(float x,float y)

		{
		p_worldtoscreen(x,y,&cx,&cy);
		}

	union codigo

		{
		unsigned int val;
		struct cbite

			{
			unsigned left  : 1;
			unsigned right : 1;
			unsigned bottom: 1;
			unsigned top   : 1;
			}bite;

		};

	typedef union codigo cod;
	cod c;


void p_code(int x,int y,cod* c)

		{
		c->val = 0;
		if (x<Clipxl) { c->bite.left=1;}    else { if (x>Clipxr) c->bite.right=1;};
		if (y<Clipyb) { c->bite.bottom=1;} else { if (y>Clipyt) c->bite.top=1;};
		}


void p_clip(int x1,int y1,int x2,int y2)

		{
		cod c1,c2;
		int x,y;

	/*  printf("       x1=%f  y1=%f  x2=%f  y2=%f  \n",x1,y1,x2,y2); */

		p_code(x1,y1,&c1);
		p_code(x2,y2,&c2);

		while (c1.val || c2.val)
			{
			if (c1.val & c2.val) return;
			c.val=c1.val; if (c.val==0) c.val=c2.val;

			if (c.bite.left)
				{
				y=y1+(y2-y1)*(Clipxl-x1)/(x2-x1);
				x=Clipxl;
				}
			else
				{
				if (c.bite.right)
					{
					y=y1+(y2-y1)*(Clipxr-x1)/(x2-x1);
					x=Clipxr;
					}
					else
					{
					if (c.bite.bottom)
						{
						x=x1+(x2-x1)*(Clipyb-y1)/(y2-y1);
						y=Clipyb;
						}
				else
					{
					if (c.bite.top)
						{
						x=x1+(x2-x1)*(Clipyt-y1)/(y2-y1);
						y=Clipyt;
						}
					}
				}
			}
			if (c.val==c1.val)
				{
				x1=x;
				y1=y;
				p_code(x,y,&c1);
				}
			else
				{
				x2=x;
				y2=y;
				p_code(x,y,&c2);
				}
			}

		LINE10(x1,479-y1,x2,479-y2,15);

	/*  printf("linea  x1=%f  y1=%f  x2=%f  y2=%f  \n",x1,y1,x2,y2); */

		}

void p_lineto(float x,float y)

		{
		int nx,ny;

		p_worldtoscreen(x,y,&nx,&ny);
		p_clip(cx,cy,nx,ny);
		cx = nx;
		cy = ny;
		}

void p_pixel(float x,float y)

		{
		int nx,ny;

		p_worldtoscreen(x,y,&nx,&ny);
		SETPIXEL10(nx,ny,15);
		}


