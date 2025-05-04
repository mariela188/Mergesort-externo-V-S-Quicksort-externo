#include "constantes.h"
#define TAM_BLOQUE 10000000

void generar_secuencia(int64_t N, const char *nombre) {
    int64_t n = N / T; //cantidad de enteros
    int64_t *buffer = malloc(TAM_BLOQUE * T);
    if (!buffer) {
        perror("Error al asignar memoria");
        exit(1);
    }

    FILE *archivo = fopen(nombre, "wb");
    if (!archivo) {
        perror("Error al abrir archivo");
        free(buffer);
        exit(1);
    }

    srand(time(NULL)); //semilla de aleatoriedad

    int64_t escritos = 0;
    while (escritos < n) {
        int64_t actual = (n - escritos > TAM_BLOQUE) ? TAM_BLOQUE : (n - escritos);

        //llenar bloque con valores únicos
        for (int64_t i = 0; i < actual; i++) {
            buffer[i] = escritos + i + 1;
        }

        //shuffle dentro del bloque (Fisher-Yates)
        for (int64_t i = actual - 1; i > 0; i--) {
            int64_t j = rand() % (i + 1);
            int64_t tmp = buffer[i];
            buffer[i] = buffer[j];
            buffer[j] = tmp;
        }

        fwrite(buffer, T, actual, archivo);
        escritos += actual;
    }

    fclose(archivo);
    free(buffer);
}

int main() {
    int multiplo = 4;
    int64_t N = (int64_t)multiplo * M;
    char nombre_archivo[32];
    snprintf(nombre_archivo, sizeof(nombre_archivo), "data/A_%dM.bin", multiplo);
    generar_secuencia(N, nombre_archivo);
}