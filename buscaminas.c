#include "juego.h"

// Función principal
int main() {
    int fila, columna;
    struct Celda tablero[9][9];

    // Inicializar el tablero
    inicializarTablero(tablero);

    // Mostrar el tablero inicial
    mostrarTablero(tablero);

    // Obtener la columna y la fila seleccionadas por el jugador
    columna = obtenerColumna();
    fila = obtenerFila();

    // Colocar bombas en el tablero (excepto en la celda seleccionada por el jugador)
    colocarBombas(tablero, fila, columna);

    // Descubrir la celda seleccionada por el jugador
    descubrirCelda(tablero, fila, columna);

    // Mostrar el tablero después del primer movimiento
    mostrarTablero(tablero);

    // Bucle principal del juego
    do {
        // Obtener la columna y la fila seleccionadas por el jugador
        columna = obtenerColumna();
        fila = obtenerFila();

        // Descubrir la celda seleccionada por el jugador
        descubrirCelda(tablero, fila, columna);

        // Mostrar el tablero después de cada movimiento
        mostrarTablero(tablero);

    } while (1); // Bucle infinito (terminado manualmente si el jugador gana o pierde)
    
    return 0;
}