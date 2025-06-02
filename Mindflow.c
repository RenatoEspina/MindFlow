#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <tdas/extra.h>
#include <tdas/list.h>
#include <tdas/map.h>
#include <tdas/queue.h>
#include <tdas/heap.h>
#include <tdas/multimap.h>
#include <tdas/set.h>
#include <tdas/stack.h>

//structuras propuestas
typedef struct {
    List cursos;
    Mes meses[12];
} Estudiante;

//Estructura relacionadas al calendario de pruebas y agenda
//Mes
typedef struct {
    char nombre[20];
    int numero; //numero del mes
    Dia dias[31]; //arreglo de dias, maximo 31 dias
} Mes;

//Dia
typedef struct {
    int numero; //numero del dia
    bool relevante[3]; //0=examen, 1=control, 2=trabajo
    List agenda; //lista de eventos del dia
} Dia;

//Estructura relacionadas a los cursos
//Curso
typedef struct {
    char nombre[50];
    List notas; //usar estructura Nota
    List repaso; //usar estructura Repaso y usar cada nodo como para un examen
} Curso;

//Nota
typedef struct {
    int nota;
    float ponderacion;
} Nota;

//repaso
typedef struct {
    List preguntas; //usar estructura Pregunta
    int puntacionPromedio; //puntuacion promedio del repaso
    int puntuacionPromedioAnterior; //para revisar el avanze o retroceso del estudiante
} Repaso;

//Pregunta
typedef struct {
    char pregunta[100];
    char respuesta[100];
    int puntuacion; //(0-100)
} Pregunta;

//Main
int main(){
    SetConsoleOutputCP(CP_UTF8);
    return 0;
}