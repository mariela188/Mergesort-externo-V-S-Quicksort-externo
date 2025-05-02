#include "mergesort_RAM.c"
#include "merge_qs.c"

#include <stdlib.h>
#include <sys/time.h>
#include "constantes.h"


/**
   * @brief Ordena un arreglo de enteros en memoria externa utilizando el algoritmo Mergesort.
   *
   * Esta función
   * 
   * @param A: nombre del archivo a ordenar
   * @param a: cantidad de subarreglos
   * @param N: tamaño en bytes de A
   * @return: Int cantidad de accesos a memoria
   * @throws Termina el programa si no puede abrir el archivo o hay un error al crear los archivos de los subarreglos.
   */
int Quicksort_externo( const char *A, int a, int N){
    FILE* archivo = fopen(A, "rb+");
    if (!archivo) {
        perror("Error al abrir archivo de entrada");
        exit(1);
    }
    if(N<=M){
        int cant_bloques = (N + B - 1) / B;
        int cant_num = N/sizeof(int64_t); //cantidad de enteros en el archivo
        int64_t* arreglo_a_ordenar= malloc(N);

        int i_a= 0; //cantidad de enteros escritos en arreglo a ordenar 
        int i_arch= 0; //cantidad de enteros escritos en archivo final 
    
        for(int i=0; i< cant_bloques; i++){ //recooro los bloques
            int64_t *bloque_i = malloc(B);
            int leidos = fread(bloque_i, sizeof(int64_t), E, archivo);
            for (int k = 0; k < leidos; k++) {
                arreglo_a_ordenar[k + i_a] = bloque_i[k];
            }
            i_a += leidos;
            free(bloque_i);
        }

        int64_t* aux= malloc(N);
        mergesort_RAM(arreglo_a_ordenar, aux, 0, cant_num-1);
        free(aux);
        fseek(archivo, 0, SEEK_SET);
        for(int i=0; i< cant_bloques-1; i++){
            int64_t *bloque_i = malloc(B);
            for (int k = 0; k < E; k++) {
                bloque_i[k] = arreglo_a_ordenar[k + i_arch];
            }
            int escritos = fwrite( bloque_i , sizeof(int64_t), E, archivo);
            i_arch += escritos;
            free(bloque_i);
        }
        int64_t *bloque_i = malloc(B);
        for (int k = 0; k < i_a-i_arch; k++) {
            bloque_i[k] = arreglo_a_ordenar[k + i_arch];
        }
        int escritos = fwrite( bloque_i , sizeof(int64_t), i_a - i_arch, archivo);
        i_arch += escritos;
        free(bloque_i);
        fclose(archivo);
        free(arreglo_a_ordenar);
        int bloques = (N + B - 1) / B;
        return 2 * bloques;

    }else{ // N>M
        int lecturas = 0;
        int cant_bloques = (N + B - 1) / B;
        int cant_sub= (N / M) + 1; // cantidad de subarreglos

        //merge_ms_externo(int n, char nombres[][32], int tamanos[], const char *A);
        int tamaños[cant_sub]; //arreglo para guardar los tamaños de cada lista
        int indice_M = 0; 
        char nombres_archivos[cant_sub][32];  // Arreglo 2D para guardar los nombres de los archivos
        FILE* subarreglos[cant_sub];
        for (int i = 0; i < cant_sub; i++) {
            snprintf(nombres_archivos[i], sizeof(nombres_archivos[i]), "%d_%d.bin", A, i); // guarda el nombre
            subarreglos[i] = fopen(nombres_archivos[i], "wb");
            if (subarreglos[i] == NULL) {
                perror("Error al crear archivo");
                for (int j = 0; j < i; j++) {
                    fclose(subarreglos[j]);
                }
                exit(1);
            }
        }
        int* tamaños = malloc(cant_sub * sizeof(int));
        for (int i = 0; i < a; i++) {// Inicializar a cero (si es necesario)
            tamaños[i] = 0;
        }
        //voy leyendo por bloques los elementos tq voy guardando
        //en archivos en memoria por bloque.
        //cuando un arhivo se llena (tiene tamaño N) lleno el siguiente

        for(int i=0; i< cant_bloques; i+B){ //recooro los bloques
            int leidos = fread(arreglo_M, Tamaño_bloque, 1, archivo);
            lecturas +=M;
            if(indice_M ==M){
                int escritos = fwrite(archivo, T, E, areglo_M);
                lecturas +=M;
                arreglo_M = 0;
            }
                
            
        }
                
    }
            
}
        
        
        
 