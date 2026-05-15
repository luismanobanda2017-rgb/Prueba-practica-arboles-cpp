/*
 * ============================================================
 *  UNIVERSIDAD TECNICA DE AMBATO
 *  Facultad de Ingenieria en Sistemas, Electronica e Industrial
 *  Asignatura : Estructura de Datos
 *  Tema       : Arboles Binarios de Busqueda (BST)
 *  Autor      : [Tu nombre aqui]
 *  Fecha      : 2025
 * ============================================================
 *
 *  DESCRIPCION:
 *  Sistema academico para gestionar estudiantes de la UTA
 *  mediante un Arbol Binario de Busqueda (BST).
 *  Clave de ordenamiento: Cedula del estudiante.
 *
 *  COMPILACION (Dev-C++ / g++):
 *    g++ -o sistema_estudiantes sistema_estudiantes.cpp
 *  EJECUCION:
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
const double NOTA_APROBACION = 7.0;  // Nota minima para aprobar (sobre 10)

// ============================================================
//  ESTRUCTURA: Estudiante
//  Contiene todos los datos academicos de un estudiante.
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
//  ESTRUCTURA: Nodo del Arbol
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
//  Implementa el Arbol Binario de Busqueda con todas las
//  operaciones requeridas por la prueba practica.
// ============================================================
class ArbolBST {
private:
    Nodo* raiz;  // Puntero a la raiz del arbol

    // --------------------------------------------------------
    //  FUNCION PRIVADA: insertarRec
    //  Inserta recursivamente un nuevo nodo en el subarbol.
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
            cout << "  [!] Ya existe un estudiante con la cedula: " << estu.cedula << "\n";

        return nodo;
    }

    // --------------------------------------------------------
    //  FUNCION PRIVADA: buscarRec
    //  Busca recursivamente un nodo por cedula.
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
    //  FUNCION PRIVADA: minimoNodo
    //  Encuentra el nodo con la cedula mas pequenya
    //  en un subarbol (el mas a la izquierda).
    // --------------------------------------------------------
    Nodo* minimoNodo(Nodo* nodo) {
        Nodo* actual = nodo;
        while (actual && actual->izquierdo != nullptr)
            actual = actual->izquierdo;
        return actual;
    }

    // --------------------------------------------------------
    //  FUNCION PRIVADA: eliminarRec
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
            // Caso: dos hijos -> reemplazar con sucesor inorden
            Nodo* sucesor = minimoNodo(nodo->derecho);
            nodo->datos   = sucesor->datos;
            nodo->derecho = eliminarRec(nodo->derecho, sucesor->datos.cedula);
        }
        return nodo;
    }

    // --------------------------------------------------------
    //  FUNCION PRIVADA: inordenRec
    //  Recorrido Inorden: Izquierdo -> Raiz -> Derecho
    //  Produce los nodos ordenados por cedula (ascendente).
    // --------------------------------------------------------
    void inordenRec(Nodo* nodo) {
        if (nodo == nullptr) return;
        inordenRec(nodo->izquierdo);
        mostrarEstudiante(nodo->datos);
        inordenRec(nodo->derecho);
    }

    // --------------------------------------------------------
    //  FUNCION PRIVADA: preordenRec
    //  Recorrido Preorden: Raiz -> Izquierdo -> Derecho
    // --------------------------------------------------------
    void preordenRec(Nodo* nodo) {
        if (nodo == nullptr) return;
        mostrarEstudiante(nodo->datos);
        preordenRec(nodo->izquierdo);
        preordenRec(nodo->derecho);
    }

    // --------------------------------------------------------
    //  FUNCION PRIVADA: postordenRec
    //  Recorrido Postorden: Izquierdo -> Derecho -> Raiz
    // --------------------------------------------------------
    void postordenRec(Nodo* nodo) {
        if (nodo == nullptr) return;
        postordenRec(nodo->izquierdo);
        postordenRec(nodo->derecho);
        mostrarEstudiante(nodo->datos);
    }

    // --------------------------------------------------------
    //  FUNCION PRIVADA: contarRec
    //  Cuenta recursivamente todos los nodos del arbol.
    // --------------------------------------------------------
    int contarRec(Nodo* nodo) {
        if (nodo == nullptr) return 0;
        return 1 + contarRec(nodo->izquierdo) + contarRec(nodo->derecho);
    }

    // --------------------------------------------------------
    //  FUNCION PRIVADA: alturaRec
    //  Calcula la altura del arbol recursivamente.
    //  Altura = numero de niveles - 1.
    // --------------------------------------------------------
    int alturaRec(Nodo* nodo) {
        if (nodo == nullptr) return -1;
        int altIzq = alturaRec(nodo->izquierdo);
        int altDer = alturaRec(nodo->derecho);
        return 1 + max(altIzq, altDer);
    }

    // --------------------------------------------------------
    //  FUNCION PRIVADA: buscarMaxNotaRec
    //  Recorre todo el arbol y devuelve el nodo con nota mayor.
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
    //  FUNCION PRIVADA: buscarMinNotaRec
    //  Recorre todo el arbol y devuelve el nodo con nota menor.
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
    //  FUNCION PRIVADA: mostrarAprobadosRec
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
    //  FUNCION PRIVADA: mostrarReprobadosRec
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
    //  FUNCION PRIVADA: liberarMemoria
    //  Libera todos los nodos del arbol (postorden).
    // --------------------------------------------------------
    void liberarMemoria(Nodo* nodo) {
        if (nodo == nullptr) return;
        liberarMemoria(nodo->izquierdo);
        liberarMemoria(nodo->derecho);
        delete nodo;
    }

public:
    // Constructor: arbol vacio
    ArbolBST() : raiz(nullptr) {}

    // Destructor: libera toda la memoria dinamica
    ~ArbolBST() { liberarMemoria(raiz); }

    // ============================================================
    //  METODOS PUBLICOS
    // ============================================================

    // --------------------------------------------------------
    //  insertarEstudiante()
    //  Inserta un nuevo estudiante en el BST.
    //  Clave: cedula (orden lexicografico).
    // --------------------------------------------------------
    void insertarEstudiante(Estudiante estu) {
        raiz = insertarRec(raiz, estu);
    }

    // --------------------------------------------------------
    //  buscarEstudiante()
    //  Busca y muestra un estudiante por su cedula.
    // --------------------------------------------------------
    void buscarEstudiante(const string& cedula) {
        Nodo* resultado = buscarRec(raiz, cedula);
        if (resultado != nullptr) {
            cout << "\n  [OK] Estudiante encontrado:\n";
            separador();
            mostrarEstudiante(resultado->datos);
            separador();
        } else {
            cout << "  [!] No se encontro ningun estudiante con cedula: " << cedula << "\n";
        }
    }

    // --------------------------------------------------------
    //  eliminarEstudiante()
    //  Elimina un estudiante del BST por su cedula.
    // --------------------------------------------------------
    void eliminarEstudiante(const string& cedula) {
        Nodo* existe = buscarRec(raiz, cedula);
        if (existe == nullptr) {
            cout << "  [!] No existe un estudiante con cedula: " << cedula << "\n";
            return;
        }
        raiz = eliminarRec(raiz, cedula);
        cout << "  [OK] Estudiante con cedula " << cedula << " eliminado correctamente.\n";
    }

    // --------------------------------------------------------
    //  recorridoInorden()
    //  Muestra todos los estudiantes ordenados por cedula.
    // --------------------------------------------------------
    void recorridoInorden() {
        if (raiz == nullptr) { sinDatos(); return; }
        cout << "\n  [INORDEN] Izq -> Raiz -> Der (ordenado por cedula)\n";
        separador();
        inordenRec(raiz);
        separador();
    }

    // --------------------------------------------------------
    //  recorridoPreorden()
    //  Muestra: Raiz -> Izquierdo -> Derecho.
    // --------------------------------------------------------
    void recorridoPreorden() {
        if (raiz == nullptr) { sinDatos(); return; }
        cout << "\n  [PREORDEN] Raiz -> Izq -> Der\n";
        separador();
        preordenRec(raiz);
        separador();
    }

    // --------------------------------------------------------
    //  recorridoPostorden()
    //  Muestra: Izquierdo -> Derecho -> Raiz.
    // --------------------------------------------------------
    void recorridoPostorden() {
        if (raiz == nullptr) { sinDatos(); return; }
        cout << "\n  [POSTORDEN] Izq -> Der -> Raiz\n";
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
    //  Retorna y muestra el total de estudiantes en el arbol.
    // --------------------------------------------------------
    void contarNodos() {
        int total = contarRec(raiz);
        cout << "\n  Total de estudiantes registrados: " << total << "\n";
    }

    // --------------------------------------------------------
    //  calcularAltura()
    //  Calcula y muestra la altura del arbol.
    //  Arbol vacio = -1 | Solo raiz = 0.
    // --------------------------------------------------------
    void calcularAltura() {
        int h = alturaRec(raiz);
        cout << "\n  Altura del arbol: " << h;
        if (h == -1) cout << " (arbol vacio)";
        else if (h == 0) cout << " (solo la raiz)";
        cout << "\n";
    }

    // --------------------------------------------------------
    //  buscarNotaMayor()
    //  Encuentra y muestra el estudiante con la nota mas alta.
    // --------------------------------------------------------
    void buscarNotaMayor() {
        if (raiz == nullptr) { sinDatos(); return; }
        Nodo* resultado = buscarMaxNotaRec(raiz, nullptr);
        cout << "\n  [*] Estudiante con MAYOR nota:\n";
        separador();
        mostrarEstudiante(resultado->datos);
        separador();
    }

    // --------------------------------------------------------
    //  buscarNotaMenor()
    //  Encuentra y muestra el estudiante con la nota mas baja.
    // --------------------------------------------------------
    void buscarNotaMenor() {
        if (raiz == nullptr) { sinDatos(); return; }
        Nodo* resultado = buscarMinNotaRec(raiz, nullptr);
        cout << "\n  [*] Estudiante con MENOR nota:\n";
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
        cout << "\n  [OK] ESTUDIANTES APROBADOS (nota >= " << NOTA_APROBACION << "):\n";
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
        cout << "\n  [X] ESTUDIANTES REPROBADOS (nota < " << NOTA_APROBACION << "):\n";
        separador();
        mostrarReprobadosRec(raiz, contador);
        separador();
        cout << "  Total reprobados: " << contador << "\n";
    }

    // ============================================================
    //  UTILIDADES DE VISUALIZACION
    // ============================================================

    // Imprime los datos de un estudiante en formato tabla
    void mostrarEstudiante(const Estudiante& e) {
        cout << "  +-----------------------------------------------+\n";
        cout << "  | Cedula   : " << left << setw(34) << e.cedula    << "|\n";
        cout << "  | Apellidos: " << left << setw(34) << e.apellidos << "|\n";
        cout << "  | Nombres  : " << left << setw(34) << e.nombres   << "|\n";
        cout << "  | Carrera  : " << left << setw(34) << e.carrera   << "|\n";
        cout << "  | Nivel    : " << left << setw(34) << e.nivel     << "|\n";
        cout << fixed << setprecision(2);
        string estado = (e.notaFinal >= NOTA_APROBACION) ? "APROBADO [OK]" : "REPROBADO [X]";
        cout << "  | Nota     : " << left << setw(8)  << e.notaFinal
             << " " << left << setw(25) << estado << "|\n";
        cout << "  +-----------------------------------------------+\n";
    }

    void separador() {
        cout << "  -------------------------------------------------\n";
    }

    void sinDatos() {
        cout << "  [!] El arbol esta vacio. No hay estudiantes registrados.\n";
    }
};

// ============================================================
//  FUNCIONES AUXILIARES DE ENTRADA
// ============================================================

// Limpia el buffer de entrada para evitar problemas con cin
void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Valida que la cedula tenga exactamente 10 digitos numericos
bool validarCedula(const string& cedula) {
    if (cedula.length() != 10) return false;
    for (char c : cedula)
        if (!isdigit(c)) return false;
    return true;
}

// Valida que la nota este en el rango [0, 10]
bool validarNota(double nota) {
    return (nota >= 0.0 && nota <= 10.0);
}

// Captura un estudiante desde la consola con validaciones
Estudiante capturarEstudiante() {
    Estudiante e;

    do {
        cout << "  Cedula (10 digitos): ";
        cin >> e.cedula;
        if (!validarCedula(e.cedula))
            cout << "  [!] Cedula invalida. Debe tener exactamente 10 digitos.\n";
    } while (!validarCedula(e.cedula));

    limpiarBuffer();

    cout << "  Apellidos          : ";
    getline(cin, e.apellidos);

    cout << "  Nombres            : ";
    getline(cin, e.nombres);

    cout << "  Carrera            : ";
    getline(cin, e.carrera);

    do {
        cout << "  Nivel (1-10)       : ";
        cin >> e.nivel;
    } while (e.nivel < 1 || e.nivel > 10);

    do {
        cout << "  Nota final (0-10)  : ";
        cin >> e.notaFinal;
        if (!validarNota(e.notaFinal))
            cout << "  [!] Nota invalida. Debe estar entre 0.0 y 10.0\n";
    } while (!validarNota(e.notaFinal));

    return e;
}

// ============================================================
//  FUNCION: cargarDatosDePrueba
//  Inserta 8 estudiantes de ejemplo para facilitar las pruebas.
// ============================================================
void cargarDatosDePrueba(ArbolBST& arbol) {
    Estudiante datos[] = {
        {"1802345678", "Moreta Guevara",   "Ana Lucia",      6.5, "Industrial",   2},
        {"1801234567", "Alvarez Torres",   "Maria Jose",     5.8, "Sistemas",     1},
        {"1805678901", "Perez Castillo",   "Juan Pablo",     7.0, "Electronica",  3},
        {"1808901234", "Herrera Montoya",  "Valeria Nicole", 7.5, "Sistemas",     4}
    };

    int n = sizeof(datos) / sizeof(datos[0]);
    for (int i = 0; i < n; i++)
        arbol.insertarEstudiante(datos[i]);

    cout << "  [OK] Se cargaron " << n << " estudiantes de prueba correctamente.\n";
}

// ============================================================
//  FUNCION: mostrarMenu
//  Despliega el menu principal del sistema.
// ============================================================
void mostrarMenu() {
    cout << "\n";
    cout << "  +===================================================+\n";
    cout << "  |   UNIVERSIDAD TECNICA DE AMBATO                   |\n";
    cout << "  |   Sistema de Gestion Academica - Arbol BST        |\n";
    cout << "  +===================================================+\n";
    cout << "  |  1.  Insertar estudiante                          |\n";
    cout << "  |  2.  Buscar estudiante por cedula                 |\n";
    cout << "  |  3.  Eliminar estudiante                          |\n";
    cout << "  +---------------------------------------------------+\n";
    cout << "  |  4.  Recorrido Inorden                            |\n";
    cout << "  |  5.  Recorrido Preorden                           |\n";
    cout << "  |  6.  Recorrido Postorden                          |\n";
    cout << "  |  7.  Recorrido por niveles (BFS)                  |\n";
    cout << "  +---------------------------------------------------+\n";
    cout << "  |  8.  Contar estudiantes                           |\n";
    cout << "  |  9.  Calcular altura del arbol                    |\n";
    cout << "  |  10. Mostrar estudiante con mayor nota            |\n";
    cout << "  |  11. Mostrar estudiante con menor nota            |\n";
    cout << "  +---------------------------------------------------+\n";
    cout << "  |  12. Mostrar estudiantes aprobados                |\n";
    cout << "  |  13. Mostrar estudiantes reprobados               |\n";
    cout << "  +---------------------------------------------------+\n";
    cout << "  |  0.  Cargar datos de prueba                       |\n";
    cout << "  |  14. Salir                                        |\n";
    cout << "  +===================================================+\n";
    cout << "  Seleccione una opcion: ";
}

// ============================================================
//  FUNCION PRINCIPAL: main
// ============================================================
int main() {
    ArbolBST arbol;
    int opcion;

    cout << "\n";
    cout << "  +===================================================+\n";
    cout << "  |     Bienvenido al Sistema Academico UTA           |\n";
    cout << "  |     Arbol Binario de Busqueda - C++               |\n";
    cout << "  +===================================================+\n";
    cout << "  [*] Ingrese opcion 0 para cargar datos de prueba.\n";

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1: {
                // -- Insertar estudiante ----------------------
                cout << "\n  -- INSERTAR ESTUDIANTE -------------------------\n";
                limpiarBuffer();
                Estudiante e = capturarEstudiante();
                arbol.insertarEstudiante(e);
                cout << "  [OK] Estudiante insertado correctamente.\n";
                break;
            }
            case 2: {
                // -- Buscar por cedula ------------------------
                string cedula;
                cout << "\n  -- BUSCAR ESTUDIANTE ---------------------------\n";
                cout << "  Ingrese la cedula: ";
                cin >> cedula;
                arbol.buscarEstudiante(cedula);
                break;
            }
            case 3: {
                // -- Eliminar estudiante ----------------------
                string cedula;
                cout << "\n  -- ELIMINAR ESTUDIANTE -------------------------\n";
                cout << "  Ingrese la cedula a eliminar: ";
                cin >> cedula;
                arbol.eliminarEstudiante(cedula);
                break;
            }
            case 4:
                // -- Recorrido Inorden ------------------------
                arbol.recorridoInorden();
                break;
            case 5:
                // -- Recorrido Preorden -----------------------
                arbol.recorridoPreorden();
                break;
            case 6:
                // -- Recorrido Postorden ----------------------
                arbol.recorridoPostorden();
                break;
            case 7:
                // -- BFS por niveles --------------------------
                arbol.recorridoPorNiveles();
                break;
            case 8:
                // -- Contar nodos -----------------------------
                arbol.contarNodos();
                break;
            case 9:
                // -- Calcular altura --------------------------
                arbol.calcularAltura();
                break;
            case 10:
                // -- Mayor nota -------------------------------
                arbol.buscarNotaMayor();
                break;
            case 11:
                // -- Menor nota -------------------------------
                arbol.buscarNotaMenor();
                break;
            case 12:
                // -- Aprobados --------------------------------
                arbol.mostrarAprobados();
                break;
            case 13:
                // -- Reprobados -------------------------------
                arbol.mostrarReprobados();
                break;
            case 0:
                // -- Datos de prueba --------------------------
                cout << "\n  -- CARGANDO DATOS DE PRUEBA --------------------\n";
                cargarDatosDePrueba(arbol);
                break;
            case 14:
                cout << "\n  Hasta luego! Sistema cerrado correctamente.\n\n";
                break;
            default:
                cout << "  [!] Opcion no valida. Intente de nuevo.\n";
        }

    } while (opcion != 14);

    return 0;
}
