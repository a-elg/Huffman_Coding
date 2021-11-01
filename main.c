// Huffman Coding in C

#include <stdio.h>
#include <stdlib.h>
#include "heaps.h"
#include "huffman.h"

int main() {
  char arreglo_caracteres[] = {'f', 'e', 'c', 'b','d','a'};
  int frecuencia[] = {5, 9, 12, 13,16,45};
//tamaño en memoria entre tamaño de cada celda para obtener el tamaño del arreglo
  int tam = sizeof(arreglo_caracteres) / sizeof(arreglo_caracteres[0]);

  printf(" Caracter | codigo de Huffman ");
  printf("\n--------------------\n");

  struct nodoHeap *raiz = construirArbolHuffman(arreglo_caracteres, frecuencia, tam);

  int arr[TAMMAX], top = 0;

  imprimirHuffcodigo(raiz, arr, top);

 
}