// Huffman Coding in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heaps.h"
#include "huffman.h"
#include "tiempo.h"

int main(int argc, char **argv){

//Variables para medición de tiempos
	double utime0, stime0, wtime0,utime1, stime1, wtime1; 

  if(argc < 2){
    printf("Error en los argumentos\n");
    exit(0);
  }

//**********************************************************************************
  //INICIAR EL CONTEO DEL TIEMPO PARA LAS EVALUACIONES DE RENDIMIENTO	
	uswtime(&utime0, &stime0, &wtime0);


  FILE *archivo = fopen(argv[1], "rb");
  //Busca la ultima posicion del archivo partiendo desde el inicio
  fseek(archivo, 0, SEEK_END);
  //obtiene el tamanio del archivo
  long long int tamano = ftell(archivo);
  //Se posiciona nuevamente en la primer posicion del arreglo
  fseek(archivo, 0, SEEK_SET);

  int frecuencia[256];
  //inicializa el array caracteres
  memset(frecuencia, 0, sizeof(int) * 256);
  //obtiene los caracteres del archivo hasta encontrar el final
  for (long long i = 0; i < tamano; i++)
  {
    unsigned char aux = fgetc(archivo);
    frecuencia[aux]++;
  }

  fclose(archivo);

  int elementos = 0; //Numero de elementos repetidos
  for (int i = 0; i < 256; i++)
  {
    if (frecuencia[i] > 0)
      elementos++;
  }
  //creacion de arreglos para ingresar al arbol
  unsigned char *bytes = (unsigned char *)malloc(sizeof(unsigned char) * elementos); //Arreglo de caracteres repetidos
  int *recurrencias = (int *)malloc(sizeof(int) * elementos);                        //Arreglo con la cantidad de repeticiones
  //asignacion de los valores a los arreglos
  int k = 0;
  int tamBytes = 0;
  for (int i = 0; i < 256; i++)
  {
    if (frecuencia[i] > 0)
    {
      tamBytes += frecuencia[i];
      bytes[k] = i;
      recurrencias[k] = frecuencia[i];
      k++;
    }
  }

  // printf("\n\nCaracteres: \n\n");
  // for (int i = 0; i < elementos; i++)
  // {
  //   printf("[%c]", bytes[i]);
  // }

  // printf("\n\nReps: \n\n");
  // for (int i = 0; i < elementos; i++)
  // {
  //   printf("[%d]", recurrencias[i]);
  // }

  // printf("\n\nCaracter | codigo de Huffman ");
  // printf("\n--------------------\n");

  //codigoHuffman(arreglo_caracteres, frecuencia, tam);
  //  struct nodoHeap *raiz = construirArbolHuffman(bytes, recurrencias, elementos);

  ///////
  char arreglo_caracteres[] = {'f', 'e', 'c', 'b', 'd', 'a'};
  int freq[] = {5, 9, 12, 13, 16, 45};
  //tamaño en memoria entre tamaño de cada celda para obtener el tamaño del arreglo
  //int tam = sizeof(arreglo_caracteres) / sizeof(arreglo_caracteres[0]);
  //int tam = sizeof(bytes) / sizeof(recurrencias[0]);
  int tam = sizeof(bytes);

  // printf(" Caracter | codigo de Huffman ");
  // printf("\n--------------------\n");
  // printf("%d\n", tam);
  // printf("elementos %d\n", elementos);
  //codigoHuffman(arreglo_caracteres, frecuencia, tam);

  struct nodoHeap *raiz = construirArbolHuffman(bytes, recurrencias, elementos);

  int arr[TAMMAX], top = 0;

  Bits_Huffman bits[256];
  for (int i = 0; i < 256; i++)
    bits[i].tam = 0;
  long long int tam_archivo = 0;
  imprimirHuffcodigo(raiz, arr, top, bits, &tam_archivo);
  // for (int i = 0; i < 256; i++)
  // {
  //   if (bits[i].tam != 0)
  //   {
  //     //printf("%c - ", i);
  //     for (int j = 0; j < bits[i].tam; j++)
  //       printf("%d", bits[i].bits[j]);
  //        printf(" - %d\n", bits[i].tam);
  //   }
  // }

  //printf("%lld\n", tam_archivo);
  codificador(argv[1], tam_archivo, bits);
  //se crea el archivo frepeticiones que guarda el numero de repeticiones, se necesita para la decodificación
  FILE *frepeticiones = fopen("frecuencias.txt", "wb");
  fprintf(frepeticiones, "%d", elementos);
  fprintf(frepeticiones, " %d", tamBytes);
  for (int i = 0; i < elementos; i++)
  {
    fprintf(frepeticiones, " %d %d", (int)bytes[i], recurrencias[i]);
  }

  fclose(frepeticiones);

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

}
