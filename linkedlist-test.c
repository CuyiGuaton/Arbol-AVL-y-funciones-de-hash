#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXchar 30

typedef struct node{
    char data[MAXchar];
    //int freq;
    struct node* next;
} node;

typedef void (*callback)(node* data);

void buscaMayorElemento(node* head, char candidate[MAXchar]);
int contarElemento(node *head, char data[MAXchar]);
node* create(char data[MAXchar], node* next); //crea un nodo nuevo
node* prepend(node* head,char data[MAXchar]); // insterta un elemento al inicio de la lista
void mostrarfreq(node* head); // muestra las palabras y sus frecuencias en la lista
void mostrar(node* head); // muestra todos los elementos de la lista
int search(node* head,char data[MAXchar]); // busca un elemento en la lista
int contarDistintas(node* head); //cuenta los elementos distintos de la lista
int contar(node *head); //cuenta los elementos de la lista
void dispose(node *head); // borra la lista


//crea un nodo
node* create(char data[MAXchar], node* next){
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL){
        printf("Error creating a new node.\n");
        exit(0);
    }
    strcpy(new_node->data, data);
    //new_node->freq = 1;
    new_node->next = next;
    return new_node;
}

// agrega un nodo al inicio de la lista
node* prepend(node* head,char data[MAXchar]){
    node* new_node = create(data,head);
    head = new_node;
    return head;
}

//muestra los elementos en la lista y su frecuencia en estos
void mostrarfreq(node* head){
    node* cursor = head;
    char aux[MAXchar];
    int freq=1;
    if(cursor != NULL){ // obtiene el primer elemento de la lsita y lo guarda en un auxiliar
      strcpy(aux, cursor->data);
      cursor = cursor->next;
    }
    while(cursor != NULL){ //recorre la lista
        if(strcmp(cursor->data, aux) == 0) //si el elemento siguiente es igual que el anterior aumenta la frecuencia
          freq++;
        else{ //si el elemento siguiente es distinto entonces muestra el elemento y la frecuencia
          printf("%s - %i\n", aux,freq);
          strcpy(aux, cursor->data);
          freq=1;
        }
    cursor = cursor->next;
    }
    printf("%s - %i\n", aux,freq);

}

//muestra los elementos de la lista dinamica
void mostrar(node* head){
    node* cursor = head;
    while(cursor != NULL){
        printf("%s ", cursor->data);
        cursor = cursor->next;
    }
}
/*
//muestra los elementos de la lista dinamica
void buscarMayorFreq(node* head, int *mayorFreq, char mayor[MAXchar]){
  node* cursor = head;
  char aux[MAXchar];
  int freq=1;
  if(cursor != NULL){ // obtiene el primer elemento de la lsita y lo guarda en un auxiliar
    strcpy(aux, cursor->data);
    cursor = cursor->next;
  }
  while(cursor != NULL){ //recorre la lista
      if(strcmp(cursor->data, aux) == 0) //si el elemento siguiente es igual que el anterior aumenta la frecuencia
        freq++;
      else{ //si el elemento siguiente es distinto entonces muestra el elemento y la frecuencia
        if (freq > (*mayorFreq)){
            (*mayorFreq) = freq;
            strcpy(mayor, cursor->data);
        }
        strcpy(aux, cursor->data);
        freq=1;
      }
  cursor = cursor->next;
  }
  if (freq > (*mayorFreq)){
      (*mayorFreq) = freq;
      strcpy(mayor, aux);
  }
}
*/

//Boyer–Moore majority vote algorithm
void buscaMayorElemento(node* head, char candidate[MAXchar]){
  node* cursor = head;
  int count = 0;
  while(cursor != NULL){
    if(count == 0)
      strcpy(candidate, cursor->data);
    if (strcmp(candidate, cursor->data) == 0)
        count++;
    else
        count--;
    cursor = cursor->next;
    }
}

//busca un elemento en el nodo
int search(node* head,char data[MAXchar]){
    node *cursor = head;
    while(cursor!=NULL){
        if(strcmp(  cursor->data, data) ==0)
            return 1;
        cursor = cursor->next;
    }
    return 0;
}

// cuenta la cantidad de veces que se repite un elemento en la lista
int contarElemento(node *head, char data[MAXchar]){
    node *cursor = head;
    int c = 0;
    while(cursor != NULL){
        if( strcmp(  cursor->data, data) ==0 )
          c++;
        cursor = cursor->next;
    }
    return c;
}

//borra la listga
void dispose(node *head){
    node *cursor, *tmp;
    if(head != NULL){
        cursor = head->next;
        head->next = NULL;
        while(cursor != NULL){
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
}

//muestra los elementos de la lista dinamica
int contarDistintas(node* head){
  node* cursor = head;
  char aux[MAXchar];
  int count = 0;
  if(cursor != NULL){ // obtiene el primer elemento de la lsita y lo guarda en un auxiliar
    strcpy(aux, cursor->data);
    cursor = cursor->next;
    count++;
  }
  while(cursor != NULL){ //recorre la lista
      if(strcmp(cursor->data, aux) != 0){ //si el elemento siguiente es igual que el anterior aumenta la frecuencia
        strcpy(aux, cursor->data);
        count++;
      }
  cursor = cursor->next;
  }
  return count;
}

int main(){
    node* head = NULL;
    node* tmp = NULL;
    head = prepend(head, "buenas");
    head = prepend(head, "hola");
    head = prepend(head, "hola");
    head = prepend(head, "chao");
    printf("Mostrando nodos:\n" );
    mostrar(head);
    printf("\nMostrar el nodo que más se repite\n" );
    char mayor[MAXchar];
    int mayorFreq=1;
    buscaMayorElemento(head, mayor);
    printf("%s - %i\n", mayor, contarElemento(head,mayor) );
    printf("\nLa cantidad de elementos distintos de la lista es: %i", contarDistintas(head));
    if( search(head,"hola") == 1)
      printf("\nLa palabra %s se encuentra en la lista\n", "hola");
    dispose(head);
   return 0;
}
