#include "tarea1.h"


void merge(int64_t* arr, int64_t* aux, int inicio, int medio, int fin) {
    int i = inicio;
    int j = medio + 1;
    int k = inicio;
    while (i <= medio && j <= fin) {
        if (arr[i] <= arr[j]) {
            aux[k++] = arr[i++];
        } else {
            aux[k++] = arr[j++];
        }
    }
    while (i <= medio) {
        aux[k++] = arr[i++];
    }
    while (j <= fin) {
        aux[k++] = arr[j++];
    }
    for (int l = inicio; l <= fin; l++) {
        arr[l] = aux[l];
    }
}


void mergesort_RAM(int64_t* arreglo, int64_t* aux, int inicio, int fin) {
    if (inicio >= fin) return;
    int medio = (inicio + fin) / 2;
    mergesort_RAM(arreglo, aux, inicio, medio);
    mergesort_RAM(arreglo, aux, medio + 1, fin);
    merge(arreglo, aux, inicio, medio, fin);
}


int merge_externo(int n, char nombres[][64], int64_t tamanos[], const char *A) {
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
    int pos[n];
    int64_t cont[n];
    int pos_salida = 0;
    int64_t cont_salida = 0;    

    //arreglo de flags para saber cuando terminar
    int terminados[n];

    //arreglo de la cantidad de elementos de cada archivo
    int64_t elementos[n];

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
    while (1) {
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
            int listo = 1;
            for (int i=0; i<n; i++) {
                listo &= terminados[i]; //si falta algún archivo por terminar, listo queda en 0
            }
            if (listo) {
                break; //si todos los archivos se escribieron completamente, se termina
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


int mergesort_externo(const char *A, int a, int64_t N) {
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
    if (N <= M) {
        int64_t* arreglo_a_ordenar = malloc(N);
        if (arreglo_a_ordenar == NULL) {
            perror("Error al asignar memoria");
            exit(1);
        }

        int64_t i_a = 0; //cantidad de enteros escritos en arreglo a ordenar 
        int64_t i_arch = 0; //cantidad de enteros escritos en archivo final 
        
        //leer archivo y llenar el arreglo en RAM
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
    else { // N > M
        int64_t div = cant_num / a; //cantidad de enteros en cada subarreglo (a priori)
        int r = cant_num % a; //resto
        int64_t tam = div * T; //tamaño en bytes de cada subarreglo (a priori)
        int64_t cant_num_sub[a]; //arreglo de la cantidad de enteros de los subarreglos
        int64_t N_sub[a]; //arreglo de los tamaños en bytes de los archivos

        char nombres_archivos[a][64]; //arreglo 2D para guardar los nombres de los archivos
        char *nombre_base = quitar_extension_bin(A); //nombre sin extensión del archivo original
        FILE* subarreglos[a]; //arreglo de cursores de los archivos

        //crear archivos para los subarreglos y llenar arreglos auxiliares
        for (int i = 0; i < a; i++) {
            snprintf(nombres_archivos[i], sizeof(nombres_archivos[i]), "%s%d.bin", nombre_base, i); //guarda un nombre único para cada archivo
            subarreglos[i] = fopen(nombres_archivos[i], "wb");
            if (subarreglos[i] == NULL) {
                perror("Error al crear archivo");
                for (int j = 0; j < i; j++) {
                    fclose(subarreglos[j]);
                }
                exit(1);
            }
            if (i < r) {
                cant_num_sub[i] = div + 1; //los primeros r tienen cant_num//a + 1 enteros
                N_sub[i] = tam + T;
            }
            else {
                cant_num_sub[i] = div; //el resto tienen cant_num//a enteros
                N_sub[i] = tam;
            }
        }
        free(nombre_base);
        
        //crear buffer de lectura y buffer de escritura
        int64_t *buffer_r = malloc(B);
        int64_t *buffer_w = malloc(B);
        if (!buffer_r || !buffer_w) {
            perror("Error al asignar memoria");
            exit(1);
        }
        int pos_w = 0; //posición en buffer de escritura

        //leer archivo de entrada y escribir en archivos de salida
        int actual = 0; //índice del archivo en que se está escribiendo
        int64_t escritos_actual = 0; //contador de elementos escritos en el archivo actual
        for(int64_t i = 0; i < cant_bloques; i++) {
            int leidos = fread(buffer_r, T, E, archivo); //leer bloque
            accesos++;
            for (int j = 0; j < leidos; j++) { //escribir elementos en buffer de escritura
                buffer_w[pos_w] = buffer_r[j];
                pos_w++;
                if (pos_w == E) { //buffer de escritura está lleno
                    if (escritos_actual+E < cant_num_sub[actual]) { //se pueden escribir E elementos
                        escritos_actual += fwrite(buffer_w, T, E, subarreglos[actual]); //escribir bloque completo
                        accesos++;
                        pos_w = 0;
                    }
                    else { //se completa el archivo actual
                        int e = cant_num_sub[actual]-escritos_actual; //cantidad de elementos para completar archivo
                        escritos_actual += fwrite(buffer_w, T, e, subarreglos[actual]); //se escriben solo los elementos que faltan
                        accesos++;
                        actual++; //se pasa al siguiente archivo
                        escritos_actual = 0;
                        //ajustar elementos restantes en el buffer de escritura
                        for (int k = e; k < E; k++) {
                            buffer_w[k-e] = buffer_w[k];
                        }
                        pos_w = E - e;
                    }
                }
            }
        }
        if (pos_w > 0) {
            fwrite(buffer_w, T, pos_w, subarreglos[a-1]); //escribir último bloque del último archivo
            accesos++;
        }

        //ordenar recursivamente los subarreglos
        for (int i=0; i<a; i++) {
            fclose(subarreglos[i]);
            accesos += mergesort_externo(nombres_archivos[i], a, N_sub[i]);
        }

        //mergear subarreglos
        fclose(archivo);
        accesos += merge_externo(a, nombres_archivos, N_sub, A);

        return accesos;
    }
}