#include "include.h"
void repasoSecuencial(Curso *curso);
void repasoAleatorio(Curso *curso);
void menuCalendario(Estudiante estudiante);
void seleccionarTipodePreguntas(Curso *curso);
void iniciarrepaso(Estudiante estudiante);

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
                printf("examen: %d, control: %d, trabajo: %d\n", mes.dias[d].relevante[0], mes.dias[d].relevante[1], mes.dias[d].relevante[2]);
                a = list_next(agenda);
            }
        }
    }
    printf("=======================================\n");
}


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
                printf("Seleccione el mes (1-12): ");
                scanf("%d", &mesSeleccionado);
                mesSeleccionado--; 
                printf("Seleccione el día (1-31): ");
                scanf("%d", &diaSeleccionado);
                diaSeleccionado--; 
                mostrarCalendarioDiario(estudiante, mesSeleccionado, diaSeleccionado);
                
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
        presioneTeclaParaContinuar();
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

void agregarRepaso(Estudiante *estudiante) {
    printf("===== Agregar Repaso =====\n");

    if (estudiante->cursos->size == 0) {
        printf("No hay cursos registrados.\n");
        presioneTeclaParaContinuar();
        return;
    }

   
    printf("Seleccione el curso al que desea agregar un repaso:\n");
    MapPair *par = map_first(estudiante->cursos);
    int index = 1;
    while (par != NULL) {
        Curso *curso = (Curso *)par->value;
        printf("%d. Curso: %s\n", index, curso->nombre);
        par = map_next(estudiante->cursos);
        index++;
    }

    int opcionCurso;
    printf("Seleccione un curso (número): ");
    scanf("%d", &opcionCurso);

    par = map_first(estudiante->cursos);
    for (int i = 1; i < opcionCurso && par != NULL; i++) {
        par = map_next(estudiante->cursos);
    }
    
    if (par == NULL) {
        printf("Curso no encontrado.\n");
        return;
    }

    Curso *cursoSeleccionado = (Curso *)par->value;
    printf("Curso seleccionado: %s\n", cursoSeleccionado->nombre);


    Repaso *nuevoRepaso = malloc(sizeof(Repaso));
    printf("Ingrese el ID del repaso: ");
    scanf("%d", &nuevoRepaso->id);
    printf("Ingrese la puntuación promedio: ");
    scanf("%d", &nuevoRepaso->puntuacionPromedio);
    printf("Ingrese la puntuación promedio anterior: ");
    scanf("%d", &nuevoRepaso->puntuacionPromedioAnterior);
    

    nuevoRepaso->preguntas = NULL;
    nuevoRepaso->cantidadPreguntas = 0;


    if (cursoSeleccionado->repaso == NULL) {
        cursoSeleccionado->repaso = list_create();
    }
    list_pushBack(cursoSeleccionado->repaso, nuevoRepaso);
    
    printf("Repaso agregado exitosamente al curso %s.\n", cursoSeleccionado->nombre);
}


