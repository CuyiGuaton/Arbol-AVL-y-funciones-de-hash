#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/*inicio definiciones y funciones que se usaran en la lista*/

#define MAX 200
#define MAXchar 30

typedef struct node{
    char data[MAXchar];
    struct node* next;
} node;

#include "linkedlist-functions.c"

/*fin definiciones y funciones que se usaran en la lista*/

char *getword(FILE *fp);
int hash(char string[30]);

int hash(char string[30]){
	int aux=0;
	int largo = strlen(string);
	for(int i=0; i<largo; i++)
		aux += string[i] - '0';
	return aux%MAX;
}

//obtiene cada palabra del archivo
char *getWord(FILE *fp){
    char word[100];
    int ch, i=0;
    while(EOF!=(ch=fgetc(fp)) && !isalpha(ch))
        ;//skip
    if(ch == EOF)
        return NULL;
    do{
        word[i++] = tolower(ch);
    }while(EOF!=(ch=fgetc(fp)) && isalpha(ch));
    word[i]='\0';
    return strdup(word);
}

int main(int argc, char const *argv[]) {
	int index;

  //crea las cabeceras de las listas y la hace null
	node* heads[MAX];
	for (size_t i = 0; i < MAX; i++) {
		heads[i] = NULL;
	}

  /* Se Abre el archivo  */
  FILE *fp;
  fp = fopen("archivo_4.tex", "r");
  char *word;
  while(word=getWord(fp)){
      index = hash(word);
      prepend(heads[0], word);
      printf("%s\n",word );
  }
  fclose(fp);
  mostrar(heads[0]);

  //muestra las listas
  for (size_t i = 0; i < MAX; i++) {
    if(heads[i]!=NULL){
      mostrar(heads[i]);
      printf("\n" );
    }
  }
	return 0;
}
