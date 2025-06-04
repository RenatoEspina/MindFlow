#include "include.h"

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
                Nota *n = list_first(notas);
                while (n != NULL) {
                    printf("      Nota: %d, Ponderación: %.2f\n", n->nota, n->ponderacion);
                    n = list_next(notas);
                }
            }

            // Repasos
            printf("    Repasos:\n");
            List *repasos = curso->repaso;
            if (list_size(repasos) == 0) {
                printf("      (Sin repasos registrados)\n");
            } else {
                Repaso *r = list_first(repasos);
                while (r != NULL) {
                    printf("      Repaso ID: %d (Puntaje Actual: %d, Anterior: %d)\n",
                           r->id, r->puntuacionPromedio, r->puntuacionPromedioAnterior);

                    // Recorrer arreglo de preguntas
                    for (int i = 0; i < r->cantidadPreguntas; i++) {
                        Pregunta *p = r->preguntas[i];
                        printf("        Pregunta: %s\n", p->pregunta);
                        printf("        Respuesta: %s\n", p->respuesta);
                        printf("        Puntuación: %d\n", p->puntuacion);
                    }
                    r = list_next(repasos);
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
            Agenda *a = list_first(agenda);
            while (a != NULL) {
                printf("      - Evento: %s\n        Descripción: %s\n        Estado: %s\n", a->nombre, a->descripcion, a->estado ? "Realizado" : "Pendiente");
                a = list_next(agenda);
            }
        }
    }
    printf("=======================================\n");
}
//

//Main
int main(){
    int opcion;
    SetConsoleOutputCP(CP_UTF8);
    Estudiante estudiante;
    //obtener año actual
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    int yearActual = tm_info->tm_year + 1900;
    inicializarEstudiante(&estudiante,yearActual);
    leerAgenda(&estudiante);
    leerCurso(&estudiante);
    leerRepaso(&estudiante);
    leerPreguntas(&estudiante);
    leerNotas(&estudiante);
    imprimirEstudiante(&estudiante);
    printf("Ingrese su opcion preferente ");
    scanf("%d", &opcion);
    switch (opcion)
    {
    case 1:
        //calendario(estudiante, yearActual);
    
        break;
        
    case 2:
        //agenda(estudiante, yearActual);
        break;
    case 3:
        //tarjetamemoria(estudiante, yearActual);
        break;
    case 4:
        //CalculadoradeNotas(estudiante, yearActual);
        break;

    case 5:
        //printf("saliendo del programa...\n");
        break;

    default:
        printf("Opción no válida. Por favor, intente de nuevo.\n");
        break;
    }
    return 0;
}