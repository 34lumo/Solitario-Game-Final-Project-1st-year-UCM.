#ifndef juego_h
#define juego_h
#include "tablero.h"

typedef enum tEstado { JUGANDO, GANADOR, BLOQUEO};

struct tJuego {
   tTablero tablero;
   tEstado estado;
}; 

// Subprogramas del enunciado
// IMPORTANTE: decide cuáles permanecen públicos y traslada los que creas que deben ser privados (si es el caso)

bool cargar(tJuego& juego, std::string nombre);
void mostrar(const tJuego& juego);
void ejecutarMovimiento(tJuego& juego);  
void actualizaEstado(tJuego& juego); 
bool hayMovimientos (tJuego& juego);
void generar(tJuego& juego, int pasos);
bool ganador(const tJuego& juego);

#endif //juego_h
