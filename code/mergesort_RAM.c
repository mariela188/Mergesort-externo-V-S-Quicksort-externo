#include "constantes.h"

/**
   * @brief Mezcla dos subarreglos ordenados en un solo arreglo ordenado.
   *
   * Esta función es parte del algoritmo mergesort en RAM. Mezcla en orden creciente los 
   * dos subarreglos contiguos del arreglo 'arr', 'arr[inicio..medio]' y 'arr[medio+1..fin]', 
   * usando el arreglo auxiliar 'aux'.
   * 
   * @param arr: arreglo original con los subarreglos a fusionar
   * @param aux: arreglo auxiliar a utilizar
   * @param inicio: índice inicial del primer subarreglo
   * @param medio: índice final del primer subarreglo
   * @param fin: índice final del segundo subarreglo
*/
void merge(int64_t* arr, int64_t* aux, int inicio, int medio, int fin) {
    int i = inicio;
    int j = medio + 1;
    int k = inicio;
    while (i <= medio && j <= fin) {
        if (arr[i] <= arr[j]) {
            aux[k++] = arr[i++];
        } else {
            aux[k++] = arr[j++];
        }
    }
    while (i <= medio) {
        aux[k++] = arr[i++];
    }
    while (j <= fin) {
        aux[k++] = arr[j++];
    }
    for (int l = inicio; l <= fin; l++) {
        arr[l] = aux[l];
    }
}

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
void mergesort_RAM(int64_t* arreglo, int64_t* aux, int inicio, int fin) {
    if (inicio >= fin) return;
    int medio = (inicio + fin) / 2;
    mergesort_RAM(arreglo, aux, inicio, medio);
    mergesort_RAM(arreglo, aux, medio + 1, fin);
    merge(arreglo, aux, inicio, medio, fin);
}
