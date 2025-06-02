#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "extra.h"
#include "map.h"

//estructuras propuestas
//Dia
typedef struct Dia{
    int numero; //numero del dia en la semana
    bool relevante[3]; //0=examen, 1=control, 2=trabajo, con esto en un mismo dia podemos saber que hay mas facil
    List* agenda; //lista de eventos del dia
} Dia;

//Mes
typedef struct Mes{
    char nombre[20];
    int numero; //numero del mes
    Dia dias[31]; //arreglo de dias, maximo 31 dias
} Mes;

//estudiante
typedef struct Estudiante{
    Map* cursos; //usar de key el nombre y de value la estructura curso
    Mes meses[12];
} Estudiante;

//agenda
typedef struct Agenda{
    char nombre[50]; //nombre del evento
    char descripcion[100]; //descripcion del evento
    bool estado; //false= pendiente, true= realizado
} Agenda;

//Estructura relacionadas a los cursos
//Curso
typedef struct Curso{
    int id; //asignar automatico, usarlo para acceder mas facil 
    char nombre[50];
    List* notas; //usar estructura Nota
    List* repaso; //usar estructura Repaso y usar cada nodo como para un examen
} Curso;

//Nota
typedef struct Nota{
    int nota;
    float ponderacion;
} Nota;

//repaso
typedef struct Repaso{
    List* preguntas; //usar estructura Pregunta
    int puntuacionPromedio; //puntuacion promedio del repaso
    int puntuacionPromedioAnterior; //para revisar el avanze o retroceso del estudiante
} Repaso;

//Pregunta
typedef struct Pregunta{
    char pregunta[100];
    char respuesta[100];
    int puntuacion; //(0-100)
} Pregunta;

#endif