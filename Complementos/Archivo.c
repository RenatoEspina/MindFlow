#include <stdio.h> 
#include <direct.h>

void comprobarExistenciaArchivo() {
    const char* rutas[] = {
        "Usuario/Cursos/cursos.csv",
        "Usuario/Cursos/notas.csv",
        "Usuario/Cursos/repasos.csv",
        "Usuario/Cursos/preguntas.csv",
        "Usuario/Calendario/agenda.csv"
    };

    const char *encabezados[] = {
        "idCurso,nombre",
        "idCurso,nota,ponderacion",
        "idCurso,idRepaso,promedio,promedioAnterior",
        "idCurso,idRepaso,pregunta,respuesta,puntuacion",
        "dia,mes,nombre,descripcion,estado"
    };

    // Revisa si existe la carpeta con el nombre, si no lo crea
    _mkdir("Usuario");
    _mkdir("Usuario/Cursos");
    _mkdir("Usuario/Calendario");

    // Revisa si existen los archivos .csv, si no existen, los crea con sus respectivos encabezados
    for (int i = 0; i < 5; i++) {
        FILE* f = fopen(rutas[i], "r");
        if (!f) {
            f = fopen(rutas[i], "w");
            fprintf(f, "%s\n", encabezados[i]);
            if (f) fclose(f);
        } else {
            fclose(f);
        }
    }
}
