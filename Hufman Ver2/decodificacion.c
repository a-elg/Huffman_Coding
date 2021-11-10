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
#include "heaps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
#define BYTE 7


int main(int argc, char **argv){
    //Variables para medición de tiempos
	double utime0, stime0, wtime0,utime1, stime1, wtime1; 

    if(argc < 2){
    printf("Error en los argumentos\n");
    exit(0);
    }

  //INICIAR EL CONTEO DEL TIEMPO PARA LAS EVALUACIONES DE RENDIMIENTO	
	uswtime(&utime0, &stime0, &wtime0);

    //Numero de nodos en el arbol y tamaño del archivo codificado
    int elementos;
    long long int tamArchivo;
    int *byte;

    //Se abre el archivo frecuencias.txt y se obtiene el tamaño del archivo
    FILE *frecuencias = fopen("frecuencias.txt", "rb");
    fscanf(frecuencias, "%d", &elementos);
    fscanf(frecuencias, "%lld", &tamArchivo);

    unsigned char *caracteres = (unsigned char *)malloc(sizeof(unsigned char) * elementos); //Arreglo de caracteres repetidos
    int *recurrencias = (int *)malloc(sizeof(int) * elementos);                             //Arreglo con la cantidad de repeticiones

    //Se leen los caracteres y su frecuencia correspondiente
    for (int i = 0; i < elementos; i++)
    {
        fscanf(frecuencias, "%d", &caracteres[i]);
        fscanf(frecuencias, "%d", &recurrencias[i]);
    }
    fclose(frecuencias);

    /*Se construye el el arbol, recibe como parametros el arreglo de caracteres, sus repeticiones y la cantidad. Devuelve el apuntador al arbol*/
    struct nodoHeap *raiz = construirArbolHuffman(caracteres, recurrencias, elementos);

    int arr[TAMMAX], top = 0;

    Bits_Huffman bits[256];
    for (int i = 0; i < 256; i++)
        bits[i].tam = 0;
     long long int tam_archivo = 0;

    imprimirHuffcodigo(raiz, arr, top, bits, &tam_archivo);

    //Se abre el archivo codificado en modo binario
    FILE *archivo = fopen("binario.dat", "rb");
    fseek(archivo, 0, SEEK_END);
    //Se obtiene el tamanio del archivo
    long long int tamano = ftell(archivo);
    //Se posiciona nuevamente en la primer posicion del archivo
    fseek(archivo, 0, SEEK_SET);

    unsigned char *bytes = (unsigned char *)malloc(tamano * sizeof(unsigned char));

    //Se incializa el arreglo de bytes
    for (long long int i = 0; i < tamano; i++)
        bytes[i] = 0;

   //Se crea el archivo de salida decodificado en modo binario
    FILE *original = fopen(argv[1], "wb");
    struct nodoHeap *aux = raiz;
    fseek(archivo, 0, SEEK_SET);

    long long int tamActual = 0;

    //Se recorre el archivo codificado recorriendo el árbol
    while (tamActual < tamArchivo){

        unsigned char byte = fgetc(archivo);
        int i = BYTE;
        while (i>=0){
            if (!CONSULTARBIT(byte, i)) 
                        aux = aux->izq;
            else if (CONSULTARBIT(byte, i)) 
                        aux = aux->der;
            if (EsHoja(aux)){
                fputc(aux->dato,original);
                aux = raiz;
                tamActual++;
            }
            --i;
        }
    }

    fclose(archivo);


     //EVALUAR LOS TIEMPOS DE EJECUCIÓN 
	uswtime(&utime1, &stime1, &wtime1);

	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");

    printf("Tamño del archivo original: %lld bytes\n", tamArchivo);
    printf("Tamaño del archivo codificado (.dat): %lld bytes\n", tamano);

    return 0;
}
