#include "tablaJugadores.h"

struct NodoTabla {
    TJugadoresLDE jugadores;
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
    tabla->cantidad = 0;
    tabla->cota = max;

    for (int i = 0; i < max; i++) {
        tabla->tabla[i] = NULL;
    }

    return tabla;
}

void liberarTTablaJugadores(TTablaJugadores &tabla) {

        for (int i = 0; i < tabla->cota; i++) {
            if (tabla->tabla[i]) {
                liberarTJugadoresLDE(tabla->tabla[i]->jugadores);
                delete tabla->tabla[i];
            }
        }
        delete[] tabla->tabla;
        delete tabla;
        tabla = NULL;
    }

void insertarJugadorEnTabla(TTablaJugadores &tabla, TJugador jugador, TFecha fecha) {
    const char* nombre = nombreTJugador(jugador);
    int pos = funcionDeDispersion(nombre) % tabla->cota;
    
    if (tabla->tabla[pos] == NULL) {
        tabla->tabla[pos] = new NodoTabla;
        tabla->tabla[pos]->jugadores = crearTJugadoresLDE();
    }
    insertarTJugadoresLDE(tabla->tabla[pos]->jugadores, jugador, fecha);
    tabla->cantidad++;
}

void eliminarJugadorDeTTablaJugadores(TTablaJugadores &tabla, const char nombre[100]) {
    int pos = funcionDeDispersion(nombre) % tabla->cota;
    NodoTabla* nodoTabla = tabla->tabla[pos];
    
            eliminarJugadorConNombreTJugadoresLDE(nodoTabla->jugadores, nombre);

            if (cantidadTJugadoresLDE(nodoTabla->jugadores) == 0) {
                liberarTJugadoresLDE(nodoTabla->jugadores);
                delete nodoTabla;
                tabla->tabla[pos] = NULL;
            }
            tabla->cantidad--;
        }
    

bool perteneceATTablaJugadores(TTablaJugadores tabla, const char nombre[100]) {
    int pos = funcionDeDispersion(nombre) % tabla->cota;
    NodoTabla* nodoTabla = tabla->tabla[pos];
    
    if (nodoTabla != NULL) {
        return estaJugadorConNombreEnTJugadoresLDE(nodoTabla->jugadores, nombre);
    }
    
    return false;
}

TJugador obtenerJugadorDeTTablaJugadores(TTablaJugadores tabla, const char nombre[100]) {
    int pos = funcionDeDispersion(nombre) % tabla->cota;
    NodoTabla* nodoTabla = tabla->tabla[pos];
    
    if (nodoTabla != NULL) {
        return obtenerJugadorConNombreTJugadoresLDE(nodoTabla->jugadores, nombre);
    }
    return NULL;
}

void imprimirTTablaJugadores(TTablaJugadores tabla) {
    for (int i = 0; i < tabla->cota; i++) {
        NodoTabla* nodoTabla = tabla->tabla[i];
        if (nodoTabla != NULL) {
            imprimirMayorAMenorTJugadoresLDE(nodoTabla->jugadores);
        }
    }
}
