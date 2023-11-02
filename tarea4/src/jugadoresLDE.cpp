#include "../include/jugadoresLDE.h"


struct rep_nodo
{
    TFecha fecha;
    TJugador jugador;
    rep_nodo *ant;
    rep_nodo *sig;
};

struct rep_jugadoresLDE
{
    rep_nodo *inicio;
    rep_nodo *fin;
    nat cantidad;
};

TJugadoresLDE crearTJugadoresLDE()
{
    TJugadoresLDE jugadores = new rep_jugadoresLDE;
    jugadores->inicio = NULL;
    jugadores->fin = NULL;
    jugadores->cantidad = 0; 
    return jugadores;
}


void insertarTJugadoresLDE(TJugadoresLDE &jugadores, TJugador &jugador, TFecha &fecha)
{
    rep_nodo *nuevoNodo = new rep_nodo;
    nuevoNodo->jugador = jugador;
    nuevoNodo->fecha = fecha;
    nuevoNodo->sig = NULL;
    nuevoNodo->ant = NULL;

    
    if (jugadores->inicio == NULL)
    {
        jugadores->inicio = nuevoNodo;
        jugadores->fin = nuevoNodo; 
        jugadores->cantidad = 1;   
        return;
    }

   
    if (compararTFechas(fecha, jugadores->inicio->fecha) > 0 || (compararTFechas(fecha, jugadores->inicio->fecha) == 0 && idTJugador(jugador) > idTJugador(jugadores->inicio->jugador)))
    {
        nuevoNodo->sig = jugadores->inicio;
        jugadores->inicio->ant = nuevoNodo;
        jugadores->inicio = nuevoNodo;
        jugadores->cantidad++; 
        return;
    }

    
    rep_nodo *actual = jugadores->inicio;
    while (actual->sig != NULL && (compararTFechas(fecha, actual->sig->fecha) < 0 || (compararTFechas(fecha, actual->sig->fecha) == 0 && idTJugador(jugador) > idTJugador(actual->sig->jugador))))
    {
        actual = actual->sig;
    }

    nuevoNodo->sig = actual->sig;
    if (actual->sig != NULL)
    {
        actual->sig->ant = nuevoNodo;
    }
    nuevoNodo->ant = actual;
    actual->sig = nuevoNodo;
    jugadores->fin =nuevoNodo;
    jugadores->cantidad++;
}



void liberarTJugadoresLDE(TJugadoresLDE &jugadoresLDE)
{
    rep_nodo *actual = jugadoresLDE->inicio;
    while (actual != NULL)
    {
        rep_nodo *siguiente = actual->sig;

        liberarTFecha(actual->fecha);
        liberarTJugador(actual->jugador);

        delete actual;
        actual = siguiente;
    }

    jugadoresLDE->cantidad = 0; 
    delete jugadoresLDE;
    jugadoresLDE = NULL;
}

void imprimirMayorAMenorTJugadoresLDE(TJugadoresLDE jugadores) {
    if (jugadores != NULL) {
        rep_nodo* actual = jugadores->inicio;
        while (actual != NULL) {
            imprimirTJugador(actual->jugador);
            imprimirTFecha(actual->fecha);
            actual = actual->sig;
        }
    }
}

void imprimirMenorAMayorTJugadoresLDE(TJugadoresLDE jugadores){

  if (jugadores != NULL) {
        rep_nodo* actual = jugadores->fin;
        while (actual != NULL) {
            imprimirTJugador(actual->jugador);
            imprimirTFecha(actual->fecha);
            actual = actual->ant;
        }
    }
}





nat cantidadTJugadoresLDE(TJugadoresLDE jugadores)
{
    return jugadores->cantidad; 
}


void eliminarInicioTJugadoresLDE(TJugadoresLDE &jugadores)
{
    if (jugadores->inicio != NULL)
    {
        rep_nodo *primerNodo = jugadores->inicio;
        rep_nodo *nuevoInicio = primerNodo->sig;
        jugadores->inicio = nuevoInicio;

        if (nuevoInicio != NULL)
        {
            jugadores->inicio->ant = NULL;
        }

        liberarTFecha(primerNodo->fecha);
        liberarTJugador(primerNodo->jugador);
        delete primerNodo;

        jugadores->cantidad--;

        if (jugadores->cantidad == 0)
        {
            jugadores->fin = NULL;
        }
    }
}




void eliminarFinalTJugadoresLDE(TJugadoresLDE &jugadores)
{
    if (jugadores->fin != NULL)
    {
        rep_nodo *ultimoNodo = jugadores->fin;
        rep_nodo *nuevoFin = ultimoNodo->ant;
        jugadores->fin = nuevoFin;

        if (nuevoFin != NULL)
        {
            jugadores->fin->sig = NULL;
        }

        liberarTFecha(ultimoNodo->fecha);
        liberarTJugador(ultimoNodo->jugador);
        delete ultimoNodo;

        jugadores->cantidad--;

        if (jugadores->cantidad == 0)
        {
            jugadores->inicio = NULL;
        }
    }
}


bool estaEnTJugadoresLDE(TJugadoresLDE jugadores, nat id)

{
    rep_nodo *actual = jugadores->inicio;

    while (actual != NULL)
    {
        if (idTJugador(actual->jugador) == id)
        {
            return true; 
        }
        actual = actual->sig;
    }

    return false; 
}





