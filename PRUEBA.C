#include<package.h>

main()
{
	p_initialice();
	p_setwindow(0,0,100,100);
	p_setviewport(0,0,640,480);
	p_moveto(20.0,20,0);
	p_lineto(60.0,60.0);
	getch();

}