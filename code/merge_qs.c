#include "constantes.h"

/**
   * @brief Función que hace merge en memoria externa de n subarreglos de quicksort ordenados.
   *
   * Esta función recibe un lista de archivos ordenados de manera
   * ascendente, donde los elementos de cada archivo son menores a los elementos del
   * archivo siguiente, y los mergea en un solo archivo de salida.
   * 
   * @param n: cantidad de archivos a mergear
   * @param nombres: lista de nombres de cada archivo a mergear
   * @param tamanos: lista de tamaños de cada archivo a mergear
   * @param A: nombre del archivo de salida
   * @return int: cantidad de accesos a memoria
*/
int merge_qs_externo(int n, char nombres[][32], int tamanos[], const char *A) {
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
        int bloques_archivo = (tamanos[i]+B-1)/B;
        for (int k=0; k<bloques_archivo; k++) {
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