#ifndef JUEGO_H
#define JUEGO_H

struct Celda {
    int bomba;
    int descubierta;
    int vecinos;
};

void inicializarTablero(struct Celda tablero[9][9]);
void mostrarTablero(struct Celda tablero[9][9]);
void colocarBombas(struct Celda tablero[9][9], int columnaSeleccionada, int filaSeleccionada);
void descubrirCelda(struct Celda tablero[9][9], int fila, int columna);
int obtenerFila();
int obtenerColumna();
int existeEnArreglo(int (*arreglo)[2], int tamano, int fila, int columna);
int verificarGanador(struct Celda tablero[9][9]);

#endif
