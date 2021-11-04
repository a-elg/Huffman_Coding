#include "huffman.h"
#include <stdio.h>
struct nodoHeap *construirArbolHuffman(unsigned char dato[], int frecuencia[], int tam)
{
  struct nodoHeap *izq, *der, *arbolito;
  //genera un arbol con los caracteres del archivo a leer y su frecuencia
  struct Heap *Heap = generarArbol(dato, frecuencia, tam);
  //hasta que el arbol cuente con solo una raiz se extraeran los nodos en pares, tomando los dos de menor frecuencia en cada ocasion
  while (!EsUnitario(Heap))
  {
    izq = extraerNodo(Heap);
    der = extraerNodo(Heap);
    //se crean los arboles temporales
    arbolito = crearNodo('#', izq->frecuencia + der->frecuencia);
    //se asignan los nodos con caracteres a los arboles temporales
    arbolito->izq = izq;
    arbolito->der = der;
    //se inserta el nodo al arbol para ordenarlo nuevamente
    insertarNodo(Heap, arbolito);
  }
  //retorna la raiz del arbol de Huffman
  return extraerNodo(Heap);
}

void imprimirHuffcodigo(struct nodoHeap *raiz, int arr[], int pos,Bits_Huffman* bits_huffman, long long int* tam_archivo)
{
  ///0 0 1 0 0 0 1 1
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
    /* printf("  %c   | ", raiz->dato);
    //Impresion de tabla
    for (i = 0; i < pos; ++i)
      printf("%d", arr[i]);

    printf("\n"); */
    bits_huffman[raiz->dato].bits = (int *)malloc(sizeof(int) * pos);
    for(int i = 0; i < pos; i++)
    {
      bits_huffman[raiz->dato].bits[i] = arr[i];
    }

    bits_huffman[raiz->dato].tam = pos;
    *tam_archivo += raiz->frecuencia * pos;
    // imprimirTabla(arr, arbol);
  }
}
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
        c = fgetc(archivo);

        for (i = 0; i < bits[c].tam; i++, k++)
        {

            if (bits[c].bits[i] == 1)
            {
                PONE_1(cadena_cerosunos, 7 - k);
            }
            if (k == 7)
            {
                k = -1;
                fwrite(&cadena_cerosunos, 1, sizeof(cadena_cerosunos), codi);
                //fputc(cadena_cerosunos, codi);
                cadena_cerosunos = 0;
            }
        }
    }

    if (k != 0)
        fwrite(&cadena_cerosunos, 1, sizeof(cadena_cerosunos), codi);
    //fputc(cadena_cerosunos, codi);

    //printf("\t%c-%s\n",c,codigos[c].cadena);
    fclose(codi);
    fclose(archivo);
}
/*void codigoHuffman(unsigned char dato[], int frecuencia[], int tam)
{
  struct nodoHeap *raiz = construirArbolHuffman(dato, frecuencia, tam);

  int arr[TAMMAX], top = 0;

  imprimirHuffcodigo(raiz, arr, top);
}*/

