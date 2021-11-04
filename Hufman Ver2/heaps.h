#ifndef HEAPS_H
#define HEAPS_H

#include <stdlib.h>
#define TAMMAX 256 //tamaño max del arreglo

/*ESTRUCTURAS*/

struct nodoHeap
{
  unsigned char dato;
  int frecuencia;
  struct nodoHeap *izq, *der;
};

struct Heap
{
  unsigned int tam;    //numero de nodos en el arbol
  unsigned int tamMax; //numero de nodos maximo del arbol (tam del arreglo del arbol)
  struct nodoHeap **nodo;
};

typedef struct Bits_Huffman
{
  int tam;
  int *bits;

} Bits_Huffman;

/*PROTOTIPOS*/

struct nodoHeap *crearNodo(unsigned char dato, unsigned int frecuencia);
struct Heap *crearArbol(unsigned tamMax);
void swapNodo(struct nodoHeap **a, struct nodoHeap **b);
void ordenaDesc(struct Heap *Heap, int posNodo);
int EsUnitario(struct Heap *Heap);
struct nodoHeap *extraerNodo(struct Heap *Heap);
void insertarNodo(struct Heap *Heap, struct nodoHeap *nodo); //creo que es insertarArbol
void ordenarArbol(struct Heap *Heap);
int EsHoja(struct nodoHeap *raiz);
struct Heap *generarArbol(unsigned char dato[], int frecuencia[], int tam);

#endif