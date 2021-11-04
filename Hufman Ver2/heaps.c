/*****************************************************************
(C)Noviembre 2021
 
EQUIPO: Ponys Salvajes
INTEGRANTES DEL EQUIPO: 
    López Gracia Angel Emmanuel 
    López Hernández Lissete 
    Martínez Martínez Fernando 
    Martínez Ortiz Fabiola Yahel	
  VERSIÓN: 5.0
DESCRIPCIÓN: Implementación de las funciones necesarias para crear la estructura de datos minHeap, con algunas operaciones basicas.

CURSO: Análisis de algoritmos
    COMPILACIÓN: "gcc [nombre_del_programa].c -o main” 
    EJECUCIÓN: "./main n" (Linux y MAC OS)
*****************************************************************/
#include "heaps.h"
#include <stdlib.h>
#include <stdio.h>

/*Función que implementa la creacion de nodos para el arbol minHeap, recibe el caracter a almacenar y las veces que se repite en el archivo a codificar.*/
struct nodoHeap *crearNodo(unsigned char dato, unsigned int frecuencia)
{
  struct nodoHeap *nodo = (struct nodoHeap *)malloc(sizeof(struct nodoHeap));
  //asignacion e inicializacion de valores del nodo
  nodo->dato = dato;
  nodo->frecuencia = frecuencia;
  nodo->izq = NULL;
  nodo->der = NULL;

  return nodo;
}
/*Funcion EsHoja, se encarga de determinar si un nodo es hoja, para ello recibe el nodo a valorar.
Retor*/
int EsHoja(struct nodoHeap *raiz)
{
  //si el nodo no posee hijos, entonces es hoja
  if(!(raiz->izq) && !(raiz->der) != 0)
  return 1; 
  else
  return 0;
}


// Verifica si el arbol es unitario
int EsUnitario(struct Heap *Heap)
{
  if(Heap->tam==1)
  return 1;
  else
  return 0;
}

// Function to swap
void swapNodo(struct nodoHeap **nodo1, struct nodoHeap **nodo2)
{
  struct nodoHeap *temp = *nodo1;
  *nodo1 = *nodo2;
  *nodo2 = temp;
}

//Ordena nodos descendentemente, en el arbol se visualiza como un ordenamiento desde arriba hacia abajo
void ordenaDesc(struct Heap *Heap, int posNodo)
{
  int minimo = posNodo;
  //Posiciones de los nodos hijos en el arreglo
  int hijo_izq = 2 * posNodo + 1;
  int hijo_der = 2 * posNodo + 2;
//Si el hijo izquierdo existe en el arbol y la frecuencia del hijo izquierdo es menor a la del nodo recibido
  if (hijo_izq < Heap->tam && Heap->nodo[hijo_izq]->frecuencia < Heap->nodo[minimo]->frecuencia){
    //el hijo izquierdo es el menor
    minimo = hijo_izq;}
//Si el hijo derecho existe en el arbol y la frecuencia del hijo derecho es menor a la del nodo  de la pos "minimo"
  if (hijo_der < Heap->tam && Heap->nodo[hijo_der]->frecuencia < Heap->nodo[minimo]->frecuencia){
    //el hijo derecho es menor
    minimo = hijo_der;}
//si el nodo indicado por la posicion posNodo no es el minimo
  if (minimo != posNodo)
  {
    //se intercambian el nodo en la posicion minimo, con el nodo en la posicion posNodo
    swapNodo(&Heap->nodo[minimo], &Heap->nodo[posNodo]);
    // se ejecuta esta funcion hasta que el arbol esté ordenado
    ordenaDesc(Heap, minimo);
  }
  }


// Extract min
struct nodoHeap *extraerNodo(struct Heap *Heap)
{
  struct nodoHeap *temp = Heap->nodo[0];
  Heap->nodo[0] = Heap->nodo[Heap->tam - 1];

  --Heap->tam;
  ordenaDesc(Heap, 0);

  return temp;
}

/*Funcion insertar nodo*/
void insertarNodo(struct Heap *arbol, struct nodoHeap *nodo)
{
  int i = arbol->tam;
//ORDENAMIENTO DEL NODO
  /*Mientras la frecuencia del nodo que se recibe sea menor a la frecuencia de su nodo padre*/
  while (nodo->frecuencia < arbol->nodo[(i - 1) / 2]->frecuencia)
  {
    //El nodo padre toma la posicion del nodo que se recibe
    arbol->nodo[i] = arbol->nodo[(i - 1) / 2];
    //Ahora se considerara el siguiente nodo padre
    i = (i - 1) / 2;
  }
  //INSERCION DEL NODO
  //Cuando el nodo que se desea insertar es mayor al siguiente nodo padre, se encontro su ubicacion, entonces se inserta
  arbol->nodo[i] = nodo;
  //ya que se inserto el nodo en el arbol, este crece de tamaño
  ++arbol->tam;
}

void ordenarArbol(struct Heap *Heap)
{
  int n = Heap->tam - 1;
  int i;

  for (i = (n - 1) / 2; i >= 0; --i)
    ordenaDesc(Heap, i);
}

struct Heap *generarArbol(unsigned char dato[], int frecuencia[], long long int tam)
{
  struct Heap *arbol = (struct Heap *)malloc(sizeof(struct Heap));

  arbol->tam = 0;

  arbol->tamMax = tam;

  arbol->nodo = (struct nodoHeap **)malloc(arbol->tamMax * sizeof(struct nodoHeap *));

  for (int i = 0; i < tam; ++i)
    arbol->nodo[i] = crearNodo(dato[i], frecuencia[i]);

  arbol->tam = tam;
  ordenarArbol(arbol);

  return arbol;
}
