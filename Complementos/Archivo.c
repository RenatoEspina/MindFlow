#include <stdio.h>

void comprobarExistenciaArchivo() {
    const char* rutas[] = {
        "../Usuario/Cursos/cursos.csv",
        "../Usuario/Cursos/notas.csv",
        "../Usuario/Cursos/repasos.csv",
        "../Usuario/Cursos/preguntas.csv",
        "../Usuario/Calendario/agenda.csv"
    };

    for (int i = 0; i < 5; i++) {
        FILE* f = fopen(rutas[i], "r");
        if (!f) {
            f = fopen(rutas[i], "w"); // Crea el archivo vacío si no existe
            if (f) fclose(f);
        } else {
            fclose(f);
        }
    }
}

