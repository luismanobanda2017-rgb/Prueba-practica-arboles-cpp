# 🎓 Sistema de Gestión Académica — Árbol Binario de Búsqueda (BST)

**Universidad Técnica de Ambato**  
**Asignatura:** Estructura de Datos  
**Tema:** Árboles Binarios de Búsqueda  
**Lenguaje:** C++  
**Autor:** [Luis Manobanda]

---

## 📋 Descripción del Proyecto

Sistema académico para gestionar estudiantes de la UTA mediante un **Árbol Binario de Búsqueda (BST)**. Cada nodo del árbol almacena la información completa de un estudiante, y la clave de ordenamiento utilizada es la **cédula de identidad**.

El sistema permite insertar, buscar, eliminar y recorrer estudiantes de forma eficiente gracias a la estructura del BST, cuya complejidad promedio de búsqueda es **O(log n)**.

---

## 🧠 Conceptos Aplicados

| Concepto | Descripción |
|---|---|
| **BST** | Árbol Binario de Búsqueda con cédula como clave |
| **Recursividad** | Insertar, buscar, eliminar, recorridos, altura, conteo |
| **Punteros** | Manejo dinámico de nodos con `new` y `delete` |
| **Cola (Queue)** | Utilizada para el recorrido BFS por niveles |
| **Clases y Objetos** | Clase `ArbolBST` encapsula toda la lógica |
| **Struct** | `Nodo` y `Estudiante` como estructuras de datos |
| **Validación** | Cédula (10 dígitos), nota (0-10), nivel (1-10) |

---

## 📁 Estructura del Repositorio

```
prueba-practica-arboles-cpp-java/
├── src/
│   └── sistema_estudiantes.cpp    ← Código fuente principal
├── capturas/
│   ├── captura_menu.png
│   ├── captura_insertar.png
│   ├── captura_recorridos.png
│   ├── captura_bfs.png
│   └── captura_funciones.png
└── README.md
```

---

## ⚙️ Compilación y Ejecución

### Opción 1: Dev-C++ (Windows)
1. Abre Dev-C++
2. Archivo → Nuevo → Proyecto → Aplicación de consola en C++
3. Copia el contenido de `src/sistema_estudiantes.cpp`
4. Presiona **F9** para compilar y ejecutar

### Opción 2: Terminal con g++ (Windows/Linux/Mac)

```bash
# Compilar
g++ -o sistema_estudiantes src/sistema_estudiantes.cpp

# Ejecutar (Linux/Mac)
./sistema_estudiantes

# Ejecutar (Windows)
sistema_estudiantes.exe
```

### Opción 3: Compilar con estándar C++11
```bash
g++ -std=c++11 -o sistema_estudiantes src/sistema_estudiantes.cpp
```

---

## 🗂️ Datos del Estudiante

Cada nodo del árbol almacena:

| Campo | Tipo | Descripción |
|---|---|---|
| `cedula` | string | 10 dígitos — clave del BST |
| `apellidos` | string | Apellidos del estudiante |
| `nombres` | string | Nombres del estudiante |
| `notaFinal` | double | Nota entre 0.0 y 10.0 |
| `carrera` | string | Carrera universitaria |
| `nivel` | int | Semestre / nivel (1 al 10) |

---

## 📌 Menú del Sistema

```
╔══════════════════════════════════════════════════╗
║   UNIVERSIDAD TÉCNICA DE AMBATO                  ║
║   Sistema de Gestión Académica - Árbol BST       ║
╠══════════════════════════════════════════════════╣
║  1.  Insertar estudiante                         ║
║  2.  Buscar estudiante por cédula                ║
║  3.  Eliminar estudiante                         ║
╠══════════════════════════════════════════════════╣
║  4.  Recorrido Inorden                           ║
║  5.  Recorrido Preorden                          ║
║  6.  Recorrido Postorden                         ║
║  7.  Recorrido por niveles (BFS)                 ║
╠══════════════════════════════════════════════════╣
║  8.  Contar estudiantes                          ║
║  9.  Calcular altura del árbol                   ║
║  10. Mostrar estudiante con mayor nota           ║
║  11. Mostrar estudiante con menor nota           ║
╠══════════════════════════════════════════════════╣
║  12. Mostrar estudiantes aprobados               ║
║  13. Mostrar estudiantes reprobados              ║
╠══════════════════════════════════════════════════╣
║  0.  Cargar datos de prueba                      ║
║  14. Salir                                       ║
╚══════════════════════════════════════════════════╝
```

---

## 🔁 Recorridos Implementados

### Inorden (Izq → Raíz → Der)
Muestra los estudiantes **ordenados por cédula** de menor a mayor. Es útil para listar registros en orden.

### Preorden (Raíz → Izq → Der)
Visita primero la raíz. Útil para **copiar o serializar** el árbol.

### Postorden (Izq → Der → Raíz)
Visita primero las hojas. Útil para **eliminar o liberar** el árbol.

### BFS — Por Niveles (Cola)
Recorre el árbol **nivel por nivel**, de arriba hacia abajo, usando una `queue<Nodo*>`. Muestra la estructura jerárquica del árbol.

---

## 📊 Funciones Avanzadas

| Función | Descripción |
|---|---|
| `contarNodos()` | Cuenta todos los nodos recursivamente |
| `calcularAltura()` | Altura = niveles - 1 (raíz = 0) |
| `buscarNotaMayor()` | Recorre todo el árbol buscando el máximo |
| `buscarNotaMenor()` | Recorre todo el árbol buscando el mínimo |
| `mostrarAprobados()` | Nota >= 7.0 |
| `mostrarReprobados()` | Nota < 7.0 |

---

## ✅ Criterios de Aprobación

- Nota mínima de aprobación: **7.0 / 10**
- Los recorridos filtran y muestran el estado `APROBADO ✔` o `REPROBADO ✗`

---

## 📝 Notas Técnicas

- El destructor `~ArbolBST()` libera toda la memoria dinámica al terminar.
- La eliminación usa el **sucesor inorden** cuando el nodo tiene dos hijos.
- Las funciones de búsqueda de nota recorren **todo el árbol** (no solo la rama izquierda/derecha) porque la nota no es la clave de ordenamiento.
- La validación de cédula verifica longitud = 10 y solo dígitos numéricos.

---

## 🖼️ Capturas de Pantalla

*(Agregar capturas después de ejecutar el programa)*

| Captura | Descripción |
|---|---|
| `captura_menu.png` | Menú principal |
| `captura_insertar.png` | Inserción de estudiantes |
| `captura_recorridos.png` | Inorden, Preorden, Postorden |
| `captura_bfs.png` | Recorrido por niveles |
| `captura_funciones.png` | Altura, conteo, notas |

---

*Estructura de Datos — UTA 2025*
