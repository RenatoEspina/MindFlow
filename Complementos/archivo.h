#ifndef ARCHIVO_H
#define ARCHIVO_H

#include "../include.h"

void comprobarExistenciaArchivo();

void leerAgenda(Estudiante* estudiante);
void leerCurso(Estudiante* estudiante);
void leerRepaso(Estudiante* estudiante);
void leerPreguntas(Estudiante* estudiante);
void leerNotas(Estudiante* estudiante);

void escribirCursos(Estudiante* estudiante);
void escribirRepasos(Estudiante* estudiante);
void escribirPreguntas(Estudiante* estudiante);
void escribirNotas(Estudiante* estudiante);
void escribirAgenda(Estudiante* estudiante);
#endif