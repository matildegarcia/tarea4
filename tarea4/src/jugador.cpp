#include "../include/jugador.h"

struct rep_jugador
{
    nat id;
    nat edad;
    char pais[100];
    char nombre[100];
    TPartida partida;
};

TJugador crearTJugador(nat id, nat edad, const char pais[100], const char nombre[100], TPartida partida)
{
    TJugador nuevoJugador = new rep_jugador;

    nuevoJugador->id = id;
    nuevoJugador->edad = edad;

    strncpy(nuevoJugador->pais, pais, sizeof(nuevoJugador->pais));
    strncpy(nuevoJugador->nombre, nombre, sizeof(nuevoJugador->nombre));
    nuevoJugador->partida = partida;

    return nuevoJugador;
}

void liberarTJugador(TJugador &jugador)
{
    if (jugador != NULL)
    {

        liberarTPartida(jugador->partida);
        delete jugador;
        jugador = NULL;
    }
}

void imprimirTJugador(TJugador jugador)
{
    if (jugador != NULL)
    {
        printf("Jugador %d: %s, %s, %d años\n", jugador->id, jugador->nombre, jugador->pais, jugador->edad);
        imprimirTPartida(jugador->partida);
    }
}

nat idTJugador(TJugador jugador)
{
    return jugador->id;
}

nat edadTJugador(TJugador jugador)
{
    return jugador->edad;
}

char *nombreTJugador(TJugador jugador)
{
    return jugador->nombre;
}

char *paisTJugador(TJugador jugador)
{
    return jugador->pais;
}

TPartida partidaTJugador(TJugador jugador)
{
    return jugador->partida;
}

void agregarJugadaATJugador(TJugador &jugador, TJugada jugada)
{

    agregarEnTPartida(jugador->partida, jugada);
}

void removerJugadaDeTJugador(TJugador &jugador, int numeroDeJugada)
{
    if (jugador != NULL)
    {
        removerDeTPartida(jugador->partida, numeroDeJugada);
    }
}

bool estaEnPartidaDeTJugador(TJugador jugador, int numeroDeJugada)
{

    bool esta = false;
    if (jugador != NULL)
    {
        return estaEnTPartida(jugador->partida, numeroDeJugada);
        esta = true;
    }

    return esta;
}

TJugada obtenerDePartidaDeTJugador(TJugador jugador, int numeroDeJugada)
{
    return obtenerDeTPartida(jugador->partida, numeroDeJugada);
}

TJugador copiarTJugador(TJugador jugador)
{
 if (jugador!=NULL){
    TJugador nuevoJugador = new rep_jugador;
    nuevoJugador->id = jugador->id;
    nuevoJugador->edad = jugador->edad;

    strncpy(nuevoJugador->pais, jugador->pais, sizeof(nuevoJugador->pais));
    strncpy(nuevoJugador->nombre, jugador->nombre, sizeof(nuevoJugador->nombre));

    nuevoJugador->partida = copiarTPartida(jugador->partida);

    return nuevoJugador;
    }else{
        return NULL;
    }
}