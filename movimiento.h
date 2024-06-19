#ifndef movimiento_h
#define  movimiento_h
#include "tablero.h"
#include "juego.h"
const int NUMDIR = 4;
const int IND = 2;

enum tDireccion { ARRIBA, DERECHA, ABAJO, IZQUIERDA };

const int DIRECCIONES[NUMDIR][IND] = {
    { -1, 0 }, // ARRIBA
    { 0, 1 },  // DERECHA
    { 1, 0 },  // ABAJO
    { 0, -1 }  // IZQUIERDA
};

struct tMovimiento {
   tDireccion dir;
   int filaSaltada, colSaltada, filaDestino, colDestino;
};

typedef tMovimiento tMovimientoArray[NUMDIR];

struct tMovimientoLista {
   tMovimientoArray posibles;
   int contador;
};


// Subprogramas del enunciado
// IMPORTANTE: decide cuáles permanecen públicos y traslada los que creas que deben ser privados (si es el caso)

tMovimiento moviendo(tDireccion dir, int fila, int col); 
tMovimiento leeMovimiento(tTablero& tablero, int& fila, int& col);
void movimientoFicha(tTablero& tablero, int fila, int col, tMovimiento& mov);
bool unicoMovimiento(tTablero& tablero, int fila, int col, tMovimientoLista& listaMov);
tMovimiento eligeMovimiento(const tMovimientoLista& listaMov);
bool movimientosPosibles(tTablero& tablero, int fila, int col, tMovimientoLista& listaMov);
bool fichaBloqueada(tTablero& tablero, int fila, int col);
//bool eligeMovimientoInverso(const tTablero& tablero, int fila, int col, tMovimiento& mov);
//void realizaMovimientoInverso(tTablero& tablero, int fila, int col, const tMovimiento& mov);

#endif // movimiento_h