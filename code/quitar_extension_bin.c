#include "constantes.h"

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