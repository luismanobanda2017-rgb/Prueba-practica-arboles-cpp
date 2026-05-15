/*
 * ============================================================
 *  UNIVERSIDAD TÉCNICA DE AMBATO
 *  Facultad de Ingeniería en Sistemas, Electrónica e Industrial
 *  Asignatura : Estructura de Datos
 *  Tema       : Árboles Binarios de Búsqueda (BST)
 *  Autor      : [Tu nombre aquí]
 *  Fecha      : 2025
 * ============================================================
 *
 *  DESCRIPCIÓN:
 *  Sistema académico para gestionar estudiantes de la UTA
 *  mediante un Árbol Binario de Búsqueda (BST).
 *  Clave de ordenamiento: Cédula del estudiante.
 *
 *  COMPILACIÓN (Dev-C++ / g++):
 *    g++ -o sistema_estudiantes sistema_estudiantes.cpp
 *  EJECUCIÓN:
 *    ./sistema_estudiantes   (Linux/Mac)
 *    sistema_estudiantes.exe (Windows)
 * ============================================================
 */

#include <iostream>
#include <string>
#include <queue>
#include <iomanip>
#include <limits>

using namespace std;

// ============================================================
//  CONSTANTES GLOBALES
// ============================================================
const double NOTA_APROBACION = 7.0;  // Nota mínima para aprobar (sobre 10)

// ============================================================
//  ESTRUCTURA: Estudiante
//  Contiene todos los datos académicos de un estudiante.
// ============================================================
struct Estudiante {
    string cedula;      // Clave primaria del BST
    string apellidos;
    string nombres;
    double notaFinal;
    string carrera;
    int    nivel;
};

// ============================================================
//  ESTRUCTURA: Nodo del Árbol
//  Cada nodo almacena un Estudiante y punteros a hijos.
// ============================================================
struct Nodo {
    Estudiante datos;
    Nodo* izquierdo;
    Nodo* derecho;

    // Constructor: inicializa punteros en nullptr
    Nodo(Estudiante e) : datos(e), izquierdo(nullptr), derecho(nullptr) {}
};
