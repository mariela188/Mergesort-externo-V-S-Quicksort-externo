#include <stdio.h>
#include <stdlib.h>

/**
   * @brief Ordena un arreglo de enteros en memoria externa utilizando el algoritmo Mergesort.
   *
   * Esta función hace...
   * 
   * @param arr: 
   * @param B: tamaño del bloque
   * @param M: tamaño del bloque de memoria
   * @param a: cantidad de subarreglos
   * @return: Int cantidad de accesos a memoria
*/
void merge_RAM(int64_t* arr, int64_t* aux, int inicio, int medio, int fin) {
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

// Función recursiva de Mergesort
void mergesort_RAM(int64_t* arr, int64_t* aux, int inicio, int fin) {
    if (inicio >= fin) return;

    int medio = (inicio + fin) / 2;
    mergesort_RAM(arr, aux, inicio, medio);
    mergesort_RAM(arr, aux, medio + 1, fin);
    merge_RAM(arr, aux, inicio, medio, fin);
}
