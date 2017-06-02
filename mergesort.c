#include<stdio.h>
#include<stdlib.h>
#include<string.h> //To use the string functions like strcmp and strcpy

#define MAXchar 30  // This is the default size of every string
#define MAXWordInFile 22006 //Max of words in the file, archivo_4 has around 21000 according to http://www.contadordepalabras.com/

void merge(char **words, int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    printf("pico\n" );
    /* create temp arrays */
    char **L, **R;
    L = malloc(n1 * sizeof(char*));
    R = malloc(n2 * sizeof(char*));
    /* Copy data to temp arrays L[] and R[] */
    printf("pico\n" );
    for (i = 0; i < n1; i++){
        L[i] = malloc((MAXchar + 1) * sizeof(char));
        strcpy(L[i], words[l + i]);
      }
      printf("pico\n" );

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

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(char **A, int size){
    int i;
    for (i=0; i < size; i++)
        printf("%s ", A[i]);
    printf("\n");
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

/* Driver program to test above functions */
int main(){
  /* abre el archivo */
  FILE *fp;
  fp = fopen("archivo_4.tex", "r");
  char *word;

  /*Guarda las palabras en un array */
  char **words;
  words = malloc(MAXWordInFile * sizeof(char*));
  int LenArray =0;
  while(word=getWord(fp)){ //se obtiene palabra por palabra del archivo
    words[LenArray] = malloc((MAXchar + 1) * sizeof(char));
    strcpy(words[LenArray], word);
    LenArray++;
  }
  fclose(fp);

  //printf("Given array is \n");
  //printArray(words,LenArray);

  mergeSort(words, 0, LenArray - 1);

  printf("\nSorted array is \n");
  printArray(words, LenArray);

  return 0;
}
