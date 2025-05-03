#include <stdint.h>
#include <string.h> 

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
void quicksort_RAM(int64_t* arreglo, int inicio, int fin) {
    if (inicio >= fin) return;

    int64_t pivote = arreglo[inicio];
    int izq = inicio + 1;
    int der = fin;
    
    while (izq <= der) {
        while (izq <= fin && arreglo[izq] <= pivote) izq++;
        while (der > inicio && arreglo[der] > pivote) der--;
        if (izq < der) {
            int64_t tmp = arreglo[izq];
            arreglo[izq] = arreglo[der];
            arreglo[der] = tmp;
        }
    }

    arreglo[inicio] = arreglo[der];
    arreglo[der] = pivote;

    quicksort_RAM(arreglo, inicio, der - 1);
    quicksort_RAM(arreglo, der + 1, fin);
}
