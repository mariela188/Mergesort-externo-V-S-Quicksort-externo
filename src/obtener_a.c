#include "tarea1.h"

int obtener_a(const char *A, int64_t N, int l, int r) {
    printf("Buscando en tramo [%d, %d]\n", l, r);
    char *A_copia; 
    if (r-l < 4) { //si el rango es pequeño se prueban todos los valores
        int min = INT32_MAX;
        int a = l;
        for (int i=l; i<=r; i++) {
            printf("(Caso base) Probando con a = %d\n", i);
            A_copia = copiar_archivo_bin(A);
            int resultado = mergesort_externo(A_copia, i, N);
            remove(A_copia);
            free(A_copia);
            if (resultado < min) {
                min = resultado;
                a = i;
            }
        }
        return a;
    }
    else { //búsqueda ternaria
        int m1 = l + (r-l)/3;
        int m2 = r - (r-l)/3;
        printf("(m1) Probando con a = %d\n", m1);
        A_copia = copiar_archivo_bin(A);
        int accesos_m1 = mergesort_externo(A_copia, m1, N);
        remove(A_copia);
        free(A_copia);
        printf("(m2) Probando con a = %d\n", m2);
        A_copia = copiar_archivo_bin(A);
        int accesos_m2 = mergesort_externo(A_copia, m2, N);
        remove(A_copia);
        free(A_copia);
        if (accesos_m1 < accesos_m2) {
            return obtener_a(A, N, m1, r);
        }
        else if (accesos_m1 > accesos_m2) {
            return obtener_a(A, N, l, m2);
        }
        else {
            return obtener_a(A, N, m1, m2);
        }
    }
}

int main() {
    int64_t N = (int64_t)60 * M;
    generar_input(N, "data/A_prueba.bin");
    int a = obtener_a("data/A_prueba.bin", N, 2, E);
    printf("Valor optimo: a = %d\n", a);
}