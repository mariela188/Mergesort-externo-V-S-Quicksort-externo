#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool esta_ordenado(const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "rb");
    if (!archivo) {
        perror("Error al abrir archivo");
        return false;
    }

    int64_t anterior, actual;
    if (fread(&anterior, sizeof(int64_t), 1, archivo) != 1) {
        fclose(archivo);
        return true; // Un archivo vacío se considera ordenado
    }

    while (fread(&actual, sizeof(int64_t), 1, archivo) == 1) {
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
    const char *archivo = "data/A_4M.bin";
    if (esta_ordenado(archivo)) {
        printf("El archivo está ordenado ascendentemente.\n");
    } else {
        printf("El archivo NO está ordenado ascendentemente.\n");
    }
    return 0;
}