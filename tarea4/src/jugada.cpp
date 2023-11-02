#include "../include/jugada.h"

const char *obtenerNombreMovimiento(int numero);

struct rep_jugada
{
    int numero;
    Movimiento movimientos[4];
};


TJugada crearTJugada(int numero, Movimiento mov1, Movimiento mov2, Movimiento mov3, Movimiento mov4)
{

    TJugada nuevaJugada = new rep_jugada; 

    nuevaJugada->numero = numero; 

    nuevaJugada->movimientos[0] = mov1;
    nuevaJugada->movimientos[1] = mov2;
    nuevaJugada->movimientos[2] = mov3;
    nuevaJugada->movimientos[3] = mov4;

    return nuevaJugada;
}


int numeroTJugada(TJugada jugada)
{
    int devuelve = 0;
    if (jugada != NULL)
    {
        devuelve = jugada->numero;
    }
    return devuelve;
}


Movimiento *movimientoTJugada(TJugada jugada)
{

    return jugada->movimientos;
}

bool tieneMovimientoEnPosTJugada(TJugada jugada, int pos, Movimiento mov)
{
    if (pos >= 0 && pos < 4)
    { 
        return jugada->movimientos[pos] == mov;
    }
    return false; 
}

const char *obtenerNombreMovimiento(int numero)
{ 
    switch (numero)
    {
    case 1:
        return "Derecha";
    case 2:
        return "Izquierda";
    case 3:
        return "Arriba";
    case 4:
        return "Abajo";
    default:
        return "Desconocido";
    }
}

void imprimirTJugada(TJugada jugada)
{
    printf("Jugada: %d \n", jugada->numero);
    printf("Movimientos: %s %s %s %s \n",
           obtenerNombreMovimiento(jugada->movimientos[0]),
           obtenerNombreMovimiento(jugada->movimientos[1]),
           obtenerNombreMovimiento(jugada->movimientos[2]),
           obtenerNombreMovimiento(jugada->movimientos[3]));
}

void liberarTJugada(TJugada &jugada)
{
    if (jugada != NULL)
    {
        delete jugada; 
        jugada = NULL; 
    }
}

TJugada copiarTJugada(TJugada jugada)
{
    if (jugada == NULL)
    {
        return NULL;
    }

    TJugada nuevaJugada = new rep_jugada;

    nuevaJugada->numero = jugada->numero;

    for (int i = 0; i < 4; i++)
    {
        nuevaJugada->movimientos[i] = jugada->movimientos[i];
    }

    return nuevaJugada;
}