#ifndef LEXICO_H_INCLUDED
#define LEXICO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

enum Estado {
    Q0, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,
    Q17, Q18, Q19, Q20, Q21, Q22, Q23, K, NUMERO_ESTADOS
};

enum Entrada {
    E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12, E13, E14, E15, E16,
    E17, E18, E19, E20, E21, NUMERO_ENTRADAS
} ;

enum Token {
    IDENTIFICADOR, RESERVADO, ENTERO, OP_ADITIVO, OP_MULTIPLICATIVO,
    LOGICO_AND, LOGICO_OR, LOGICO_NOT, OP_ASIGNACION, OP_IGUALDAD, OP_RELACIONAL, COMA,
    PARENTESIS_IZQ, PARENTESIS_DER, TABULADOR, DESINDENTACION, NUEVA_LINEA, DOS_PUNTOS, FLOTANTE,
    FIN_ENTRADA, ERROR, NUMERO_TOKENS
};

enum Salida {
    NO, SI
};

class Lexico {
private:
    int matriz[NUMERO_ESTADOS][NUMERO_ENTRADAS] = {
        {Q0, Q19, Q1, Q2, Q3, Q4, Q5, Q5, Q5, Q6, Q8, Q10, Q11, Q13, Q15, Q16, Q17, Q18, Q20, K, Q23, K},
        {K, K, Q1, Q1, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, Q2, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, Q21, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, Q7, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, Q9, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, Q12, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, Q12, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, Q14, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, Q22, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, Q22, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K},
        {K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K, K}
    };
    /** Estando es un estado terminal, la entrada determina si el token a finalizado */
    int salidas[NUMERO_ESTADOS][NUMERO_ENTRADAS] = {
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, NO, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, NO, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO},
        {SI, SI, SI, NO, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI, SI},
        {NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO}
    };

    char caracter;
    int estado;
    int tipo;
    bool error;
    string simbolo;
    ifstream archivo;
    stack<int> pila;
    int pendientesDEDENT;
    bool sigueNuevaLinea;

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
            tipo = OP_MULTIPLICATIVO;
            break;
        case Q7:
            tipo = LOGICO_AND;
            break;
        case Q9:
            tipo = LOGICO_OR;
            break;
        case Q10:
            tipo = LOGICO_NOT;
            break;
        case Q11:
            tipo = OP_ASIGNACION;
            break;
        case Q12:
            tipo = OP_IGUALDAD;
            break;
        case Q13:
        case Q14:
            tipo = OP_RELACIONAL;
            break;
        case Q15:
            tipo = COMA;
            break;
        case Q16:
            tipo = PARENTESIS_IZQ;
            break;
        case Q17:
            tipo = PARENTESIS_DER;
            break;
        case Q18:
            tipo = TABULADOR;
            break;
        case Q19:
            tipo = NUEVA_LINEA;
            sigueNuevaLinea = true;
            break;
        case Q20:
            tipo = DOS_PUNTOS;
            break;
        case Q22:
            tipo = FLOTANTE;
            break;
        case Q23:
            tipo = FIN_ENTRADA;
            break;
        default:
            tipo = ERROR;
            break;
        }
    }

    int transicion( char c ) {
        if( c == ' ' || c == '\v' || c == '\f' ) {
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
        } else if( c == '(' ) {
            return E15;
        } else if( c == ')' ) {
            return E16;
        } else if( c == '\t' ) {
            return E17;
        } else if( c == ':' ) {
            return E18;
        } else if( c == '.' ) {
            return E19;
        } else if( c == EOF ) {
            return E20;
        } else { // RESTO DE ASCII
            return E21;
        }
    }

public:
    Lexico() {
        archivo.open( "entrada.txt" );

        if ( !archivo.is_open() ) {
            error = true;
        } else {
            error = false;
            pendientesDEDENT = 0;
            pila.push( 0 );
            sigueNuevaLinea = false;
        }
    }

    ~Lexico() {
        archivo.close();
    }

    void sigSimbolo() {
        int columna, temp;

        estado = Q0;
        simbolo = "";
        error = false;

        if( !tabsTokens() ) {
            temp = transicion( archivo.peek() );
            while ( temp == E0 ) {
                archivo.get( caracter );
                temp = transicion( archivo.peek() );
            }

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
            fijaTipo( estado );

        }
    }

    bool tabsTokens() {
        int temp, cuenta;

        temp = transicion( archivo.peek() );
        if( temp != E1 ) {
            if( sigueNuevaLinea ) {
                cuenta = 0;
                while ( temp == E17 ) {
                    cuenta++;
                    archivo.get( caracter );
                    temp = transicion( archivo.peek() );
                }

                if( cuenta > pila.top() ) {
                    pila.push( cuenta );
                    tipo = TABULADOR;
                    simbolo = "\t";
                } else if( cuenta < pila.top() ) {
                    while( cuenta < pila.top() ) {
                        pila.pop();
                        pendientesDEDENT++;
                    }
                }
                sigueNuevaLinea = false;
                return true;
            }
            if( pendientesDEDENT > 0 ) {
                tipo = DESINDENTACION;
                simbolo = "";
                pendientesDEDENT--;
                return true;
            }
        }
        return false;
    }

    bool hayError() {
        return error;
    }

    bool fin() {
        return ( tipo == FIN_ENTRADA && pendientesDEDENT == 0 ) || hayError();
    }

    string dameSimbolo() {
        return simbolo;
    }

    int dameTipo() {
        return tipo;
    }

};
#endif // LEXICO_H_INCLUDED
