#include <stdio.h>
/**
   * @brief Funcion que hace merge a arreglos en memoria externa.
   *
   * Esta función recibe un lista de archivos ordenados de manera
   * ascendente y los mergea en un solo archivo de salida.
   * 
   * @param B: tamaño del bloque
   * @param cant_archivos: tamaño de lista de archivos a mergear
   * @param nom_archivos: lista de nombres de archivos a mergear
   * @param tam_arch: tamaño de cada archivo a mergear
   * @return: Int cantidad de accesos a memoria
*/
char * merge_externo(int B, int cant_archivos, char *nom_archivos[], int tam_arch[]){
    //archivo final donde unir todos los archivos
    FILE *archivo_final = fopen("salida.txt", "w"); // "w" = write (escribir)
    if (!archivo_final) {
        perror("Error al abrir archivo de salida");
        exit(1);
    }
    //recorrer archivos a unir
    for (int i = 0; i < cant_archivos; i++) {
        FILE *archivo = fopen(nom_archivos[i], "rb");
        if (!archivo) {
            perror("Error al abrir un archivo de entrada");
            exit(1);
        }
        //cantidad de números en un bloque
        int E= B / sizeof(int)

        

        // traigo bloques a memoria 
        for(int j = 0; j < tam_arch[i] / sizeof(int); j++) {
            
            int bloque1[E];
            size_t leidos;
            fread(bloque1, sizeof(int), B / sizeof(int), archivo);


        }
        fread(archivo[i], sizeof(int), tam_arch[i] / sizeof(int), archivo);
        fclose(archivo);
    }

}