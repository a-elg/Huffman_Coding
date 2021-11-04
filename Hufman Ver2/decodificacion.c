#include "huffman.h"
#include "heaps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
#define BYTE 7
int main()
{

    //Variables para medición de tiempos
	double utime0, stime0, wtime0,utime1, stime1, wtime1; 

    char nombreArchivo[100];
    printf("Ingrese el nombre del archivo de salida:\n");
    scanf("%s", nombreArchivo);

    //**********************************************************************************
  //INICIAR EL CONTEO DEL TIEMPO PARA LAS EVALUACIONES DE RENDIMIENTO	
	uswtime(&utime0, &stime0, &wtime0);

    //No. nodos en el arbol, tamaño del archivo codificado
   int elementos;
    long long int tamArchivo;
    int *byte;
    FILE *frecuencias = fopen("frecuencias.txt", "rb");
    fscanf(frecuencias, "%d", &elementos);
    fscanf(frecuencias, "%lld", &tamArchivo);

    unsigned char *caracteres = (unsigned char *)malloc(sizeof(unsigned char) * elementos); //Arreglo de caracteres repetidos
    int *recurrencias = (int *)malloc(sizeof(int) * elementos);                             //Arreglo con la cantidad de repeticiones

    for (int i = 0; i < elementos; i++)
    {
        fscanf(frecuencias, "%d", &caracteres[i]);
        fscanf(frecuencias, "%d", &recurrencias[i]);
    }

    fclose(frecuencias);
    //1110111101010000          a=111   b=011  c=110
    //abc
    //
    // 1. Lee archivo de codificación fgetc||fread //11110000
    // 2. funcion(arreglo archivo, posbyte, posbit, arbol, tamArchivo, tamActual)
    //  2.1 if( caracter leido==1)
    //    raiz->izq
    //
    struct nodoHeap *raiz = construirArbolHuffman(caracteres, recurrencias, elementos);

    int arr[TAMMAX], top = 0;

    Bits_Huffman bits[256];
    for (int i = 0; i < 256; i++)
        bits[i].tam = 0;
     long long int tam_archivo = 0;

    imprimirHuffcodigo(raiz, arr, top, bits, &tam_archivo);
    for (int i = 0; i < 256; i++)
    {
        if (bits[i].tam != 0)
        {
            printf("%c - ", i);
            for (int j = 0; j < bits[i].tam; j++)
                printf("%d", bits[i].bits[j]);
            printf(" - %d\n", bits[i].tam);
        }
    }

    FILE *archivo = fopen("binario.dat", "rb");
    fseek(archivo, 0, SEEK_END);
    //obtiene el tamanio del archivo
    long long int tamano = ftell(archivo);
    //Se posiciona nuevamente en la primer posicion del archivo
    fseek(archivo, 0, SEEK_SET);

    unsigned char *bytes = (unsigned char *)malloc(tamano * sizeof(unsigned char));

    for (long long int i = 0; i < tamano; i++)
        bytes[i] = 0;

    //fread(bytes, 1, tamano, archivo);

   
    FILE *original = fopen(nombreArchivo, "wb");
    struct nodoHeap *aux = raiz;
    fseek(archivo, 0, SEEK_SET);

    long long int tamActual = 0;

    while (tamArchivo != tamActual)
    {
        unsigned char byte = fgetc(archivo);
        int i = BYTE;
        while (i>=0)
        {
            if (!CONSULTARBIT(byte, i)) aux = aux->izq;
            else if (CONSULTARBIT(byte, i)) aux = aux->der;
            if (EsHoja(aux))
            {
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

    return 0;
}