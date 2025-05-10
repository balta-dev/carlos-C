#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "Analizador_Lexico.h" 

void InicializarTS(TablaDeSimbolos* TS){
    TS->cant = 0;

}

bool agregarTS(TablaDeSimbolos* TS, const char* palabra, int CompLex) {
    if (TS->cant >= MAX_SIM - 1) {
        fprintf(stderr, "Error: Tabla de símbolos llena.\n");
        return false;
    }

    TS->cant++;
    
    snprintf(TS->elem[TS->cant].lexema, sizeof(TS->elem[TS->cant].lexema), "%s", palabra);
    
    TS->elem[TS->cant].compLex = CompLex;
    return true;
}

void CompletarTS(TablaDeSimbolos* TS) {
    if (TS == NULL) return;

    // Asignar el componente léxico correcto a cada palabra reservada
    agregarTS(TS, "while", Twhile);
    agregarTS(TS, "if", Tif);
    agregarTS(TS, "def", Tdef);
    agregarTS(TS, "program", Tprogram);
    agregarTS(TS, "title", Ttitle);
    agregarTS(TS, "read", Tread);
    agregarTS(TS, "print", Tprint);
    agregarTS(TS, "pot", Tpot);
    agregarTS(TS, "root", Troot);
    agregarTS(TS, "array", Tarray);
    agregarTS(TS, "else", Telse);
}


void InstalarEnTS(const char* lexema, TablaDeSimbolos* TS, TipoSG* CompLex) {
    bool pre_ex = false;
    uint8_t i;

    for (i = 0; i < TS->cant; i++) {
        if (strcmp(lexema, TS->elem[i].lexema) == 0) {
            *CompLex = TS->elem[i].compLex;
            pre_ex = true;
            break;
        }
    }

    if (!pre_ex) {
        strcpy(TS->elem[TS->cant].lexema, lexema);  
        TS->elem[TS->cant].compLex = Tid;
        *CompLex = Tid;
        TS->cant++;
    }
}


void LeerCar(FILE* fuente, long* control, char* car) {
    fseek(fuente, *control, SEEK_SET);  // Posiciona al inicio del carácter actual
    int c = fgetc(fuente);             // Lee un carácter (fgetc retorna int, no char)
    
    if (c != EOF) {
        *car = (char)c;                // Almacena el carácter leído
    } else {
        *car = EOF;                    // Fin de archivo
    }
}


bool EsId(FILE* fuente, long* control, char* lexema) {
    
    typedef enum { L, D, O } Sigma;
    
    // delta[estado][simbolo que representa]

    int estadoActual = 0;
    int estadoFinal = 2;

    int delta[2][3] = {
        {1, 3, 3},  // estado 0 (q0) va a estado 1 (q1) por medio de L, va a estado 3 (q3) por medio de D, va a q3 por medio de O.
        {1, 1, 2},  // q1 va a q1 por medio de L, va a q1 por medio de D, va a q2 por medio de O.
    };

    // en resumen, define el comportamiento del autómata.
    // q2 es el estado final, así que la única forma de llegar es a través de una (o muchas) letra/s y un símbolo. las demás transiciones son opcionales.

    long contLocal = *control;
    char car;
    int len = 0;

    Sigma CarASimb(char c) {    
        if (isalpha(c)) return L;
        else if (isdigit(c)) return D;
        else return O;

    }

    while (estadoActual != estadoFinal && estadoActual != 3) {
        LeerCar(fuente, &contLocal, &car);
        if (car == EOF) break;
        estadoActual = delta[estadoActual][CarASimb(car)];
        contLocal++;
        if (estadoActual == 1) lexema[len++] = car;
    }

    lexema[len] = '\0';

    if (estadoActual == estadoFinal && len < MAX_LEX - 1) {
        *control = contLocal - 1;
        return true;
    }

    return false;
}





bool EsConstanteReal(FILE* fuente, long* control, char* lexema){

    typedef enum {D, O, PUNTO} Sigma;

    int estadoActual = 0;
    int estadoFinal = 4;

    int delta[4][3] = {
        {1, 5, 5},
        {1, 4, 2},
        {3, 5, 5},
        {3, 4, 4}
        };

    long contLocal = *control;
    char car;
    int len = 0;

    Sigma CarASimb(char c) {
    switch (c) {
    case '0' ... '9': return D;
    case '.': return PUNTO;
    default: return O;
    }
}

    while (estadoActual != estadoFinal && estadoActual != 5) {
        LeerCar(fuente, &contLocal, &car);
        if (car == EOF) break;
        estadoActual = delta[estadoActual][CarASimb(car)];
        contLocal++;

        if (estadoActual != estadoFinal && len < MAX_LEX - 1) lexema[len++] = car;

    }

    lexema[len] = '\0';

    if (estadoActual == estadoFinal) {
        *control = contLocal - 1;
        return true;
    }

    return false;

}



