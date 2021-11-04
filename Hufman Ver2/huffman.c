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

#include "huffman.h"
#include <stdio.h>

/*Funcion para crear el arbol. Recibe como parametros el arreglo de caracteres, sus repeticiones y la cantidad. Devuelve el apuntador al arbol*/
struct nodoHeap *construirArbolHuffman(unsigned char dato[], int frecuencia[], int tam)
{
  //Crear variables para generar nodos a insertar en el arbol
  struct nodoHeap *izq, *der, *arbolito;
  //Genera un arbol con los caracteres del archivo a leer y su frecuencia (definido en heap.c)
  struct Heap *Heap = generarArbol(dato, frecuencia, tam);
  //Hasta que el arbol cuente con solo una raiz se extraeran los nodos en pares, tomando los dos de menor frecuencia en cada ocasion
  while (!EsUnitario(Heap))
  {
    //Se extraen los dos nodos de menor frecuencia
    izq = extraerNodo(Heap);
    der = extraerNodo(Heap);
    //Se crean los arboles temporales
    arbolito = crearNodo('#', izq->frecuencia + der->frecuencia);
    //Se asignan los nodos con caracteres a los arboles temporales
    arbolito->izq = izq;
    arbolito->der = der;
    //se inserta el nodo al arbol para ordenarlo nuevamente
    insertarNodo(Heap, arbolito);
  }
  //retorna la raiz del arbol de Huffman
  return extraerNodo(Heap);
}

/*Funcion para almecenar los codigos Huffman de los nodos, recibe como parámetros los bits del archivo, el arbol y el tamaño del archivo
 */
void imprimirHuffcodigo(struct nodoHeap *raiz, int arr[], int pos,Bits_Huffman* bits_huffman, long long int* tam_archivo)
{ 
  int i;
  //Si se trata de un hijo izquierdo, guarda un 0 en el arreglo
  if (raiz->izq)
  {
    arr[pos] = 0;
    imprimirHuffcodigo(raiz->izq, arr, pos + 1, bits_huffman, tam_archivo);
  }
  //Si se trata de un hijo derecho, guarda un 1 en el arreglo
  if (raiz->der)
  {
    arr[pos] = 1;
    imprimirHuffcodigo(raiz->der, arr, pos + 1, bits_huffman, tam_archivo);
  }
  //Si se trata de una hoja, imprime el caracter en el nodo
  if (EsHoja(raiz))
  {
    bits_huffman[raiz->dato].bits = (int *)malloc(sizeof(int) * pos);
    for(int i = 0; i < pos; i++)
    {
      bits_huffman[raiz->dato].bits[i] = arr[i];//
    }

    bits_huffman[raiz->dato].tam = pos;
    *tam_archivo += raiz->frecuencia * pos;
  }
}

/*
  Funcion para codificar y escribir la salida .dat. Recibe el nombre del archivo original, el tamaño y los codigos Huffman
  La función se encarga de ensambar bit a bit un byte para luego plasmarlo en el archivo .dat
*/
void codificador(char nombre[], long long int tamano_archivo, Bits_Huffman* bits)
{
    FILE *archivo = fopen(nombre, "rb");
    FILE *codi = fopen("binario.dat", "wb");
    unsigned char c;
    int i = 0;
    int k = 0;
    unsigned char cadena_cerosunos = 0; //00000000

    for (int l = 0; l < tamano_archivo; l++)
    {
        c = fgetc(archivo);//Se lee el archivo

        for (i = 0; i < bits[c].tam; i++, k++)
        {

            if (bits[c].bits[i] == 1)
            {
                PONE_1(cadena_cerosunos, 7 - k);//Se pone un 1 en la posicion correspondiente
            }
            if (k == 7)
            {
                k = -1;
                fwrite(&cadena_cerosunos, 1, sizeof(cadena_cerosunos), codi);//Se escribe el byte en el archivo
                //fputc(cadena_cerosunos, codi);
                cadena_cerosunos = 0;
            }
        }
    }

    if (k != 0)
        fwrite(&cadena_cerosunos, 1, sizeof(cadena_cerosunos), codi);//Se escribe el ultimo byte en el archivo
    fclose(codi);//Se cierra el archivo de codificacion
    fclose(archivo);//Se cierra el archivo de salida
}
