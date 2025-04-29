#include <stdio.h>
#include <stdlib.h>

/**
   * @brief Ordena un arreglo de enteros en memoria externa utilizando el algoritmo Mergesort.
   *
   * Esta función calcula la posición exacta en bytes en el archivo binario a
   * partir del índice proporcionado, lee los bytes correspondientes a un nodo,
   * y los deserializa para reconstruir la estructura TreeNode en memoria.
   * Es responsabilidad del usuario asegurarse de que el offset sea válido,
   * es decir, que exista un nodo en esa posición.
   *
   * @param A: puntero a un archivo
   * @param B: tamaño del bloque
   * @param M: tamaño del bloque de memoria
   * @param a: cantidad de subarreglos
   * @return: Int cantidad de accesos a memoria
   * @return TreeNode El nodo deserializado desde el archivo
   * @throws Termina el programa si no puede abrir el archivo o ...
   */
void merge_RAM(int* arr, int* aux, int inicio, int medio, int fin) {
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
void mergesort(int* arr, int* aux, int inicio, int fin) {
    if (inicio >= fin) return;

    int medio = (inicio + fin) / 2;
    mergesort(arr, aux, inicio, medio);
    mergesort(arr, aux, medio + 1, fin);
    merge_RAM(arr, aux, inicio, medio, fin);
}
