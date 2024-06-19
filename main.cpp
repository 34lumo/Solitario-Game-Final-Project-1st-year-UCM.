#include <iostream>
#include "tablero.h"
#include "juego.h"
#include "movimiento.h"
using namespace std;

string solicitaNombreFichero();

int main() {
    bool seguirJugando = true;

    while (seguirJugando) 
    {
        string nombre = solicitaNombreFichero();
        tJuego juego;
        tTablero tablero;
        tMovimiento movimiento;

        if (cargar(juego, nombre)) 
        {
            mostrar(juego);

            while (juego.estado == JUGANDO) 
            {
                ejecutarMovimiento(juego);
                mostrar(juego);
            }

            if (juego.estado == GANADOR) {
                cout << "¡Felicidades! Has ganado el juego." << endl;
            }
            else if (juego.estado == BLOQUEO) {
                cout << "El tablero está bloqueado. No se pueden realizar más movimientos." << endl;
            }
        }
        else 
        {
            cout << "Error: No se pudo cargar el archivo." << endl;
        }

        char respuesta;
        cout << "¿Desea volver a jugar? (s/n): ";
        cin >> respuesta;
        if (respuesta == 's' || respuesta == 'S')
        {
            seguirJugando = true;
        }
        else
        {
            seguirJugando = false;
        }

    }
    return 0;
}

string solicitaNombreFichero() {
    string nombre;
    cout << "Nombre del fichero de configuracion: ";
    cin >> nombre;
    nombre = nombre + ".txt";
    return nombre;
}
