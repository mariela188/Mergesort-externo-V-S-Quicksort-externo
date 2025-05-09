# Mergesort externo V/S Quicksort externo
Tarea 1 del Ramo CC4102 - Diseño y Análisis de Algoritmos

## Contenido
Para esta tarea, la organización del trabajo sigue el siguiente formato:

- `src/`: Código fuente
  - `tarea1.h`: librerias, deifiniciones y encabezado de funciones.
  - `mergesort_externo.c`: implementación de algoritmo de mergesort en memoria externa.
  - `quicksort_externo.c`: implementación de algoritmo de quicksort en memoria externa.
  - `util.c`: implementación de función que genera archivos y otras funciones auxiliares utilizadas.
  - `verificar_algoritmos.c`: código para verificar si los archivos resultantes de los algortimos están correctamente ordenados.
  - `obtener_a.c`: código para la obtención de la aridad óptima para Mergesort externo.
  - `test_docker.c`: código de prueba para testear el contenedor de Docker. 
  - `comparar_algoritmos.c`: código para comparar los algortimos en tiempo y accesos a disco.

- `bin/`: Archivos ejecutables
  - `obtener_a`: ejecutable para obtener la aridad óptima para Mergesort externo.
  - `verificar_algoritmos`: ejecutable para verificar correcto funcionamiento de los algoritmos.
  - `test_docker`: ejecutable para probar el funcionamiento de los algoritmos en el contenedor de Docker.
  - `comparar_algoritmos`: ejecutable para realizar la comparación de los resultados de los algoritmos.

- `data/`: Archivos binarios 


## Instrucciones para correr el código
### Compilación
Para compilar los ejecutables se deben correr los siguientes comandos:
- verificar algoritmos:
  ```bash
  gcc src/mergesort_externo.c src/quicksort_externo.c src/util.c src/verificar_algoritmos.c -o bin/verificar_algoritmos
  ```
- obtener a:
  ```bash
  gcc src/mergesort_externo.c src/util.c src/obtener_a.c -o bin/obtener_a
  ```
- test docker:
  ```bash
  gcc src/mergesort_externo.c src/quicksort_externo.c src/util.c src/test_docker.c -o bin/test_docker
  ```
- comparar algoritmos:
  ```bash
  gcc src/mergesort_externo.c src/quicksort_externo.c src/util.c src/comparar_algoritmos.c -o bin/comparar_algoritmos
  ```
### Uso
Para correr cada programa se deben correr los siguientes comandos:
- verificar algoritmos:
  ```bash
  ./bin/verificar_algoritmos
  ```
- obtener a:
  ```bash
  ./bin/obtener_a
  ```
- test docker:
  ```bash
  ./bin/test_docker
  ```
- comparar algoritmos:
  ```bash
  ./bin/comparar_algoritmos
  ```

