#ifndef LEXICO_H_INCLUDED
#define LEXICO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

enum Estado {
    Q0, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,
    Q17, Q18, K, NUMERO_ESTADOS
};

enum Entrada {
    E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12, E13, E14, E15,
    NUMERO_ENTRADAS
    /*
        E0 Espacio      E4 "        E8 ;        E12 !
        E1 Letra        E5 + -      E9 $        E13 =
        E2 Digito       E6 * /      E10 |       E14 < >
        E3 .            E7 ( )      E11 &       E15 ASCII (restante)
    */
} ;

enum Token {
    IDENTIFICADOR, ENTERO, REAL, CADENA, OP_ADICION, OP_MULTIPLICACION,
    PARENTESIS, DELIMITADOR, FIN_ENTRADA, OP_LOGICO, OP_ASIGNACION,
    OP_RELACIONAL, ERROR
};

class Lexico {
private:
    int matriz[NUMERO_ESTADOS][NUMERO_ENTRADAS] = {
        {Q0, Q1, Q2, K, Q5, Q7, Q8, Q9, Q10, Q11, Q12, Q14, Q15, Q16, Q17, K},
        {K, Q1, Q1, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, Q2, Q3, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, Q4, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, Q4, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {Q5, Q5, Q5, Q5, Q6, Q5, Q5, Q5, Q5, Q5, Q5, Q5, Q5, Q5, Q5, Q5},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, Q13, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, Q13, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, Q18, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, Q18, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, Q18, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K}
    };
    int salidas[NUMERO_ESTADOS][NUMERO_ENTRADAS];

    char caracter;
    int estado;
    int tipo;
    bool error;
    string simbolo;
    ifstream archivo;

    void fijaTipo( int estado ) {
        switch( estado ) {
        case Q1:
            tipo = IDENTIFICADOR;
            break;
        case Q2:
            tipo = ENTERO;
            break;
        case Q4:
            tipo = REAL;
            break;
        case Q6:
            tipo = CADENA;
            break;
        case Q7:
            tipo = OP_ADICION;
            break;
        case Q8:
            tipo = OP_MULTIPLICACION;
            break;
        case Q9:
            tipo = PARENTESIS;
            break;
        case Q10:
            tipo = DELIMITADOR;
            break;
        case Q11:
            tipo = FIN_ENTRADA;
            break;
        case Q13:
        case Q15:
            tipo = OP_LOGICO;
            break;
        case Q16:
            tipo = OP_ASIGNACION;
            break;
        case Q17:
        case Q18:
            tipo = OP_RELACIONAL;
            break;
        default:
            tipo = ERROR;
            break;
        }
    }

    int transicion( char c ) {
        if( isspace( c ) ) {
            return E0;
        } else if( isalpha( c ) ||  c == '_' ) {
            return E1;
        } else if( isdigit( c ) ) {
            return E2;
        } else if( c == '.' ) {
            return E3;
        } else if( c == '"' ) {
            return E4;
        } else if( c == '+' || c == '-' ) {
            return E5;
        } else if( c == '*' || c == '/' ) {
            return E6;
        } else if( c == '(' || c == ')' ) {
            return E7;
        } else if( c == ';' ) {
            return E8;
        } else if( c == '$' ) {
            return E9;
        } else if( c == '|' ) {
            return E10;
        } else if( c == '&' ) {
            return E11;
        } else if( c == '!' ) {
            return E12;
        } else if( c == '=' ) {
            return E13;
        } else if( c == '<' || c == '>' ) {
            return E14;
        } else {
            return E15;
        }
    }

public:
    Lexico() {
        fill_n( salidas[Q0],  NUMERO_ENTRADAS, -1 );
        fill_n( salidas[Q1],  NUMERO_ENTRADAS, IDENTIFICADOR );
        salidas[Q1][E1] = salidas[Q1][E2] = -1;
        fill_n( salidas[Q2],  NUMERO_ENTRADAS, ENTERO );
        salidas[Q2][E2] = salidas[Q2][E3] = -1;
        fill_n( salidas[Q3],  NUMERO_ENTRADAS, -1 );
        fill_n( salidas[Q4],  NUMERO_ENTRADAS, REAL );
        salidas[Q3][E2] = -1;
        fill_n( salidas[Q5],  NUMERO_ENTRADAS, -1 );
        fill_n( salidas[Q6],  NUMERO_ENTRADAS, CADENA );
        fill_n( salidas[Q7],  NUMERO_ENTRADAS, OP_ADICION );
        fill_n( salidas[Q8],  NUMERO_ENTRADAS, OP_MULTIPLICACION );
        fill_n( salidas[Q9],  NUMERO_ENTRADAS, PARENTESIS );
        fill_n( salidas[Q10], NUMERO_ENTRADAS, DELIMITADOR );
        fill_n( salidas[Q11], NUMERO_ENTRADAS, FIN_ENTRADA );
        fill_n( salidas[Q12], NUMERO_ENTRADAS, -1 );
        fill_n( salidas[Q13], NUMERO_ENTRADAS, OP_LOGICO );
        fill_n( salidas[Q14], NUMERO_ENTRADAS, -1 );
        fill_n( salidas[Q15], NUMERO_ENTRADAS, OP_LOGICO );
        salidas[Q15][E13] = -1;
        fill_n( salidas[Q16], NUMERO_ENTRADAS, OP_ASIGNACION );
        salidas[Q16][E13] = -1;
        fill_n( salidas[Q17], NUMERO_ENTRADAS, OP_RELACIONAL );
        salidas[Q17][E13] = -1;
        fill_n( salidas[Q18], NUMERO_ENTRADAS, OP_RELACIONAL );

        error = false;

        archivo.open( "entrada.txt" );

        if ( !archivo.is_open() ) {
            error = true;
        }
    }

    ~Lexico() {
        archivo.close();
    }

    void sigSimbolo() {
        int columna;

        estado = Q0;
        simbolo = "";
        error = false;

        while ( transicion( archivo.peek() ) == E0 ) {
            archivo.get( caracter );
        }

        while( true ) {
            columna = transicion( archivo.peek() );
            if( salidas[estado][columna] != -1 ) {
                break;
            }
            estado = matriz[estado][columna];
            if( estado == K ) {
                error = true;
                break;
            }
            archivo.get( caracter );
            simbolo += caracter;
        }
        fijaTipo( estado );
    }

    bool hayError() {
        return error;
    }

    bool fin() {
        return simbolo == "$" || hayError();
    }

    string dameSimbolo() {
        return simbolo;
    }

    int dameTipo() {
        return tipo;
    }
};
#endif // LEXICO_H_INCLUDED
