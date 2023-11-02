#include "../include/jugadoresABB.h"
#include "../include/colaJugadoresABB.h"
#include "../include/pilaJugador.h"

void auxLiberaNodo(TJugadoresABB nodo);
void mayoresTJugadoresABBRecursivo(TJugadoresABB jugadoresABB, nat edad, TJugadoresABB &nuevosJugadoresABB);
TPilaJugador invertirPila(TPilaJugador pila);

struct rep_jugadoresABB {
  
TJugadoresABB left, right;
TJugador jugador;
nat cantidad;

};

TJugadoresABB crearTJugadoresABB() {
    return NULL;
}


bool esVacioTJugadoresABB(TJugadoresABB jugadoresABB) {
    return (jugadoresABB == NULL) ;
}

void insertarTJugadoresABB(TJugadoresABB &jugadoresABB, TJugador jugador) {
    if (jugadoresABB == NULL) {
        jugadoresABB = new rep_jugadoresABB;
        jugadoresABB->left = NULL;
        jugadoresABB->right = NULL;
        jugadoresABB->jugador = jugador;
        jugadoresABB->cantidad = 1; 
    } else {
        int idJugador = idTJugador(jugador);
        int idNodo = idTJugador(jugadoresABB->jugador);
        
        if (idJugador < idNodo) {
            insertarTJugadoresABB(jugadoresABB->left, jugador);
        } else if (idJugador > idNodo) {
            insertarTJugadoresABB(jugadoresABB->right, jugador);
        }
        
        
        jugadoresABB->cantidad = 1; 
        if (jugadoresABB->left != NULL) {
            jugadoresABB->cantidad += jugadoresABB->left->cantidad;
        }
        if (jugadoresABB->right != NULL) {
            jugadoresABB->cantidad += jugadoresABB->right->cantidad;
        }
    }
}

void auxLiberaNodo(TJugadoresABB nodo) {
  if (nodo != NULL) {
    auxLiberaNodo(nodo->left);
    auxLiberaNodo(nodo->right);
    
    liberarTJugador(nodo->jugador);
    delete nodo;
  }
}

void liberarTJugadoresABB(TJugadoresABB &jugadoresABB) {
    auxLiberaNodo(jugadoresABB);
    jugadoresABB = NULL;
}

void imprimirTJugadoresABB(TJugadoresABB jugadoresABB) {
    if (jugadoresABB != NULL) {
       
        imprimirTJugadoresABB(jugadoresABB->left);
      
        imprimirTJugador(jugadoresABB->jugador);
        
        imprimirTJugadoresABB(jugadoresABB->right);
    }
}

nat cantidadTJugadoresABB(TJugadoresABB jugadoresABB) {
    if (jugadoresABB != NULL) {
        return jugadoresABB->cantidad;
    } else {
        return 0;
    }
}

TJugador maxIdJugador(TJugadoresABB jugadoresABB) {
    if (jugadoresABB->right == NULL) {
        return jugadoresABB->jugador; 
    }
    return maxIdJugador(jugadoresABB->right); 
}

bool estaTJugadoresABB(TJugadoresABB jugadoresABB, nat id) {
    if (jugadoresABB == NULL) {
        return false; 
    }

    nat idNodo = idTJugador(jugadoresABB->jugador);

    if (id == idNodo) {
        return true; 
    } else if (id < idNodo) {
        return estaTJugadoresABB(jugadoresABB->left, id); 
    } else {
        return estaTJugadoresABB(jugadoresABB->right, id); 
    }
}

void removerTJugadoresABB(TJugadoresABB &jugadoresABB, nat id) {
    if (jugadoresABB == NULL) {
        return;
    }

    if (id < idTJugador(jugadoresABB->jugador)) {
        removerTJugadoresABB(jugadoresABB->left, id);
    } else if (id > idTJugador(jugadoresABB->jugador)) {  
        removerTJugadoresABB(jugadoresABB->right, id);
    } else {
        if (jugadoresABB->left == NULL && jugadoresABB->right == NULL) {

            liberarTJugador(jugadoresABB->jugador); 
            delete jugadoresABB;
            jugadoresABB = NULL;
        } else if (jugadoresABB->right == NULL) {

            TJugadoresABB temp = jugadoresABB;
            jugadoresABB = jugadoresABB->left;
            liberarTJugador(temp->jugador); 
            delete temp;
        } else if (jugadoresABB->left == NULL) {

            TJugadoresABB temp = jugadoresABB;
            jugadoresABB = jugadoresABB->right;
            liberarTJugador(temp->jugador); 
            delete temp;
        } else {
            TJugador temp = copiarTJugador(maxIdJugador(jugadoresABB->left));
            liberarTJugador(jugadoresABB->jugador); 
            jugadoresABB->jugador = temp; 
            removerTJugadoresABB(jugadoresABB->left, idTJugador(temp));
        }
    }
    
    if (jugadoresABB != NULL) {
        jugadoresABB->cantidad = 1; 
        if (jugadoresABB->left != NULL) {
            jugadoresABB->cantidad += jugadoresABB->left->cantidad;
        }
        if (jugadoresABB->right != NULL) {
            jugadoresABB->cantidad += jugadoresABB->right->cantidad;
        }
    }
}

TJugador obtenerDeTJugadoresABB(TJugadoresABB jugadoresABB, nat id) {
    if (jugadoresABB == NULL) {
        return NULL; 
    }

    nat idNodo = idTJugador(jugadoresABB->jugador);

    if (id == idNodo) {
        return jugadoresABB->jugador; 
    } else if (id < idNodo) {
        return obtenerDeTJugadoresABB(jugadoresABB->left, id); 
    } else {
        return obtenerDeTJugadoresABB(jugadoresABB->right, id); 
    }
}

