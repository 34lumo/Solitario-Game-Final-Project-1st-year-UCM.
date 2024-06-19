#include "tablero.h"
#include "movimiento.h"
#include <iostream>
#include <iomanip>
using namespace std;

const string FG_BLACK = "\x1B[30m";
const string FG_BLUE = "\x1b[34m";
const string BG_BLACK = "\x1B[40m";
const string BG_BROWN = "\x1B[48;5;94m";
const string BG_ORANGE = "\x1B[48;2;204;102;0m";
const string Reset = "\x1b[0m";

const char Horizontal = char(196);
const char UpperLeft = char(218);
const char UpperCross = char(194);
const char UpperRight = char(191);
const char Vertical = char(179);
const char MidLeft = char(195);
const char MidCross = char(197);
const char MidRight = char(180);
const char LowerLeft = char(192);
const char LowerCross = char(193);
const char LowerRight = char(217);
const char Square = char(219);

//tCelda intToEnum(int iceldas);

//Funcion para cargar
void cargar(tTablero& tablero, std::ifstream& archivo) 
{
    archivo >> tablero.filas >> tablero.columnas;

    for (int i = 0; i < tablero.filas; i++) {
        for (int j = 0; j < tablero.columnas; j++) 
        {
            int valor;
            archivo >> valor;
            tablero.celdas[i][j] = tCelda(valor);
        }
    }

    archivo >> tablero.filaMeta >> tablero.colMeta;
}
//Funcion para pasar de las celdas en entero a Enum
/*tCelda intToEnum(int iceldas)
{
	tCelda valor = NULA;
	switch (iceldas)
	{
	case 0:
		valor = NULA;
		break;
	case 1:
		valor = VACIA;
		break;
	case 2:
		valor = FICHA;
		break;
	}

	return valor;
}
*/

// dibuja la cabecera de la tabla (nº de las columnas)
void dibujaCabecera(const tTablero& tablero) {
    cout << setw(2) << "    ";
    cout << setw(5) << 1;
    for (int i = 2; i <= tablero.columnas; i++)
    cout << setw(7) << i;
    cout << endl;
}

void dibujaBordeHorizontal(const tTablero& tablero, char left, char cross, char right) {
    cout << "    ";
    cout << left;
    for (int i = 0; i < tablero.columnas - 1; i++)
        cout << string(6, Horizontal) << cross;
    cout << string(6, Horizontal) << right << endl;
}

// dibuja la banda exterior de las celdas de una fila del tablero
void dibujaBordeCelda(const tTablero& tablero, int fila) {
    cout << "    ";  // para llegar a la posición de la tabla
    for (int k = 0; k < tablero.columnas; k++) { // para cada columna
        cout << Vertical; // pintamos barra vertical
        if (tablero.filaMeta == fila && tablero.colMeta == k) // si contiene meta: fondo naranja
            cout << BG_ORANGE;
        else if (tablero.celdas[fila][k] == NULA) // si es celda NULA: fondo negro
            cout << BG_BLACK;
        else // si es útil (con o sin ficha): fondo marrón
            cout << BG_BROWN;
        cout << "      "; // pintamos la banda
        cout << Reset;
    }
    cout << Vertical << endl; // pintamos barra vertical
}

// dibuja la banda central de las celdas de una fila del tablero
void dibujaCentroCelda(const tTablero& tablero, int fila) {
    cout << "  " << setw(2) << fila + 1;  // pintamos el nº de fila
    for (int k = 0; k < tablero.columnas; k++) { // para cada columna
        cout << Vertical; // pintamos barra vertical
        if (tablero.celdas[fila][k] == NULA) { // si es celda NULA: fondo negro y pintamos
            cout << BG_BLACK;
            cout << "      ";
        }
        else { // para celda útil
            if (tablero.filaMeta == fila && tablero.colMeta == k)  // si contiene la meta: fondo naranja
                cout << BG_ORANGE;
            else  // si no contiene la meta: fondo marrón
                cout << BG_BROWN;
            cout << "  "; // pintamos la primera parte de la banda
            if (tablero.celdas[fila][k] == VACIA)  // si está vacía: primer plano negro
                cout << FG_BLACK;
            else  // si tiene ficha: primer plano azul
                cout << FG_BLUE;
            cout << Square << Square;  // pintamos el cuadrado duplicado
            cout << Reset;
            if (tablero.filaMeta == fila && tablero.colMeta == k)
                cout << BG_ORANGE;
            else
                cout << BG_BROWN;
            cout << "  ";  // pintamos la tercera parte de la banda
        }
        cout << Reset;
    }
    cout << Vertical << endl;  // pintamos la barra vertical
}

void muestracasilla(const tTablero& tablero, int i)
{
    if (i == tablero.filas - 1)
      {
        dibujaBordeCelda(tablero, i);
        dibujaCentroCelda(tablero, i);
        dibujaBordeCelda(tablero, i);
        dibujaBordeHorizontal(tablero, LowerLeft, LowerCross, LowerRight);
      }
    else
    {
        dibujaBordeCelda(tablero, i);
        dibujaCentroCelda(tablero, i);
        dibujaBordeCelda(tablero, i);
        dibujaBordeHorizontal(tablero, MidLeft, MidCross, MidRight);
    }
}

//Funcion mostrar
void mostrar(const tTablero& tablero)
{
    
    system("cls");
    cout << Reset;

    dibujaCabecera(tablero);
    dibujaBordeHorizontal(tablero, UpperLeft, UpperCross, UpperRight);
    for (int i = 0; i < tablero.filas; i++)
    {
        muestracasilla(tablero, i);
    }

}

bool eleccionValida(tTablero& tablero, int fila, int col)
{
    tMovimientoLista listaMov;
    bool validada = false;

    if (valida(tablero, fila, col) && tablero.celdas[fila][col] == FICHA)
        validada = true;

    return validada;
}

bool valida(const tTablero& tablero, int fila, int col)
{
    bool valida = false;
    if (fila < tablero.filas && col < tablero.columnas)
        valida = true;

    return valida;
}

tCelda dameCelda(const tTablero& tablero, int fila, int col)
{
    tCelda celda = tablero.celdas[fila][col];
    return celda;
}

void ponCelda(tTablero& tablero, int fila, int col, tCelda celda)
{
    tablero.celdas[fila][col] = celda;
}