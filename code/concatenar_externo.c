#include "constantes.h"

/**
   * @brief Función que concatena n archivos en memoria externa.
   *
   * Esta función recibe un lista de archivos binarios y los concatena en un solo 
   * archivo de salida. Retorna la cantidad de accesos realizados a la memoria externa.
   * 
   * @param n: cantidad de archivos a concatenar
   * @param nombres: lista de nombres de cada archivo
   * @param tamanos: lista de tamaños de cada archivo
   * @param A: nombre del archivo de salida
   * @return int: cantidad de accesos a memoria externa
   * @throws Termina el programa si no puede abrir algún archivo o si hay un error al 
   * asignar memoria para malloc.
*/
int concatenar_externo(int n, char nombres[][32], int64_t tamanos[], const char *A) {
    //contador de accesos a memoria
    int accesos = 0;

    //abrir archivo de salida
    FILE *salida = fopen(A, "rb+"); //"rb+" = leer y escribir en binario
    if (!salida) {
        perror("Error al abrir archivo de salida");
        exit(1);
    }  

    //crear buffer de lectura y buffer de escritura
    int64_t *buffer_r = malloc(B);
    int64_t *buffer_w = malloc(B);
    if (!buffer_r || !buffer_w) {
        perror("Error al asignar memoria");
        exit(1);
    }

    //posición en buffer de escritura
    int pos_w = 0;

    //leer cada archivo y escribirlo en archivo de salida
    for (int i=0; i<n; i++) {
        FILE *archivo = fopen(nombres[i], "rb");
        if (!archivo) {
            perror("Error al abrir un archivo de entrada");
            exit(1);
        }
        int64_t bloques_archivo = (tamanos[i]+B-1)/B;
        for (int64_t k=0; k<bloques_archivo; k++) {
            int leidos = fread(buffer_r, T, E, archivo); //leer bloque
            accesos++;
            for (int j=0; j<leidos; j++) { //escribir elementos en buffer de escritura
                buffer_w[pos_w] = buffer_r[j];
                pos_w++;
                if (pos_w == E) { //buffer de escritura está lleno
                    fwrite(buffer_w, T, E, salida); //escribir bloque
                    accesos++;
                    pos_w = 0;
                }
            }
        }
        fclose(archivo);
        remove(nombres[i]);
    }
    if (pos_w > 0) {
        fwrite(buffer_w, T, pos_w, salida); //escribir último bloque del archivo
        accesos++;
    }

    //liberar buffers y cerrar archivo de salida
    free(buffer_r);
    free(buffer_w);
    fclose(salida);

    return accesos;
}