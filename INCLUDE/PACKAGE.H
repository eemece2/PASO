
/*  fichero cabecera PACKAGE.H  */
/*  Se incluira cuando se utilicen las func. de PACKAGE.C    */

void p_initialice();
void p_close();
void p_setwindow(float x1,float y1,float x2,float y2);
void p_setviewport(int x1,int y1,int x2,int y2);
void p_moveto(float x,float y);
void p_lineto(float x,float y);
void LINEX10(int x1,int y1,int x2,int y2,int c);
void SETPIXEL10(int x,int y,int c);
void p_pixel(float x,float y,int c);