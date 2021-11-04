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
#ifndef HEAPS_H
#define HEAPS_H

#include <stdlib.h>
#define TAMMAX 256 //tamaño max del arreglo



/*ESTRUCTURAS*/
/*La estructura nodo heap almacena un caracter su frecuencia (numero de veces que se repite en el codigo), así como un apuntador a un nodo izquierdo y derecho*/
struct nodoHeap
{
  unsigned char dato;
  int frecuencia;
  struct nodoHeap *izq, *der;
};
/*
La estructura Heap almacena los nodos que se encuentran en el arbol y el tamaño maximo de nosdos que puede contener, asi como un doble apuntador a la estructura nodo*/
struct Heap
{
  unsigned int tam;    //numero de nodos en el arbol
  unsigned int tamMax; //numero de nodos maximo del arbol (tam del arreglo del arbol)
  struct nodoHeap **nodo;
};

/*La estructura Bits_Huffman almacena los codigos de huffman de cada caracter leido en el archivo a codificar, *bits almacena la cadena binaria correspondiente a cada caracter y tam es la longitud de dicha cadena*/
typedef struct Bits_Huffman
{
  int tam;
  int *bits;

} Bits_Huffman;

/*PROTOTIPOS*/
/*Prototipo para la función que implementa la creacion de nodos para el arbol minHeap, recibe el caracter a almacenar y las veces que se repite en el archivo a codificar*/
struct nodoHeap *crearNodo(unsigned char dato, unsigned int frecuencia);


/*Prototipo para la funcion swapnodo intercambia la posición de los nodos a y b dentro de la estructura del arbol minHeap*/
void swapNodo(struct nodoHeap **a, struct nodoHeap **b);

/*Prototipo para la funcion ordenaDesc, que se encarga de ordenar un nodo en el arbol, en inglés se denomina HeapifyDown, y parte desde una posicion superior, desciende en la estructura hasta encontrar su posicion correcta */
void ordenaDesc(struct Heap *Heap, int posNodo);

/*Prototipo para la función EsUnitario determinar si un arbol contiene un unico nodo, recibe un apuntador a Heap*/
int EsUnitario(struct Heap *Heap);

/*Prototipo para la función extraerNodo, que se encarga de remover un nodo del arbol pasado por referencia*/
struct nodoHeap *extraerNodo(struct Heap *Heap);

/*Prototipo para la función insertar nodo, se encarga de insertar un nodo en el arbol pasado por referencia*/
void insertarNodo(struct Heap *Heap, struct nodoHeap *nodo); 

/*Prototipo para la funcion ordenarArbol, se encarga de ordenar el arbol para que cumpla la condicion de que todos sus padres son menores que sus hijos, recibe el arbol a modificar*/
void ordenarArbol(struct Heap *Heap);

/*Prototipo para la funcion EsHoja, se encarga de determinar si un nodo es hoja, para ello recibe el nodo a valorar*/
int EsHoja(struct nodoHeap *raiz);

/*Prototipo para la funcion generar arbol, se encarga de inicializar la estructura y generar los primeros nodos en el, oara ello recibe el tamaño (numero de nodos) y el caracter que almacenara cada nodo, con su frecuencia */
struct Heap *generarArbol(unsigned char dato[], int frecuencia[], long long int tam);

#endif