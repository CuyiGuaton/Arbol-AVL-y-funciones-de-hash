#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 200

struct node{
	char word[50];
	struct node * next;
};

int chartoint(char algo[50]);

int chartoint(char algo[50]){
	int aux=0;
	int largo = strlen(algo);
	for(int i=0; i<largo; i++)
		aux += algo[i] - '0';
	return aux;
}

int main(int argc, char const *argv[]) {
	//int pico = chartoint("");
	//printf("%i\n", pico%MAX);
	int *array[MAX];
	struct node word1;
	struct node word2;

	strcpy(word1.word , "pico");
	word1 -> next =	malloc(sizeof(word2));

	return 0;
}
