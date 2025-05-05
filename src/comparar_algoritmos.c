#include "tarea1.h"

void imprimir_primeros(const char *nombre_archivo, int cantidad) {
    FILE *archivo = fopen(nombre_archivo, "rb");
    if (!archivo) {
        perror("Error al abrir el archivo");
        return;
    }

    int64_t numero;
    for (int i = 0; i < cantidad; i++) {
        if (fread(&numero, sizeof(int64_t), 1, archivo) != 1) {
            break; //si se alcanzó el final del archivo antes de leer 10
        }
        printf("%lld" "\n", numero);
    }

    printf("\n");
    fclose(archivo);
}

int main() {
    clock_t inicio, fin;
    double tiempo;
    int64_t N = (int64_t)60 * M;
    int cantidad_a_imprimir = 100;

    printf("Archivo original\n");
    imprimir_primeros("data/A_60M.bin", cantidad_a_imprimir);

    inicio = clock();
    int accesos = mergesort_externo("data/A_60M.bin", 4, N);
    fin = clock();

    printf("Archivo ordenado\n");
    imprimir_primeros("data/A_60M.bin", cantidad_a_imprimir);

    tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;

    printf("Tiempo de ejecucion: %.6f segundos\n", tiempo);
    printf("Accesos a memoria externa: %d\n", accesos);

    return 0;
}