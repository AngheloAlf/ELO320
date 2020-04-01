NOMBRES Y APELLIDOS
ROL USM
EMAILS

Archivos:
- `main.c`: Contiene el programa principal a ser ejecutado, y la función para generar el network-config.txt.
- `constants.h`: Se define el rango de los ids y de los Gbps.
- `edge.c`/`.h`: Contiene estructura de arco y una lista de arcos, más las funciones respectivas para manejar estas estructuras.
- `intmap.c`/`.h`: Es una estructura para manejar la no-duplicidad de las ids generadas.
- `subset.c`/`.h`: Estructura subset requerida para el algoritmo kruskal.
- `graph.c`/`.h`: Estructura grafo y funciones para manejarlo, más el algoritmo de kruskal.
- `utils.c`/`.h`: Contiene funciones para manejar números aleatorios más comodamente.

Como compilar:
- Ejecutar comando `make`: Genera el ejecutable llamado `tarea2`.
- Ejecutar comando `make debug`: Genera el ejecutable `tarea2`, pero con flags de debug activadas.
- Ejecutar comando `make clean`: Limpia archivos generados y borra el ejecutable.

Particularidades del programa:
- Al programa se le debe entregar como parametro la cantidad de nodos a considerar, el nombre de el archivo matriz (connectionMatrix.txt) y el nombre del archivo de configuración a generar (network-config.txt).
  - Un ejemplo de ejecución sería: `./tarea2 1000 connectionMatrix.txt network-config.txt`
- Ya que las ids se generan aleatoriamente, el programa genera un archivo `nodes_ids.txt` donde se indica que id se le asigno a que nodo.
- Si un error ocurre en la alocación de memoria, el programa muestra un mensaje de error y finaliza inmediatamente.
