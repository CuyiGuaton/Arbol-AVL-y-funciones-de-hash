#include<stdio.h>
#include<stdlib.h>
#include<string.h> //To use the string functions like strcmp and strcpy
#include <time.h>
#include <ctype.h>

#define MAXchar 30  // This is the default size of every string
#define MAXWordInFile 22006 //Max of words in the file, archivo_4 has around 21000 according to http://www.contadordepalabras.com/

void merge(char **words, int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    /* create temp arrays */
    char **L, **R;
    L = malloc(n1 * sizeof(char*));
    R = malloc(n2 * sizeof(char*));
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++){
        L[i] = malloc((MAXchar + 1) * sizeof(char));
        strcpy(L[i], words[l + i]);
      }

    for (j = 0; j < n2; j++){
        R[j] = malloc((MAXchar + 1) * sizeof(char));
        strcpy(R[j], words[m +1 + j]);
      }

    /* Merge the temp arrays back into arr[l..r] */
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2){
        if (strcmp(L[i] , R[j]) <=0 ){  // if L[i] <= R[j]
            strcpy(words[k], L[i]);
            i++;
        }
        else{
            strcpy(words[k], R[j]);
            j++;
        }
        k++;
    }

    //  Copy the remaining elements of L[], if there
    //    are any
    while (i < n1){
        strcpy(words[k], L[i]);
        i++;
        k++;
    }

    //  Copy the remaining elements of R[], if there
    //    are any
    while (j < n2){
        strcpy(words[k], R[j]);
        j++;
        k++;
    }

}

//words is the array, l left index and r right index
void mergeSort(char **words, int l, int r){
    if (l < r){
        int m = l+(r-l)/2; // find the middle point in the array
        mergeSort(words, l, m); // sort first halve
        mergeSort(words, m+1, r); // sort second halve
        merge(words, l, m, r); // merga both halves
    }
}

//Print array
void printArray(char **A, int size){
    int i;
    for (i=0; i < size; i++)
        printf("%s ", A[i]);
    printf("\n");
}

//get each word of FILE
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

//Search word in the array
int searchWord(char **words, char string[MAXchar], int size) {
  size_t i;
  for (i = 0; i < size; i++)
    if(strcmp(words[i], string) == 0);
      return 1;
  return 0;
}

//Search word in the array
int countDistinct(char **words, int size) {
  size_t i;
  int freq = 0;
  for (i = 0; i < size-1; i++)
    if(strcmp(words[i],words[i+1]) != 0)
      freq++;
  return freq;
}

/* Driver program to test above functions */
int main(){
  clock_t start_t, end_t, total_t;

  /* Open Folder */
  FILE *fp;
  fp = fopen("archivo_4.tex", "r");
  char *word;

  /*Save words in the array words */
  char **words;
  words = malloc(MAXWordInFile * sizeof(char*));
  int LenArray =0;
  while(word=getWord(fp)){ //it get each word of in the file
    words[LenArray] = malloc((MAXchar + 1) * sizeof(char));
    strcpy(words[LenArray], word);
    LenArray++;
  }
  fclose(fp);
  mergeSort(words, 0, LenArray - 1);

  printf("\nSorted array is \n");
  printArray(words, LenArray);
  start_t = clock();
	/* Pregunta 1*/
  printf("\n1.- ¿Se encuentra la palabra readiness? \n" );
  if(searchWord(words, "readiness", LenArray) == 1)
    printf("Resp: Sí\n");
  else
    printf("Resp: No\n");
  end_t = clock();
  printf("\n Tiempo en responder: %f segundos\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);

  start_t = clock();
	/* Pregunta 2*/
  printf("\n2.- ¿Se encuentra la palabra fearless? \n" );

  if(searchWord(words, "fearless", LenArray) == 1)
    printf("Resp: Sí\n");
  else
    printf("Resp: No\n");
  end_t = clock();
  printf("\n Tiempo en responder: %f segundos\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);

  start_t = clock();
	/* Pregunta 3*/
	printf("\n3.- ¿Cuantas palabras distintas hay en el archivo?" );
	printf("\nResp: Hay %i palabras distintas en el archivo\n", countDistinct(words,LenArray));
  end_t = clock();
  printf("\nTiempo en responder: %f segundos\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);

  start_t = clock();


	/* Pregunta 4*/
	printf("\n4.- ¿Cual es la palabra más utilizada?\n" );

  printf("Resp: Es la palabra  que se repite veces\n");
  end_t = clock();
  printf("\n Tiempo en responder: %f segundos\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);

  return 0;
}
