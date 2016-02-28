#ifndef SINTACTICO_H_INCLUDED
#define SINTACTICO_H_INCLUDED

#include "Lexico.h"

class Sintactico {
private:
    Lexico lex;
    bool error;

    void comprueba( string simbolo ) {
        if( lex.dameSimbolo() == simbolo ) {
            lex.sigSimbolo();
        } else {
            reportaError();
        }
    }

    void comprueba( Token tipo ) {
        if( lex.dameTipo() == tipo ) {
            lex.sigSimbolo();
        } else {
            reportaError();
        }
    }

    void reportaError() {
        error = true;
    }

public:
    void analiza() {
        lex.sigSimbolo();
        A();
        comprueba( FIN_ENTRADA );
    }

    bool hayError() {
        return error;
    }

    void A() {
        comprueba( IDENTIFICADOR );
        comprueba( OP_ASIGNACION );
        if( lex.dameTipo() == PARENTESIS_IZQ ) {
            lex.sigSimbolo();
            P();
            comprueba( PARENTESIS_DER );
            comprueba( DELIMITADOR );
            Ap();
        }  else {
            reportaError();
        }
    }
    void Ap() {
        if( lex.dameTipo() == IDENTIFICADOR ) {
            lex.sigSimbolo();
            comprueba( OP_ASIGNACION );
            if( lex.dameTipo() == PARENTESIS_IZQ ) {
                lex.sigSimbolo();
                P();
                comprueba( PARENTESIS_DER );
                comprueba( DELIMITADOR );
                Ap();
            }
        }
    }
    void P() {
        if( lex.dameTipo() == PARENTESIS_IZQ ) {
            lex.sigSimbolo();
            P();
            comprueba( PARENTESIS_DER );
        }
    }
};

#endif // SINTACTICO_H_INCLUDED
