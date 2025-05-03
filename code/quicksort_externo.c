#include "quicksort_externo.h"

/**
   * @brief Ordena un arreglo de enteros en memoria externa utilizando el algoritmo quicksort.
   *
   * Esta función ordena un archivo binario de N bytes de enteros de 64 bits mediante
   * el algoritmo de quicksort en memoria externa, usando a-1 pivotes para particionar el arreglo
   * original. Retorna la cantidad de accesos a la memoria externa.
   * 
   * @param A: nombre del archivo a ordenar
   * @param a: cantidad de subarreglos a generar al particionar
   * @param N: tamaño en bytes de A
   * @return int: cantidad de accesos a memoria externa
   * @throws Termina el programa si no puede abrir el archivo o si hay un error al crear los 
   * archivos de los subarreglos o al asignar memoria para malloc.
   */
int quicksort_externo(const char *A, int a, int64_t N) {
    //contador de accesos
    int accesos = 0;

    //abrir archivo de entrada
    FILE* archivo = fopen(A, "rb+");
    if (!archivo) {
        perror("Error al abrir archivo de entrada");
        exit(1);
    }

    int64_t cant_bloques = (N + B - 1) / B; //cantidad de bloques del archivo
    int64_t cant_num = N/T; //cantidad de enteros en el archivo

    //caso base
    if (N <= M) { //leer archivo por bloques y guardarlos en un arreglo, luego ordenar arreglo y escribirlo por bloques 
        int64_t* arreglo_a_ordenar = malloc(N);
        if (arreglo_a_ordenar == NULL) {
            perror("Error al asignar memoria");
            exit(1);
        }

        int64_t i_a = 0; //cantidad de enteros escritos en arreglo a ordenar 
        int64_t i_arch = 0; //cantidad de enteros escritos en archivo final 
        
        //leer archivo y lenar el arreglo en RAM
        for (int64_t i = 0; i < cant_bloques; i++) { //recorro los bloques
            int64_t *bloque_i = malloc(B);
            if (bloque_i == NULL) {
                perror("Error al asignar memoria");
                exit(1);
            }
            int leidos = fread(bloque_i, T, E, archivo);
            accesos++;
            for (int k = 0; k < leidos; k++) {
                arreglo_a_ordenar[k + i_a] = bloque_i[k];
            }
            i_a += leidos;
            free(bloque_i);
        }

        //ordenar arreglo usando quicksort en RAM
        quicksort_RAM(arreglo_a_ordenar, 0, cant_num-1); //CAMBIAR A QUICKSORT
        

        //escribir arreglo ordenado en el archivo original
        fseek(archivo, 0, SEEK_SET);
        for(int64_t i = 0; i < cant_bloques-1; i++){
            int64_t *bloque_i = malloc(B);
            if (bloque_i == NULL) {
                perror("Error al asignar memoria");
                exit(1);
            }
            for (int k = 0; k < E; k++) {
                bloque_i[k] = arreglo_a_ordenar[k + i_arch];
            }
            int escritos = fwrite(bloque_i , T, E, archivo);
            accesos++;
            i_arch += escritos;
            free(bloque_i);
        }
        //escribir último bloque
        int64_t *bloque_final = malloc(B);
        if (bloque_final == NULL) {
            perror("Error al asignar memoria");
            exit(1);
        }
        for (int k = 0; k < i_a-i_arch; k++) {
            bloque_final[k] = arreglo_a_ordenar[k + i_arch];
        }
        int escritos = fwrite(bloque_final , T, i_a-i_arch, archivo);
        accesos++;
        i_arch += escritos;
        free(bloque_final);
        free(arreglo_a_ordenar);

        //cerrar archivo y retornar
        fclose(archivo);
        return accesos; 
    }
    //caso recursivo
    else{ //N>M, dividir el archivo en a subarreglos
        //crear arreglos auxiliares
        int64_t **arreglo_en_RAM = malloc(a * sizeof(int64_t*)); //arreglo_en_RAM[a][E] para guardar los bloques de subarreglos
        if (arreglo_en_RAM == NULL) {
            perror("Error al asignar memoria");
            exit(1);
        }
        int cnt_sub_RAM[a]; //cnt_sub_RAM[a] para guardar los contadores de cada subarreglo
        int64_t N_subarreglos[a]; //arreglo de enteros para almacenar los bytes escritos en cada archivo

        char nombres_archivos[a][32]; //arreglo 2D para guardar los nombres de los archivos
        FILE* subarreglos[a]; //arreglo de cursores de los archivos

        //crear archivos e inicializar arreglos auxiliares
        for (int i = 0; i < a; i++) {
            arreglo_en_RAM[i] = malloc(B);
            if (arreglo_en_RAM[i] == NULL) {
                perror("Error al asignar memoria");
                exit(1);
            }
            cnt_sub_RAM[i] = 0;
            N_subarreglos[i] = 0;
            snprintf(nombres_archivos[i], sizeof(nombres_archivos[i]), "%s_%d.bin", A, i); //guarda un nombre único para cada archivo
            subarreglos[i] = fopen(nombres_archivos[i], "wb");
            if (subarreglos[i] == NULL) {
                perror("Error al crear archivo");
                for (int j = 0; j < i; j++) {
                    fclose(subarreglos[j]);
                }
                exit(1);
            }
        }

        //leer archivo de entrada por bloques
        int64_t pivotes[a-1]; //arreglo de pivotes
        for (int64_t i = 0; i < cant_bloques; i++) { //recorro los bloques
            int64_t *bloque_i = malloc(B);
            if (bloque_i == NULL) {
                perror("Error al asignar memoria");
                exit(1);
            }
            int leidos = fread(bloque_i, T, E, archivo);
            accesos++;
            if (i == 0) { // bloque_i es el primero, saco pivotes
                for (int j = 0; j < a-1; j++) {
                    pivotes[j] = bloque_i[j];
                }
                
                mquicksort_RAM(pivotes, 0, a-2); 
                
            }
            for (int l = 0; l < leidos; l++) { //recorrer bloque en RAM
                int64_t num = bloque_i[l]; 
                for (int j = 0; j < a; j++) { //recorrer pivotes, guardar el elemento en el subarreglo correspondiente
                    if (num <= pivotes[j] || j == a-1) { //si el elemento es menor o igual al pivote, lo guardo en el subarreglo
                        arreglo_en_RAM[j][cnt_sub_RAM[j]] = num;
                        cnt_sub_RAM[j]++;
                        if (cnt_sub_RAM[j] == E) { //si el bloque se llena, lo guardo en el subarreglo
                            fwrite(arreglo_en_RAM[j], T, cnt_sub_RAM[j], subarreglos[j]); //escribo el bloque en el subarreglo
                            accesos++;
                            N_subarreglos[j] += B;
                            cnt_sub_RAM[j] = 0;
                        }
                        break;
                    } 
                }
            }
            free(bloque_i);
        }
        //escribir los bloques restantes en disco
        for (int j = 0; j < a; j++) {
            if (cnt_sub_RAM[j] > 0) { //si el bloque no está vacío
                fwrite(arreglo_en_RAM[j], T, cnt_sub_RAM[j], subarreglos[j]);
                accesos++;
                N_subarreglos[j] += cnt_sub_RAM[j]*T;
            }
        }
        
        //ordenar recursivamente los subarreglos
        for (int i = 0; i < a; i++) {
            free(arreglo_en_RAM[i]);
            fclose(subarreglos[i]);
            accesos += quicksort_externo(nombres_archivos[i], a, N_subarreglos[i]);
        }
        free(arreglo_en_RAM);

        //concatenar archivos
        fclose(archivo);
        accesos += concatenar_externo(a, nombres_archivos, N_subarreglos, A);

        return accesos;
    }    
}