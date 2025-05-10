#include <stdio.h>
#include <string.h>
#include "Evaluador.h"

// Inicializa el estado del evaluador (vacía todos los elementos)
void inicializarEstado(TEstado* estado) {
    estado->cant = 0;
    for (int i = 0; i < MaxVar; i++) {
        estado->elementos[i].lexemaId[0] = '\0'; // Inicializar lexema vacío
        estado->elementos[i].ValReal = 0.0f;     // Inicializar valor real a 0
        estado->elementos[i].Tipo = Treal;       // Tipo por defecto es Treal
        estado->elementos[i].CantArray = 0;      // Arreglo vacío
    }
}

// Busca un elemento en el estado
bool buscarElemento(const TEstado* estado, const char* lexema, TElemEstado* resultado) {
    for (int i = 0; i < estado->cant; i++) {
        if (strcmp(estado->elementos[i].lexemaId, lexema) == 0) {
            *resultado = estado->elementos[i];  // Copiar el elemento encontrado
            return true;
        }
    }
    return false; // No encontrado
}

// Agrega un nuevo elemento al estado
void agregarElemento(TEstado* estado, const TElemEstado* elem) {
    if (estado->cant < MaxVar) {
        estado->elementos[estado->cant] = *elem;  // Copiar el nuevo elemento
        estado->cant++;
    } else {
        printf("Error: El estado ha alcanzado su capacidad máxima\n");
    }
}
