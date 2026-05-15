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

    // --------------------------------------------------------
    //  FUNCIÓN PRIVADA: inordenRec
    //  Recorrido Inorden: Izquierdo → Raíz → Derecho
    //  Produce los nodos ordenados por cédula (ascendente).
    // --------------------------------------------------------
    void inordenRec(Nodo* nodo) {
        if (nodo == nullptr) return;
        inordenRec(nodo->izquierdo);
        mostrarEstudiante(nodo->datos);
        inordenRec(nodo->derecho);
    }

    // --------------------------------------------------------
    //  FUNCIÓN PRIVADA: preordenRec
    //  Recorrido Preorden: Raíz → Izquierdo → Derecho
    // --------------------------------------------------------
    void preordenRec(Nodo* nodo) {
        if (nodo == nullptr) return;
        mostrarEstudiante(nodo->datos);
        preordenRec(nodo->izquierdo);
        preordenRec(nodo->derecho);
    }

    // --------------------------------------------------------
    //  FUNCIÓN PRIVADA: postordenRec
    //  Recorrido Postorden: Izquierdo → Derecho → Raíz
    // --------------------------------------------------------
    void postordenRec(Nodo* nodo) {
        if (nodo == nullptr) return;
        postordenRec(nodo->izquierdo);
        postordenRec(nodo->derecho);
        mostrarEstudiante(nodo->datos);
    }

    // --------------------------------------------------------
    //  FUNCIÓN PRIVADA: contarRec
    //  Cuenta recursivamente todos los nodos del árbol.
    // --------------------------------------------------------
    int contarRec(Nodo* nodo) {
        if (nodo == nullptr) return 0;
        return 1 + contarRec(nodo->izquierdo) + contarRec(nodo->derecho);
    }

    // --------------------------------------------------------
    //  FUNCIÓN PRIVADA: alturaRec
    //  Calcula la altura del árbol recursivamente.
    //  Altura = número de niveles - 1.
    // --------------------------------------------------------
    int alturaRec(Nodo* nodo) {
        if (nodo == nullptr) return -1;
        int altIzq = alturaRec(nodo->izquierdo);
        int altDer = alturaRec(nodo->derecho);
        return 1 + max(altIzq, altDer);
    }

    // --------------------------------------------------------
    //  FUNCIÓN PRIVADA: buscarMaxNotaRec
    //  Recorre todo el árbol y devuelve el nodo con nota mayor.
    // --------------------------------------------------------
    Nodo* buscarMaxNotaRec(Nodo* nodo, Nodo* maxActual) {
        if (nodo == nullptr) return maxActual;
        if (maxActual == nullptr || nodo->datos.notaFinal > maxActual->datos.notaFinal)
            maxActual = nodo;
        maxActual = buscarMaxNotaRec(nodo->izquierdo, maxActual);
        maxActual = buscarMaxNotaRec(nodo->derecho,   maxActual);
        return maxActual;
    }

    // --------------------------------------------------------
    //  FUNCIÓN PRIVADA: buscarMinNotaRec
    //  Recorre todo el árbol y devuelve el nodo con nota menor.
    // --------------------------------------------------------
    Nodo* buscarMinNotaRec(Nodo* nodo, Nodo* minActual) {
        if (nodo == nullptr) return minActual;
        if (minActual == nullptr || nodo->datos.notaFinal < minActual->datos.notaFinal)
            minActual = nodo;
        minActual = buscarMinNotaRec(nodo->izquierdo, minActual);
        minActual = buscarMinNotaRec(nodo->derecho,   minActual);
        return minActual;
    }

    // --------------------------------------------------------
    //  FUNCIÓN PRIVADA: mostrarAprobadosRec
    //  Muestra recursivamente estudiantes con nota >= 7.
    // --------------------------------------------------------
    void mostrarAprobadosRec(Nodo* nodo, int& contador) {
        if (nodo == nullptr) return;
        mostrarAprobadosRec(nodo->izquierdo, contador);
        if (nodo->datos.notaFinal >= NOTA_APROBACION) {
            mostrarEstudiante(nodo->datos);
            contador++;
        }
        mostrarAprobadosRec(nodo->derecho, contador);
    }

    // --------------------------------------------------------
    //  FUNCIÓN PRIVADA: mostrarReprobadosRec
    //  Muestra recursivamente estudiantes con nota < 7.
    // --------------------------------------------------------
    void mostrarReprobadosRec(Nodo* nodo, int& contador) {
        if (nodo == nullptr) return;
        mostrarReprobadosRec(nodo->izquierdo, contador);
        if (nodo->datos.notaFinal < NOTA_APROBACION) {
            mostrarEstudiante(nodo->datos);
            contador++;
        }
        mostrarReprobadosRec(nodo->derecho, contador);
    }

    // --------------------------------------------------------
    //  FUNCIÓN PRIVADA: liberarMemoria
    //  Libera todos los nodos del árbol (postorden).
    // --------------------------------------------------------
    void liberarMemoria(Nodo* nodo) {
        if (nodo == nullptr) return;
        liberarMemoria(nodo->izquierdo);
        liberarMemoria(nodo->derecho);
        delete nodo;
    }

