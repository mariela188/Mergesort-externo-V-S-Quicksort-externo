#include "tarea1.h"


void quicksort_RAM(int64_t* arreglo, int inicio, int fin) {
    if (inicio >= fin) return;

    int64_t pivote = arreglo[inicio];
    int izq = inicio + 1;
    int der = fin;
    
    while (izq <= der) {
        while (izq <= fin && arreglo[izq] <= pivote) izq++;
        while (der > inicio && arreglo[der] > pivote) der--;
        if (izq < der) {
            int64_t tmp = arreglo[izq];
            arreglo[izq] = arreglo[der];
            arreglo[der] = tmp;
        }
    }

    arreglo[inicio] = arreglo[der];
    arreglo[der] = pivote;

    quicksort_RAM(arreglo, inicio, der - 1);
    quicksort_RAM(arreglo, der + 1, fin);
}


int concatenar_externo(int n, char nombres[][64], int64_t tamanos[], const char *A) {
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
        quicksort_RAM(arreglo_a_ordenar, 0, cant_num-1);
        

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

        char nombres_archivos[a][64]; //arreglo 2D para guardar los nombres de los archivos
        char *nombre_base = quitar_extension_bin(A); //nombre sin extensión del archivo original
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
            snprintf(nombres_archivos[i], sizeof(nombres_archivos[i]), "%s_%d.bin", nombre_base, i); //guarda un nombre único para cada archivo
            subarreglos[i] = fopen(nombres_archivos[i], "wb");
            if (subarreglos[i] == NULL) {
                perror("Error al crear archivo");
                for (int j = 0; j < i; j++) {
                    fclose(subarreglos[j]);
                }
                exit(1);
            }
        }
        free(nombre_base);

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
                
                quicksort_RAM(pivotes, 0, a-2); 
                
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