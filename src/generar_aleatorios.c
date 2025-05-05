#include "tarea1.h"
#define TAMANO_BLOQUE 65536  //64 KB

void generar_aleatorios(const char *nombre_archivo, int64_t N) {
    //Abrir archivo
    FILE *archivo = fopen(nombre_archivo, "wb");
    if (!archivo) {
        perror("No se pudo abrir el archivo");
        return;
    }

    //Generador de números aleatorios
    srand(time(NULL));

    //Cantidad de enteros
    int64_t cantidad_enteros = N / T;

    //Cantidad de enteros que caben en 64 KB
    int64_t enteros_por_bloque = TAMANO_BLOQUE / T;

    //Reservamos memoria para un bloque de 64 KB
    int64_t *bloque = (int64_t *)malloc(TAMANO_BLOQUE);
    if (!bloque) {
        perror("Error al asignar memoria");
        exit(1);
    }

    //Escribir los números aleatorios en bloques
    int64_t escritos = 0;
    while (escritos < cantidad_enteros) {
        //Calcular cuántos enteros escribiremos en este bloque
        int64_t cantidad_a_escribir = enteros_por_bloque;
        if (cantidad_enteros - escritos < enteros_por_bloque) {
            cantidad_a_escribir = cantidad_enteros - escritos;
        }

        //Llenar bloque con números aleatorios
        for (int64_t i = 0; i < cantidad_a_escribir; ++i) {
            bloque[i] = ((int64_t)rand() << 32) | rand();  //Número aleatorio de 64 bits
        }

        //Escribir bloque en el archivo
        int64_t cantidad_real = fwrite(bloque, T, cantidad_a_escribir, archivo);
        if (cantidad_real != cantidad_a_escribir) {
            perror("Error al escribir en el archivo");
            exit(1);
        }

        escritos += cantidad_a_escribir;
    }

    //Liberar memoria y cerrar archivo
    free(bloque);
    fclose(archivo);
}
