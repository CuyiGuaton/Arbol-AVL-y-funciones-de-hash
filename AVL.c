#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DERECHA 1
#define IZQUIERDA 0
#define TRUE 1
#define FALSE 0

typedef struct nodo
 {
   char numero[20];
   int FE;
   struct nodo *derecho;
   struct nodo *izquierdo;
   struct nodo *padre;
 }*ptr;

void Insertar(ptr *nodo, char dato[20]);
void Eliminar_nodo(ptr *n, char dato[20]);
int Buscar(ptr n, char dato[20]);
int EsHoja(ptr n);
int Num_Nodos(ptr n, int* c);
int Altura_Arbol(ptr n, int* altura);
int Nivel_Nodo(ptr n, char dato[20]);
void InOrden(ptr, void (*func)(char*));
void PreOrden(ptr, void (*func)(char*));
void PostOrden(ptr, void (*func)(char*));
void Equilibrar(ptr *raiz, ptr nodo, int, int);
void RSI(ptr *r, ptr nodo);
void RSD(ptr *r, ptr nodo);
void RDI(ptr *r, ptr nodo);
void RDD(ptr *r, ptr nodo);
void Eliminar_Arbol(ptr *nodo);
void auxContador(ptr n, int*);
void auxAltura(ptr a, int, int*);
void Mostrar(int *n);

//--- / Menu /--------------------------------------------//
int main()
{
   ptr Arbol = NULL;
   int i, ndatos, opcion;
   char pal;

   do
    {
     printf("\n\n");
     printf("\n*********************");
     printf("\n1. Insertar nodo    *");
     printf("\n2. Nivel nodo       *");
     printf("\n3. Buscar nodo      *");
     printf("\n4. Eliminar nodo    *");
     printf("\n5. Eliminar árbol   *");
     printf("\n6. Salir            *");
     printf("\n*********************");

     printf("\n\n");
     printf(" Elija opción    ");
     scanf("%d",&opcion);

     switch (opcion)
        {
            case 1:   system("cls");

                      printf("\n Indique cuántos datos desea insertar      ");
                      scanf("%d",&ndatos);
                      system("cls");
                      printf("\n Introduzca %d datos\n\n", ndatos);

                      for(i=1; i<=ndatos; i++)
                      {
                          scanf("%s",&pal);
                          Insertar(&Arbol, pal);
                      }
                      system("cls");
                      printf("\n Número nodos ----> %d ", Num_Nodos(Arbol, &ndatos));

                      printf("\n\n Altura `árbol ----> %d ", Altura_Arbol(Arbol, &ndatos));

                      printf("\n\n InOrden      ----> ");
                      InOrden(Arbol, Mostrar);
                      printf("\n\n PreOrden     ----> ");
                      PreOrden(Arbol, Mostrar);
                      printf("\n\n PostOrden    ----> ");
                      PostOrden(Arbol, Mostrar);
                      printf("\n\n\n");

                      system("pause");
                      system("cls");
                      break;

            case 2:   system("cls");
                      printf("\n\n Introduzca nodo      ");
                      scanf("%s", &pal);
                      system("cls");
                      printf("\n\n Nivel de %s  ---->  %d\n",pal, Nivel_Nodo(Arbol, pal));
                      printf("\n\n\n");
                      system("PAUSE");
                      system("cls");
                      break;

           case 3:   system("cls");

                    printf("\n Introduzca dato a buscar      ");
                    scanf("%s", &pal);
                    system("cls");
                    Buscar(Arbol, pal);
                    printf("\n\n\n");
                    system("PAUSE");
                    system("cls");
                    break;

           case 4:  system("cls");
                    printf("\n Introduzca dato a eliminar      ");
                    scanf("%s", &pal);

                    system("cls");

                    Eliminar_nodo(&Arbol, pal);

                    printf("\n\n Eliminado    ----> %s  ",pal);

                    printf("\n\n InOrden      ----> ");

                    InOrden(Arbol, Mostrar);

                    printf("\n\n Número nodos ----> %d", Num_Nodos(Arbol, &pal));

                    printf("\n\n Altura árbol ----> %d", Altura_Arbol(Arbol, &pal));

                    printf("\n\n\n");

                    system("PAUSE");

                    system("cls");

                    break;


           case 5:  system("cls");

                    Eliminar_Arbol(&Arbol);

                    printf("\n ARBOL ELIMINADO");

                    printf("\n\n\n");

                    system("PAUSE");

                    system("cls");

                    break;

          case 6:   break;

          default:  system("cls");

                    break;
           }
     } while (opcion < 6);

    return 0;
  }


