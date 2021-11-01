#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heaps.h"

struct nodoHeap *construirArbolHuffman(char dato[], int frecuencia[], int tam);
void imprimirHuffcodigo(struct nodoHeap *raiz, int arr[], int top);
void codigoHuffman(char dato[], int frecuencia[], int tam);
void imprimirTabla(int arr[], int n);

#endif