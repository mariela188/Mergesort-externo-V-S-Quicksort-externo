#ifndef TAREA1_H
#define TAREA1_H

//Librerías
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//Constantes
#define B 512 //Tamaño en bytes de un bloque
#define M (50 * 1024 * 1024) //Tamaño en bytes de la memoria principal (RAM)
#define T sizeof(int64_t) //Tamaño en bytes de cada entero del input
#define E (B / T) //Cantidad máxima de enteros por bloque

//Funciones
//util.c

/**
   * @brief Devuelve el nombre de un archivo binario sin su extensión.
   *
   * Esta función retorna el nombre de un archivo binario sin su extensión .bin.
   * 
   * @param nombre: nombre del archivo binario
   * @return char*: nombre del archivo sin extensión (asignado con malloc)
   * @throws Termina el programa si el archivo no tiene extensión .bin o no se puede 
   * asignar memoria para malloc.
*/
char *quitar_extension_bin(const char* nombre);

/**
   * @brief Genera una copia de un archivo binario.
   *
   * Esta función copia el contenido de un archivo binario en otro archivo
   * del mismo nombre con el sufijo "_copia".
   * 
   * @param nombre: nombre del archivo a copiar
   * @return char*: nombre de la copia del archivo (asignado con malloc)
   * @throws Termina el programa si no se puede abrir un archivo o no se puede 
   * asignar memoria para malloc.
*/
char *copiar_archivo_bin(const char *archivo);



/**
   * @brief Genera un archivo binario de N bytes.
   *
   * Esta función genera un archivo binario de enteros 
   * de tamaño total N bytes, y le asigna el nombre dado. 
   * 
   * @param nombre: nombre del archivo a generar
   * @param N: tamaño en bytes del archivo a generar.
*/
void generar_input(int64_t N, const char *nombre);

/**
   * @brief Verifica si un archivo binario está ordenado ascendentemente.
   * 
   * Esta función recibe el nombre de un archivo binario y verifica si su contenido
   * está ordenado ascendentemente.
   * 
   * @param nombre_archivo: nombre del archivo a verificar
   * @return bool: true si el archivo está ordenado, false en caso contrario
   * @throws Termina el programa si no puede abrir el archivo.
   */
  bool esta_ordenado(const char *nombre_archivo);

//mergesort_externo.c

/**
   * @brief Mezcla dos subarreglos ordenados en un solo arreglo ordenado.
   *
   * Esta función es parte del algoritmo mergesort en RAM. Mezcla en orden creciente los 
   * dos subarreglos contiguos del arreglo 'arr', 'arr[inicio..medio]' y 'arr[medio+1..fin]', 
   * usando el arreglo auxiliar 'aux'.
   * 
   * @param arr: arreglo original con los subarreglos a mezclar
   * @param aux: arreglo auxiliar a utilizar
   * @param inicio: índice inicial del primer subarreglo
   * @param medio: índice final del primer subarreglo
   * @param fin: índice final del segundo subarreglo
*/
void merge(int64_t* arr, int64_t* aux, int inicio, int medio, int fin);

/**
   * @brief Ordena un arreglo de enteros en memoria RAM.
   *
   * Esta función ordena un arreglo de enteros de 64 bits a través del algoritmo
   * mergesort usando el arreglo auxiliar 'aux'.
   * 
   * @param arreglo: arreglo de enteros a ordenar
   * @param aux: arreglo auxiliar a utilizar
   * @param incio: índice del inicio del subarreglo a ordenar
   * @param fin: índice del final del subarreglo a ordenar
*/
void mergesort_RAM(int64_t* arreglo, int64_t *aux, int inicio, int fin);

