#include "tarea1.h"
#define TAM_BLOQUE 10000000

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


void generar_input(int64_t N, const char *nombre) {
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
