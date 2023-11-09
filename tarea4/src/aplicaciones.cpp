#include "../include/aplicaciones.h"
#include "../include/colaDePrioridadJugador.h"


void listarEnOrden(TTablaJugadores t, char** nombres, nat n) {
    TColaDePrioridadJugador cola = crearCP(100);

    for (nat i = 0; i < n; i++) {

   TJugador jugador =  obtenerJugadorDeTTablaJugadores( t, nombres[i]);
   
     if (jugador !=NULL){
            insertarEnCP(copiarTJugador(jugador), cola);

     }
            }

    while (!estaVaciaCP(cola)) {
        TJugador jugador = prioritario(cola);
        imprimirTJugador(jugador);
        eliminarPrioritario(cola);
    }

    liberarCP(cola);
}
