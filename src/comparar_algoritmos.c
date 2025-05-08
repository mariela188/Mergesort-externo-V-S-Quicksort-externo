#include "tarea1.h"

int main() {
    int a = 50; //valor óptimo encontrado
    time_t inicio, fin;
    int tiempo;
    int accesos;
    char A[20];
    char *A_copia;
    int64_t N;
    int accesos_ms[75];
    int tiempos_ms[75];
    int accesos_qs[75];
    int tiempos_qs[75];
    int contador = 0; //contador para llenar arreglos
    printf("================================\n");
    for (int k=4; k<=60; k+=4) {
        printf("================================\n");
        printf("Comparacion con archivos de tamano N = %dM.\n", k);
        printf("================================\n");
        N = (int64_t)k * M;
        for (int i=1; i<=5; i++) {
            snprintf(A, sizeof(A), "data/A_%dM_%d.bin", k, i); //guardar nombre del input en A
            printf("Generando archivo %d de 5...\n", i);
            generar_input(N, A);
            printf("--------------------------------\n");
            //mergesort
            printf("Ordenando archivo con Mergesort...\n");
            A_copia = copiar_archivo_bin(A); //copiar input
            time(&inicio);
            accesos = mergesort_externo(A_copia, a, N);
            time(&fin);
            printf("Archivo ordenado.\n");
            remove(A_copia);
            free(A_copia);
            tiempo = difftime(fin, inicio);
            printf("Accesos a memoria externa: %d I/Os\n", accesos);
            printf("Tiempo de ejecucion: %d segundos\n", tiempo);
            accesos_ms[contador] = accesos;
            tiempos_ms[contador] = tiempo;
            printf("--------------------------------\n");
            //quicksort
            printf("Ordenando archivo con Quicksort...\n");
            A_copia = copiar_archivo_bin(A); //copiar input
            time(&inicio);
            accesos = quicksort_externo(A_copia, a, N);
            time(&fin);
            printf("Archivo ordenado.\n");
            remove(A_copia);
            free(A_copia);
            tiempo = difftime(fin, inicio);
            printf("Accesos a memoria externa: %d I/Os\n", accesos);
            printf("Tiempo de ejecucion: %d segundos\n", tiempo);
            accesos_qs[contador] = accesos;
            tiempos_qs[contador] = tiempo;
            printf("================================\n");
            remove(A);
            contador++;       
        }
        printf("================================\n");
    }
    printf("================================\n");
    printf("Exportando resultados a archivos CSV...\n");
    //Escribir resultados en archivos csv
    FILE *archivo_ms = fopen("resultados_mergesort.csv", "w");
    FILE *archivo_qs = fopen("resultados_quicksort.csv", "w");
    if (!archivo_ms || !archivo_qs) {
        perror("No se pudieron crear los archivos CSV");
        exit(1);
    }

    fprintf(archivo_ms, "Tamaño input,I/Os,Tiempo (s)\n");
    fprintf(archivo_qs, "Tamaño input,I/Os,Tiempo (s)\n");
    contador = 0;
    for (int k=4; k<=60; k+=4) {
        for (int i=1; i<=5; i++) {
            fprintf(archivo_ms, "%dM,%d,%d\n", k, accesos_ms[contador], tiempos_ms[contador]);
            fprintf(archivo_qs, "%dM,%d,%d\n", k, accesos_qs[contador], tiempos_qs[contador]);
            contador++;
        }
    }

    fclose(archivo_ms);
    fclose(archivo_qs);

    printf("Datos exportados a resultados_mergesort.csv y resultados_quicksort.csv.\n");

    return 0;
}