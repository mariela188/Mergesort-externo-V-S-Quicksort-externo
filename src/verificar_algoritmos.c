#include "tarea1.h"

int main() {
    int64_t N = (int64_t)60 * M;
    int a = 50; //valor óptimo obtenido
    printf("Generando archivo de prueba...\n");
    generar_input(N, "data/A.bin");
    if (!esta_ordenado("data/A.bin")) {
        printf("Archivo desordenado generado.\n");
    }
    else {
        printf("Archivo ya esta ordenado.\n");
        exit(1);
    }
    char *A_copia;
    //mergesort
    printf("Probando mergesort externo...\n");
    A_copia = copiar_archivo_bin("data/A.bin");
    mergesort_externo(A_copia, a, N);
    if (esta_ordenado(A_copia)) {
        printf("Archivo ordenado correctamente.\n");
    }
    else {
        printf("Archivo no se ordeno correctamente.\n");
        exit(1);
    }
    free(A_copia);
    //quicksort
    printf("Probando quicksort externo...\n");
    A_copia = copiar_archivo_bin("data/A.bin");
    quicksort_externo(A_copia, a, N);
    if (esta_ordenado(A_copia)) {
        printf("Archivo ordenado correctamente.\n");
    }
    else {
        printf("Archivo no se ordeno correctamente.\n");
        exit(1);
    }
    free(A_copia);
}