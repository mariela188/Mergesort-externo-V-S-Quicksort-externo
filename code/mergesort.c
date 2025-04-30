#include "mergesort_RAM.c"
#include "merge.c"

#include <stdlib.h>
#include <sys/time.h>


/**
   * @brief Ordena un arreglo de enteros en memoria externa utilizando el algoritmo Quiqksort.
   *
   * Esta función
   * 
   * @param A: puntero a un archivo a ordenar
   * @param B: tamaño del bloques
   * @param M: tamaño de RAM
   * @param a: cantidad de subarreglos
   * @param N: tamaño en bytes de A
   * @return: Int cantidad de accesos a memoria
   * @throws Termina el programa si no puede abrir el archivo o hay un error al crear los archivos de los subarreglos.
   */
int Quicksort_externo( FILE *A , int B, int M, int a, int N) {
    FILE* archivo = fopen(A, "rb");
    if (!archivo) {
        perror("Error al abrir archivo de entrada");
        exit(1);
    }

    //cantidad de números en un bloque
    int E= B / sizeof(int)

    int bloque1[E];
    size_t leidos;
    fread(bloque1, sizeof(int), B / sizeof(int), archivo);
    int pivotes[a-1];
    for (i = 0, i<a, i++){
        pivotes[i] = bloque1[i];
    }
    int pivotes_aux[a-1] = malloc((a-1)* sizeof(int));
    mergesort(pivotes, pivotes_aux, 0, a-1);

    int arreglo_en_RAM[a][b];
    int contadores_en_RAM[a][b];

    //creo archivos para cada subarreglo
    FILE* subarreglos[a];
    char nombre[32];

    for (int i = 0; i < A; i++) {
        snprintf(nombre, sizeof(nombre), "temp_%d.bin", i);  // genera nombre
        subarreglos[i] = fopen(nombre, "wb");                   // crea archivo binario

        if (subarreglos[i] == NULL) {
            perror("Error al crear archivo");
            // cerrar los archivos abiertos antes de salir
            for (int j = 0; j < i; j++) {
                fclose(subarreglos[j]);
            }
            exit(1);
        }
    }

    //primer bloque en RAM
    //recorro el bloque con i
    for (int i = 0; i < E; i++) {
        num= bloque1[i];
        //guardo los elementos en el subarreglo correspondiente
        //recorro pivotes con j
        for (int j = 0; j < a; j++) {
            if (num <= pivotes[j] || j==a-1){
                cantidad_de_elementos= contadores_en_RAM[j];
                arreglo_en_RAM[j][cantidad_de_elementos] = num;
                contadores_en_RAM[j]++;

                //si el bloque se llena, lo guardo en el subarreglo
                if (contadores_en_RAM[j] == E){
                    //escribo el bloque en el archivo[]
                    fopen(subarreglos[j], "wb");
                    fwrite(arreglo_en_RAM[j], sizeof(int), E, subarreglos[j]);
                    fclose(subarreglos[j]);
                    //vacio el bloque
                    contadores_en_RAM[j] = 0;
                }
                break;
            } 
        }

    }




    fclose(archivo);



}