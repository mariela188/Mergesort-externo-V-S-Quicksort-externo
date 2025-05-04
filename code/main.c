#include "constantes.h"
#include "generar_secuencias.c"

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
    int64_t tamano = (int64_t)60 * M;
    generar_secuencia(tamano, "prueba_secuencia.bin");
    imprimir_primeros_10("prueba_secuencia.bin");
    return 0;
}