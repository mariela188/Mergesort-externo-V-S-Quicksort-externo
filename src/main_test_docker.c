#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "tarea1.h"



// Declaraciones de las funciones (se asume que ya están definidas en otro archivo)


int main() {
    const int64_t N = (int64_t)4 * M; // 4 MB
    const char *archivo_merge = "A_merge.bin";
    const char *archivo_quick = "A_quick.bin";

    printf("Generando archivo de entrada para MergeSort...\n");
    generar_input(N, archivo_merge);
    printf("Archivo de entrada para MergeSort generado con exito\n");

    printf("Generando archivo de entrada para QuickSort...\n");
    generar_input(N, archivo_quick);
    printf("Archivo de entrada para QuickSort generado con exito\n");

    printf("Ordenando archivo con MergeSort externo...\n");
    if (mergesort_externo(archivo_merge, 0, N) == 0) {
        printf("MergeSort completado exitosamente.\n");
    } else {
        printf("Error al ejecutar MergeSort.\n");
    }

    printf("Ordenando archivo con QuickSort externo...\n");
    if (quicksort_externo(archivo_quick, 0, N) == 0) {
        printf("QuickSort completado exitosamente.\n");
    } else {
        printf("Error al ejecutar QuickSort.\n");
    }

    printf("Verificando si el archivo ordenado con MergeSort está correctamente ordenado...\n");
    if (esta_ordenado(archivo_merge)) {
        printf("Archivo ordenado correctamente con MergeSort.\n");
    } else {
        printf("Archivo NO está ordenado correctamente con MergeSort.\n");
    }

    printf("🔎 Verificando si el archivo ordenado con QuickSort está correctamente ordenado...\n");
    if (esta_ordenado(archivo_quick)) {
        printf("Archivo ordenado correctamente con QuickSort.\n");
    } else {
        printf("Archivo NO está ordenado correctamente con QuickSort.\n");
    }

    return 0;
}
