#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

#define B 512 //Tamaño de un bloque en bytes
#define M (50 * 1024 * 1024) //Tamaño de la RAM en bytes
#define T sizeof(int64_t) //Tamaño de cada entero del input en bytes
#define E (B / T) //Cantidad de enteros por bloque

#endif //CONSTANTES_H