void Insertar(ptr *nodo, char dato[20])
{
   ptr padre = NULL;

   ptr actual = *nodo;


  while(actual!=NULL && strcoll(dato,actual->numero)!=0)
  {
      padre = actual;

      if(strcoll(dato,actual->numero) < 0)

       actual = actual->izquierdo;

      else if(strcoll(dato,actual->numero) > 0)

      actual = actual->derecho;
  }
  if(actual!=NULL)

   return;

  if(padre==NULL)
  {
      *nodo = (ptr)malloc(sizeof(struct nodo));

      strcpy((*nodo)->numero,dato);
      //(*nodo)->numero = dato;

      (*nodo)->izquierdo = (*nodo)->derecho = NULL;

      (*nodo)->padre = NULL;

      (*nodo)->FE = 0;
  }

  else if(strcoll(dato,padre->numero) < 0)
  {
      actual = (ptr)malloc(sizeof(struct nodo));

      padre->izquierdo = actual;

      strcpy(actual->numero,dato);

      actual->izquierdo = actual->derecho = NULL;

      actual->padre = padre;

      actual->FE = 0;

      Equilibrar(nodo, padre, IZQUIERDA, TRUE);
  }
  else if(strcoll(dato,padre->numero) > 0)
  {
      actual = (ptr)malloc(sizeof(struct nodo));

      padre->derecho = actual;

      strcpy(actual->numero,dato);

      actual->izquierdo = actual->derecho = NULL;

      actual->padre = padre;

      actual->FE = 0;

      Equilibrar(nodo, padre, DERECHA, TRUE);
  }
}



void Equilibrar(ptr *r, ptr nodo, int rama, char dato[20])
{
   int salir = FALSE;

   while(nodo && !salir)
   {
      if(dato)

        if(rama == IZQUIERDA)

          nodo->FE--;

        else

          nodo->FE++;

      else

        if(rama == IZQUIERDA)

          nodo->FE++;

        else

          nodo->FE--;

      if(nodo->FE == 0)

        salir = TRUE;

      else if(nodo->FE == -2)
        {
        if(nodo->izquierdo->FE == 1)

          RDD(r, nodo);

        else

          RSD(r, nodo);

      salir = TRUE;

     }else if(nodo->FE == 2){

        if(nodo->derecho->FE == -1)

          RDI(r, nodo);

        else

          RSI(r, nodo);

      salir = TRUE;
      }
      if(nodo->padre)

        if(nodo->padre->derecho == nodo)

          rama = DERECHA;

        else

          rama = IZQUIERDA;

     nodo = nodo->padre;
   }
}


int EsHoja(ptr nodo)
{
   return !nodo->derecho && !nodo->izquierdo;
}




void RDD(ptr *r, ptr nodo)
{
   ptr Padre = nodo->padre;
   ptr A = nodo;
   ptr B = A->izquierdo;
   ptr C = B->derecho;
   ptr CI = C->izquierdo;
   ptr CD = C->derecho;
   if(Padre)
     if(Padre->derecho == A)
       Padre->derecho = C;
     else
       Padre->izquierdo = C;
   else
       *r = C;
   B->derecho = CI;
   A->izquierdo = CD;
   C->izquierdo = B;
   C->derecho = A;
   C->padre = Padre;
   A->padre = B->padre = C;
   if(CI)
     CI->padre = B;
   if(CD)
     CD->padre = A;

  switch(C->FE)
  {
      case -1: B->FE = 0;

               A->FE = 1;

               break;

      case 0:  B->FE = 0;

               A->FE = 0;

               break;

      case 1:  B->FE = -1;

               A->FE = 0;

               break;
  }
   C->FE = 0;
}



void RDI(ptr *r, ptr nodo)
{
   ptr Padre = nodo->padre;
   ptr A = nodo;
   ptr B = A->derecho;
   ptr C = B->izquierdo;
   ptr CI = C->izquierdo;
   ptr CD = C->derecho;
   if(Padre)
     if(Padre->derecho == A)
       Padre->derecho = C;
     else
       Padre->izquierdo = C;
   else
     *r = C;

   A->derecho = CI;
   B->izquierdo = CD;
   C->izquierdo = A;
   C->derecho = B;
   C->padre = Padre;
   A->padre = B->padre = C;
   if(CI)
     CI->padre = A;
   if(CD)
     CD->padre = B;

   switch(C->FE)
    {
      case -1: A->FE = 0;

               B->FE = 1;

               break;

      case 0:  A->FE = 0;

               B->FE = 0;

               break;

      case 1:  A->FE = -1;

               B->FE = 0;

               break;
   }
   C->FE = 0;
}




void RSD(ptr *r, ptr nodo)
{
   ptr Padre = nodo->padre;
   ptr A = nodo;
   ptr B = A->izquierdo;
   ptr C = B->derecho;
   if(Padre)
     if(Padre->derecho == A)
       Padre->derecho = B;
     else
       Padre->izquierdo = B;
   else
    *r = B;

   A->izquierdo = C;

   B->derecho = A;

   A->padre = B;

   if(C)

     C->padre = A;

   B->padre = Padre;

   A->FE = 0;

   B->FE = 0;
}



void RSI(ptr *r, ptr nodo)
{
   ptr Padre = nodo->padre;
   ptr A = nodo;
   ptr B = A->derecho;
   ptr C = B->izquierdo;
   if(Padre)
     if(Padre->derecho == A)
       Padre->derecho = B;
     else
       Padre->izquierdo = B;
   else
     *r = B;

   A->derecho = C;

   B->izquierdo = A;

   A->padre = B;

   if(C)

    C->padre = A;

   B->padre = Padre;

   A->FE = 0;

   B->FE = 0;
}