TJugador obtenerTJugadorDeTJugadoresLDE(TJugadoresLDE jugadores, nat id)
{
    rep_nodo *actual = jugadores->inicio;
     TJugador jugadorEncontrado = NULL; 
    

    while (actual != NULL)
    {
        if (idTJugador(actual->jugador) == id)
        {
           jugadorEncontrado =  actual->jugador; 
        }
        actual = actual->sig;
    }
    return  jugadorEncontrado;
}


TFecha obtenerTFechaDeTJugadoresLDE(TJugadoresLDE jugadores, nat id)
{
    TFecha fechaMayor = NULL; 
    rep_nodo *actual = jugadores->inicio;

    while (actual != NULL)
    {
        if (idTJugador(actual->jugador) == id)
        {
          
            if (fechaMayor == NULL || compararTFechas(actual->fecha, fechaMayor) > 0)
            {
                fechaMayor = copiarTFecha(actual->fecha);
            }
        }
        actual = actual->sig;
    }


    return fechaMayor;
}

TJugadoresLDE obtenerSegunTFecha(TJugadoresLDE jugadores, TFecha fecha)
{
    TJugadoresLDE jugadoresConFecha = crearTJugadoresLDE(); 
    rep_nodo *actual = jugadores->inicio;

    while (actual != NULL)
    {
        if (compararTFechas(actual->fecha, fecha) == 0)
        {
            TJugador copiaJugador = copiarTJugador(actual->jugador);
            insertarTJugadoresLDE(jugadoresConFecha, copiaJugador, actual->fecha);
        }
        actual = actual->sig;
    }

    return jugadoresConFecha;
}



TJugadoresLDE unirTJugadoresLDE(TJugadoresLDE &jugadores1, TJugadoresLDE &jugadores2)
{
    if (jugadores2->cantidad == 0)
    {
        liberarTJugadoresLDE(jugadores2);
        return jugadores1;
    }

    if (jugadores1->cantidad == 0)
    {
        liberarTJugadoresLDE(jugadores1);
        return jugadores2;
    }

    TJugadoresLDE jugadoresUnion = crearTJugadoresLDE();
   
    rep_nodo *actual1 = jugadores1->inicio;
    
    while (actual1 != NULL)
    {
        TJugador copiaJugador = copiarTJugador(actual1->jugador);
        TFecha copia1 = copiarTFecha(actual1->fecha);

        insertarTJugadoresLDE(jugadoresUnion, copiaJugador, copia1);

        actual1 = actual1->sig;
    }

    rep_nodo *actual2 = jugadores2->inicio;
    
    while (actual2 != NULL)
    {
        TJugador copiaJugador = copiarTJugador(actual2->jugador);
        TFecha copia2 = copiarTFecha(actual2->fecha);

        insertarTJugadoresLDE(jugadoresUnion, copiaJugador, copia2);

        actual2 = actual2->sig;
    }

    jugadoresUnion->cantidad = jugadores1->cantidad + jugadores2->cantidad;
   
    liberarTJugadoresLDE(jugadores1);
    liberarTJugadoresLDE(jugadores2);

    return jugadoresUnion;
}


TJugador obtenerInicioDeTJugadoresLDE(TJugadoresLDE jugadores) {
    if (jugadores->inicio != NULL) {
        return jugadores->inicio->jugador;
    } else {
        return NULL;
    }
}

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES TAREA 4 ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void eliminarJugadorConNombreTJugadoresLDE(TJugadoresLDE &jugadores, const char nombre[100]) {
    rep_nodo *actual = jugadores->inicio;

    while (actual != NULL) {
        if (strcmp(nombre, nombreTJugador(actual->jugador)) == 0) {   // strcmp devuelve 0 si los strings son iguales

            if (actual->ant == NULL) { 
                eliminarInicioTJugadoresLDE(jugadores);
            } else if (actual->sig == NULL) {
                eliminarFinalTJugadoresLDE(jugadores);
            } else {
                actual->ant->sig = actual->sig;
                actual->sig->ant = actual->ant;
                liberarTJugador(actual->jugador);
                liberarTFecha(actual->fecha);
                delete actual;
                jugadores->cantidad--;
            }
            return; 
        }
        actual = actual->sig;
    }
}

bool estaJugadorConNombreEnTJugadoresLDE(TJugadoresLDE jugadores, const char nombre[100]) {
    rep_nodo *actual = jugadores->inicio;

    while (actual != NULL) {
        if (strcmp(nombre, nombreTJugador(actual->jugador)) == 0) {
            return true;
        }
        actual = actual->sig;
    }
    return false;
}

TJugador obtenerJugadorConNombreTJugadoresLDE(TJugadoresLDE jugadores, const char nombre[100]) {
    TJugador jugadorEncontrado = NULL;
    rep_nodo *actual = jugadores->inicio;

    while (actual != NULL && jugadorEncontrado == NULL) {
        if (strcmp(nombre, nombreTJugador(actual->jugador)) == 0) {
            jugadorEncontrado = actual->jugador;
        } else {
            actual = actual->sig;
        }
    }

    return jugadorEncontrado;
}
///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES TAREA 4 ///////////////////////////////
///////////////////////////////////////////////////////////////////////////
