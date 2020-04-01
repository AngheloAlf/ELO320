NOMBRES Y APELLIDOS
ROL USM
EMAILS

Archivos:
- `main.c`: Contiene el programa principal a ser ejecutado.
- `hashtable.c`/`.h`: Contiene las definiciones/declaraciones que implementan el objeto tabla hash y funciones para poder trabajar con dicho objeto.
- `hashfunctions.c`/`.h`: Contiene las definiciones/declaraciones de las funciones hash especificadas en la tarea.
- `utils.c`/`.h`: Contiene las definiciones/declaraciones de funciones generales. En este caso contiene funciones para manejar números aleatorios más comodamente.

Como compilar:
- Ejecutar comando `make`: Genera el ejecutable llamado `tarea1`.
- Ejecutar comando `make debug`: Genera el ejecutable `tarea1`, pero con flags de debug activadas.
- Ejecutar comando `make clean`: Limpia archivos generados y borra el ejecutable.

Particularidades del programa:
- Si un error ocurre en la alocación de memoria, el programa muestra un mensaje de error y finaliza inmediatamente.
