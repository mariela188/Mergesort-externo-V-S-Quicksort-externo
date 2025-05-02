#include "constantes.h"

/**
   * @brief Función que hace merge de n arreglos ordenados en memoria externa.
   *
   * Esta función recibe un lista de archivos ordenados de manera
   * ascendente y los mergea en un solo archivo de salida. Retorna la cantidad
   * de accesos realizados a la memoria externa.
   * 
   * @param n: cantidad de archivos a mergear
   * @param nombres: lista de nombres de cada archivo a mergear
   * @param tamanos: lista de tamaños de cada archivo a mergear
   * @param A: nombre del arhivo de salida
   * @return int: cantidad de accesos a memoria externa
   * @throws Termina el programa si no puede abrir algún archivo o si hay un error al 
   * asignar memoria para malloc.
*/
int merge_externo(int n, char nombres[][32], int tamanos[], const char *A) {
    //contador de accesos a memoria
    int accesos = 0;

    //crear n+1 buffers (uno por cada arhivo de entrada y uno de salida)
    int64_t **buffers = malloc(n * sizeof(int64_t *));  //arreglo de punteros
    if (buffers == NULL) {
        perror("Error al asignar memoria");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        buffers[i] = malloc(B);
        if (buffers[i] == NULL) {
            perror("Error al asignar memoria");
            exit(1);
        }
    }
    int64_t *buffer_salida = malloc(B);
    if (buffer_salida == NULL) {
        perror("Error al asignar memoria");
        exit(1);
    }

    //abrir archivo de salida
    FILE *salida = fopen(A, "rb+"); //"rb+" = leer y escribir en binario
    if (!salida) {
        perror("Error al abrir archivo de salida");
        exit(1);
    }

    //posiciones en que se está leyendo para cada buffer y
    //cantidad de elementos escritos de cada archivo 
    int pos[n], cont[n];
    int pos_salida = 0;
    int cont_salida = 0;    

    //variable y arreglo de flags para saber cuando terminar
    int listo = 0;
    int terminados[n];

    //arreglo de la cantidad de elementos de cada archivo
    int elementos[n];

    //lectura inicial de los archivos de entrada
    FILE *archivos[n];
    for (int i=0; i<n; i++) {
        FILE *archivo = fopen(nombres[i], "rb");
        if (!archivo) {
            perror("Error al abrir un archivo de entrada");
            exit(1);
        }
        archivos[i] = archivo;
        fread(buffers[i], T, E, archivos[i]);
        accesos++;
        pos[i] = 0;
        terminados[i] = 0;
        cont[i] = 0;
        elementos[i] = tamanos[i]/T;
    }

    //recorrer archivos
    while (!listo) {
        listo = 1;
        //encontrar mínimo entre la posicion actual de cada buffer
        int64_t min = INT64_MAX; //máximo valor posible
        int indice_min;
        for (int i=0; i<n; i++) {
            if (!terminados[i]) { //solo se busca entre los archivos sin terminar
                if (buffers[i][pos[i]] < min) {
                    min = buffers[i][pos[i]];
                    indice_min = i;
                }
            }
        }
        buffer_salida[pos_salida] = min; //escribir mínimo en buffer de salida
        pos_salida++; //aumentar posición en buffer de salida
        pos[indice_min]++; //aumentar posición en buffer correspondiente
        cont[indice_min]++; //aumentar contador en buffer correspondiente
        if (pos_salida == E) { //buffer de salida está lleno
            fwrite(buffer_salida, T, E, salida); //escribir bloque
            accesos++;
            pos_salida = 0;
        }
        if (cont[indice_min] == elementos[indice_min]) { //se escribieron todos los elementos del archivo correspondiente
            terminados[indice_min] = 1; //se marca como terminado
            for (int i=0; i<n; i++) {
                listo &= terminados[i]; //si falta algún archivo por terminar, listo queda en 0
            }
        }
        else { //aún faltan elementos por leer
            if (pos[indice_min] == E) { //se escribieron todos los elementos del buffer
                fread(buffers[indice_min], T, E, archivos[indice_min]); //leer siguiente bloque
                accesos++;
                pos[indice_min] = 0;
            }
        }
    }
    if (pos_salida > 0) {
        fwrite(buffer_salida, T, pos_salida, salida); //escribir último bloque del archivo
        accesos++;
    }
    //liberar buffers y eliminar archivos
    for (int i=0; i<n; i++) {
        free(buffers[i]);
        fclose(archivos[i]);
        remove(nombres[i]);
    }
    free(buffer_salida);

    fclose(salida);

    return accesos;
}
