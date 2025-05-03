#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

#define B 512 //Tamaño en bytes de un bloque
#define M (50 * 1024 * 1024) //Tamaño en bytes de la memoria principal (RAM)
#define T sizeof(int64_t) //Tamaño en bytes de cada entero del input
#define E (B / T) //Cantidad máxima de enteros por bloque

#endif // CONSTANTES_H