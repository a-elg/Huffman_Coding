#ifndef HUFFMAN_H
#define HUFFMAN_H
#define PESOBIT(bpos) (1 << bpos)
#define CONSULTARBIT(var, bpos) ((*(unsigned *)&var & PESOBIT(bpos)) ? 1 : 0)
#define PONE_1(var, bpos) (*(unsigned *)&var |= PESOBIT(bpos))
#define PONE_0(var, bpos) (*(unsigned *)&var &= ~(PESOBIT(bpos)))
#define CAMBIA(var, bpos) (*(unsigned *)&var ^= PESOBIT(bpos))
#include "heaps.h"

struct nodoHeap *construirArbolHuffman(unsigned char dato[], int frecuencia[], int tam);
void imprimirHuffcodigo(struct nodoHeap *raiz, int arr[], int pos,Bits_Huffman* bits_huffman,long long int* tam_archivo);
void codigoHuffman(unsigned char dato[], int frecuencia[], int tam);
void imprimirTabla(int arr[], int n);
void codificador(char nombre[], long long int tamano_archivo, Bits_Huffman* bits);
#endif