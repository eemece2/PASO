/* pasoaux.h */

void activamotor();
void desactivamotor();
void pasomotor(int motor,int sentido);
void pausa(long t);
void transline(int x1,int y1,int x2,int y2,int col);
void transpixel(int x,int y,int col);
void linea_planta(long x1,long z1,long x2,long z2,int col);
void move_to(int x,int y,int u,int v);
void linea_to_rel(int x2,int y2,int u2,int v2,int time);
void move_graf_to(int x,int y,int u,int v);
void linea_graf_to(int x,int y,int u,int v);
void linea_to(int x2,int y2,int u2,int v2,int time);
void initialize(void);

long ciclos_delay(int vel,int ax,int ay);

#define MA	0
#define MB	1
#define MC	2
#define MD	3
#define MNULL	4
#define XMAX	26320
#define YMAX	11280

#define col_iz	 	    1 //LIGHTBLUE
#define col_der		    2 //LIGHTRED
#define col_tray_iz	    3 //LIGHTGREEN
#define col_tray_der	4 //LIGHTMAGENTA

#define RPL	96.6857	/* Pasos del motor por mm */

#define PID2	1.5708
#define PI	3.1416
#define PI2	6.2832

