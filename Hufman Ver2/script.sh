#!/bin/bash

  gcc heaps.c main.c tiempo.o huffman.c -o salida 
 # "imagen jpg. 23.8 KiB (24 321 bytes) "
  ./salida Pinguinos.jpg 
 gcc heaps.c decodificacion.c tiempo.o huffman.c -o salida 
  ./salida PinguinosDeco.jpg >> deco.txt 

#"Imagen JPG Tamaño 6.4 KiB (6 536 bytes)"

  gcc heaps.c main.c tiempo.o huffman.c -o salida 
  ./salida gatito.jpg 
gcc heaps.c decodificacion.c tiempo.o huffman.c -o salida 
  ./salida gatitoDeco.jpg >> deco.txt 

#zip

  gcc heaps.c main.c tiempo.o huffman.c -o salida 
./salida p1.zip 
gcc heaps.c decodificacion.c tiempo.o huffman.c -o salida 
  ./salida p1Deco.zip >> deco.txt 

#zip

  gcc heaps.c main.c tiempo.o huffman.c -o salida 
./salida p3.zip 
gcc heaps.c decodificacion.c tiempo.o huffman.c -o salida 
  ./salida p3Deco.zip >> deco.txt 

#PDF

  gcc heaps.c main.c tiempo.o huffman.c -o salida 
./salida Practica2.pdf 
gcc heaps.c decodificacion.c tiempo.o huffman.c -o salida 
  ./salida prac2Deco.pdf >> deco.txt 

#PDF

  gcc heaps.c main.c tiempo.o huffman.c -o salida 
./salida instru.pdf 
gcc heaps.c decodificacion.c tiempo.o huffman.c -o salida 
  ./salida instruDeco.pdf >> deco.txt 


#MKV

  gcc heaps.c main.c tiempo.o huffman.c -o salida 
./salida video1.mkv 
gcc heaps.c decodificacion.c tiempo.o huffman.c -o salida 
  ./salida video1Deco.mkv >> deco.txt 


#MKV 

  gcc heaps.c main.c tiempo.o huffman.c -o salida 
./salida video2.mkv 
gcc heaps.c decodificacion.c tiempo.o huffman.c -o salida 
  ./salida video2Deco.mkv >> deco.txt 

#png

  gcc heaps.c main.c tiempo.o huffman.c -o salida 
./salida kitten.png 
gcc heaps.c decodificacion.c tiempo.o huffman.c -o salida 
  ./salida kittenDeco.png >> deco.txt 

#png

  gcc heaps.c main.c tiempo.o huffman.c -o salida 
./salida logoescom.png 
gcc heaps.c decodificacion.c tiempo.o huffman.c -o salida 
  ./salida logoescom.png >> deco.txt