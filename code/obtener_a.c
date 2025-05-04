#include "constantes.h"
#include "mergesort_externo.h"

int obtener_a(char *A, int64_t N, int l, int r) {
    if (r-l < 4) { //si el rango es pequeño se prueban todos los valores
        int min = INT32_MAX;
        int a = l;
        for (int i=l; i<=r; i++) {
            int resultado = mergesort_externo(A, i, N);
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
        int fm1 = mergesort_externo(A, m1, N);
        int fm2 = mergesort_externo(A, m1, N);
        if (fm1 < fm2) {
            return obtener_a(A, N, m1, r);
        }
        else if (fm1 > fm2) {
            return obtener_a(A, N, l, m2);
        }
        else {
            return obtener_a(A, N, m1, m2);
        }
        
    }
}

int main() {
    int64_t N = (int64_t)60*M;
    int a = obtener_a("data/A.bin", N, 2, E);
    printf("valor de a óptimo: %d\n", a);
}