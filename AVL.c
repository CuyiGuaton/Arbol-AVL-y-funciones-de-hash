#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h> //To use the string functions like strcmp and strcpy
#include <time.h>
#define HEIGHT 1
#define MAXchar 30

struct node
{
  char data[MAXchar];
  struct node* left;
  struct node* right;
  int height;
  int freq;
};


int get_height(struct node* root){
  if(!root)
    return 0;
  else
    return root->height;
}

int max(int a, int b){
  return (a > b) ? a : b;
}


int get_balance(struct node* root){
  if(!root)
    return 0;
  return (get_height(root->left) - get_height(root->right));
}

struct node* left_rotate(struct node* root){
  struct node* right = root->right;
  struct node* left = right->left;
  //perform rotation
  right->left = root;
  root->right = left;
  //update heights of the rotated nodes
  root->height = max(get_height(root->left), get_height(root->right)) + 1;
  right->height = max(get_height(right->left), get_height(right->right)) + 1;
  //return new root
  return right;
}

struct node* right_rotate(struct node* root){
  struct node* left = root->left;
  struct node* right = left->right;
  //perform rotation
  left->right = root;
  root->left = right;
  //update heights of the rotated nodes
  root->height = max(get_height(root->left), get_height(root->right)) + 1;
  left->height = max(get_height(left->left), get_height(left->right)) + 1;
  //return new root
  return left;
}

struct node* get_node(char word[MAXchar]){
  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  new_node->left = NULL;
  new_node->right = NULL;
  strcpy(new_node->data, word);
  new_node->height = HEIGHT;
  new_node->freq=1;
  return new_node;
}

struct node* insert(struct node* root, char word[MAXchar]){
  //normal insertion
  if(!root){
    struct node* new_node = get_node(word);
    return new_node;
  }
  if(strcmp(root->data, word) == 0){ //root->data > word
    root->freq++;
    return root;
  }
  if(strcmp(root->data, word) > 0) //root->data > word
    root->left = insert(root->left, word);
  else
    root->right = insert(root->right, word);
  //update height of root
  root->height = max(get_height(root->left), get_height(root->right)) + 1;
  //check for balancing
  int balance = get_balance(root);
  //left-left case
  if(balance > 1 && strcmp(root->left->data , word) > 0){
    root = right_rotate(root);
  }
  //right-right case
  else if(balance < -1 && strcmp(root->right->data, word) < 0 ){
    root = left_rotate(root);
  }
  //left-right case
  else if(balance > 1 && strcmp(root->left->data, word) < 0){ //root->left->data < word
    root->left = left_rotate(root->left);
    root = right_rotate(root);
  }
  //right-left case
  else if(balance < -1 && strcmp(root->right->data, word)>0){ //root->right->data > word
    root->right = right_rotate(root->right);
    root = left_rotate(root);
  }
  return root;
}



//utility function used in balancing of node
//in deletion operation
struct node* balance_tree(struct node* root){
  struct node* x, *y;
  int lheight,rheight;
  lheight = get_height(root->left);
  rheight = get_height(root->right);
  if(lheight >= rheight)
    x = root->left;
  else
    x = root->right;
  lheight = get_height(x->left);
  rheight = get_height(x->right);
  if(x == root->left){
    if(lheight >= rheight){
      y = x->left;
    }
    else
      y = x->right;
  }
  if(x == root->right){
    if(lheight > rheight){
      y = x->left;
    }
    else
      y = x->right;
  }
  //left-left case
  if(root->left == x && x->left == y){
    root = right_rotate(root);
  }
  //right-right case
  else if(x == root->right && x->right == y){
    root = left_rotate(root);
  }
  //left-right case
  else if(x == root->left && y == x->right){
    root->left = left_rotate(root->left);
    root = right_rotate(root);
  }
  //right-left case
  else if(x == root->right && y == x->left){
    root->right = right_rotate(root->right);
    root = left_rotate(root);
  }
  return root;
}


//function for printing the pre-order of tree
void preorder(struct node* root){
  if(!root)
    return;
  printf("%s - %i\n",root->data, root->freq);
  preorder(root->left);
  preorder(root->right);
}

//function for printing the pre-order of tree
void searchByFreq(struct node* root,int freq){
  if(!root)
    return;
  if(root->freq == freq)
    printf("\"%s\"",root->data);
  searchByFreq(root->left, freq);
  searchByFreq(root->right, freq);
}

//function for search a word in the tree
int searchWord(struct node* root, char word[MAXchar]){
  if(root == NULL)
    return;
  if (strcmp(root->data, word) == 0)
    return 1;
  if(strcmp(root->data, word) > 0)
    return searchWord(root->left, word);
  if(strcmp(root->data, word) < 0)
    return searchWord(root->right, word);
}

//function for count elements i the tree
int countElements(struct node* root){
      int count = 1;             //Node itself should be counted
      if (root ==NULL)
          return 0;
      else{
          count += countElements(root->left);
          count += countElements(root->right);
          return count;
      }
  }


// Returns maximum value in a given Binary Tree
int findMaxFreq(struct node* root)
  {
      // Base case
      if (root == NULL)
        return;
      int res = root->freq;
      int lres = findMaxFreq(root->left);
      int rres = findMaxFreq(root->right);
      if (lres > res)
        res = lres;
      if (rres > res)
        res = rres;
      return res;
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


//function to test the functionality of code
main(){
  clock_t start_t, end_t, total_t;
  struct node* root = NULL;
  /* Open Folder */
  FILE *fp;
  fp = fopen("archivo_4.tex", "r");
  /*Save words in the array words */
  start_t = clock();
  char *word;
  while(word=getWord(fp)){ //it get each word of in the file
    root = insert(root, word);
  }
  fclose(fp);
  printf("pic\n" );
  //balance_tree(root);
  printf("Preorder\n");
  preorder(root);
  end_t = clock();
  printf("\n Tiempo en general el árbol: %f segundos\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);

  start_t = clock();
	/* Pregunta 1*/
  printf("\n1.- ¿Se encuentra la palabra readiness? \n" );
  if(searchWord(root, "readiness") == 1)
    printf("Resp: Sí\n");
  else
    printf("Resp: No\n");
  end_t = clock();
  printf("\n Tiempo en responder: %f segundos\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);

  start_t = clock();
	/* Pregunta 2*/
  printf("\n2.- ¿Se encuentra la palabra fearless? \n" );
  if(searchWord(root, "fearless") == 1)
    printf("Resp: Sí\n");
  else
    printf("Resp: No\n");
  end_t = clock();
  printf("\n Tiempo en responder: %f segundos\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);


	/* Pregunta 3*/
  start_t = clock();
	printf("\n3.- ¿Cuantas palabras distintas hay en el archivo?" );
  int count = 0;
  count = countElements(root);
	printf("\nResp: Hay %i palabras distintas en el archivo\n", count);
  end_t = clock();
  printf("\nTiempo en responder: %f segundos\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);


  /* Pregunta 4*/
  start_t = clock();
	printf("\n4.- ¿Cual es la palabra más utilizada?\n");
  char maxFreqWord[MAXchar];
  int maxFreq = 0;
  maxFreq = findMaxFreq(root);
  printf("Resp: Es la palabra ");
  searchByFreq(root,maxFreq);
  printf(" que se repite %i veces\n", maxFreq);
  end_t = clock();
  printf("\n Tiempo en responder: %f segundos\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);


}
