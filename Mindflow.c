#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "Complementos/extra.h"
#include "Complementos/list.h"
#include "Complementos/map.h"
#include "Complementos/estructuras.h"
#include "Complementos/equal.h"

void inicializarCurso(Curso *curso, int id){
    curso->id = id; // Asignar un ID automático, podriamos usar el size del map cursos
    strcpy(curso->nombre, ""); // Inicializar el nombre del curso como vacío
    curso->notas = list_create(); // Crear una lista para las notas
    curso->repaso = list_create(); // Crear una lista para los repasos
}

void inicializarCalendario(Mes meses[], int year) {
    const char *nombres[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio","Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    int dias_por_mes[] = {31, 28, 31, 30, 31, 30,31, 31, 30, 31, 30, 31};

    // Verifica año bisiesto para febrero
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) dias_por_mes[1] = 29;

    for (int i = 0; i < 12; i++) {
        strcpy(meses[i].nombre, nombres[i]);
        meses[i].numero = i + 1;
        for (int d = 0; d < dias_por_mes[i]; d++) {
            meses[i].dias[d].numero = d + 1;
            
            // Inicializa la lista de eventos del día
            meses[i].dias[d].agenda = list_create();
            
            // Inicializa los eventos relevantes a falso
            for (int k = 0; k < 3; k++) meses[i].dias[d].relevante[k] = false;
        }

        // Marca como inválidos los días que no existen en el mes
        for (int d = dias_por_mes[i]; d < 31; d++) {
            meses[i].dias[d].numero = 0;
            meses[i].dias[d].agenda = NULL;
            for (int k = 0; k < 3; k++) meses[i].dias[d].relevante[k] = false;
        }
    }
}


void inicializarEstudiante(Estudiante *estudiante, int yearActual) {
    estudiante->cursos = map_create(string_equal, string_hash);
    inicializarCalendario(estudiante->meses, yearActual);
}

//FUNCION PARA DEBUGEAR
void imprimirEstudiante(const Estudiante *estudiante) {
    printf("===== INFORMACIÓN DEL ESTUDIANTE =====\n");
    // Imprimir cursos
    printf("\nCursos registrados:\n");
    if (estudiante->cursos->size == 0) {
        printf("  (Ningún curso registrado aún)\n");
    } else {
        MapPair *par = map_first(estudiante->cursos);
        while (par != NULL) {
            Curso *curso = (Curso *)par->value;
            printf("  - Curso ID: %d, Nombre: %s\n", curso->id, curso->nombre);
            // Notas
            printf("    Notas:\n");
            List *notas = curso->notas;
            if (list_size(notas) == 0) {
                printf("      (Sin notas registradas)\n");
            } else {
                for (Nota *n = list_first(notas); n != NULL; n = list_next(notas)) {
                    printf("      Nota: %d, Ponderación: %.2f\n", n->nota, n->ponderacion);
                }
            }
            // Repasos
            printf("    Repasos:\n");
            List *repasos = curso->repaso;
            if (list_size(repasos) == 0) {
                printf("      (Sin repasos registrados)\n");
            } else {
                for (Repaso *r = list_first(repasos); r != NULL; r = list_next(repasos)) {
                    printf("      Repaso (Puntaje Actual: %d, Anterior: %d)\n", r->puntuacionPromedio, r->puntuacionPromedioAnterior);
                    for (Pregunta *p = list_first(r->preguntas); p != NULL; p = list_next(r->preguntas)) {
                        printf("        Pregunta: %s\n        Respuesta: %s\n        Puntuación: %d\n", p->pregunta, p->respuesta, p->puntuacion);
                    }
                }
            }
            par = map_next(estudiante->cursos);
        }
    }
    // Imprimir calendario
    printf("\nCalendario:\n");
    for (int i = 0; i < 12; i++) {
        Mes mes = estudiante->meses[i];
        printf("  Mes: %s (%d)\n", mes.nombre, mes.numero);
        for (int d = 0; d < 31; d++) {
            if (mes.dias[d].numero == 0) continue; // día no válido
            printf("    Día %2d: ", mes.dias[d].numero);
            bool hayAlgo = false;
            if (mes.dias[d].relevante[0]) { printf("[Examen] "); hayAlgo = true; }
            if (mes.dias[d].relevante[1]) { printf("[Control] "); hayAlgo = true; }
            if (mes.dias[d].relevante[2]) { printf("[Trabajo] "); hayAlgo = true; }
            if (!hayAlgo) printf("(sin eventos relevantes)");
            printf("\n");
            List *agenda = mes.dias[d].agenda;
            for (Agenda *a = list_first(agenda); a != NULL; a = list_next(agenda)) {
                printf("      - Evento: %s\n        Descripción: %s\n        Estado: %s\n",
                    a->nombre, a->descripcion, a->estado ? "Realizado" : "Pendiente");
            }
        }
    }
    printf("=======================================\n");
}
//

//Main
int main(){
    SetConsoleOutputCP(CP_UTF8);
    Estudiante estudiante;
    //obtener año actual
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    int yearActual = tm_info->tm_year + 1900;
    inicializarEstudiante(&estudiante,yearActual);
    //imprimirEstudiante(&estudiante);
    return 0;
}