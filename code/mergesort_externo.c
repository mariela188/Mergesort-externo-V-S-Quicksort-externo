#include "mergesort_externo.h"


/**
   * @brief Ordena un arreglo de enteros en memoria externa utilizando el algoritmo mergesort.
   *
   * Esta función ordena un archivo binario de N bytes de enteros de 64 bits mediante
   * el algoritmo de mergesort en memoria externa, dividiendolo en 'a' subarreglos. 
   * Retorna la cantidad de accesos a la memoria externa.
   * 
   * @param A: nombre del archivo a ordenar
   * @param a: cantidad de subarreglos a generar (aridad)
   * @param N: tamaño en bytes de A
   * @return int: cantidad de accesos a memoria
   * @throws Termina el programa si no puede abrir el archivo o si hay un error al crear los 
   * archivos de los subarreglos o al asignar memoria para malloc.
   */
int mergesort_externo(const char *A, int a, int N) {
    //contador de accesos
    int accesos = 0;

    //abrir archivo de entrada
    FILE* archivo = fopen(A, "rb+");
    if (!archivo) {
        perror("Error al abrir archivo de entrada");
        exit(1);
    }
   
    //caso base (listo)
    if (N <= M) {
        int cant_bloques = (N + B - 1) / B; //cantidad de bloques del archivo
        int cant_num = N/T; //cantidad de enteros en el archivo
        int64_t* arreglo_a_ordenar = malloc(N);
        if (arreglo_a_ordenar == NULL) {
            perror("Error al asignar memoria");
            exit(1);
        }

        int i_a = 0; //cantidad de enteros escritos en arreglo a ordenar 
        int i_arch = 0; //cantidad de enteros escritos en archivo final 
        
        //llenar el arreglo en RAM
        for (int i = 0; i < cant_bloques; i++) { //recorro los bloques
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

        //ordenar arreglo usando mergesort en RAM
        int64_t* aux = malloc(N);
        if (aux == NULL) {
            perror("Error al asignar memoria");
            exit(1);
        }
        mergesort_RAM(arreglo_a_ordenar, aux, 0, cant_num-1);
        free(aux);

        //escribir arreglo ordenado en el archivo original
        fseek(archivo, 0, SEEK_SET);
        for(int i = 0; i < cant_bloques-1; i++){
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
    else { // N>M
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