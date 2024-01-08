#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Celda {
    int bomba;
    int descubierta;
    int vecinos;
};

void inicializarTablero(struct Celda tablero[9][9]);
void colocarBombas(struct Celda tablero[9][9], int columnaSeleccionada, int filaSeleccionada);
void mostrarTablero(struct Celda tablero[9][9]);
int existeEnArreglo(int arreglo[][2], int tamano, int fila, int columna);
void descubrirCelda(int fila, int columna);
int obtenerFila();
int obtenerColumna();

int main() {
    int finalizado = 0;
    int fila, columna;
    struct Celda tablero[9][9];

    inicializarTablero(tablero);
    mostrarTablero(tablero);

    columna = obtenerColumna();
    fila = obtenerColumna();
    colocarBombas(tablero, fila, columna);

    mostrarTablero(tablero);
    
    return 0;
}

int obtenerFila() {
    int fila = 0;
    printf("Escribe la fila: ");
    scanf("%d", &fila);
    return fila;
}

int obtenerColumna() {
    int columna = 0;
    printf("Escribe la columna: ");
    scanf("%d", & columna);
    return columna;
}

void descubrirCelda(int fila, int columna) {

}

void inicializarTablero(struct Celda tablero[9][9]) {
    struct Celda (*fila)[9] = tablero;

    for (int i = 0; i < 9; i++) {
        struct Celda *celda = *fila;
        for (int j = 0; j < 9; j++) {
            *celda = (struct Celda){0, 0, 0};
            celda++;
        }
        fila++;
    }
}

void mostrarTablero(struct Celda tablero[9][9]) {
    printf("  0 1 2 3 4 5 6 7 8\n");
    for (int i = 0; i < 9; i++) {
        printf("%d ", i);
        for (int j = 0; j < 9; j++) {
            if (tablero[i][j].descubierta) {
                if (tablero[i][j].bomba) {
                    printf("* ");
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

void colocarBombas(struct Celda tablero[9][9], int columnaSeleccionada, int filaSeleccionada) {
    int celdasConBomba[8][2];
    int fila, columna;
    srand(time(NULL));

    for(int i = 0; i < 8; i++) {
        fila = rand() % 9;
        columna = rand() % 9;
        if(!existeEnArreglo(celdasConBomba, 8, fila, columna) && fila != filaSeleccionada && columna != columnaSeleccionada) {
            celdasConBomba[i][0] = fila;
            celdasConBomba[i][1] = columna;
        }
    }

    for(int i = 0; i < 8; i++) {
        fila = celdasConBomba[i][0];
        columna = celdasConBomba[i][1];

        tablero[fila][columna].bomba = 1;
    }

    for(int i = 0; i < 8; i++) {
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

void descubrirCelda(int fila, int columna) {
    // Verificar si la casilla ya está descubierta
    if (tablero[fila][columna].descubierta) {
        printf("Esta casilla ya ha sido descubierta.\n");
        return;
    }

    // Descubrir la casilla
    
    tablero[fila][columna].descubierta = 1;

    // Si la casilla no tiene minas adyacentes, descubre las casillas adyacentes
    if (tablero[fila][columna].minas_adyacentes == 0) {
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                int nueva_fila = fila + x;
                int nueva_columna = columna + y;
                if (nueva_fila >= 0 && nueva_fila < 10 && nueva_columna >= 0 && nueva_columna < 10) {
                    descubrir_casilla(nueva_fila, nueva_columna);
                }
            }
        }
    }
}

int existeEnArreglo(int arreglo[10][2], int tamano, int fila, int columna) {
    for (int i = 0; i < tamano; i++) {
        if (arreglo[i][0] == fila && arreglo[i][1] == columna) {
            return 1;
        }
    }
    return 0;
}