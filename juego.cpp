#include "movimiento.h"
#include "tablero.h"
#include <iostream>
#include <fstream>
using namespace std;

bool cargar(tJuego& juego, string nombre) {
    ifstream archivo(nombre); 
    bool carga = true;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        carga = false;
    }

    cargar(juego.tablero, archivo); 
    juego.estado = JUGANDO;

    archivo.close(); 
    return carga;
}

void mostrar(const tJuego& juego) 
{
    mostrar(juego.tablero);
}

void actualizaEstado(tJuego& juego)
{
    if (ganador(juego))
       juego.estado = GANADOR;
    else if (!hayMovimientos(juego))
       juego.estado = BLOQUEO;
    else
       juego.estado = JUGANDO;
}

bool ganador(const tJuego& juego)
{
    bool ganado = true;
    bool ficha = false;
    int i = 0;

    // Primero comprobamos que haya una ficha en la meta.
    if(juego.tablero.celdas[juego.tablero.filaMeta][juego.tablero.colMeta] == FICHA)
    {
        //si si que lo hay hacemos una busqueda por el array para comprobar que no queden mas fichas para jugar
        while (i < juego.tablero.filas && !ficha)
        {
            int j = 0;
            while (j < juego.tablero.columnas && !ficha)
            {
                if (juego.tablero.celdas[i][j] == FICHA)
                {
                    ficha = true;
                    ganado = false;
                }
                else
                    j++;
            }
            i++;
        }
    }
    else
    {
        ganado = false;
    }
    return ganado;
}

bool hayMovimientos(tJuego& juego)
{
    tMovimientoLista listaMov;

    bool hayMov = false;
    int i = 0; 
    while (i < juego.tablero.filas && !hayMov) {
        int j = 0;
        while (j < juego.tablero.columnas && !hayMov)
        {
            if (!fichaBloqueada(juego.tablero, i, j))
                hayMov = true;
            else
            {
                j++;
            }
        }
        i++;
    }
    return hayMov;
}

void ejecutarMovimiento(tJuego& juego)
{
   int fila = 0, col = 0;
   tMovimiento movimiento = leeMovimiento(juego.tablero, fila, col);
   movimientoFicha(juego.tablero, fila, col, movimiento);
   actualizaEstado(juego);
}