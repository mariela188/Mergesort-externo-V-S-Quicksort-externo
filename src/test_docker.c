#include "tarea1.h"

int main() {
    int64_t N = (int64_t)4 * M; //4*M
    int a = 50;
    time_t inicio, fin;
    int tiempo;
    int accesos;
    char *archivo_ms = "data/A_ms.bin";
    char *archivo_qs = "data/A_qs.bin";

    printf("Generando archivo de entrada para Mergesort...\n");
    generar_input(N, archivo_ms);
    printf("Archivo de entrada para Mergesort generado con exito.\n");

    printf("Generando archivo de entrada para Quicksort...\n");
    generar_input(N, archivo_qs);
    printf("Archivo de entrada para Quicksort generado con exito.\n");

    printf("Ordenando archivo con Mergesort externo...\n");
    time(&inicio);
    accesos = mergesort_externo(archivo_ms, a, N);
    time(&fin);
    tiempo = difftime(fin, inicio);
    printf("Completado.\n");
    printf("Accesos a memoria externa: %d I/Os\n", accesos);
    printf("Tiempo de ejecucion: %d segundos\n", tiempo);
    printf("Verificando si el archivo está correctamente ordenado...\n");
    if (esta_ordenado(archivo_ms)) {
        printf("Archivo ordenado correctamente.\n");
    } else {
        printf("Archivo NO está ordenado correctamente.\n");
        exit(1);
    }

    printf("Ordenando archivo con Quicksort externo...\n");
    time(&fin);
    accesos = quicksort_externo(archivo_qs, a, N);
    time(&fin);
    tiempo = difftime(fin, inicio);
    printf("Completado.\n");
    printf("Accesos a memoria externa: %d I/Os\n", accesos);
    printf("Tiempo de ejecucion: %d segundos\n", tiempo);
    printf("Verificando si el archivo está correctamente ordenado...\n");
    if (esta_ordenado(archivo_qs)) {
        printf("Archivo ordenado correctamente.\n");
    } else {
        printf("Archivo NO está ordenado correctamente.\n");
        exit(1);
    }
    printf("Proceso completado con exito.\n");
    return 0;
}
