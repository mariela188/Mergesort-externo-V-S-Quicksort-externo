#include "tarea1.h"
#define TAMANO_BLOQUE 65536  //64 KB

char *quitar_extension_bin(const char* nombre) {
    size_t len = strlen(nombre);
    if (strcmp(nombre + len - 4, ".bin") != 0) {
        fprintf(stderr, "El archivo no termina en .bin\n");
        exit(1);
    }
    char* sin_extension = malloc(len - 3);
    if (!sin_extension) {
        perror("Error al asignar memoria");
        exit(1);
    }
    strncpy(sin_extension, nombre, len - 4);
    sin_extension[len-4] = '\0';
    return sin_extension;
}


char *copiar_archivo_bin(const char *archivo) {
    //abrir archivo de origen
    FILE *archivo_origen = fopen(archivo, "rb");
    if (archivo_origen == NULL) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    //crear y abrir archivo de destino
    char *nombre_base = quitar_extension_bin(archivo);
    char *nombre_copia = malloc(64);
    if (!nombre_copia) {
        perror("Error al asignar memoria");
        exit(1);
    }
    snprintf(nombre_copia, 64, "%s_copia.bin", nombre_base);
    FILE *archivo_copia = fopen(nombre_copia, "wb");
    if (archivo_copia == NULL) {
        perror("Error al abrir la copia del archivo");
        fclose(archivo_origen);
        exit(1);
    }

    //copiar el archivo en bloques de 64 KB
    char buffer[65536];
    size_t bytes_leidos;
    while ((bytes_leidos = fread(buffer, 1, sizeof(buffer), archivo_origen)) > 0) {
        fwrite(buffer, 1, bytes_leidos, archivo_copia);
    }

    //cerrar archivos
    fclose(archivo_origen);
    fclose(archivo_copia);
    free(nombre_base);

    //retornar nombre
    return nombre_copia;
}


void generar_input(int64_t N, const char *nombre_archivo) {
    //Abrir archivo
    FILE *archivo = fopen(nombre_archivo, "wb");
    if (!archivo) {
        perror("No se pudo abrir el archivo");
        exit(1);
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
