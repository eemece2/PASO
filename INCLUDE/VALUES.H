GAHI;
	initgraph(&g_driver,&g_modo,"c:\\lenguage\\turboc");


	COUT(CONTROLPORT,146);   /* A IN, B IN, C OUT  */

	cleardevice();
	setcolor(4);


	k=0;
	i=0;
	h=150;
	ah=70;
	p=40;

        line(0,h     ,630,h     );
	line(0,h+ah  ,630,h+ah  );
	line(0,h+ah*2,630,h+ah*2);
	line(0,h+ah*3,630,h+ah*3);


	while(i&1==0)
	{
		i=CIN(APORT);
	}

	for(k=0;k<=630;k++)
	{
		in[k]=CIN(APORT);
		time(0);
	}

	for(k=0;k<=630;k++)
	{
		c1=in[k]&1;
		c2=in[k]&2;c2=c2/2;
		c3=in[k]&4;c3=c3/4;
		c4=in[k]&8;c4=c4/8;
		setcolor(15);
		putpixel(k,h     -c1*p,15);
		putpixel(k,h+ah  -c2*p,15);
		putpixel(k,h+ah*2-c3*p,15);
		putpixel(k,h+ah*3-c4*p,15);
	}


/*	while(!kbhit())
	{
		i=CIN(APORT);

		c1=i&1;
		c2=i&2;c2=c2/2;
		c3=i&4;c3=c3/4;
		c4=i&8;c4=c4/8;
		setcolor(15);
		line(k-1,h     -c1o*p,k,h     -c1*p);
		line(k-1,h+ah  -c2o*p,k,h+ah  -c2*p);
		line(k-1,h+ah*2-c3o*p,k,h+ah*2-c3*p);
		line(k-1,h+ah*3-c4o*p,k,h+ah*3-c4*p);

		putpixel