public:
    // Constructor: árbol vacío
    ArbolBST() : raiz(nullptr) {}

    // Destructor: libera toda la memoria dinámica
    ~ArbolBST() { liberarMemoria(raiz); }

    // ============================================================
    //  MÉTODOS PÚBLICOS
    // ============================================================

    // --------------------------------------------------------
    //  insertarEstudiante()
    //  Inserta un nuevo estudiante en el BST.
    //  Clave: cédula (orden lexicográfico).
    // --------------------------------------------------------
    void insertarEstudiante(Estudiante estu) {
        raiz = insertarRec(raiz, estu);
    }

    // --------------------------------------------------------
    //  buscarEstudiante()
    //  Busca y muestra un estudiante por su cédula.
    // --------------------------------------------------------
    void buscarEstudiante(const string& cedula) {
        Nodo* resultado = buscarRec(raiz, cedula);
        if (resultado != nullptr) {
            cout << "\n  ✔ Estudiante encontrado:\n";
            separador();
            mostrarEstudiante(resultado->datos);
            separador();
        } else {
            cout << "  [!] No se encontró ningún estudiante con cédula: " << cedula << "\n";
        }
    }

    // --------------------------------------------------------
    //  eliminarEstudiante()
    //  Elimina un estudiante del BST por su cédula.
    // --------------------------------------------------------
    void eliminarEstudiante(const string& cedula) {
        Nodo* existe = buscarRec(raiz, cedula);
        if (existe == nullptr) {
            cout << "  [!] No existe un estudiante con cédula: " << cedula << "\n";
            return;
        }
        raiz = eliminarRec(raiz, cedula);
        cout << "  ✔ Estudiante con cédula " << cedula << " eliminado correctamente.\n";
    }

    // --------------------------------------------------------
    //  recorridoInorden()
    //  Muestra todos los estudiantes ordenados por cédula.
    // --------------------------------------------------------
    void recorridoInorden() {
        if (raiz == nullptr) { sinDatos(); return; }
        cout << "\n  [INORDEN] Izq → Raíz → Der (ordenado por cédula)\n";
        separador();
        inordenRec(raiz);
        separador();
    }

    // --------------------------------------------------------
    //  recorridoPreorden()
    //  Muestra: Raíz → Izquierdo → Derecho.
    // --------------------------------------------------------
    void recorridoPreorden() {
        if (raiz == nullptr) { sinDatos(); return; }
        cout << "\n  [PREORDEN] Raíz → Izq → Der\n";
        separador();
        preordenRec(raiz);
        separador();
    }

    // --------------------------------------------------------
    //  recorridoPostorden()
    //  Muestra: Izquierdo → Derecho → Raíz.
    // --------------------------------------------------------
    void recorridoPostorden() {
        if (raiz == nullptr) { sinDatos(); return; }
        cout << "\n  [POSTORDEN] Izq → Der → Raíz\n";
        separador();
        postordenRec(raiz);
        separador();
    }

    // --------------------------------------------------------
    //  recorridoPorNiveles()
    //  BFS (Breadth-First Search) usando una cola (queue).
    //  Recorre nivel por nivel de arriba hacia abajo.
    // --------------------------------------------------------
    void recorridoPorNiveles() {
        if (raiz == nullptr) { sinDatos(); return; }
        cout << "\n  [BFS - POR NIVELES] Nivel por nivel\n";
        separador();

        queue<Nodo*> cola;
        cola.push(raiz);
        int nivel = 0;

        while (!cola.empty()) {
            int tamNivel = cola.size();
            cout << "  Nivel " << nivel << ":\n";

            for (int i = 0; i < tamNivel; i++) {
                Nodo* actual = cola.front();
                cola.pop();
                mostrarEstudiante(actual->datos);

                if (actual->izquierdo != nullptr) cola.push(actual->izquierdo);
                if (actual->derecho   != nullptr) cola.push(actual->derecho);
            }
            nivel++;
        }
        separador();
    }

    // --------------------------------------------------------
    //  contarNodos()
    //  Retorna y muestra el total de estudiantes en el árbol.
    // --------------------------------------------------------
    void contarNodos() {
        int total = contarRec(raiz);
        cout << "\n  Total de estudiantes registrados: " << total << "\n";
    }

    // --------------------------------------------------------
    //  calcularAltura()
    //  Calcula y muestra la altura del árbol.
    //  Árbol vacío = -1 | Solo raíz = 0.
    // --------------------------------------------------------
    void calcularAltura() {
        int h = alturaRec(raiz);
        cout << "\n  Altura del árbol: " << h;
        if (h == -1) cout << " (árbol vacío)";
        else if (h == 0) cout << " (solo la raíz)";
        cout << "\n";
    }

    // --------------------------------------------------------
    //  buscarNotaMayor()
    //  Encuentra y muestra el estudiante con la nota más alta.
    // --------------------------------------------------------
    void buscarNotaMayor() {
        if (raiz == nullptr) { sinDatos(); return; }
        Nodo* resultado = buscarMaxNotaRec(raiz, nullptr);
        cout << "\n  ★ Estudiante con MAYOR nota:\n";
        separador();
        mostrarEstudiante(resultado->datos);
        separador();
    }

    // --------------------------------------------------------
    //  buscarNotaMenor()
    //  Encuentra y muestra el estudiante con la nota más baja.
    // --------------------------------------------------------
    void buscarNotaMenor() {
        if (raiz == nullptr) { sinDatos(); return; }
        Nodo* resultado = buscarMinNotaRec(raiz, nullptr);
        cout << "\n  ★ Estudiante con MENOR nota:\n";
        separador();
        mostrarEstudiante(resultado->datos);
        separador();
    }

    // --------------------------------------------------------
    //  mostrarAprobados()
    //  Lista todos los estudiantes con nota >= 7.0.
    // --------------------------------------------------------
    void mostrarAprobados() {
        if (raiz == nullptr) { sinDatos(); return; }
        int contador = 0;
        cout << "\n  ✔ ESTUDIANTES APROBADOS (nota >= " << NOTA_APROBACION << "):\n";
        separador();
        mostrarAprobadosRec(raiz, contador);
        separador();
        cout << "  Total aprobados: " << contador << "\n";
    }

    // --------------------------------------------------------
    //  mostrarReprobados()
    //  Lista todos los estudiantes con nota < 7.0.
    // --------------------------------------------------------
    void mostrarReprobados() {
        if (raiz == nullptr) { sinDatos(); return; }
        int contador = 0;
        cout << "\n  ✗ ESTUDIANTES REPROBADOS (nota < " << NOTA_APROBACION << "):\n";
        separador();
        mostrarReprobadosRec(raiz, contador);
        separador();
        cout << "  Total reprobados: " << contador << "\n";
    }

