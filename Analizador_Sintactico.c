#include "Analizador_Sintactico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Analizador_Predictivo(const char* archivo, TApuntNodo* arbol, bool* estado) {
    FILE* f = fopen(archivo, "r");
    if (!f) {
        fprintf(stderr, "Error al abrir el archivo: %s\n", archivo);
        *estado = -1;
        return;
    }

    // Aquí iría la lógica de análisis sintáctico, construcción de árbol, etc.

    fclose(f);
    *estado = 0;  // éxito
}
