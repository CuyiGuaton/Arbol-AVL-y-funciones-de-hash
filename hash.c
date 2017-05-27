#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*inicio definiciones y funciones que se usaran en la lista*/

#define MAX 200
#define MAXchar 30

typedef struct node{
    char data[MAXchar];
    struct node* next;
} node;

#include "linkedlist-functions.c"

/*fin definiciones y funciones que se usaran en la lista*/

int hash(char string[30]){
	int aux=0;
	int largo = strlen(string);
	for(int i=0; i<largo; i++)
		aux += string[i] - '0';
	return aux%MAX;
}

int main(int argc, char const *argv[]) {
	//int test = hash("klfdklfdsakñlfdsklñdfsklfsdkldsf");
	//printf("%i\n", test);
	return 0;
}
