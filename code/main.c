#include "constantes.h"
#include "mergesort_externo.h"
#include "quicksort_externo.h"

void imprimir_primeros_10(const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "rb");
    if (!archivo) {
        perror("Error al abrir el archivo");
        return;
    }

    int64_t numero;
    for (int i = 0; i < 10; i++) {
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

    printf("Archivo original\n");
    imprimir_primeros_10("data/A.bin");

    inicio = clock();
    int accesos = mergesort_externo("data/A.bin", 2, N);
    fin = clock();

    printf("Archivo ordenado\n");
    imprimir_primeros_10("data/A.bin");

    tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;

    printf("Tiempo de ejecucion: %.6f segundos\n", tiempo);
    printf("Accesos a memoria externa: %d\n", accesos);

    return 0;
}