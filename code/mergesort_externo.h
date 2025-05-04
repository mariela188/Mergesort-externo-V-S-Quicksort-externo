#include "constantes.h"

char *quitar_extension_bin(const char* nombre);
void mergesort_RAM(int64_t* arreglo, int64_t *aux, int inicio, int fin);
int merge_externo(int n, char nombres[][32], int64_t tamanos[], const char *A);
int mergesort_externo(const char *A, int a, int64_t N);