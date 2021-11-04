  #!/bin/bash

  gcc heaps.c main.c tiempo.o huffman.c -o salida 
  ./salida Pinguinos.jpg >> codificacion.txt
  ./salida gatito.jpg >> codificacion.txt