/**
   * @brief Función que hace merge de n arreglos ordenados en memoria externa.
   *
   * Esta función recibe un lista de archivos ordenados de manera
   * ascendente y los mergea en un solo archivo de salida. Retorna la cantidad
   * de accesos realizados a la memoria externa.
   * 
   * @param n: cantidad de archivos a mergear
   * @param nombres: lista de nombres de cada archivo a mergear
   * @param tamanos: lista de tamaños de cada archivo a mergear
   * @param A: nombre del arhivo de salida
   * @return int: cantidad de accesos a memoria externa
   * @throws Termina el programa si no puede abrir algún archivo o si hay un error al 
   * asignar memoria para malloc.
*/
int merge_externo(int n, char nombres[][64], int64_t tamanos[], const char *A);

/**
   * @brief Ordena un arreglo de enteros en memoria externa utilizando el algoritmo mergesort.
   *
   * Esta función ordena un archivo binario de N bytes de enteros de 64 bits mediante
   * el algoritmo de mergesort en memoria externa, dividiendolo en 'a' subarreglos. 
   * Retorna la cantidad de accesos a la memoria externa.
   * 
   * @param A: nombre del archivo a ordenar
   * @param a: cantidad de subarreglos a generar (aridad)
   * @param N: tamaño en bytes de A
   * @return int: cantidad de accesos a memoria
   * @throws Termina el programa si no puede abrir el archivo o si hay un error al crear los 
   * archivos de los subarreglos o al asignar memoria para malloc.
   */
int mergesort_externo(const char *A, int a, int64_t N);

//quicksort_externo.c

/**
 * @brief Ordena un arreglo de enteros en memoria RAM.
 *
 * Esta función ordena un arreglo de enteros de 64 bits a través del algoritmo
 * quicksort.
 * 
 * @param arreglo: arreglo de enteros a ordenar
 * @param inicio: índice del inicio del subarreglo a ordenar
 * @param fin: índice del final del subarreglo a ordenar
 */
void quicksort_RAM(int64_t* arreglo, int inicio, int fin);

/**
   * @brief Función que concatena n archivos en memoria externa.
   *
   * Esta función recibe un lista de archivos binarios y los concatena en un solo 
   * archivo de salida. Retorna la cantidad de accesos realizados a la memoria externa.
   * 
   * @param n: cantidad de archivos a concatenar
   * @param nombres: lista de nombres de cada archivo
   * @param tamanos: lista de tamaños de cada archivo
   * @param A: nombre del archivo de salida
   * @return int: cantidad de accesos a memoria externa
   * @throws Termina el programa si no puede abrir algún archivo o si hay un error al 
   * asignar memoria para malloc.
*/
int concatenar_externo(int n, char nombres[][64], int64_t tamanos[], const char *A);

/**
   * @brief Ordena un arreglo de enteros en memoria externa utilizando el algoritmo quicksort.
   *
   * Esta función ordena un archivo binario de N bytes de enteros de 64 bits mediante
   * el algoritmo de quicksort en memoria externa, usando a-1 pivotes para particionar el arreglo
   * original. Retorna la cantidad de accesos a la memoria externa.
   * 
   * @param A: nombre del archivo a ordenar
   * @param a: cantidad de subarreglos a generar al particionar
   * @param N: tamaño en bytes de A
   * @return int: cantidad de accesos a memoria externa
   * @throws Termina el programa si no puede abrir el archivo o si hay un error al crear los 
   * archivos de los subarreglos o al asignar memoria para malloc.
   */
int quicksort_externo(const char *A, int a, int64_t N);

//obtener_a.c

/**
   * @brief Retorna la mejor aridad para mergesort externo dentro del rango especificado
   *
   * Esta función entrega la aridad 'a' que minimiza los accesos a disco en mergesort
   * externo para un archivo de prueba. La aridad óptima se encuentra a través de 
   * búsqueda ternaria dentro del rango [l, r]. 
   * 
   * @param A: nombre del archivo de prueba
   * @param N: tamaño en bytes de A
   * @param l: limite inferior del rango de búsqueda
   * @param r: limite superior del rango de búsqueda
   * @return int: aridad óptima dentro del rango
   * @throws Termina el programa si ocurre algún error al ordenar el archivo de prueba
   * con mergesort externo.
   */
int obtener_a(const char *A, int64_t N, int l, int r);

#endif // TAREA1_H