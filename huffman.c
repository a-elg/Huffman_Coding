#include "huffman.h"
#include <stdio.h>
struct nodoHeap *construirArbolHuffman(char dato[], int frecuencia[], int tam)
{
  struct nodoHeap *izq, *der, *arbolito;
  //genera un arbol con los caracteres del archivo a leer y su frecuencia
  struct Heap *Heap = generarArbol(dato, frecuencia, tam);
  //hasta que el arbol cuente con solo una raiz se extraeran los nodos en pares, tomando los dos de menor frecuencia en cada ocasion
  while (!EsUnitario(Heap))
  {
    izq = extraerNodo(Heap);
    der = extraerNodo(Heap);
    //se crean los arboles temporales
    arbolito = crearNodo('#', izq->frecuencia + der->frecuencia);
    //se asignan los nodos con caracteres a los arboles temporales
    arbolito->izq = izq;
    arbolito->der = der;
    //se inserta el nodo al arbol para ordenarlo nuevamente
    insertarNodo(Heap, arbolito);
  }
  //retorna la raiz del arbol de Huffman
  return extraerNodo(Heap);
}

void imprimirHuffcodigo(struct nodoHeap *raiz, int arr[], int pos)
{
  ///0 0 1 0 0 0 1 1
  int i;
  //Si se trata de un hijo izquierdo, guarda un 0 en el arreglo
  if (raiz->izq)
  {
    arr[pos] = 0;
    imprimirHuffcodigo(raiz->izq, arr, pos + 1);
  }
  //Si se trata de un hijo derecho, guarda un 1 en el arreglo
  if (raiz->der)
  {
    arr[pos] = 1;
    imprimirHuffcodigo(raiz->der, arr, pos + 1);
  }
  //Si se trata de una hoja, imprime el caracter en el nodo
  if (EsHoja(raiz))
  {
    printf("  %c   | ", raiz->dato);
    //Impresion de tabla
    for (i = 0; i < pos; ++i)
      printf("%d", arr[i]);

    printf("\n");
    // imprimirTabla(arr, arbol);
  }
}

void codigoHuffman(char dato[], int frecuencia[], int tam)
{
  struct nodoHeap *raiz = construirArbolHuffman(dato, frecuencia, tam);

  int arr[TAMMAX], top = 0;

  imprimirHuffcodigo(raiz, arr, top);
}

