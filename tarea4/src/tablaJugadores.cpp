#include "tablaJugadores.h"

struct NodoTabla {
    char nombre[100];  
    TJugadoresLDE jugadores;  
    NodoTabla* siguiente;
};

struct rep_tablaJugadores {
    NodoTabla** tabla;
    int cantidad;
    int cota;
};

nat funcionDeDispersion(const char nombre[100]) {
    nat res = 0;
    int i = 0;
    while (i < 100 && nombre[i] != '\0') {
        res += int(nombre[i]);
        i++;
    }
    return res;
}

TTablaJugadores crearTTablaJugadores(int max) {
    TTablaJugadores tabla = new rep_tablaJugadores;
    tabla->tabla = new NodoTabla*[max];
    tabla->cota = max;
    tabla->cantidad= 0;

    for (int i = 0; i < max; i++) {
        tabla->tabla[i] = NULL;
    }
    return tabla;
}

void liberarTTablaJugadores(TTablaJugadores &tabla) {
    if (tabla != NULL) {
        for (int i = 0; i < tabla->cota; i++) {
            NodoTabla* actual = tabla->tabla[i];
            while (actual != NULL) {
                NodoTabla* siguiente = actual->siguiente;
                liberarTJugadoresLDE(actual->jugadores);
                delete actual;
                actual = siguiente;
            }
        }
        tabla->cantidad = 0;
        delete[] tabla->tabla;
        delete tabla;
        tabla = NULL;
    }
}

void insertarJugadorEnTabla(TTablaJugadores &tabla, TJugador jugador, TFecha fecha) {
    int posicion = funcionDeDispersion(nombreTJugador(jugador)) % tabla->cota;

    NodoTabla* nuevoNodo = new NodoTabla;
    strcpy(nuevoNodo->nombre, nombreTJugador(jugador));  
    nuevoNodo->jugadores = crearTJugadoresLDE();
    insertarTJugadoresLDE(nuevoNodo->jugadores, jugador, fecha);

    nuevoNodo->siguiente = tabla->tabla[posicion];
    tabla->tabla[posicion] = nuevoNodo;

    tabla->cantidad++;
}

// Función para eliminar al jugador de nombre "nombre" de la TTablaJugadores "tabla".
// La función libera la memoria del jugador eliminado. 
// La función es Theta(m) promedio, donde m es la cantidad de jugadas en la partida del jugador con nombre "nombre".
// PRE: perteneceATTablaJugadores(tabla, nombre)
void eliminarJugadorDeTTablaJugadores(TTablaJugadores &tabla, const char nombre[100]) {

    int posicion = funcionDeDispersion(nombre);
    NodoTabla* actual = tabla->tabla[posicion];
    NodoTabla* anterior = NULL;

    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) {
            if (anterior == NULL) {
                tabla->tabla[posicion] = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            liberarTJugadoresLDE(actual->jugadores);
            delete actual;
            tabla->cantidad--;
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
}

// Función para verificar si en una TTablaJugadores "tabla" existe un jugador con nombre "nombre".
// Devuelve true si existe, false en caso contrario.
// La función es Theta(1) promedio.
bool perteneceATTablaJugadores(TTablaJugadores tabla, const char nombre[100]) {
    int posicion = funcionDeDispersion(nombre);
    NodoTabla* actual = tabla->tabla[posicion];

    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) { 
            return true;
        }
        actual = actual->siguiente;
    }

    return false;
}

// Función para obtener el jugador con nombre "nombre" de la TTablaJugadores "tabla".
// La función es Theta(1) promedio.
// PRE: perteneceATTablaJugadores(tabla, nombre)
TJugador obtenerJugadorDeTTablaJugadores(TTablaJugadores tabla, const char nombre[100]) {
    int posicion = funcionDeDispersion(nombre);
    NodoTabla* actual = tabla->tabla[posicion];

    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) {
            if (cantidadTJugadoresLDE(actual->jugadores) > 0) {
                return obtenerInicioDeTJugadoresLDE(actual->jugadores);
            }
        }
        actual = actual->siguiente;
    }

    return NULL;
}


void imprimirTTablaJugadores(TTablaJugadores tabla) {
    if (tabla != NULL) {
        for (int i = 0; i < tabla->cota; i++) {
            NodoTabla* actual = tabla->tabla[i];
            while (actual != NULL) {
                TJugadoresLDE jugadores = actual->jugadores;
                imprimirMenorAMayorTJugadoresLDE(jugadores);
                actual = actual->siguiente;
            }
        }
    }
}