nat alturaTJugadoresABB(TJugadoresABB jugadoresABB) {
    nat resultado;
    if (jugadoresABB == NULL) {
        return 0; 
    }

    nat alturaIzquierdo = alturaTJugadoresABB(jugadoresABB->left);
    nat alturaDerecho = alturaTJugadoresABB(jugadoresABB->right);

    if (alturaIzquierdo < alturaDerecho ){
        resultado = 1 + alturaDerecho ;
    
    } else{
        resultado= 1 + alturaIzquierdo;
    }
    return resultado;
}

bool esPerfectoTJugadoresABB(TJugadoresABB jugadoresABB) {
    if (jugadoresABB == NULL) {
        return true; 
    }

    nat alturaIzquierdo = alturaTJugadoresABB(jugadoresABB->left);
    nat alturaDerecho = alturaTJugadoresABB(jugadoresABB->right);

    if (alturaIzquierdo != alturaDerecho) {
        return false; 
    }

    return esPerfectoTJugadoresABB(jugadoresABB->left) && esPerfectoTJugadoresABB(jugadoresABB->right);
}

TJugadoresABB mayoresTJugadoresABB(TJugadoresABB jugadoresABB, nat edad) {
    TJugadoresABB nuevosJugadoresABB = crearTJugadoresABB();
    mayoresTJugadoresABBRecursivo(jugadoresABB, edad, nuevosJugadoresABB);
    return nuevosJugadoresABB;
}

void mayoresTJugadoresABBRecursivo(TJugadoresABB jugadoresABB, nat edad, TJugadoresABB &nuevosJugadoresABB) {
    if (jugadoresABB == NULL) {
        return;
    }

    mayoresTJugadoresABBRecursivo(jugadoresABB->left, edad, nuevosJugadoresABB);

    if (edadTJugador(jugadoresABB->jugador) > edad) {
        insertarTJugadoresABB(nuevosJugadoresABB, copiarTJugador(jugadoresABB->jugador));
    }

    mayoresTJugadoresABBRecursivo(jugadoresABB->right, edad, nuevosJugadoresABB);
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

nat amplitudTJugadoresABB(TJugadoresABB t) {
    if (esVacioTJugadoresABB(t)) {
        return 0;  
    }

    TColaJugadoresABB cola = crearTColaJugadoresABB(); 

    encolarEnTColaJugadoresABB(t, cola); 
    encolarEnTColaJugadoresABB(NULL, cola);  

    nat amplitudMax = 0;  
    nat amplitudActual = 0;

    while (cantidadEnTColaJugadoresABB(cola) > 1) { 
        TJugadoresABB actual = frenteDeTColaJugadoresABB(cola);
        desencolarDeTColaJugadoresABB(cola);

        if (actual == NULL) {    
            
            if (amplitudActual > amplitudMax) { 
                amplitudMax = amplitudActual;
            }

           amplitudActual= 0;      
            encolarEnTColaJugadoresABB(NULL, cola);  
        } else {                                          
            amplitudActual++;  
            if (actual->left != NULL) {
                encolarEnTColaJugadoresABB(actual->left, cola);
            }
            if (actual->right != NULL) {
                encolarEnTColaJugadoresABB(actual->right, cola);
            }
        }
    }
    if (amplitudActual > amplitudMax) {  
        amplitudMax = amplitudActual;
    }

    liberarTColaJugadoresABB(cola);  
    return amplitudMax;
}



TPilaJugador serializarTJugadoresABB(TJugadoresABB t) {
    TPilaJugador pila = crearTPilaJugador();

    if (!esVacioTJugadoresABB(t)) {
        TColaJugadoresABB cola = crearTColaJugadoresABB();
        encolarEnTColaJugadoresABB(t, cola);

        while (cantidadEnTColaJugadoresABB(cola) > 0) {
            for (nat i = 0; i < cantidadEnTColaJugadoresABB(cola); i++) {
                TJugadoresABB nodo = frenteDeTColaJugadoresABB(cola);
                desencolarDeTColaJugadoresABB(cola);
                apilarEnTPilaJugador(pila, nodo->jugador);

                if (nodo->left != NULL) {
                    encolarEnTColaJugadoresABB(nodo->left, cola);
                }
                if (nodo->right != NULL) {
                    encolarEnTColaJugadoresABB(nodo->right, cola);
                }
            }
        }

        liberarTColaJugadoresABB(cola);
    }

    TPilaJugador pilaInvertida = invertirPila(pila);
    return pilaInvertida;
}

TPilaJugador invertirPila(TPilaJugador pila) {
    TPilaJugador pilaInvertida = crearTPilaJugador();
    while (cantidadEnTPilaJugador(pila) > 0) {
        apilarEnTPilaJugador(pilaInvertida, cimaDeTPilaJugador(pila));
        desapilarDeTPilaJugador(pila);
    }
    liberarTPilaJugador(pila);
    return pilaInvertida;
}


TJugadoresABB deserializarTJugadoresABB(TPilaJugador &p) {
    TJugadoresABB arbol = crearTJugadoresABB(); 
   
    while (cantidadEnTPilaJugador(p) > 0) {
        TJugador jugador = cimaDeTPilaJugador(p);
        insertarTJugadoresABB(arbol, copiarTJugador(jugador));
        desapilarDeTPilaJugador(p);
    }
    liberarTPilaJugador(p);
    return arbol;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////