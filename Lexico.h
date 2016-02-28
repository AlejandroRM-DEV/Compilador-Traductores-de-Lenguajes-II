#ifndef LEXICO_H_INCLUDED
#define LEXICO_H_INCLUDED

#include <iostream>
#include <fstream>

using namespace std;

enum Estado {
    Q0, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,
    Q17, Q18, Q19, Q20, Q21, Q22, Q23, Q24, Q25, Q26, Q27, Q28, Q29, Q30, Q31,
    Q32, K, NUMERO_ESTADOS
};

enum Entrada {
    E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12, E13, E14, E15, E16,
    E17, E18, E19, E20, E21, E22, E23, NUMERO_ENTRADAS
} ;

enum Token {
    IDENTIFICADOR, RESERVADO, ENTERO, OP_ADITIVO, OP_INCREMENTO, OP_DECREMENTO, OP_MULTIPLICATIVO,
    LOGICO_AND, LOGICO_OR, LOGICO_NOT, OP_ASIGNACION, OP_IGUALDAD, OP_RELACIONAL, COMA, DELIMITADOR,
    COMENTARIO, PARENTESIS_IZQ, PARENTESIS_DER, LLAVE_IZQ, LLAVE_DER, FLOTANTE, CADENA,
    FIN_ENTRADA, ERROR, NUMERO_TOKENS
};

enum Salida {
    NO, SI
};

class Lexico {
private:
    int matriz[NUMERO_ESTADOS][NUMERO_ENTRADAS] = {
        {Q0, Q12, Q1, Q2, Q3, Q4, Q8, Q7, Q7, Q9, Q11, Q13, Q14, Q16, Q18, Q19, Q24, Q25, Q26, Q27, K, Q30, Q32, K},
        {K, K, Q1, Q1, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, Q2, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, Q28, K, K, K},
        {K, K, K, K, Q5, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, Q6, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, Q23, Q20, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, Q10, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, Q12, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, Q15, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, Q15, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, Q17, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q21, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, K, Q20},
        {Q20, Q20, Q20, Q20, Q20, Q20, Q22, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, Q20, K, Q20},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {Q23, Q22, Q23, Q23, Q23, Q23, Q23, Q23, Q23, Q23, Q23, Q23, Q23, Q23, Q23, Q23, Q23, Q23, Q23, Q23, Q23, Q23, Q22, Q23},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, Q29, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, Q29, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q30, Q31, K, Q30},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K}
    };
    /** Estando es un estado terminal, la entrada determina si el token a finalizado */
    int salidas[NUMERO_ESTADOS][NUMERO_ENTRADAS] = {
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, NO, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, NO, SI, SI, SI},
        {SI, SI, SI, SI, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, NO, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, SI, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO}
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
        case Q3:
        case Q4:
            tipo = OP_ADITIVO;
            break;
        case Q5:
            tipo = OP_INCREMENTO;
            break;
        case Q6:
            tipo = OP_DECREMENTO;
            break;
        case Q7:
        case Q8:
            tipo = OP_MULTIPLICATIVO;
            break;
        case Q10:
            tipo = LOGICO_AND;
            break;
        case Q12:
            tipo = LOGICO_OR;
            break;
        case Q13:
            tipo = LOGICO_NOT;
            break;
        case Q14:
            tipo = OP_ASIGNACION;
            break;
        case Q15:
            tipo = OP_IGUALDAD;
            break;
        case Q16:
        case Q17:
            tipo = OP_RELACIONAL;
            break;
        case Q18:
            tipo = COMA;
            break;
        case Q19:
            tipo = DELIMITADOR;
            break;
        case Q22:
            tipo = COMENTARIO;
            break;
        case Q24:
            tipo = PARENTESIS_IZQ;
            break;
        case Q25:
            tipo = PARENTESIS_DER;
            break;
        case Q26:
            tipo = LLAVE_IZQ;
            break;
        case Q27:
            tipo = LLAVE_DER;
            break;
        case Q29:
            tipo = FLOTANTE;
            break;
        case Q31:
            tipo = CADENA;
            break;
        case Q32:
            tipo = FIN_ENTRADA;
            break;
        default:
            tipo = ERROR;
            break;
        }
    }

    int transicion( char c ) {
        if( c == ' ' || c == '\t' || c == '\v' || c == '\f' ) {
            return E0;
        } else if( c == '\r' || c == '\n' ) {
            return E1;
        } else if( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) ||  c == '_' ) {
            return E2;
        } else if( c >= '0' && c <= '9' ) {
            return E3;
        } else if( c == '+' ) {
            return E4;
        } else if( c == '-' ) {
            return E5;
        } else if( c == '/'  ) {
            return E6;
        } else if( c == '*' ) {
            return E7;
        } else if( c == '%' ) {
            return E8;
        } else if( c == '&' ) {
            return E9;
        } else if( c == '|' ) {
            return E10;
        } else if( c == '!' ) {
            return E11;
        } else if( c == '=' ) {
            return E12;
        } else if( c == '<' || c == '>' ) {
            return E13;
        } else if( c == ',' ) {
            return E14;
        } else if( c == ';' ) {
            return E15;
        } else if( c == '(' ) {
            return E16;
        } else if( c == ')' ) {
            return E17;
        } else if( c == '{' ) {
            return E18;
        } else if( c == '}' ) {
            return E19;
        } else if( c == '.' ) {
            return E20;
        } else if( c == '"' ) {
            return E21;
        } else if( c == EOF ) {
            return E22;
        } else { // RESTO DE ASCII
            return E21;
        }
    }

public:
    Lexico() {
        archivo.open( "entrada4.txt" );

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
        char temp;

        do {
            temp = transicion( archivo.peek() );
            while ( temp == E0 || temp == E1 ) {
                archivo.get( caracter );
                temp = transicion( archivo.peek() );
            }

            estado = Q0;
            simbolo = "";
            error = false;

            while( true ) {
                columna = transicion( archivo.peek() );
                if( salidas[estado][columna] == SI ) {
                    break;
                }
                estado = matriz[estado][columna];

                archivo.get( caracter );
                simbolo += caracter;

                if( estado == K ) {
                    error = true;
                    break;
                }
            }
        } while ( estado == Q22 ); // Ignora comentarios
        fijaTipo( estado );
    }

    bool hayError() {
        return error;
    }

    bool fin() {
        return ( tipo == FIN_ENTRADA ) || hayError();
    }

    string dameSimbolo() {
        return simbolo;
    }

    int dameTipo() {
        return tipo;
    }

};
#endif // LEXICO_H_INCLUDED
