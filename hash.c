#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/*inicio definiciones y funciones que se usaran en la lista*/

#define MAX 800 // len of the array of pinters
#define MAXchar 30

typedef struct node{
    char data[MAXchar];
    struct node* next;
} node;

#include "linkedlist-functions.c"

/*fin definiciones y funciones que se usaran en la lista*/

char *getword(FILE *fp);
int hash(char string[30]);
/*
int hash(char string[30]){
	int hash=5381;
  int i;
	int largo = strlen(string);
	for(i=0; i<largo; i++)
		//aux += string[i] - '0';
    hash = ((hash << 5) + hash) + string[i];
	return hash;
}
*/


int hash(char string[30]){
	int hash=0;
  int i;
	int largo = strlen(string);
	for(i=0; i<largo; i++)
		hash += string[i] - '0';

	return hash%MAX;
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
  int i;
  clock_t start_t, end_t, total_t;
  start_t = clock();

  //crea las cabeceras de las listas y la hace null
	node* heads[MAX];
	for (i = 0; i < MAX; i++) {
		heads[i] = NULL;
	}

  /* Se Abre el archivo  */
  FILE *fp;
  fp = fopen("archivo_4.tex", "r");
  char *word;
  while(word=getWord(fp)){ //se obtiene palabra por palabra del archivo
      index = hash(word); // se encuentra su indice hash a la palabra
      heads[index] =prepend(heads[index], word); //se guarda en la lista que corresponde según su valor hash
  }
  fclose(fp);
  //muestra las listas
  printf("Number hash list - words\n");
  for (i = 0; i < MAX; i++) {
    if(heads[i] != NULL){
      printf("%i ", i);
     mostrar(heads[i]);
      printf("\n" );
    }
  }

  end_t = clock();
  printf("\n Tiempo en generar las listas: %f segundos\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);
  start_t = clock();

	/* Pregunta 1*/
  printf("\n1.- ¿Se encuentra la palabra readiness? \n" );
  int flag = 0;
  for (  i = 0; i < MAX; i++) {
    flag = search(heads[i], "readiness");
    if(flag == 1){
      printf("Resp: Sí\n");
      break;
    }
  }
  if (flag == 0) {
    printf("\nResp: No\n");
  }
  end_t = clock();
  printf("\n Tiempo en responder: %f segundos\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);

  start_t = clock();
	/* Pregunta 2*/
  printf("\n2.- ¿Se encuentra la palabra fearless? \n" );
  flag = 0;
  for (  i = 0; i < MAX; i++) {
    flag = search(heads[i], "fearless");
    if(flag == 1){
      printf("Resp: Sí\n");
      break;
    }
  }
  if (flag == 0) {
    printf("Resp: No\n");
  }
  end_t = clock();
  printf("\n Tiempo en responder: %f segundos\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);

  start_t = clock();
	/* Pregunta 3*/
	printf("\n3.- ¿Cuantas palabras distintas hay en el archivo?\n" );
	int count = 0;
	for (  i = 0; i < MAX; i++) {
		count += contarDistintas(heads[i]);
	}
	printf("\nResp: Hay %i palabras distintas en el archivo\n", count );
  end_t = clock();
  printf("\nTiempo en responder: %f segundos\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);

  start_t = clock();
	/* Pregunta 4*/
	printf("\n4.- ¿Cual es la palabra más utilizada?\n" );
  char aux[MAXchar];
  char mayor[MAXchar];
  int auxFreq = 0;
  int mayorFreq = 0;
  for (  i = 0; i < MAX; i++) {
    buscaMayorElemento(heads[i], aux);
    auxFreq = contarElemento(heads[i], aux);
    if(auxFreq > mayorFreq){
      strcpy(mayor,aux);
      mayorFreq = auxFreq;
    }
  }
  printf("Resp: Es la palabra \"%s\" que se repite %i veces\n", mayor,mayorFreq);
  end_t = clock();
  printf("\n Tiempo en responder: %f segundos\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);


  //se borran las listas
  for (  i = 0; i < MAX; i++) {
    dispose(heads[i]);
  }

	return 0;
}
