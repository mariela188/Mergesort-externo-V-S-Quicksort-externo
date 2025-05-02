#include "constantes.h"
#include "quicksort.c"

int main() {
    const char* nombre_archivo = "prueba_pequena.bin";
    int64_t datos[] = {42, 7, 19, -3, 88};  // 5 enteros desordenados
    size_t n = sizeof(datos) / sizeof(int64_t);

    // Escribir en binario
    FILE* archivo = fopen(nombre_archivo, "wb");
    if (!archivo) {
        perror("Error al crear el archivo");
        return 1;
    }
    fwrite(datos, sizeof(int64_t), n, archivo);
    fclose(archivo);

    // Leer el archivo para verificar que quedó bien
    archivo = fopen(nombre_archivo, "rb");
    if (!archivo) {
        perror("Error al abrir archivo para leer");
        return 1;
    }

    int64_t leido;
    printf("Contenido del archivo:\n");
    for (size_t i = 0; i < n; i++) {
        fread(&leido, sizeof(int64_t), 1, archivo);
        printf("%ld\n", leido);
    }

    fclose(archivo);

    int resultado = Quicksort_externo("prueba_pequena.bin", 2, 5*T);

    // Leer el archivo para verificar que quedó bien
    archivo = fopen(nombre_archivo, "rb");
    if (!archivo) {
        perror("Error al abrir archivo para leer");
        return 1;
    }

    int64_t leido_;
    printf("Archivo ordenado:\n");
    for (size_t i = 0; i < n; i++) {
        fread(&leido_, sizeof(int64_t), 1, archivo);
        printf("%ld\n", leido_);
    }

    fclose(archivo);

    printf("accesos: %d", resultado);


    return 0;
}