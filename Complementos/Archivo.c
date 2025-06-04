#include "../include.h"
//**CONSIDERACION**
//al trabajar con archivos tienen que programarlas en base a donde se encuentra el ejecutable, no ah donde se programa la funcion.

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

//FUNCIONES DE LECTURA

void leerAgenda(Estudiante* estudiante) {
    FILE* archivo = fopen("Usuario/Calendario/agenda.csv", "r");
    if (!archivo) {
        perror("Error al abrir agenda.csv");
        return;
    }

    char** campos;
    campos = leer_linea_csv(archivo, ','); // leer encabezado y descartarlo

    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
        int dia = atoi(campos[0]);
        int mes = atoi(campos[1]);

        // Ajustamos a índices de 0 a 30 y 0 a 11
        Dia* d = &estudiante->meses[mes - 1].dias[dia - 1];
        d->numero = dia;

        // Crear y poblar estructura Agenda
        Agenda* evento = malloc(sizeof(Agenda));
        strcpy(evento->nombre, campos[2]);
        strcpy(evento->descripcion, campos[3]);
        evento->estado = (strcmp(campos[4], "1") == 0 || strcmp(campos[4], "true") == 0);

        if (d->agenda == NULL) {
            d->agenda = list_create();
        }
        list_pushBack(d->agenda, evento);

        free(campos);
    }

    fclose(archivo);
}

void leerCurso(Estudiante* estudiante) {
    FILE* archivo = fopen("Usuario/Cursos/cursos.csv", "r");
    if (!archivo) {
        perror("Error al abrir cursos.csv");
        return;
    }

    char** campos;
    campos = leer_linea_csv(archivo, ','); // leer encabezado y descartarlo

    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
        int id = atoi(campos[0]);

        Curso* curso = malloc(sizeof(Curso));
        inicializarCurso(curso, id);
        strcpy(curso->nombre, campos[1]);

        map_insert(estudiante->cursos, curso->nombre, curso);

        free(campos);
    }

    fclose(archivo);
}

void leerRepaso(Estudiante* estudiante) {
    FILE* archivo = fopen("Usuario/Cursos/repasos.csv", "r");
    if (!archivo) {
        perror("Error al abrir repasos.csv");
        return;
    }

    char** campos;
    campos = leer_linea_csv(archivo, ','); // leer encabezado y descartarlo

    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
        int idCurso = atoi(campos[0]);
        int idRepaso = atoi(campos[1]);

        Repaso* repaso = malloc(sizeof(Repaso));
        repaso->id = idRepaso;
        repaso->preguntas = NULL;
        repaso->cantidadPreguntas = 0;
        repaso->puntuacionPromedio = atoi(campos[2]);
        repaso->puntuacionPromedioAnterior = atoi(campos[3]);

        Curso* curso = NULL;
        for (MapPair* pair = map_first(estudiante->cursos); pair != NULL; pair = map_next(estudiante->cursos)) {
            Curso* c = pair->value;
            if (c->id == idCurso) {
                curso = c;
                break;
            }
        }
        if (curso == NULL) {
            free(repaso);
            free(campos);
            continue;
        }

        if (curso->repaso == NULL) {
            curso->repaso = list_create();
            if (curso->repaso == NULL) {
                free(repaso);
                free(campos);
                fclose(archivo);
                return;
            }
        }

        list_pushFront(curso->repaso, repaso);

        free(campos);
    }

    fclose(archivo);
}

void leerPreguntas(Estudiante* estudiante) {
    FILE* archivo = fopen("Usuario/Cursos/preguntas.csv", "r");
    if (!archivo) {
        perror("Error al abrir preguntas.csv");
        return;
    }

    char** campos;
    campos = leer_linea_csv(archivo, ','); // leer encabezado y descartarlo

    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
        int idCurso = atoi(campos[0]);
        int idRepaso = atoi(campos[1]);

        Pregunta* pregunta = malloc(sizeof(Pregunta));
        strcpy(pregunta->pregunta, campos[2]);
        strcpy(pregunta->respuesta, campos[3]);
        pregunta->puntuacion = atoi(campos[4]);

        Curso* curso = NULL;
        for (MapPair* pair = map_first(estudiante->cursos); pair != NULL; pair = map_next(estudiante->cursos)) {
            Curso* c = pair->value;
            if (c->id == idCurso) {
                curso = c;
                break;
            }
        }
        if (curso == NULL) {
            free(pregunta);
            free(campos);
            continue;
        }

        int encontrado = 0;
        for (size_t i = 0; i < list_size(curso->repaso); i++) {
            Repaso* repaso = list_get(curso->repaso, i);
            if (repaso->id == idRepaso) {
                if (repaso->preguntas == NULL) {
                    repaso->preguntas = malloc(sizeof(Pregunta*) * 10);
                }
                if (repaso->cantidadPreguntas % 10 == 0 && repaso->cantidadPreguntas > 0) {
                    repaso->preguntas = realloc(repaso->preguntas, sizeof(Pregunta*) * (repaso->cantidadPreguntas + 10));
                }
                repaso->preguntas[repaso->cantidadPreguntas++] = pregunta;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            free(pregunta);
        }

        free(campos);
    }

    fclose(archivo);
}

void leerNotas(Estudiante* estudiante) {
    FILE* archivo = fopen("Usuario/Cursos/notas.csv", "r");
    if (!archivo) {
        perror("Error al abrir notas.csv");
        return;
    }

    char** campos;
    campos = leer_linea_csv(archivo, ','); // leer encabezado y descartarlo

    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
        int idCurso = atoi(campos[0]);

        Nota* nota = malloc(sizeof(Nota));
        nota->nota = atoi(campos[1]);
        nota->ponderacion = atof(campos[2]);

        Curso* curso = NULL;
        for (MapPair* pair = map_first(estudiante->cursos); pair != NULL; pair = map_next(estudiante->cursos)) {
            Curso* c = pair->value;
            if (c->id == idCurso) {
                curso = c;
                break;
            }
        }
        if (curso == NULL) {
            free(nota);
            free(campos);
            continue;
        }
        list_pushBack(curso->notas, nota);

        free(campos);
    }

    fclose(archivo);
}