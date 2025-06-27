#include "include.h"
void seleccionarTipodePreguntas(Curso *curso);
void repasoSecuencial(Curso *curso);
void repasoAleatorio(Curso *curso);
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





void mostrarCalendarioMensual(Estudiante estudiante, int mesSeleccionado) {
    printf("===== CALENDARIO - MES: %s =====\n", estudiante.meses[mesSeleccionado].nombre);
    
    for (int d = 0; d < 31; d++) {
        if (estudiante.meses[mesSeleccionado].dias[d].numero == 0) continue; // Día no válido
        
        printf("Día %2d: ", estudiante.meses[mesSeleccionado].dias[d].numero);
        bool hayEventos = false;
        
        if (estudiante.meses[mesSeleccionado].dias[d].relevante[0]) { printf("[Examen] "); hayEventos = true; }
        if (estudiante.meses[mesSeleccionado].dias[d].relevante[1]) { printf("[Control] "); hayEventos = true; }
        if (estudiante.meses[mesSeleccionado].dias[d].relevante[2]) { printf("[Trabajo] "); hayEventos = true; }
        if (!hayEventos) printf("(sin eventos relevantes)");
        
        printf("\n");
    }
    printf("============================\n");
}

void mostrarCalendarioDiario(Estudiante estudiante, int mesSeleccionado, int diaSeleccionado) {
    printf("===== CALENDARIO - Día: %d de %s =====\n", estudiante.meses[mesSeleccionado].dias[diaSeleccionado].numero, estudiante.meses[mesSeleccionado].nombre);
    
    List *agenda = estudiante.meses[mesSeleccionado].dias[diaSeleccionado].agenda;
    Agenda *a = list_first(agenda);
    
    if (a == NULL) {
        printf("No hay eventos para este día.\n");
    } else {
        while (a != NULL) {
            printf("  - Evento: %s\n    Descripción: %s\n    Estado: %s\n", a->nombre, a->descripcion, a->estado ? "Realizado" : "Pendiente");
            a = list_next(agenda);
        }
    }
    printf("============================\n");
}

void menuCalendario(Estudiante estudiante) {
    int opcionCalendario;
    int tipoVista = 0; // 0 = mensual, 1 = diario
    int mesSeleccionado, diaSeleccionado;

    do {
        printf("===== MENÚ CALENDARIO =====\n");
        printf("1. Ver calendario mensual\n");
        printf("2. Ver calendario diario\n");
        printf("3. Cambiar visualización (mensual / diaria)\n");
        printf("4. Volver\n");
        printf("\nSeleccione una opción: ");
        scanf("%d", &opcionCalendario);

        switch (opcionCalendario) {
            case 1:
                if (tipoVista == 0) {
                    printf("Seleccione el mes (1-12): ");
                    scanf("%d", &mesSeleccionado);
                    mesSeleccionado--; // Ajuste de índice (mes 1 es mes 0 en la estructura)
                    mostrarCalendarioMensual(estudiante, mesSeleccionado);
                }
                break;
            
            case 2:
                if (tipoVista == 1) {
                    printf("Seleccione el mes (1-12): ");
                    scanf("%d", &mesSeleccionado);
                    mesSeleccionado--; 
                    printf("Seleccione el día (1-31): ");
                    scanf("%d", &diaSeleccionado);
                    diaSeleccionado--; 
                    mostrarCalendarioDiario(estudiante, mesSeleccionado, diaSeleccionado);
                }
                break;
            case 3:
                tipoVista = (tipoVista == 0) ? 1 : 0; // Cambiar entre mensual y diario
                printf("Visualización cambiada a %s\n", (tipoVista == 0) ? "mensual" : "diaria");
                break;

            case 4:
                printf("Volviendo al menú principal...\n");
                break;

            default:
                printf("Opción no válida. Intente de nuevo.\n");
                break;
        }
    } while (opcionCalendario != 4);
}

void seleccionarCurso(Estudiante estudiante)
{
    printf("-------Seleccionar Curso-------\n");
    if(estudiante.cursos->size == 0) {
        printf("No hay cursos registrados.\n");
        return;
    }
    MapPair *par= map_first(estudiante.cursos);
    int index=1;
    while(par!=NULL)
    {

        Curso *curso = (Curso *)par->value;
        printf("%d. Curso: %s\n",index,curso->nombre);
        par= map_next(estudiante.cursos);
        index++;
    }
    int opcionCurso;
    printf("Seleccione el curso (número): ");
    scanf("%d", &opcionCurso);
    par= map_first(estudiante.cursos);
    for(int i=1; i<opcionCurso && par!=NULL;i++)
    {
        par= map_next(estudiante.cursos);
    }
    if(par == NULL) {
        printf("Curso no encontrado.\n");
        return;
    }
    Curso *cursoSeleccionado = (Curso *)par->value;
    printf("Curso seleccionado: %s\n", cursoSeleccionado->nombre);
    seleccionarTipodePreguntas(cursoSeleccionado);
    
}

