#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define TAMANO_BLOQUE 65536  // 64 KB

// Función para generar números aleatorios y escribirlos en un archivo binario
void generar_aleatorios(const char *nombre_archivo, size_t N) {
    // Abrimos el archivo en modo escritura binaria
    FILE *archivo = fopen(nombre_archivo, "wb");
    if (!archivo) {
        perror("No se pudo abrir el archivo");
        return;
    }

    // Inicializamos el generador de números aleatorios
    srand(time(NULL));

    // Calculamos cuántos enteros de 64 bits necesitamos escribir
    size_t cantidad_enteros = N / sizeof(int64_t);

    // Cuántos enteros caben en 64 KB
    size_t enteros_por_bloque = TAMANO_BLOQUE / sizeof(int64_t);

    // Reservamos memoria para un bloque de 64 KB
    int64_t *bloque = (int64_t *)malloc(TAMANO_BLOQUE);
    if (!bloque) {
        perror("No se pudo reservar memoria");
        fclose(archivo);
        return;
    }

    // Escribimos los números aleatorios en bloques
    size_t escritos = 0;
    while (escritos < cantidad_enteros) {
        // Calculamos cuántos enteros escribiremos en este bloque (puede ser menos de 64KB en el último)
        size_t cantidad_a_escribir = enteros_por_bloque;
        if (cantidad_enteros - escritos < enteros_por_bloque) {
            cantidad_a_escribir = cantidad_enteros - escritos;
        }

        // Llenamos el bloque con números aleatorios
        for (size_t i = 0; i < cantidad_a_escribir; ++i) {
            bloque[i] = ((int64_t)rand() << 32) | rand();  // Número aleatorio de 64 bits
        }

        // Escribimos el bloque en el archivo
        size_t cantidad_real = fwrite(bloque, sizeof(int64_t), cantidad_a_escribir, archivo);
        if (cantidad_real != cantidad_a_escribir) {
            perror("Error al escribir en el archivo");
            break;
        }

        escritos += cantidad_a_escribir;
    }

    // Liberamos la memoria y cerramos el archivo
    free(bloque);
    fclose(archivo);
}
