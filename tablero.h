#ifndef tablero_h
#define tablero_h
#include <fstream>

const int MAX = 6;

typedef enum tCelda { NULA, VACIA, FICHA };

typedef tCelda tCeldaArray[MAX][MAX];

struct tTablero {
   int filas, columnas;
   int filaMeta, colMeta;
   tCeldaArray celdas;
};


// SUBPROGRAMAS
// IMPORTANTE: decide cuáles permanecen públicos y traslada los que creas que deben ser privados (si es el caso)
//tCelda intToEnum(int iceldas);
void cargar(tTablero& tablero, std::ifstream& file);
void mostrar(const tTablero& tablero);
void muestracasilla(const tTablero& tablero, int i);
bool valida(const tTablero& tablero, int fila, int col);
bool eleccionValida(tTablero& tablero, int fila, int col);
tCelda dameCelda(const tTablero& tablero, int fila, int col);
void ponCelda(tTablero& tablero, int fila, int col, tCelda celda);
int numFilas(const tTablero& tablero);
int numColumnas(const tTablero& tablero);
void dameMeta(const tTablero& tablero, int &fila, int &col);
void ponMeta(tTablero& tablero, int fila, int col);
void mostrar(const tTablero& tablero);
void fichaAleatoria(const tTablero& tablero, int& fila, int& col);
void reseteaTablero(tTablero& tablero, int f, int c);


#endif //tablero_h