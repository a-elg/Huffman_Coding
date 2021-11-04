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

#ifndef HUFFMAN_H
#define HUFFMAN_H
#define PESOBIT(bpos) (1 << bpos)
#define CONSULTARBIT(var, bpos) ((*(unsigned *)&var & PESOBIT(bpos)) ? 1 : 0)
#define PONE_1(var, bpos) (*(unsigned *)&var |= PESOBIT(bpos))
#define PONE_0(var, bpos) (*(unsigned *)&var &= ~(PESOBIT(bpos)))
#define CAMBIA(var, bpos) (*(unsigned *)&var ^= PESOBIT(bpos))
#include "heaps.h"

/*Prototipos*/
/*Prototipo de la función para crear el arbol, recibe el arreglo de caracteres, sus repeticiones y la cantidad. Devuelve el apuntador al arbol*/
struct nodoHeap *construirArbolHuffman(unsigned char dato[], int frecuencia[], int tam);

/*Prototipo de la función que */
void imprimirHuffcodigo(struct nodoHeap *raiz, int arr[], int pos,Bits_Huffman* bits_huffman,long long int* tam_archivo);

/*Prototipo para la función que codifica y escribir la salida .dat. Recibe el nombre del archivo original, el tamaño y los codigos Huffman*/
void codificador(char nombre[], long long int tamano_archivo, Bits_Huffman* bits);
#endif