// Huffman Coding in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heaps.h"
#include "huffman.h"
#include "tiempo.h"

int main(int argc, char **argv) {
  // Variables para medición de tiempos
  double utime0, stime0, wtime0, utime1, stime1, wtime1;

  if (argc < 2) {
    printf("Error en los argumentos\n");
    exit(0);
  }

  // INICIAR EL CONTEO DEL TIEMPO PARA LAS EVALUACIONES DE RENDIMIENTO
  uswtime(&utime0, &stime0, &wtime0);

  //Abre el archivo especificado en el argumento 1, en modo binario
  FILE *archivo = fopen(argv[1], "rb");
  //Busca la ultima posicion del archivo partiendo desde el inicio
  fseek(archivo, 0, SEEK_END);
  //Obtiene el tamaño del archivo
  long long int tamano = ftell(archivo);
  /*Se posiciona nuevamente en la primer posicion del arreglo (buscar el tamaño del arreglo
   con fseek deja el puntero en la ultima posicion del archivo)
  */
  fseek(archivo, 0, SEEK_SET);

  int frecuencia[256];
  //inicializa el array caracteres (con todas las combinaciones de caracteres posibles) en blanco
  memset(frecuencia, 0, sizeof(int) * 256);

  // obtiene los caracteres del archivo hasta encontrar el final
  for (long long i = 0; i < tamano; i++) {
    unsigned char aux = fgetc(archivo);
    frecuencia[aux]++;
  }

  fclose(archivo);

  int elementos = 0; //Numero de elementos repetidos
  for (int i = 0; i < 256; i++) {
    if (frecuencia[i] > 0) elementos++;
  }

  //Creacion de arreglos para ingresar al arbol
  unsigned char *bytes = (unsigned char *)malloc(sizeof(unsigned char) * elementos); //Arreglo de caracteres repetidos
  int *recurrencias = (int *)malloc(sizeof(int) * elementos);                        //Arreglo con la cantidad de repeticiones
  
  //Asignacion de los valores a los arreglos
  int k = 0;
  int tamBytes = 0;
  for (int i = 0; i < 256; i++) {
    if (frecuencia[i] > 0) {
      tamBytes += frecuencia[i];
      bytes[k] = i;
      recurrencias[k] = frecuencia[i];
      k++;
    }
  }

  /*Se construye el arbol, recibe como parametros el arreglo de caracteres, sus repeticiones y la cantidad. Devuelve el apuntador al arbol*/
  struct nodoHeap *raiz = construirArbolHuffman(bytes, recurrencias, elementos);

  int arr[TAMMAX], top = 0;

  Bits_Huffman bits[256];//estructura definida en heap.h
  for (int i = 0; i < 256; i++)
    bits[i].tam = 0;
  long long int tam_archivo = 0;
  
  /*Funcion para almecenar los codigos Huffman de los nodos, recibe como parámetros los bits del archivo, el arbol y el tamaño del archivo*/
  imprimirHuffcodigo(raiz, arr, top, bits, &tam_archivo);
  
  codificador(argv[1], tamano, bits);

  //se crea el archivo de frecuencias que se necesita para la decodificación
  FILE *frepeticiones = fopen("frecuencias.txt", "wb");
  fprintf(frepeticiones, "%d", elementos);
  fprintf(frepeticiones, " %d", tamBytes);
  for (int i = 0; i < elementos; i++) {
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
