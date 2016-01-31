#ifndef LEXICO_H_INCLUDED
#define LEXICO_H_INCLUDED

#include <iostream>
#include <fstream>

using namespace std;

enum Estado {
    Q0, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,
    Q17, Q18, K, NUMERO_ESTADOS
};

enum Entrada {
    E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12, E13, E14, E15,
    NUMERO_ENTRADAS
} ;

enum Token {
    IDENTIFICADOR, ENTERO, REAL, CADENA, OP_ADICION, OP_MULTIPLICACION,
    PARENTESIS, DELIMITADOR, FIN_ENTRADA, OP_LOGICO, OP_ASIGNACION,
    OP_RELACIONAL, ERROR
};

enum Salida {
    NO, SI
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
     /** Estando es un estado terminal, la entrada determina si el token a finalizado */
    int salidas[NUMERO_ESTADOS][NUMERO_ENTRADAS] = {
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, NO, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, NO, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, NO, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, NO, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, NO, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO}
    };

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
        if(  c == ' ' || c == '\t' || c == '\v' || c == '\f' ||
                c == '\r' || c == '\n' ) {
            return E0;
        } else if( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) ||  c == '_' ) {
            return E1;
        } else if( c >= '0' && c <= '9' ) {
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
        archivo.open( "entrada.txt" );

        if ( !archivo.is_open() ) {
            error = true;
        } else {
            error = false;
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
            if( salidas[estado][columna] == SI ) {
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
