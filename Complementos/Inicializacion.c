#include "../include.h"

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