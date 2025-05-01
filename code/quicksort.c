#include "mergesort_RAM.c"
#include "merge_qs.c"

#include <stdlib.h>
#include <sys/time.h>
#include "constantes.h"


/**
   * @brief Ordena un arreglo de enteros en memoria externa utilizando el algoritmo Quiqksort.
   *
   * Esta función
   * 
   * @param A: nombre del archivo a ordenar
   * @param a: cantidad de subarreglos
   * @param N: tamaño en bytes de A
   * @return: Int cantidad de accesos a memoria
   * @throws Termina el programa si no puede abrir el archivo o hay un error al crear los archivos de los subarreglos.
   */
int Quicksort_externo( const char *A, int a, int N) {
    FILE* archivo = fopen(A, "rb+");
    if (!archivo) {
        perror("Error al abrir archivo de entrada");
        exit(1);
    }
    if(N<= M){//leer archivo por bloques y guardarlos en un arreglo. luego ordenar arreglo y escribirlo por bloques 
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
    }

    else{ //N> M, dividir el archivo en subarreglos
        int lecturas = 0;
        int cant_bloques = (N + B - 1) / B;
        int64_t** arreglo_en_RAM = malloc(a * sizeof(int64_t*));// arreglo_en_RAM[a][E] para guardar los bloques de subarreglos
        for (int i = 0; i < a; i++) {
            arreglo_en_RAM[i] = malloc(E * T);
        }
        
        int* cnt_sub_RAM = malloc(a * sizeof(int));// cnt_sub_RAM[a][E] para guardar los contadores de cada subarreglo
        for (int i = 0; i < a; i++) {
            cnt_sub_RAM[i] = 0; // Inicializamos cada contador en 0
        }

        char nombres_archivos[a][32];  // Arreglo 2D para guardar los nombres de los archivos
        FILE* subarreglos[a];

        for (int i = 0; i < a; i++) {
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

        
        // Crear un arreglo de enteros para almacenar los bytes leídos de cada archivo
        int* N_subarreglo = malloc(a * sizeof(int));
        if (N_subarreglo == NULL) {
            perror("Error al asignar memoria para N_subarreglo");
            exit(1);
        }
        for (int i = 0; i < a; i++) {// Inicializar a cero (si es necesario)
            N_subarreglo[i] = 0;
        }

        for(int i=0; i< cant_bloques; i++){ //recooro los bloques
            int64_t *bloque_i = malloc(B);
            int leidos = fread(bloque_i, T, E, archivo);
            lecturas +=1;
            int64_t pivotes[a-1]; 
            if (leidos > E) {
                perror("Error leyendo bloque");
            }
            if(i==0){// bloque_i es el primero, saco pivotes
                for (int j = 0; j < a-1; j++){
                    pivotes[j] = bloque_i[j];
                }
                int64_t * pivotes_aux = malloc((a-1)* T);
                mergesort_RAM(pivotes, pivotes_aux, 0, a-2);
                free(pivotes_aux);
            }
            for (int l= 0; l < leidos; l++) { //recorrer bloque en ram
                int64_t num = bloque_i[l]; 
                for (int j = 0; j < a; j++) { //recorrer pivotes, guardar el elemento en el subarreglo correspondiente
                    if (num <= pivotes[j] || j==a-1){ //si el elemento es menor o igual al pivote, lo guardo en el subarreglo
                        arreglo_en_RAM[j][cnt_sub_RAM[j]] = num;
                        cnt_sub_RAM[j]++;

                        if (cnt_sub_RAM[j] == E){ //si el bloque se llena, lo guardo en el subarreglo
                            fwrite(arreglo_en_RAM[j], T, cnt_sub_RAM[j], subarreglos[j]);//escribo el bloque en el subarreglo[]
                            lecturas +=1;
                            N_subarreglo[j] += B;
                            cnt_sub_RAM[j] = 0;
                        }
                        break;
                    } 
                }
                
            }
            free(bloque_i);
        }
        
        for (int j = 0; j < a; j++) {//escribir los bloques restantes en disco
            if (cnt_sub_RAM[j] > 0) { //si el bloque no está vacío
                fwrite(arreglo_en_RAM[j], T, cnt_sub_RAM[j], subarreglos[j]);
                lecturas +=1;
                N_subarreglo[j] += cnt_sub_RAM[j] * T;
            }
        }
        
        for (int i = 0; i < a; i++) {
            lecturas += Quicksort_externo(nombres_archivos[i], a, N_subarreglo[i]);
        }
        for (int i = 0; i < a; i++) {
            free(arreglo_en_RAM[i]);
            fclose(subarreglos[i]);
        }
        lecturas += merge_qs_externo(a, nombres_archivos, N_subarreglo, A);

    
        
        free(arreglo_en_RAM);
        free(cnt_sub_RAM);
       
        free(subarreglos);
        free(N_subarreglo);
        return lecturas;
    }
    fclose(archivo);
    
}