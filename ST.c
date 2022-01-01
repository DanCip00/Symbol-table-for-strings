//L'ID viene assegnato crescente con l'inerimento. Id è una cosa separata dall'indice
//Inserimento in vettore ordinato per ottimizzare la ricerca
//
#include "ST.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define initdim 50 //Default starting size, automatic reallocation

typedef struct{
    int id;
    char *name;
}item;

struct tab{
    int size;
    int max_size;
    item *vect;
    int *posid;
};

    /*ITEM*/

static item newitem(char *buf,int id){
    item new;
    new.id=id;
    new.name=malloc(sizeof(char)*(strlen(buf)+1));
    strcpy(new.name,buf);
    return new;
}

static item itemSetNull(void){
    item it;
    it.id=-1;
    it.name=NULL;
    return it;
}

    /*INIT & FREE*/
ST STinit(void){
    int i;
    ST tab=malloc(sizeof(struct tab));
    
    tab->vect=malloc(sizeof(item)*initdim);
    tab->posid=malloc(sizeof(int)*initdim);
    for(i=0;i<initdim;i++)
        tab->posid[i]=-1;
    tab->max_size=initdim;
    tab->size=0;
    return tab;
}

void STfree(ST tab){
    int i;
    
    for (i=0;i<tab->size;i++)
        free(tab->vect[i].name);
    free(tab->vect);
    free(tab->posid);
    free(tab);
}
    /*RICERCA*/
static int strmin(const char string_i[],const char string_2[]){
    int i,max;
    max=(int)(strlen(string_i)>=strlen(string_2)?strlen(string_2):strlen(string_i));
    for (i=0;i<max && toupper(string_i[i])==toupper(string_2[i]);i++);
    if (toupper(string_i[i])<toupper(string_2[i]))
        return 1;
    return 0;
}
static item STfind(ST tab,char *key,int l,int r){ //Ricerca dicotomica
    int m;
    
    if (l>r)
        return itemSetNull();
    m=(l+r)/2;
    if (strcmp(tab->vect[m].name,key)==0)
        return tab->vect[m];
    if (strmin(key,tab->vect[m].name))
        return STfind(tab,key,l,m-1);
    return STfind(tab,key,m+1,r);
}

int STsearchIndex(ST tab,char *buf){
    item it;
    
    it=STfind(tab,buf,0,tab->size-1);
    return it.id;
}


char* STsearch(ST tab,int ID){  //Accesso diretto a discapito di un vettore in più
    int i=tab->posid[ID];
    
    if(i==-1)
        return NULL;
    return tab->vect[i].name;
}

    /*INSERIMENTO*/  //Ordine ascendente

int STinsert(ST tab,char *buf){ //Costo ricerca o(log N) più costo di insermento o(N)-->o(N)
    int i;
    item new;
    
    i=STsearchIndex(tab,buf);
    if (i!=-1)
        return i;
    
    if (tab->size+1>tab->max_size){
        tab->max_size+=initdim;
        tab->vect=realloc(tab->vect,sizeof(item)*(tab->max_size));
    }
    
    new=newitem(buf,tab->size);
    for (i=(tab->size)-1;i>=0 && strmin(new.name,tab->vect[i].name);i--){
        tab->vect[i+1]=tab->vect[i];
        tab->posid[i]+=1;
    }
    tab->vect[i+1]=new;
    tab->posid[new.id]=i+1;
    tab->size++;
    
    return new.id;
}
    /*DI SERVIZIO*/
int STsize(ST tab){
    return tab->size;
}
    /*output*/
void STprint(ST tab){
    int i;
    
    for (i=0;i<tab->size;i++){
        printf("%d ->%s\t%d\n",i,tab->vect[i].name,tab->vect[i].id);
    }
    printf("Pos ID\n");
    for (i=0;i<tab->size;i++)
    printf("ID %d-->POS %d\n",i,tab->posid[i]);
}
