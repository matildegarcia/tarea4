#include "../include/pilaJugador.h"

TPilaJugador invertirPila(TPilaJugador pila);

struct rep_pilaJugadorElemento {
    TJugador jugador;
    rep_pilaJugadorElemento* siguiente;
};

struct rep_pilaJugador {
    rep_pilaJugadorElemento* tope;
    nat cantidad;
};

TPilaJugador crearTPilaJugador() {
    TPilaJugador pila = new rep_pilaJugador;
    pila->tope = NULL;
    pila->cantidad = 0;
    return pila;
}

void liberarTPilaJugador(TPilaJugador &p) {
    while (p->tope != NULL) {
        rep_pilaJugadorElemento* aux= p->tope;
        p->tope = p->tope->siguiente;
        liberarTJugador(aux->jugador);
        delete aux; 
    }
    delete p; 
    p = NULL;
}

nat cantidadEnTPilaJugador(TPilaJugador p) {
    return p->cantidad;
}

void apilarEnTPilaJugador(TPilaJugador &p, TJugador jugador) {
  
    rep_pilaJugadorElemento* nuevo = new rep_pilaJugadorElemento;
    nuevo->jugador = copiarTJugador(jugador);
    nuevo->siguiente = p->tope;
    p->tope = nuevo;
    p->cantidad++;
}

TJugador cimaDeTPilaJugador(TPilaJugador p) {
        return p->tope->jugador;
}

void desapilarDeTPilaJugador(TPilaJugador &p) {
    if ( p->tope!=NULL){ 
        rep_pilaJugadorElemento* aux = p->tope;
        p->tope = p->tope->siguiente;
        liberarTJugador(aux->jugador);
        delete aux; 
        p->cantidad--;
   
}
    }