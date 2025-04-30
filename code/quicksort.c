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
int Quicksort_externo( const char *A , int B, int M, int a, int N) {
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
        int E= B / sizeof(int64_t); //cantidad de enteros en un bloque

    
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
        free(aux);
        int bloques = (N + B - 1) / B;
        return 2 * bloques; 
    }

    else{ //N> M, elegir pivotes y dividir el archivo en subarreglos
        
        int E= B / sizeof(int64_t); //cantidad de números en un bloque
        int64_t * bloque1= malloc(B); //leeremos el bloque 1 para elegir los pivotes
        int leidos;
        fread(bloque1, sizeof(int64_t), E, archivo);
        int pivotes[a-1]; 
        for (int i = 0, i<a, i++){
            pivotes[i] = bloque1[i]
        }
        int * pivotes_aux = malloc((a-1)* sizeof(int));
        mergesort(pivotes, pivotes_aux, 0, a-1);

        int arreglo_en_RAM[a][b]; 
        int contadores_en_RAM[a][b];

        
        FILE* subarreglos[a]; //creo a archivos para escribir cada subarreglo en disco
        char nombre[32];
        for (int i = 0; i < A; i++) {
            snprintf(nombre, sizeof(nombre), "temp_%d.bin", i);  // genera nombre
            subarreglos[i] = fopen(nombre, "wb");// crea archivo binario
            if (subarreglos[i] == NULL) {
                perror("Error al crear archivo");
                for (int j = 0; j < i; j++) {//cerrar los archivos abiertos antes de salir
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
    }

 




    fclose(archivo);



}