/*-----------------------------------------------------------------*\
 | Fichero:        IBMSTUF.H                                       |
 | Proyecto:       (general)                                       |
 | Programado por: S. Scott Zimmerman                              |
 | Copyright (c) 1988 por Zimtech. Todos los Derechos Reservados   |
 | Descripci¢n:    Ver IBMSTUF.C                                   |
 | Uso:            Como cabecera para ficheros que usan IBMSTUF    |
 *-----------------------------------------------------------------*/

/* Funciones prototipo: */

int getint(int, int,int,int);
int getline(int, char *,int,int);
int center(int, char *);
void cursinit(void);
void cursxy(int *, int *);
void cursoff();
void curson();
void cursize(int, int);

extern int width;

enum AUXKEYS {
    S_TAB = 15,
    A_Q, A_W, A_E, A_R, A_T, A_Y, A_U, A_I, A_O, A_P,
    A_A = 30, A_S, A_D, A_F, A_G, A_H, A_J, A_K, A_L,
    A_Z = 44, A_X, A_C, A_V, A_B, A_N, A_M,
    F1 = 59, F2, F3, F4, F5, F6, F7, F8, F9, F10,
    NUMLOCK, SCROLLOCK, HOME,
    UP, PG_UP, MINUS, LEFT, FIVE, RIGHT, PLUS,
    END, DOWN, PG_DOWN, INS, DEL,
    S_F1, S_F2, S_F3, S_F4, S_F5, S_F6, S_F7, S_F8, S_F9, S_F10,
    C_F1, C_F2, C_F3, C_F4, C_F5, C_F6, C_F7, C_F8, C_F9, C_F10,
    A_F1, A_F2, A_F3, A_F4, A_F5, A_F6, A_F7, A_F8, A_F9, A_F10,
    ECHO, C_LEFT, C_RIGHT, C_END, C_PG_DOWN, C_HOME,
    A_1 = 120, A_2, A_3, A_4, A_5, A_6, A_7, A_8, A_9, A_0, A_HYPHEN,
    A_EQUAL, C_PG_UP
    };
