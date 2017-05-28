void buscaMayorElemento(node* head, char candidate[MAXchar]);//Boyer–Moore majority vote algorithm
node* create(char data[MAXchar], node* next); //crea un nodo nuevo
node* prepend(node* head,char data[MAXchar]); // insterta un elemento al inicio de la lista
void mostrar(node* head); // muestra todos los elementos de la lista
int search(node* head,char data[MAXchar]); // busca un elemento en la lista
int contarElemento(node *head, char data[MAXchar]); // cuenta la cantidad de veces que un elemento está en la lista
int contarDistintas(node* head); //cuenta los elementos distintos de una lista
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

//muestra los elementos de la lista dinamica
void mostrar(node* head){
    node* cursor = head;
    while(cursor != NULL){
        printf("%s ", cursor->data);
        cursor = cursor->next;
    }
}

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

//cuenta los elementos distintos de una lista
int contarDistintas(node* head){
  node* i = head;
  node* j;
  char aux[MAXchar];
  int count = 0;
  int flag;
  while(i != NULL){ //recorre la lista
      flag = 0;
      j = i->next; // compara un elemento con todos los que le sigue
      while (j != NULL){
        if(strcmp( i->data, j->data ) == 0){ //si son iguales flag es 1 y no lo cuenta porque es repetido
          flag = 1;
          break;
        }
        j = j->next;
      }
      if( flag == 0 ) // si no se repetio nunca entonces se cuenta
        count++;
      i = i->next;
  }
  return count;
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