void seleccionarTipodePreguntas(Curso *curso)
{
    int tipopregunta;
    printf("-------Seleccionar Tipo de Preguntas-------\n");
    printf("1. Preguntas de opción secuencial(orden agregada)\n");
    printf("2. Preguntas de opción aleatoria\n");
    printf("Seleccione el tipo de preguntas (número): ");
    scanf("%d", &tipopregunta);
    switch (tipopregunta)
    {
        case 1:

            repasoSecuencial(curso);
            break;
        case 2:
            repasoAleatorio(curso);
            break;
        default:
            printf("Opción no válida. Por favor, intente de nuevo.\n");
            break;

    }

}

void repasoSecuencial(Curso *curso)
{
    printf("===== REPASO SECUENCIAL =====\n");

    // Asegúrate de que el curso tiene repasos y preguntas
    if (curso->repaso == NULL || list_size(curso->repaso) == 0) {
        printf("No hay repasos registrados para este curso.\n");
        return;
    }

    // Tomamos el primer repaso del curso (si es secuencial)
    Repaso *repaso = list_first(curso->repaso);

    if (repaso == NULL || repaso->cantidadPreguntas == 0) {
        printf("Este repaso no tiene preguntas registradas.\n");
        return;
    }

    // Mostrar preguntas en orden secuencial
    for (int i = 0; i < repaso->cantidadPreguntas; i++) {
        Pregunta *p = repaso->preguntas[i];
        printf("Pregunta %d: %s\n", i + 1, p->pregunta);
        printf("Respuesta: %s\n", p->respuesta);
        printf("Puntuación: %d\n", p->puntuacion);
        printf("===========================\n");
    }
}

void repasoAleatorio(Curso *curso)
{
    printf("===== REPASO ALEATORIO =====\n");

    // Verificar si el curso tiene repasos y preguntas
    if (curso->repaso == NULL || list_size(curso->repaso) == 0) {
        printf("No hay repasos registrados para este curso.\n");
        return;
    }

    // Tomamos el primer repaso del curso
    Repaso *repaso = list_first(curso->repaso);

    if (repaso == NULL || repaso->cantidadPreguntas == 0) {
        printf("Este repaso no tiene preguntas registradas.\n");
        return;
    }

    // Barajar las preguntas de forma aleatoria usando Fisher-Yates
    for (int i = repaso->cantidadPreguntas - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // Seleccionar un índice aleatorio entre 0 e i
        // Intercambiar las preguntas i y j
        Pregunta *temp = repaso->preguntas[i];
        repaso->preguntas[i] = repaso->preguntas[j];
        repaso->preguntas[j] = temp;
    }

    // Mostrar las preguntas en orden aleatorio
    for (int i = 0; i < repaso->cantidadPreguntas; i++) {
        Pregunta *p = repaso->preguntas[i];
        printf("Pregunta %d: %s\n", i + 1, p->pregunta);
        printf("Respuesta: %s\n", p->respuesta);
        printf("Puntuación: %d\n", p->puntuacion);
        printf("===========================\n");
    }
}




void iniciarrepaso(Estudiante estudiante)
{
    printf("===== INICIAR REPASO =====\n");
    seleccionarCurso(estudiante);

    presioneTeclaParaContinuar();
}


void menuprincipal(int *opcion) {
    printf("===== MENÚ PRINCIPAL =====\n");
    printf("1. Ver calendario\n");
    printf("2. Ver cursos\n");
    printf("3. Iniciar repaso\n");
    printf("4. Salir\n");
    printf("\n");
    printf("Seleccione una opción: ");
    scanf("%d", opcion);
}

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

    do{
        limpiarPantalla();
        menuprincipal(&opcion);
        switch (opcion)
        {
        case 1:
            menuCalendario(estudiante);
            break;
            
        case 2:
            //cursos(estudiante, yearActual);
            break;
        case 3:
            iniciarrepaso(estudiante);
            break;
        case 4:
            printf("saliendo del programa...\n");
            break;

        default:
            printf("Opción no válida. Por favor, intente de nuevo.\n");
            break;
        }
    }while(opcion != 4);
    return 0;
}