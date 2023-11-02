#include "../include/colaJugadoresABB.h"
#include "../include/jugadoresLDE.h"

struct rep_auxiliar {
    TJugadoresABB jugador;
    rep_auxiliar* sig;
};

struct rep_colaJugadoresABB {
    rep_auxiliar* cabeza;
    rep_auxiliar* cola;
    nat cantidad;
};

 TColaJugadoresABB crearTColaJugadoresABB() {
   
    TColaJugadoresABB cola = new rep_colaJugadoresABB;
    cola->cabeza = NULL;
    cola->cola = NULL;
    cola->cantidad = 0;
    return cola;
}

void liberarTColaJugadoresABB(TColaJugadoresABB &c) {
    while (c->cabeza != NULL) {
        rep_auxiliar* borro = c->cabeza;
        c->cabeza = c->cabeza->sig;
        delete borro; 
    }
    delete c; 
    c = NULL;
}

nat cantidadEnTColaJugadoresABB(TColaJugadoresABB c) { 
   return c->cantidad;
 }

void encolarEnTColaJugadoresABB(TJugadoresABB t, TColaJugadoresABB &c) {
    rep_auxiliar* nuevoNodo = new rep_auxiliar;
    nuevoNodo->jugador = t;
    nuevoNodo->sig = NULL;
    if (c->cola == NULL) {
        c->cabeza = nuevoNodo;
        c->cola = nuevoNodo;
    } else {
        c->cola->sig = nuevoNodo;
        c->cola = nuevoNodo;
    }
    c->cantidad++;
}

TJugadoresABB frenteDeTColaJugadoresABB(TColaJugadoresABB c) { 
  return   c->cabeza->jugador;
}

void desencolarDeTColaJugadoresABB(TColaJugadoresABB &c) {

    if(c->cabeza!=NULL){  
        rep_auxiliar* d = c->cabeza;
        c->cabeza = c->cabeza->sig;
        if (c->cabeza== NULL){
          c->cola=NULL;
        }
     c->cantidad--;
        delete d; 
    }
}