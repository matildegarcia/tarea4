#include "../include/conjuntoIds.h"

struct rep_conjuntoIds {
    bool* elem;
    nat cantMax;
    nat cant;  
};


TConjuntoIds crearTConjuntoIds(nat cantMax) {
    TConjuntoIds conjunto = new rep_conjuntoIds;
    conjunto->cantMax = cantMax;
    conjunto->elem = new bool[cantMax];
    conjunto->cant = 0; 
    for (nat i = 0; i < cantMax; i++) {
        conjunto->elem[i] = false;
    }
    return conjunto;
}


bool esVacioTConjuntoIds(const TConjuntoIds c) {
    return c->cant== 0; 
}


void insertarTConjuntoIds(nat id, TConjuntoIds& c) {
    if (id > 0 && id <= c->cantMax && !c->elem[id - 1]) {
        c->elem[id - 1] = true;
        c->cant++;  
    }
}

void borrarTConjuntoIds(nat id, TConjuntoIds& c) {
    if (id > 0 && id <= c->cantMax && c->elem[id - 1]) {
        c->elem[id - 1] = false;
        c->cant--;  
    }
}

bool perteneceTConjuntoIds(nat id, TConjuntoIds c) {
    if (id > 0 && id <= c->cantMax) {
        return c->elem[id - 1];
    }
    return false;
}

nat cardinalTConjuntoIds(TConjuntoIds c) {
    return c->cant;
}

nat cantMaxTConjuntoIds(TConjuntoIds c) {
    return c->cantMax;
}

void imprimirTConjuntoIds(TConjuntoIds c) {
    for (nat i = 1; i <= cantMaxTConjuntoIds(c); i++) {
        if (perteneceTConjuntoIds(i, c)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}


void liberarTConjuntoIds(TConjuntoIds &c) {
    delete[] c->elem; 
    delete c; 
    c = NULL; 
}


TConjuntoIds unionTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2) {
    TConjuntoIds resultado = crearTConjuntoIds(c1->cantMax);
    
    for (nat i = 1; i <= c1->cantMax; i++) {
        if (perteneceTConjuntoIds(i, c1) || perteneceTConjuntoIds(i, c2)) {
            insertarTConjuntoIds(i, resultado);
        }
    }
    return resultado;
}

TConjuntoIds interseccionTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2) {
    TConjuntoIds inter = crearTConjuntoIds(c1->cantMax);
    
    for (nat i = 1; i <= c1->cantMax; i++) {
        if (perteneceTConjuntoIds(i, c1) && perteneceTConjuntoIds(i, c2)) {
            insertarTConjuntoIds(i, inter);
        }
    }
    return inter;
}

TConjuntoIds diferenciaTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2) {
    TConjuntoIds dif = crearTConjuntoIds(c1->cantMax);

    for (nat i = 1; i <= c1->cantMax; i++) {
        if (perteneceTConjuntoIds(i, c1) && !perteneceTConjuntoIds(i, c2) ) {
            insertarTConjuntoIds(i, dif);
        }
    }
    return dif;
}