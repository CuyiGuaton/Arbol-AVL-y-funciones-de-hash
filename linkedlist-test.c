#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char data[30];
    //int freq;
    struct node* next;
} node;

typedef void (*callback)(node* data);

//crea un nodo
node* create(char data[30], node* next){
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
node* prepend(node* head,char data[30]){
    node* new_node = create(data,head);
    head = new_node;
    return head;
}

//muestra los elementos en la lista y su frecuencia en estos
void mostrarfreq(node* head){
    node* cursor = head;
    char aux[30];
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
void mostrar(node* head)
{
    node* cursor = head;
    while(cursor != NULL)
    {
        printf("%s ", cursor->data);
        cursor = cursor->next;
    }
}

//busca un elemento en el nodo
node* search(node* head,char data[30])
{
    node *cursor = head;
    while(cursor!=NULL)
    {
        if(strcmp(  cursor->data, data) ==0)
            return cursor;
        cursor = cursor->next;
    }
    return NULL;
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

int main(){
    node* head = NULL;
    node* tmp = NULL;

    head = prepend(head, "pico");
    head = prepend(head, "pico");
    head = prepend(head, "tula");
    mostrar(head);
    printf("\n" );
    mostrarfreq(head);
    dispose(head);
   return 0;
}
