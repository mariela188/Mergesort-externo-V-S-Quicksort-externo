#include "tarea1.h"

bool esta_ordenado(const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "rb");
    if (!archivo) {
        perror("Error al abrir archivo");
        return false;
    }

    int64_t anterior, actual;
    if (fread(&anterior, T, 1, archivo) != 1) {
        fclose(archivo);
        return true;
    }

    while (fread(&actual, T, 1, archivo) == 1) {
        if (actual < anterior) {
            fclose(archivo);
            return false;
        }
        anterior = actual;
    }

    fclose(archivo);
    return true;
}

int main() {
    int64_t N = (int64_t)60 * M;
    int a = 50; //valor óptimo obtenido
    printf("Generando archivo de prueba...\n");
    generar_input(N, "data/A.bin");
    if (!esta_ordenado("data/A.bin")) {
        printf("Archivo desordenado generado");
    }
    else {
        printf("Archivo ya esta ordenado)");
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
    A_copia = copiar_archivo_bin("data/A.bin");
    quicksort_externo(A_copia, a, N);
    if (esta_ordenado(A_copia)) {
        printf("Archivo ordenado correctamente.\n");
    }
    else {
        printf("Archivo no se ordeno correctamente.\n");
        exit(1);
    }
}