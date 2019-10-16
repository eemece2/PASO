

/*  Graphics Gems, fichero cabecera  GEMS.H   */


/*********************/
/*                   */
/* 2d geometry types */
/*                   */
/*********************/


typedef struct point2struct
	{
	float x,y;
	}	point2;

typedef point2 vector2;

typedef struct intpoint2struct
	{
	int x,y;
	}	intpoint2;

 typedef struct matrix3struct
	{
	float m[3][3];
	}	matrix3;

typedef struct box2dstruct
	{
	point2 min,max;
	} box2;
typedef struct intbox2dstruct
{
	intpoint2 min,max;
} INTBOX2;



/*********************/
/*                   */
/* 3d geometry types */
/*                   */
/*********************/


typedef struct point3struct
	{
	float x,y,z;
	}	point3;

typedef point3 vector3;

typedef struct intpoint3struct
	{
	int x,y,z;
	}	intpoint3;

typedef struct matrix4struct
	{
	float element[4][4];
	}	matrix4;

typedef struct box3dstruct
	{
	point3 min,max;
	}	box3;

/************/
/*          */
/*  macros  */
/*          */
/************/

#define NEWTYPE(x) (x *)malloc(sizeof(x))