//Nota: Estas otras funciones que devuelven booleanos también le faltan autómatas

bool EsCadena(FILE* fuente, long* control, char* lexema){

    typedef enum {C, O} Sigma;

    int estadoActual = 0;
    int estadoFinal = 2;

    int delta[2][2] = { //en Pascal se definieron más estados, pero no se definieron transiciones. Con esto alcanza.
        {1, 3},
        {2, 1}
    };             

    long contLocal = *control;
    char car;
    int len = 0;

   
    Sigma CarASimb(char car) {
    switch(car) {
        case '\'': return C; // #39 en Pascal es comilla simple (') en ASCII
        default: return O;
    }
}

    while (estadoActual != 3 && estadoActual != 2) {
        LeerCar(fuente, &contLocal, &car);
        if (car == EOF) break;
        estadoActual = delta[estadoActual][CarASimb(car)];
        contLocal++;

        if (len < MAX_LEX - 1) lexema[len++] = car;

    }

    lexema[len] = '\0';

    if (estadoActual == estadoFinal) {
        *control = contLocal - 1;
        return true;
    }

    return false;
}



bool EsSimboloEspecial(FILE* fuente, long* control, char* lexema, TipoSG* CompLex) {
    char car;
    LeerCar(fuente, control, &car);
    lexema[0] = car;  // Almacena el primer carácter

    switch(car) {
        case ';':   *CompLex = Tpycom; break;
        case ',':   *CompLex = Tcoma; break;
        case '(':   *CompLex = TParen_ab; break;
        case ')':   *CompLex = TParen_cer; break;
        case '[':   *CompLex = TCorr_ab; break;
        case ']':   *CompLex = TCorr_cer; break;
        case '{':   *CompLex = TLlav_ab; break;
        case '}':   *CompLex = TLlav_cer; break;

        case '=':
            
            *CompLex = Tasig;
            LeerCar(fuente, control, &car);
            if (car == '=') {  // Compara con '='
                lexema[1] = '=';  // Carácter, no string
                (*control)++;
                *CompLex = TRelacional;
            }
            break;

        case '<':
            
            *CompLex = TRelacional;
            LeerCar(fuente, control, &car);
                
                if (car == '=') {
                    lexema[1] = '=';
                    (*control)++;
                } else if (car == '>') {
                    lexema[1] = '>';
                    (*control)++;
                }
            
            break;

        case '>':
            
            *CompLex = TRelacional;
            LeerCar(fuente, control, &car);
            
            if (car == '=') {
                lexema[1] = '=';
                (*control)++;
            }
            
            break;

        case '|': *CompLex = Tor; break;
        case '&': *CompLex = Tand; break;
        case '!': *CompLex = Tnot; break;
        case '+': *CompLex = Tmas; break;
        case '-': *CompLex = Tmenos; break;
        case '*': *CompLex = Tmultip; break;
        case '/': *CompLex = Tdiv; break;

        default:
            (*control)--;
            return false;
    }

    // Asegura terminación nula (para símbolos de 1 o 2 caracteres)
    lexema[ (car == '=' || car == '<' || car == '>') ? 2 : 1 ] = '\0';
    return true;
}


void ObtenerSiguienteCompLex(FILE* fuente, long* control, TipoSG* CompLex, char* lexema, TablaDeSimbolos* TS){

    char car;

    // 1. Ignorar espacios y caracteres de control
    do {
        LeerCar(fuente, control, &car);  // Leer sin verificación bool
        if (car == EOF) {
            *CompLex = pesos;  // Fin de archivo
            lexema[0] = '\0';
            return;
        }
    } while (car >= 1 && car <= 32);  // Mientras sea espacio/control

    // 2. Procesar componente léxico
    if (EsId(fuente, control, lexema)) {
        InstalarEnTS(lexema, TS, CompLex);
    } 
    else if (EsConstanteReal(fuente, control, lexema)) {
        *CompLex = TCreal;
    } 
    else if (EsCadena(fuente, control, lexema)) {
        *CompLex = Tcad;
    } 
    else if (!EsSimboloEspecial(fuente, control, lexema, CompLex)) {
        *CompLex = ErrorLexico;
        printf(lexema, "Carácter inválido: %c", car);
    }

}

