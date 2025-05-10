#include <stdio.h>
#include <stdbool.h>
#include "Analizador_Sintactico.h"
#include "Evaluador.h"


int main() {

    const char* program = "Promedio y Varianza.txt";
    bool error = true;

    TApuntNodo arbol;
    //TEstado estado;

    Analizador_Predictivo(program,&arbol,&error);

    if (!error)
        {
            //GuardarArbol('Arbol.txt',arbol);
            //InicializarEst(estado);
            //evalLenguaje(arbol,estado);
        }


}
