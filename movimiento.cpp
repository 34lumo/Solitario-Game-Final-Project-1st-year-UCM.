#include "movimiento.h"
#include "tablero.h"
#include "juego.h"
#include <iostream>
using namespace std;

tMovimiento leeMovimiento(tTablero& tablero, int& fila, int& col)
{
    tMovimiento movimiento;
    tMovimientoLista listaMov;
    listaMov.contador = 0; 

    cout << "Selecciona una Ficha (Fila y Columna): ";
    cin >> fila >> col;
    fila = fila - 1;
    col = col - 1;
    if(eleccionValida(tablero, fila, col))
    {
        if (movimientosPosibles(tablero, fila, col, listaMov))
            movimiento = eligeMovimiento(listaMov);
        else
        {
                cout << "No hay movimientos posibles para la ficha seleccionada." << endl;
        }
    }
    else
    {
        cout << "En la posición seleccionada no se encuentra ninguna ficha" << endl;
    }

    return movimiento;
}


tMovimiento moviendo(tDireccion dir, int fila, int col)
{
    tMovimiento movimiento;

    movimiento.dir = dir;

    //Calcular Celda Saltada.
    movimiento.filaSaltada = fila + DIRECCIONES[dir][0];
    movimiento.colSaltada = col + DIRECCIONES[dir][1];
 
    //Calcular celda destino.
    movimiento.filaDestino = movimiento.filaSaltada + DIRECCIONES[dir][0];
    movimiento.colDestino = movimiento.colSaltada + DIRECCIONES[dir][1];

    return movimiento;
}

bool movimientosPosibles(tTablero& tablero, int fila, int col, tMovimientoLista& listaMov)
{
    bool hayMovimientos = false;
    listaMov.contador = 0;

    for (int dir = 0; dir < NUMDIR; dir++)
    {
        tMovimiento movimiento = moviendo(tDireccion(dir), fila, col);

        if (valida(tablero, movimiento.filaDestino, movimiento.colDestino))
        {
            if (tablero.celdas[movimiento.filaDestino][movimiento.colDestino] == VACIA && tablero.celdas[movimiento.filaSaltada][movimiento.colSaltada] == FICHA)
            {
                listaMov.posibles[listaMov.contador] = movimiento;
                hayMovimientos = true;
                listaMov.contador++;
            }
        }
    }
        
    return hayMovimientos;
}
//En el caso de que haya un solo movimiento
bool unicoMovimiento(tTablero& tablero, int fila, int col, tMovimientoLista& listaMov) 
{
    bool unicoMov = false;
    if (listaMov.contador == 1) 
    {
        movimientoFicha(tablero, fila, col, listaMov.posibles[0]); 
        unicoMov = true;
    }
    return unicoMov;
}

//En el caso de que haya mas de un unico movimiento.
tMovimiento eligeMovimiento(const tMovimientoLista& listaMov) 
{
    int opcion;

    if (listaMov.contador == 1)
      opcion = 0;

    else 
    {
        for (int i = 0; i < listaMov.contador; i++) {
            switch (listaMov.posibles[i].dir) {
            case ARRIBA:
                cout << "Arriba" << endl;
                break;
            case DERECHA:
                cout << "Derecha" << endl;
                break;
            case ABAJO:
                cout << "Abajo" << endl;
                break;
            case IZQUIERDA:
                cout << "Izquierda" << endl;
                break;
            }
        }
        cin >> opcion;
        opcion = opcion - 1;
    }
    return listaMov.posibles[opcion];
}

void movimientoFicha(tTablero& tablero, int fila, int col, tMovimiento& mov)
{
   ponCelda(tablero, fila, col, VACIA);
   ponCelda(tablero, mov.filaSaltada, mov.colSaltada, VACIA);
   ponCelda(tablero, mov.filaDestino, mov.colDestino, FICHA);
}

bool fichaBloqueada(tTablero& tablero, int fila, int col)
{
    tMovimientoLista listaMov;
    bool bloqueo = true;

    if (movimientosPosibles(tablero, fila, col, listaMov))
    {
        bloqueo = false;
    }
    return bloqueo;
}

