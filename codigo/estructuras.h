#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

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

//estructuras propuestas
typedef struct {
    Map cursos; //usar de key el nombre y de value la estructura curso
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
    bool relevante[3]; //0=examen, 1=control, 2=trabajo, con esto en un mismo dia podemos saber que hay mas facil
    List agenda; //lista de eventos del dia
} Dia;

//agenda
typedef struct {
    char nombre[50]; //nombre del evento
    char descripcion[100]; //descripcion del evento
    bool estado; //false= pendiente, true= realizado
} Agenda;

//Estructura relacionadas a los cursos
//Curso
typedef struct {
    int id; //asignar automatico, usarlo para acceder mas facil 
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


#endif