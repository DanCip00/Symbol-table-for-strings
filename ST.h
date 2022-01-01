//ADT di prima classe per ST
//
//
#ifndef ST_h
#define ST_h

#include <stdio.h>

typedef struct tab *ST;


ST STinit(void);
void STfree(ST tab);

int STinsert(ST tab,char *buf); //Costo ricerca o(log N) + costo di insermento o(N)-->o(N)

char* STsearch(ST tab,int ID);       //Accesso diretto a discapito di un vettore in più
int STsearchIndex(ST tab,char *buf); //Ricerca dicotomica o(logN)

int STsize(ST tab);
void STprint(ST tab);
#endif /* ST_h */
