void buscarMayorFreq(node* head, int *mayorFreq, char mayor[MAXchar] ); //busca la palabra que más se repite en la lista
node* create(char data[MAXchar], node* next); //crea un nodo nuevo
node* prepend(node* head,char data[MAXchar]); // insterta un elemento al inicio de la lista
void mostrarfreq(node* head); // muestra las palabras y sus frecuencias en la lista
void mostrar(node* head); // muestra todos los elementos de la lista
node* search(node* head,char data[MAXchar]); // busca un elemento en la lista
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

//busca un elemento en el nodo
node* search(node* head,char data[MAXchar]){
    node *cursor = head;
    while(cursor!=NULL){
        if(strcmp(  cursor->data, data) ==0)
            return cursor;
        cursor = cursor->next;
    }
    return NULL;
}

// cuenta los elementos de la lista
int contar(node *head){
    node *cursor = head;
    int c = 0;
    while(cursor != NULL){
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