void iniciarrepaso(Estudiante estudiante)
{
    int opcion;
    do{
        limpiarPantalla();
        printf("===== REPASO =====\n");
        printf("1. Seleccionar curso\n");
        printf("2. agregar preguntas al repaso de un curso\n");
        printf("3. Volver al menú principal\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
    switch (opcion)
    {
        case 1:
            seleccionarCurso(estudiante);
            break;
        case 2:
            agregarRepaso(&estudiante);
            break;
        case 3:
            printf("Volviendo al menú principal...\n");
            return;
        default:
            printf("Opción no válida. Por favor, intente de nuevo.\n");
            return;
    }
    } while(opcion != 3);

    presioneTeclaParaContinuar();
}

void crearCurso(Estudiante estudiante){
    Curso* curso = malloc(sizeof(Curso));
    inicializarCurso(curso, estudiante.cursos->size + 1);

    printf("Ingrese el nombre del curso: ");
    scanf("%s", curso->nombre);

    map_insert(estudiante.cursos, curso->nombre, curso);

    printf("Curso '%s' agregado\n", curso->nombre);
    presioneTeclaParaContinuar();
}

void calcularRestante(float suma, float sumaPonderacion){
    float notaExencion;
    int resultado;

    do {
        printf("Ingrese la nota de exención(ejemplo: 1.0 - 7.0): ");
        resultado = scanf("%f", &notaExencion);
        while (getchar() != '\n'); // limpiar ENTER extra

        if (resultado != 1 || notaExencion < 1.0 || notaExencion > 7.0) {
            printf("Entrada inválida. Por favor ingrese un número decimal válido entre 1.0 y 7.0.\n");
        }
    } while (resultado != 1 || notaExencion < 1.0 || notaExencion > 7.0);
    float PromedioExencion = (notaExencion * 100.0 - suma) / 100.0 - sumaPonderacion;
    printf("Necesitas: %.2f\n", PromedioExencion);
    presioneTeclaParaContinuar();
}

void eliminarNota(Curso *curso) {
    if (list_size(curso->notas) == 0) {
        printf("No hay notas registradas.\n");
        return;
    }

    printf("Notas actuales:\n");
    int index = 0;
    for (Nota* n = list_first(curso->notas); n != NULL; n = list_next(curso->notas)) {
        printf("%d) Nota: %.1f, Ponderación: %.2f\n", index,(float)n->nota, n->ponderacion);
        index++;
    }

    printf("Ingrese el número de la nota a eliminar: ");
    int eliminarIndex;
    scanf("%d", &eliminarIndex);

    if (eliminarIndex < 0 || eliminarIndex >= list_size(curso->notas)) {
        printf("Índice inválido.\n");
        presioneTeclaParaContinuar();
        return;
    }

    // Recorremos para llegar a esa posición
    int i = 0;
    Nota *n = list_first(curso->notas);
    while (i < eliminarIndex && n != NULL) {
        n = list_next(curso->notas);
        i++;
    }

    if (n != NULL) {
        list_popCurrent(curso->notas); // Elimina la nota actual
        free(n); // Libera la memoria de la Nota
        printf("Nota eliminada correctamente.\n");
    } else {
        printf("No se pudo eliminar.\n");
    }
}

void agregarNota(Curso *curso){
    Nota *nota = malloc(sizeof(Nota));
    float notaActual;
    int resultado;
    do{
        printf("Ingrese la nota(Ejemplo 1.0 - 7.0): ");
        resultado = scanf("%f", &notaActual);
        while (getchar() != '\n'); // Limpiar el buffer

        if(resultado != 1 || notaActual < 1.0 || notaActual > 7.0){
            printf("Entrada inválida. Por favor ingrese un número decimal válido entre 1.0 y 7.0.\n");
        }
    }while(resultado != 1 || notaActual < 1.0 || notaActual > 7.0);

    nota->nota = notaActual;

    printf("\nIngrese la ponderación(Ejemplo 0 - 100): ");
    scanf("%f", &nota->ponderacion);
    list_pushBack(curso->notas, nota);
    puts("\nNota agregada.");
}

void Modifica(Curso *curso) {
    int opcion;
    limpiarPantalla();
    puts("Que quieres hacer?");
    puts("1) Agregar nota");
    puts("2) Eliminar nota");
    printf("Ingrese su opción: ");
    scanf("%d", &opcion);
    switch (opcion)
    {
    case 1:
        agregarNota(curso);
        break;
    case 2:
        eliminarNota(curso);
        break;
    default:
        break;
    }
    presioneTeclaParaContinuar();
}

void calcularPromedio(Curso *curso){
    limpiarPantalla();
    if(list_size(curso->notas) == 0){
        puts("Este curso no tiene notas registradas.");
        return;
    }
    float suma = 0.0;
    float sumaPonderacion = 0.0;

    printf("===== Notas del curso %s =====\n", curso->nombre);
    for(Nota *n = list_first(curso->notas); n != NULL ; n = list_next(curso->notas)){
        printf("Nota: %.1f| Ponderación: %.2f\n", (float)n->nota, n->ponderacion);
        suma += n->nota * n->ponderacion;
        sumaPonderacion += n->ponderacion;
    }
    float promedio = (suma / sumaPonderacion);
    printf("En %s tienes un %.2f de promedio\n", curso->nombre, promedio);
    if(sumaPonderacion < 100.0){
        int opcion;
        puts("¿Quieres saber tu nota faltante?");
        puts("1) Calcular");
        puts("2) volver");
        scanf("%d", &opcion);
        if(opcion == 1){
            calcularRestante(suma, sumaPonderacion);
        } else if(opcion == 2){
            puts("volviendo a menuCurso");
            presioneTeclaParaContinuar();
        }
    }
}

void cursos(Estudiante estudiante) {
    limpiarPantalla();
    int opcion = 0;

    if (estudiante.cursos->size == 0) {
        printf("No hay cursos registrados.\n");
        printf("1. Agregar curso nuevo\n");
        printf("2. Volver\n");
        printf("Seleccione opción: ");
        scanf("%d", &opcion);
        if (opcion == 1) crearCurso(estudiante);
        return;
    }

    printf("===== Cursos disponibles =====\n");
    int index = 1;
    for (MapPair *p = map_first(estudiante.cursos); p != NULL; p = map_next(estudiante.cursos)) {
        Curso *curso = p->value;
        printf("%d. %s (ID: %d)\n", index, curso->nombre, curso->id);
        index++;
    }

    printf("Seleccione número de curso: ");
    int seleccion;
    scanf("%d", &seleccion);

    if (seleccion < 1 || seleccion >= index) {
        printf("Selección inválida.\n");
        return;
    }

    // Encontrar el curso elegido
    index = 1;
    MapPair *p = map_first(estudiante.cursos);
    
    while (p != NULL && index < seleccion) {
        p = map_next(estudiante.cursos);
        index++;
    }

    if (p == NULL) {
        printf("Curso no encontrado.\n");
        return;
    }

    Curso *cursoSeleccionado = p->value;

    do {
        limpiarPantalla();
        printf("\n===== Curso: %s =====\n", cursoSeleccionado->nombre);
        printf("  Notas Ponderación:\n");
        for(Nota* n = list_first(cursoSeleccionado->notas); n != NULL ; n = list_next(cursoSeleccionado->notas)){
            printf("   %.1f - %f \n", (float)n->nota, n->ponderacion);
        }
        printf("1. Modificar notas\n");
        printf("2. Calcular promedio\n");
        printf("3. Volver\n");
        printf("Seleccione opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                Modifica(cursoSeleccionado);
                break;
            case 2:
                calcularPromedio(cursoSeleccionado);
                break;
            case 3:
                printf("Volviendo...\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (opcion != 3);
}

void menuprincipal(int *opcion) {
    printf("===== MENÚ PRINCIPAL =====\n");
    printf("1. Ver calendario\n");
    printf("2. Ver cursos\n");
    printf("3. Repaso\n");
    printf("4. Salir\n");
    printf("\n");
    printf("Seleccione una opción: ");
    scanf("%d", opcion);
}
int main(){
    int opcion;
    SetConsoleOutputCP(CP_UTF8);
    comprobarExistenciaArchivo();
    Estudiante estudiante;


    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    int yearActual = tm_info->tm_year + 1900;
    inicializarEstudiante(&estudiante, yearActual);
    leerAgenda(&estudiante);
    leerCurso(&estudiante);
    leerRepaso(&estudiante);
    leerPreguntas(&estudiante);
    leerNotas(&estudiante);
    //imprimirEstudiante(&estudiante);
    
   

    do{
        limpiarPantalla();
        menuprincipal(&opcion);
        switch (opcion)
        {
        case 1:
            menuCalendario(estudiante);
            break;
            
        case 2:
            cursos(estudiante);
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
    escribirAgenda(&estudiante);
    escribirCursos(&estudiante);
    escribirRepasos(&estudiante);
    escribirPreguntas(&estudiante);
    escribirNotas(&estudiante);
    return 0;
}