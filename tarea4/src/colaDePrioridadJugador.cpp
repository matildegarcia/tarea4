/*
  Módulo de implementación de `TColaDePrioridadJugador`.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/colaDePrioridadJugador.h"
#include "../include/utils.h"


#include <assert.h>
//#include <stdlib.h>
//#include <string.h>


void intercambio(TJugador &jugador1, TJugador &jugador2);
void filtradoDescendente(nat pos, TColaDePrioridadJugador &cp);

struct rep_colaDePrioridadJugador {
    TJugador *arreglo;
    nat cantidad;
    bool *pertenece;
    nat *prioridades; 
    bool prioridadInvertida; 
};

TColaDePrioridadJugador crearCP(nat N) {
    TColaDePrioridadJugador cp = new rep_colaDePrioridadJugador;
    cp->arreglo = new TJugador[N+1];
    cp->cantidad = 0;
    cp->pertenece = new bool[N + 1];
    cp->prioridades = new nat[N + 1]; 
    cp->prioridadInvertida= false;

    for (nat i = 0; i <= N; i++) {
        cp->pertenece[i] = false;
        cp->prioridades[i] = 0; 
    }
    return cp;
}

void invertirPrioridad(TColaDePrioridadJugador &cp) {
    cp->prioridadInvertida = !cp->prioridadInvertida;

    if (cp->cantidad > 1) {
        for (nat i = cp->cantidad / 2; i >= 1; i--) {
            filtradoDescendente(i, cp);
        }
    }
}

   void liberarCP(TColaDePrioridadJugador &cp) {
    if (cp != NULL) {
        for (nat i = 1; i <= cp->cantidad; i++) {
            liberarTJugador(cp->arreglo[i]);
        }
        delete[] cp->arreglo;
        delete[] cp->pertenece;
        delete[] cp->prioridades;
        delete cp;
        cp = NULL; 
    }
}


void insertarEnCP(TJugador jugador, TColaDePrioridadJugador &cp) {
    if (estaVaciaCP(cp)) {
        cp->cantidad++;
        cp->arreglo[1] = jugador;
        cp->pertenece[idTJugador(jugador)] = true;
        cp->prioridades[idTJugador(jugador)] = edadTJugador(jugador);
    } else {
        cp->cantidad++;
        int pos = cp->cantidad;
        cp->arreglo[pos] = jugador;
        cp->pertenece[idTJugador(jugador)] = true;
        cp->prioridades[idTJugador(jugador)] = edadTJugador(jugador);
        
        if (!cp->prioridadInvertida){
        while (pos > 1 && cp->prioridades[idTJugador(cp->arreglo[pos])] < cp->prioridades[idTJugador(cp->arreglo[pos / 2])]) {
            intercambio(cp->arreglo[pos], cp->arreglo[pos / 2]);
            pos = pos / 2;
        }
        }else{

   while (pos > 1 && cp->prioridades[idTJugador(cp->arreglo[pos])] >= cp->prioridades[idTJugador(cp->arreglo[pos / 2])]) {
    intercambio(cp->arreglo[pos], cp->arreglo[pos / 2]);
    pos = pos / 2;
}
        }
    }
}

void intercambio(TJugador &jugador1, TJugador &jugador2) {
    TJugador temp = jugador1;
    jugador1 = jugador2;
    jugador2 = temp;
}

bool estaVaciaCP(TColaDePrioridadJugador cp) {
    return (cp->cantidad == 0); 
}

TJugador prioritario(TColaDePrioridadJugador cp) {
    return cp->arreglo[1];
}

void eliminarPrioritario(TColaDePrioridadJugador &cp) {
    if (cp->cantidad > 1) {
        nat id_eliminado = idTJugador(cp->arreglo[1]);
        cp->pertenece[id_eliminado] = false;
        liberarTJugador(cp->arreglo[1]); 
        cp->arreglo[1] = cp->arreglo[cp->cantidad];
        cp->prioridades[idTJugador(cp->arreglo[1])] = edadTJugador(cp->arreglo[1]);
        cp->pertenece[idTJugador(cp->arreglo[1])] = true;
        cp->cantidad--;

        filtradoDescendente(1, cp);
    } else if (cp->cantidad == 1) {
        nat id_eliminado = idTJugador(cp->arreglo[1]);
        cp->pertenece[id_eliminado] = false;
        liberarTJugador(cp->arreglo[1]); 
        cp->cantidad--;
    }
}

void filtradoDescendente(nat pos, TColaDePrioridadJugador &cp) {
    nat hijo_izquierdo = 2 * pos;
    nat hijo_derecho = 2 * pos + 1;
    nat extremo = pos;

    if (!cp->prioridadInvertida) {
        if (hijo_izquierdo <= cp->cantidad &&
            (cp->prioridades[idTJugador(cp->arreglo[hijo_izquierdo])] < cp->prioridades[idTJugador(cp->arreglo[extremo])])) {
            extremo = hijo_izquierdo;
        }

        if (hijo_derecho <= cp->cantidad &&
            (cp->prioridades[idTJugador(cp->arreglo[hijo_derecho])] < cp->prioridades[idTJugador(cp->arreglo[extremo])])) {
            extremo = hijo_derecho;
        }
    } else {
        if (hijo_izquierdo <= cp->cantidad &&
            (cp->prioridades[idTJugador(cp->arreglo[hijo_izquierdo])] >= cp->prioridades[idTJugador(cp->arreglo[extremo])])) {
            extremo = hijo_izquierdo;
        }

        if (hijo_derecho <= cp->cantidad &&
            (cp->prioridades[idTJugador(cp->arreglo[hijo_derecho])] >= cp->prioridades[idTJugador(cp->arreglo[extremo])])) {
            extremo = hijo_derecho;
        }
    }

    if (extremo != pos) {
        intercambio(cp->arreglo[pos], cp->arreglo[extremo]);
        filtradoDescendente(extremo, cp);
    }
}

bool estaEnCP(nat id, TColaDePrioridadJugador cp) {
   return (cp->pertenece[id]) ;
  
}

nat prioridad(nat id, TColaDePrioridadJugador cp) {
        return cp->prioridades[id];
}
