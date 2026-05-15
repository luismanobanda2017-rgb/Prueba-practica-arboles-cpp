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

// ============================================================
//  CLASE: ArbolBST
//  Implementa el Árbol Binario de Búsqueda con todas las
//  operaciones requeridas por la prueba práctica.
// ============================================================
class ArbolBST {
private:
    Nodo* raiz;  // Puntero a la raíz del árbol

    // --------------------------------------------------------
    //  FUNCIÓN PRIVADA: insertarRec
    //  Inserta recursivamente un nuevo nodo en el subárbol.
    //  @param nodo  : nodo actual del recorrido
    //  @param estu  : datos del estudiante a insertar
    //  @return      : nodo actualizado
    // --------------------------------------------------------
    Nodo* insertarRec(Nodo* nodo, Estudiante estu) {
        if (nodo == nullptr)
            return new Nodo(estu);

        if (estu.cedula < nodo->datos.cedula)
            nodo->izquierdo = insertarRec(nodo->izquierdo, estu);
        else if (estu.cedula > nodo->datos.cedula)
            nodo->derecho = insertarRec(nodo->derecho, estu);
        else
            cout << "  [!] Ya existe un estudiante con la cédula: " << estu.cedula << "\n";

        return nodo;
    }

    // --------------------------------------------------------
    //  FUNCIÓN PRIVADA: buscarRec
    //  Busca recursivamente un nodo por cédula.
    //  @return puntero al nodo encontrado o nullptr
    // --------------------------------------------------------
    Nodo* buscarRec(Nodo* nodo, const string& cedula) {
        if (nodo == nullptr || nodo->datos.cedula == cedula)
            return nodo;

        if (cedula < nodo->datos.cedula)
            return buscarRec(nodo->izquierdo, cedula);
        else
            return buscarRec(nodo->derecho, cedula);
    }

    // --------------------------------------------------------
    //  FUNCIÓN PRIVADA: minimoNodo
    //  Encuentra el nodo con la cédula más pequeña
    //  en un subárbol (el más a la izquierda).
    // --------------------------------------------------------
    Nodo* minimoNodo(Nodo* nodo) {
        Nodo* actual = nodo;
        while (actual && actual->izquierdo != nullptr)
            actual = actual->izquierdo;
        return actual;
    }

    // --------------------------------------------------------
    //  FUNCIÓN PRIVADA: eliminarRec
    //  Elimina recursivamente un nodo manteniendo la
    //  propiedad del BST. Usa el sucesor inorden.
    // --------------------------------------------------------
    Nodo* eliminarRec(Nodo* nodo, const string& cedula) {
        if (nodo == nullptr) return nodo;

        if (cedula < nodo->datos.cedula)
            nodo->izquierdo = eliminarRec(nodo->izquierdo, cedula);
        else if (cedula > nodo->datos.cedula)
            nodo->derecho = eliminarRec(nodo->derecho, cedula);
        else {
            // Nodo encontrado: tres casos posibles
            if (nodo->izquierdo == nullptr) {
                Nodo* temp = nodo->derecho;
                delete nodo;
                return temp;
            } else if (nodo->derecho == nullptr) {
                Nodo* temp = nodo->izquierdo;
                delete nodo;
                return temp;
            }
            // Caso: dos hijos → reemplazar con sucesor inorden
            Nodo* sucesor = minimoNodo(nodo->derecho);
            nodo->datos   = sucesor->datos;
            nodo->derecho = eliminarRec(nodo->derecho, sucesor->datos.cedula);
        }
        return nodo;
    }

