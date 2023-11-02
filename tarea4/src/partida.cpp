#include "../include/partida.h"

struct rep_partida
{

    TJugada jugada;
    rep_partida *sig;
};

TPartida crearTPartida()
{
    TPartida nuevaPartida = NULL; 
    return nuevaPartida;
}

void agregarEnTPartida(TPartida &partida, TJugada jugada)
{

    TPartida nuevoNodo = new rep_partida;
    nuevoNodo->jugada = jugada;

    if (partida == NULL || numeroTJugada(jugada) < numeroTJugada(partida->jugada))
    {

        nuevoNodo->sig = partida;
        partida = nuevoNodo;
    }
    else
    {

        TPartida actual = partida;

        while (actual->sig != NULL && numeroTJugada(jugada) > numeroTJugada(actual->sig->jugada))
        {
            actual = actual->sig;
        }

        nuevoNodo->sig = actual->sig;
        actual->sig = nuevoNodo;
    }
}

void imprimirTPartida(TPartida partida)
{
    TPartida actual = partida;

    while (actual != NULL)
    {
        imprimirTJugada(actual->jugada);
        actual = actual->sig;
    }
}

void liberarTPartida(TPartida &partida)
{
    while (partida != NULL)
    {
        TPartida siguiente = partida->sig;
        liberarTJugada(partida->jugada);
        delete partida;
        partida = siguiente;
    }
}

bool esVaciaTPartida(TPartida partida)
{
    return (partida == NULL);
}

TPartida copiarTPartida(TPartida partida)
{
    TPartida nuevaPartida = crearTPartida(); 
    TPartida actual = partida;

    while (actual != NULL)
    {

        TJugada copiaJugada = copiarTJugada(actual->jugada);
        agregarEnTPartida(nuevaPartida, copiaJugada);

        actual = actual->sig;
    }

    return nuevaPartida;
}

bool estaEnTPartida(TPartida partida, int numeroDeJugada)
{
    TPartida actual = partida;
    bool encontrado = false;

    while (actual != NULL)
    {
        if (numeroTJugada(actual->jugada) == numeroDeJugada)
        {
            encontrado = true;
        }
        actual = actual->sig;
    }

    return encontrado;
}

TJugada obtenerDeTPartida(TPartida partida, int numeroDeJugada)
{

    TPartida actual = partida;

    while (actual != NULL)
    {
        if (numeroTJugada(actual->jugada) == numeroDeJugada)
        {
            return actual->jugada;
        }
        actual = actual->sig;
    }

    return NULL;
}

void imprimirJugadasConMovimiento(TPartida partida, int pos, Movimiento mov)
{

    TPartida actual = partida;

    while (actual != NULL)
    {
        if (movimientoTJugada(actual->jugada)[pos - 1] == mov)
        {

            imprimirTJugada(actual->jugada);
        }
        actual = actual->sig;
    }
}

void removerDeTPartida(TPartida &partida, int numeroDeJugada)
{
    TPartida actual = partida;
    TPartida anterior = NULL;
    bool jugadaEliminada = false;

    while (actual != NULL && !jugadaEliminada)
    {
        if (numeroTJugada(actual->jugada) == numeroDeJugada)
        {

            if (anterior != NULL)
            {

                anterior->sig = actual->sig;
                liberarTJugada(actual->jugada);
                delete actual;
            }
            else
            {

                partida = actual->sig;
                liberarTJugada(actual->jugada);
                delete actual;
            }
            jugadaEliminada = true;
        }
        else
        {
            anterior = actual;
            actual = actual->sig;
        }
    }
}
