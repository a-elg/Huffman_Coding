#ifndef HEAPS_H
#define HEAPS_H

#define TAMMAX 256 //tamaño max del arreglo

/*ESTRUCTURAS*/

struct nodoHeap {
  char dato;
  unsigned int frecuencia;
  struct nodoHeap *izq, *der;
};

struct Heap {
  unsigned int tam; //numero de nodos en el arbol
  unsigned int tamMax;//numero de nodos maximo del arbol (tam del arreglo del arbol)
  struct nodoHeap **nodo;
};

/*PROTOTIPOS*/

struct nodoHeap *crearNodo(char dato, unsigned int frecuencia);
struct Heap *crearArbol(unsigned tamMax);
void swapNodo(struct nodoHeap **a, struct nodoHeap **b);
void ordenaDesc(struct Heap *Heap, int posNodo);
int EsUnitario(struct Heap *Heap);
struct nodoHeap *extraerNodo(struct Heap *Heap);
void insertarNodo(struct Heap *Heap, struct nodoHeap *nodo);//creo que es insertarArbol
void ordenarArbol(struct Heap *Heap);
int EsHoja(struct nodoHeap *raiz);
struct Heap *generarArbol(char dato[], int frecuencia[], int tam) ;




#endif 