/*-----------------------------------------------------------------*\
 | Fichero:        IBMSTUF.C                                       |
 | Proyecto:       (general)                                       |
 | Programado por: S. Scott Zimmerman                              |
 | Copyright (c) 1988 por Zimtech. Todos los derechos reservados.  |
 | Descripci�n:    Ver funciones individuales                      |
 | Uso:            Uso con otros m�dulos                           |
\*-----------------------------------------------------------------*/

#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <bios.h>

#define VIDEO 0x10

/* Funciones prototipos: */
void cursinit(void);
void curson(void);
void cursoff(void);
void cursize(int, int);
int center(int, char *);
int getline(int, char *,int col,int row);
int getint(int min, int max,int col,int row);
void cursxy(int *, int *);
void putcaracter(int col,int row,char ch);

static union REGS inregs, outregs;
static int curstop, cursbot, cursflg = 1, width = 80;

/*==================================================================*/
int getint(int min, int max,int col,int row)  /* Obtiene un entero desde la entrada */
{
  char string[79], buffmax[8],buffmin[8];
  int maxchars;
  register i;

  sprintf(buffmin, "%1d", min);
  sprintf(buffmax, "%1d", max);
  maxchars = strlen(buffmin);
  if (strlen(buffmax) > maxchars) maxchars=strlen(buffmax);
  do  {
/*    clreol();
*/
    getline(maxchars, string,col,row);
    i = atoi(string);
  } while (i < min || i > max);
  return (i);
}
/*==================================================================*/
int getline(int maxlen, char buffer[],int col,int row)/* Obtiene una l�nea de texto */
{
  register i = 0;
  char ch;
  int done = 0;


  do {
    ch = getch();
    if ((i < maxlen) && (ch > ' ')) {
      buffer[i++] = ch;        /* Caracter normal                   */
      putcaracter(col,row,ch);
      col+=10;
    }
    else {
      switch (ch) {
      case '\r':               /* Vuelta de carro o Escape          */
      case '\x1b':
        done = 1;              /* Fin de entrada                    */
        break;
      case '\x08':             /* Espacio-atras                     */
        if (i) {
/*	  cursxy(&col, &row);
	  gotoxy(--col, row);
*/
	  col-=10;
	  setcolor(WHITE);
	  putcaracter(col,row,'�');
	  setcolor(BLUE);
	  /*	  gotoxy(col, row);
*/
          buffer[i--] = '\0';
        }
        break;
      case ' ':                /* Deniega empezar con un espacio    */
        if (i && (i < maxlen)) {
          buffer[i++] = ch;    /* Ponerlo si no es el primero       */
	  putcaracter(col,row,ch);
	  col+=10;
        }
        break;
      case '\0':               /* Teclado de caracteres extendido   */
        ch = getch();          /* Obtiene un c�digo extendido       */
        if ((ch == 75) && (i)) { /* Flecha izquierda                */
/*	  cursxy(&col, &row);
	  gotoxy(--col, row);
*/
	  col-=10;
	  setcolor(WHITE);
	  putcaracter(col,row,'�');
	  setcolor(BLUE);
/*	  gotoxy(col, row);
*/
          buffer[i--] = '\0';
        }
        break;
      }
    }
  } while (!done);
  buffer[i++]='\0';            /* Pone el caracter nulo al final    */
  return(i);                   /* Devuelve la longitud de la cadena */
}
/*==================================================================*/
int center(int line, char *string) /* Centra una cadena sobre 'line'*/
{
  int num;

  num = strlen(string);        /* Obtiene la longitud de la cadena  */
  gotoxy ((width - num + 1) / 2, line);  /* Calc posici�n cursor    */
  cputs(string);               /* Imprime la cadena                 */
  return (num);
}
/*==================================================================*/
void cursinit()                /* Inicializa tel tama�o del cursor  */
{
  int equip;
  equip = biosequip();         /* Chequea si es monocroma o color   */
  if ((equip & 0x0030) == 0x30)
    cursize(11, 12);           /* Cursor para monitor monocromo     */
  else
    cursize(6,7);              /* Cursor para monitor en color      */
  cursflg = 1;                 /* El cursor est� en 'on'            */
}
/*==================================================================*/
void cursxy(int *column, int *row) /* Lee posici�n (x,y) del cursor */
{
  inregs.h.ah = 3;        /* Selec registros para la llamada a BIOS */
  inregs.h.bh = 0;             /* La p�gina mostrada es la n�mero 0 */
  int86(VIDEO, &inregs, &outregs); /* Llama a la BIOS               */
  *column = outregs.h.dl + 1;  /* Selec column (+1 para rng 1...80) */
  *row = outregs.h.dh + 1;     /* Selec fila (+1 para rng 1...25)   */
}
/*==================================================================*/
void cursoff()                 /* Quita el cursor. (Para volver a   */
                               /* ponerlo, utilice curson() )       */
{
  if (cursflg) {
    inregs.h.ah = 1;        /* Selec registros para llamada de BIOS */
    inregs.h.ch = 0x20;        /* Selecciona comienzo de scan       */
    inregs.h.cl = 0;           /* Selecciona fin de scan            */
    int86(VIDEO, &inregs, &outregs); /* Llamada a la BIOS           */
    cursflg = 0;
  }
}
/*==================================================================*/
void curson()             /* Coloca cursor con modelado por defecto */
{
  if (!cursflg) {
    inregs.h.ah = 1;        /* Selec registros para llamada de BIOS */
    inregs.h.ch = curstop;     /* Selecciona comienzo de scan       */
    inregs.h.cl = cursbot;     /* Selecciona fin de scan            */
    int86(VIDEO, &inregs, &outregs);  /* Llamada a la BIOS          */
    cursflg = 1;
  }
}
/*==================================================================*/
void cursize(int top, int bottom) /* Selec modelador del cursor     */
{
  inregs.h.ah = 1;          /* Selec registros para llamada de BIOS */
  inregs.h.ch = curstop = top; /* Selecciona comienzo de scan       */
  inregs.h.cl = cursbot = bottom; /* Selecciona fin de scan         */
  int86(VIDEO, &inregs, &outregs); /* Llamada a BIOS                */
}

void putcaracter(int col,int row,char ch)
{
	char caract[2];
	caract[0]=ch;
	caract[1]='\0';
	outtextxy(col,row,caract);
}
