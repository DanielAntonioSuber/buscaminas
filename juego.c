
#include "juego.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para obtener la fila seleccionada por el jugador
int obtenerFila() {
    int fila = 0;
    printf("Escribe la fila: ");
    scanf("%d", &fila);
    return fila;
}

// Función para obtener la columna seleccionada por el jugador
int obtenerColumna() {
    int columna = 0;
    printf("Escribe la columna: ");
    scanf("%d", &columna);
    return columna;
}

// Función para inicializar el tablero con celdas vacías
void inicializarTablero(struct Celda tablero[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            tablero[i][j] = (struct Celda){0, 0, 0};
        }
    }
}

// Función para mostrar el estado actual del tablero
void mostrarTablero(struct Celda tablero[9][9]) {
    printf("  0 1 2 3 4 5 6 7 8\n");
    for (int i = 0; i < 9; i++) {
        printf("%d ", i);
        for (int j = 0; j < 9; j++) {
            if (tablero[i][j].descubierta) {
                if (tablero[i][j].bomba) {
                    printf("* ");
                } else if(tablero[i][j].vecinos == 0) {
                    printf("# ");
                } else {
                    printf("%d ", tablero[i][j].vecinos);
                }
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

// Función para colocar bombas en el tablero
void colocarBombas(struct Celda tablero[9][9], int columnaSeleccionada, int filaSeleccionada) {
    int celdasConBomba[8][2];
    int fila, columna;
    srand(time(NULL));

    // Generar posiciones aleatorias para las bombas (excepto en la celda seleccionada por el jugador)
    for(int i = 0; i < 9;) {
        fila = rand() % 9;
        columna = rand() % 9;
        if( (i == 0  || !existeEnArreglo(celdasConBomba, 8, fila, columna)) && (fila != filaSeleccionada && columna != columnaSeleccionada)) {
            celdasConBomba[i][0] = fila;
            celdasConBomba[i][1] = columna;
            ++i;
        }
    }

    // Colocar bombas en las posiciones generadas
    for(int i = 0; i < 8; i++) {
        fila = celdasConBomba[i][0];
        columna = celdasConBomba[i][1];

        tablero[fila][columna].bomba = 1;
    }

    // Calcular el número de vecinos (bombas adyacentes) para cada celda sin bomba
    for(int i = 0; i < 8; i++) {
        fila = celdasConBomba[i][0];
        columna = celdasConBomba[i][1];

        int filaAnterior = fila - 1;
        int filaPosterior = fila + 1;
        int columnaPosterior = columna + 1;
        int columnaAnterior = columna - 1;

        if (!(filaAnterior < 0)) {
            if (columnaAnterior >= 0 && tablero[filaAnterior][columnaAnterior].bomba != 1) {
                tablero[filaAnterior][columnaAnterior].vecinos += 1;
            }

            if(tablero[filaAnterior][columnaAnterior].bomba != 1) {
                tablero[filaAnterior][columna].vecinos += 1;
            }

            if (columnaPosterior < 9 && columnaPosterior >= 0 && tablero[filaAnterior][columnaPosterior].bomba != 1) {
                tablero[filaAnterior][columnaPosterior].vecinos += 1;
            }
        }

        if (filaPosterior < 9 && filaPosterior >= 0) {
            if (columnaAnterior >= 0 && tablero[filaPosterior][columnaAnterior].bomba != 1) {
                tablero[filaPosterior][columnaAnterior].vecinos += 1;
            }

            if(tablero[filaPosterior][columna].bomba != 1) {
                tablero[filaPosterior][columna].vecinos += 1;
            }

            if (columnaPosterior < 9 && columnaPosterior >= 0 && tablero[filaPosterior][columnaPosterior].bomba != 1) {
                tablero[filaPosterior][columnaPosterior].vecinos += 1;
            }
        }

        if (columnaAnterior >= 0 && tablero[fila][columnaAnterior].bomba != 1) {
            tablero[fila][columnaAnterior].vecinos += 1;
        }

        if (columnaPosterior < 9 && columnaPosterior >= 0 && tablero[fila][columnaPosterior].bomba != 1) {
            tablero[fila][columnaPosterior].vecinos += 1;
        }
    }
}

// Función para descubrir una celda en el tablero
void descubrirCelda(struct Celda tablero[9][9], int fila, int columna) {
    // Verificar si la celda está fuera de los límites o ya ha sido descubierta
    if (fila < 0 || fila >= 9 || columna < 0 || columna >= 9 || tablero[fila][columna].descubierta == 1) {
        return;
    }

    // Marcar la celda como descubierta
    tablero[fila][columna].descubierta = 1;

    // Verificar si la celda contiene una bomba
    if (tablero[fila][columna].bomba == 1) {
        printf("¡Has perdido! Se encontró una mina en la celda (%d, %d).\n", fila, columna);
        mostrarTablero(tablero); // Mostrar todas las minas
        exit(0);
    } else {
        // Obtener el número de vecinos (bombas adyacentes) de la celda
        int count = tablero[fila][columna].vecinos;

        // Si la celda no tiene vecinos (valor 0), descubrir celdas adyacentes recursivamente
        if (count == 0) {
            for (int i = fila - 1; i <= fila + 1; i++) {
                for (int j = columna - 1; j <= columna + 1; j++) {
                    descubrirCelda(tablero, i, j);
                }
            }
        }
    }

    // Verificar si el jugador ha ganado el juego
    if (verificarGanador(tablero)) {
        printf("¡Felicidades! Has ganado el juego.\n");
        mostrarTablero(tablero); // Mostrar todas las celdas, incluyendo las minas
        exit(0);
    }
}

// Función para verificar si una fila y columna dadas existen en un arreglo bidimensional
int existeEnArreglo(int (*arreglo)[2], int tamano, int fila, int columna) {
    for (int i = 0; i < tamano; i++) {
        if (*(arreglo[i]) == fila && *(arreglo[i] + 1) == columna) {
            return 1;
        }
    }
    return 0;
}
// Función para verificar si todas las celdas sin bombas han sido descubiertas
int verificarGanador(struct Celda tablero[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (tablero[i][j].bomba == 0 && tablero[i][j].descubierta == 0) {
                return 0; // Todavía hay celdas sin descubrir que no tienen bombas
            }
        }
    }
    return 1; // Todas las celdas sin bombas han sido descubiertas
}