void Eliminar_nodo(ptr *n, char dato[20])
{
   ptr padre = NULL;

   ptr actual;

   ptr nodo;

   char aux[20];

   actual = *n;

   while(actual!=NULL)
   {
      if(strcoll(dato, actual->numero) == 0)
      {
         if(EsHoja(actual))
         {
            if(padre)

               if(padre->derecho == actual)

                  padre->derecho = NULL;

               else if(padre->izquierdo == actual)

                  padre->izquierdo = NULL;

            free(actual);

            actual = NULL;

            if((padre->derecho == actual && padre->FE == 1) || (padre->izquierdo == actual && padre->FE == -1))
               {
               padre->FE = 0;

               actual = padre;

               padre = actual->padre;
               }
            if(padre)

               if(padre->derecho == actual)

                  Equilibrar(n, padre, DERECHA, FALSE);

               else

                  Equilibrar(n, padre, IZQUIERDA, FALSE);

            return;

          }else {

            padre = actual;

            if(actual->derecho)
            {
               nodo = actual->derecho;

               while(nodo->izquierdo)
               {
                  padre = nodo;

                  nodo = nodo->izquierdo;
               }
            }

           else{

               nodo = actual->izquierdo;

               while(nodo->derecho)
                {
                  padre = nodo;

                  nodo = nodo->derecho;
                 }
              }

            strcpy(aux,actual->numero);

            strcpy(actual->numero , nodo->numero);

            strcpy(nodo->numero , aux);

            actual = nodo;
           }

         }else {

           padre = actual;

           if(strcoll((dato, actual->numero) > 0))

             actual = actual->derecho;

           else if(strcoll(dato, actual->numero) < 0)

             actual = actual->izquierdo;
      }
   }
}

// Ordenamientos /-----------------------------------------------------/

void InOrden(ptr nodo, void (*func)(char*))
{
   if(nodo->izquierdo)

      InOrden(nodo->izquierdo, func);

   func(&(nodo->numero));

   if(nodo->derecho)

      InOrden(nodo->derecho, func);
}


void PreOrden(ptr nodo, void (*func)(char*))
{
   func(&nodo->numero);

   if(nodo->izquierdo)

      PreOrden(nodo->izquierdo, func);

   if(nodo->derecho)

      PreOrden(nodo->derecho, func);
}
void PostOrden(ptr nodo, void (*func)(char*))
{
   if(nodo->izquierdo)

     PostOrden(nodo->izquierdo, func);

   if(nodo->derecho)

     PostOrden(nodo->derecho, func);

   func(&nodo->numero);
}
// Busqueda /--------------------------------------------------//

int Buscar(ptr nodo, char dato[20])
{
   ptr actual = nodo;
   while(actual!= NULL)
   {
      if(strcoll(dato, actual->numero) == 0)
      {
        printf("\n %s  EXISTE", dato);
        return TRUE;
      }
      else if((dato, actual->numero) < 0)
         strcpy(actual , actual->izquierdo);
      else if((dato, actual->numero) > 0)
         strcpy(actual , actual->derecho);
   }
    printf("\n %s  NO EXISTE", dato);
    return FALSE;
}

// Niveles /---------------------------------------------//


int Nivel_Nodo(ptr nodo, char dato[20])
{
   int altura = 0;
   ptr actual = nodo;
   while(actual != NULL)
     {
      if(strcoll(dato, actual->numero) == 0)
        return altura;
      else {
         altura++;
      if(strcoll(dato, actual->numero) < 0)
         actual = actual->izquierdo;
      else if(strcoll(dato, actual->numero) > 0)
         actual = actual->derecho;
      }
   }
   return -1;
}




void auxContador(ptr nodo, int *c)
{
   (*c)++;
   if(nodo->izquierdo)
   auxContador(nodo->izquierdo, c);
   if(nodo->derecho)
    auxContador(nodo->derecho, c);
}

int Num_Nodos(ptr nodo, int *cont)
{
   *cont = 0;
   auxContador(nodo, cont);
   return *cont;
}

void auxAltura(ptr nodo, int a, int *altura)
{
   if(nodo->izquierdo)
   auxAltura(nodo->izquierdo, a+1, altura);
   if(nodo->derecho)
   auxAltura(nodo->derecho, a+1, altura);
   if(EsHoja(nodo) && a > *altura)
   *altura = a;
}

int Altura_Arbol(ptr nodo, int *altura)
{
   *altura = 0;
   auxAltura(nodo, 0, altura);
    return *altura;
}




void Mostrar(int *n)
{
   printf("%d, ", *n);
}




void Eliminar_Arbol(ptr *nodo)
{
   if(*nodo)
   {
      Eliminar_Arbol(&(*nodo)->izquierdo);
      Eliminar_Arbol(&(*nodo)->derecho);
      free(*nodo);
      *nodo = NULL;
   }
}
