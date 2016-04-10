#ifndef SINTACTICO_H_INCLUDED
#define SINTACTICO_H_INCLUDED

#include "Lexico.h"
#include "Clases.h"

class Sintactico {
private:
    Lexico lex;
    bool error;

    void comprueba( string simbolo ) {
        if( lex.dameSimbolo() == simbolo ) {
            lex.sigSimbolo();
        } else {
            //cout << "Se esperaba " << simbolo << endl;
            reportaError();
        }
    }

    void comprueba( Token tipo ) {
        if( lex.dameTipo() == tipo ) {
            lex.sigSimbolo();
        } else {
            //cout << "Se esperaba " << tipo << endl;
            reportaError();
        }
    }

    void reportaError() {
        error = true;
        /*cout << "Error [" << lex.dameSimbolo() << "] " << lex.dameTipo() << endl;
        while( !lex.fin() ) {
            lex.sigSimbolo();
            cout << lex.dameSimbolo() << endl;
        }*/
    }

public:
    Sintactico() {
        error = false;
    }
    bool hayError() {
        return error;
    }

    UnidadTraduccion*  analiza() {
        lex.sigSimbolo();
        UnidadTraduccion* nodo = unidad_traduccion();
        comprueba( FIN_ENTRADA );
        return nodo;
    }

    UnidadTraduccion* unidad_traduccion() {
        UnidadTraduccion* ut = new UnidadTraduccion();

        Nodo* p = single_input();
        if( p != nullptr ) {
            ut->definiciones.push_back( p );
        }
        unidad_traduccion_prima( ut );

        return ut;
    }

    void unidad_traduccion_prima( UnidadTraduccion* ut ) {
        if( error ) return;

        if( lex.dameTipo() != FIN_ENTRADA ) {
            Nodo* p = single_input();
            if( p != nullptr ) {
                ut->definiciones.push_back( p );
            }
            unidad_traduccion_prima( ut );
        }
    }

    Nodo* single_input() {
        Nodo* p = nullptr;
        if( !error ) {
            if( lex.dameTipo() == NUEVA_LINEA ) {
                lex.sigSimbolo();
            } else {
                bool tabs = ( lex.dameTipo() == TABULADOR );
                if( tabs ) comprueba( TABULADOR );
                p = stmt();
                if( tabs ) comprueba( DESINDENTACION );
            }
        }
        return p;
    }

    Nodo* stmt() {
        Nodo* nodo = nullptr;
        if( error ) return nullptr;

        if( lex.dameTipo() == NUEVA_LINEA ) {
            lex.sigSimbolo();
            return nullptr;
        }
        //compound_stmt
        if( nodo == nullptr ) {
            nodo = if_stmt();
        }
        if( nodo == nullptr ) {
            nodo = while_stmt();
        }
        //simple_stmt
        if( nodo == nullptr ) {
            nodo = print_stmt();
            if( nodo != nullptr )comprueba( NUEVA_LINEA );
        }
        if( nodo == nullptr ) {
            nodo = expresion_stmt();
            if( nodo != nullptr )comprueba( NUEVA_LINEA );
        }
        return nodo;
    }

    Proposicion* if_stmt() {
        if( error ) return nullptr;

        if( lex.dameSimbolo() == "if" ) {
            lex.sigSimbolo();
            If* proposicionIf = new If();
            proposicionIf->exp = expresion_stmt();
            comprueba( DOS_PUNTOS );
            proposicionIf->proIf = suite();
            proposicionIf->proElse = if_stmt_else();
            return proposicionIf;
        }
        return nullptr;
    }

    Else* if_stmt_else() {
        Else* pc = nullptr;
        vector<Nodo*> vec;

        if( !error ) {
            if( lex.dameSimbolo() == "else" ) {
                lex.sigSimbolo();
                comprueba( DOS_PUNTOS );

                bool tabs = false;

                comprueba( NUEVA_LINEA );
                tabs = ( lex.dameTipo() == TABULADOR );

                if( tabs ) comprueba( TABULADOR );
                pc = new Else();
                while( siguienteSuiteStmt() ) {
                    Nodo* p = stmt();
                    if( p != nullptr ) {
                        pc->cuerpo.push_back( p );
                    }
                }
                if( tabs ) comprueba( DESINDENTACION );
            }
        }
        return pc;
    }

    Proposicion* while_stmt() {
        if( error ) return nullptr;

        if( lex.dameSimbolo() == "while" ) {
            lex.sigSimbolo();
            While* p = new While();
            p->exp = expresion_stmt();
            comprueba( DOS_PUNTOS );
            p->proposicion =  suite();
            p->proElse = if_stmt_else();
            return p;
        }
        return nullptr;
    }

    Proposicion* print_stmt() {
        if( error ) return nullptr;

        if( lex.dameSimbolo() == "print" ) {
            lex.sigSimbolo();
            comprueba( PARENTESIS_IZQ );
            Print* p = new Print();
            p->exp = expresion_stmt();
            comprueba( PARENTESIS_DER );
            return p;
        }
        return nullptr;
    }

    Bloque* suite() {
        Bloque* pc = nullptr;
        vector<Nodo*> vec;

        if( !error ) {
            bool tabs = false;

            comprueba( NUEVA_LINEA );
            tabs = ( lex.dameTipo() == TABULADOR );

            if( tabs ) comprueba( TABULADOR );
            pc = new Bloque();
            while( siguienteSuiteStmt() ) {
                Nodo* p = stmt();
                if( p != nullptr ) {
                    pc->cuerpo.push_back( p );
                }
            }
            if( tabs ) comprueba( DESINDENTACION );
        }
        return pc;
    }

    bool siguienteSuiteStmt() {
        return lex.dameTipo() != DESINDENTACION &&  // Indentacion menor, se acabaron las proposiciones del bloque
               lex.dameTipo() != TABULADOR &&
               lex.dameTipo() != FIN_ENTRADA && // No hay nada mas que revisar
               lex.dameSimbolo() != "else" && // Sin indentacion, else se considera ID
               !error;
    }

    Expresion* expresion_stmt() {
        Expresion* exp = nullptr;
        if( !error ) {
            exp = expresion_de_asignacion();
        }
        return exp;
    }

    Expresion* expresion_de_asignacion() {
        Expresion* exp = nullptr;
        if( !error ) {
            exp = expresion_unaria();
            switch( lex.dameTipo() ) {
            case OP_ASIGNACION:
                lex.sigSimbolo();
                if( Identificador* dv = dynamic_cast<Identificador*>( exp ) ) {
                    exp = new Asignacion( dv, expresion_aditiva() );
                } else {
                    reportaError();
                }
                break;
            case OP_MULTIPLICATIVO:
                expresion_multiplicativa_prima( exp );
            case OP_ADITIVO :
                expresion_aditiva_prima( exp );
            case OP_RELACIONAL:
                expresion_relacional_prima( exp );
            case OP_IGUALDAD:
                expresion_de_igualdad_prima( exp );
            case LOGICO_AND:
                expresion_logica_AND_prima( exp );
            case LOGICO_OR:
                expresion_logica_OR_prima( exp );
                break;
            default:
                break;
            }
        }
        return exp;
    }

    Expresion* expresion_logica_OR() {
        Expresion* exp = nullptr;
        if( !error ) {
            exp = expresion_logica_AND();
            expresion_logica_OR_prima( exp );
        }
        return exp;
    }

    void expresion_logica_OR_prima( Expresion* &exp ) {
        if( !error ) {
            if( lex.dameTipo() == LOGICO_OR ) {
                lex.sigSimbolo();
                exp = new OR( exp, expresion_logica_AND() );
                expresion_logica_OR_prima( exp );
            }
        }
    }

    Expresion* expresion_logica_AND() {
        Expresion* exp = nullptr;
        if( !error ) {
            exp = expresion_de_igualdad();
            expresion_logica_AND_prima( exp );
        }
        return exp;
    }

    void expresion_logica_AND_prima( Expresion* &exp ) {
        if( !error ) {
            if( lex.dameTipo() == LOGICO_AND ) {
                lex.sigSimbolo();
                exp = new AND( exp, expresion_de_igualdad() );
                expresion_logica_AND_prima( exp );
            }
        }
    }

    Expresion* expresion_de_igualdad() {
        Expresion* exp = nullptr;
        if( !error ) {
            exp = expresion_relacional();
            expresion_de_igualdad_prima( exp );
        }
        return exp;
    }

    void expresion_de_igualdad_prima( Expresion* &exp ) {
        if( !error ) {
            if( lex.dameTipo() == OP_IGUALDAD ) {
                if( lex.dameSimbolo() == "==" ) {
                    lex.sigSimbolo();
                    exp = new Igual( exp, expresion_relacional() );
                } else {
                    lex.sigSimbolo();
                    exp = new Diferente( exp, expresion_relacional() );
                }
                expresion_de_igualdad_prima( exp );
            }
        }
    }

    Expresion* expresion_relacional() {
        Expresion* exp = nullptr;
        if( !error ) {
            exp = expresion_aditiva();
            expresion_relacional_prima( exp );
        }
        return exp;
    }

    void expresion_relacional_prima( Expresion* &exp ) {
        if( !error ) {
            if( lex.dameTipo() == OP_RELACIONAL ) {
                if( lex.dameSimbolo() == "<" ) {
                    lex.sigSimbolo();
                    exp = new Menor( exp, expresion_aditiva() );
                } else if( lex.dameSimbolo() == "<=" ) {
                    lex.sigSimbolo();
                    exp = new MenorIgual( exp, expresion_aditiva() );
                } else if( lex.dameSimbolo() == ">" ) {
                    lex.sigSimbolo();
                    exp = new Mayor( exp, expresion_aditiva() );
                } else {
                    lex.sigSimbolo();
                    exp = new MayorIgual( exp, expresion_aditiva() );
                }
                expresion_relacional_prima( exp );
            }
        }
    }

    Expresion* expresion_aditiva() {
        Expresion* exp = nullptr;
        if( !error ) {
            exp = expresion_multiplicativa();
            expresion_aditiva_prima( exp );
        }
        return exp;
    }

    void expresion_aditiva_prima( Expresion* &exp ) {
        if( !error ) {
            if( lex.dameTipo() == OP_ADITIVO ) {
                if( lex.dameSimbolo() == "+" ) {
                    lex.sigSimbolo();
                    exp = new Suma( exp, expresion_multiplicativa() );
                } else {
                    lex.sigSimbolo();
                    exp = new Resta( exp, expresion_multiplicativa() );
                }
                expresion_aditiva_prima( exp );
            }
        }
    }

    Expresion* expresion_multiplicativa() {
        Expresion* exp = nullptr;
        if( !error ) {
            exp = expresion_unaria();
            expresion_multiplicativa_prima( exp );
        }
        return exp;
    }

    void expresion_multiplicativa_prima( Expresion* &exp ) {
        if( !error ) {
            if( lex.dameTipo() == OP_MULTIPLICATIVO ) {
                if( lex.dameSimbolo() == "*" ) {
                    lex.sigSimbolo();
                    exp = new Multiplicacion( exp, expresion_unaria() );
                } else if( lex.dameSimbolo() == "/" ) {
                    lex.sigSimbolo();
                    exp = new Division( exp, expresion_unaria() );
                } else {
                    lex.sigSimbolo();
                    exp = new Modulo( exp, expresion_unaria() );
                }
                expresion_multiplicativa_prima( exp );
            }
        }
    }

    Expresion* expresion_unaria() {
        Expresion* exp = nullptr;
        if( !error ) {
            switch( lex.dameTipo() ) {
            case OP_ADITIVO:
                if( lex.dameSimbolo() == "+" ) {
                    lex.sigSimbolo();
                    exp = new UnarioPositivo( expresion_primaria() );
                } else {
                    lex.sigSimbolo();
                    exp = new UnarioNegativo( expresion_primaria() );
                }
                break;
            default:
                exp = expresion_primaria();
            }
        }
        return exp;
    }

    Expresion* expresion_primaria() {
        Expresion* exp = nullptr;
        if( !error ) {
            switch( lex.dameTipo() ) {
            case IDENTIFICADOR:
                exp = new Identificador( lex.dameSimbolo() );
                lex.sigSimbolo();
                break;
            case ENTERO:
                exp = new Entero( lex.dameSimbolo() );
                lex.sigSimbolo();
                break;
            case FLOTANTE:
                exp = new Real( lex.dameSimbolo() );
                lex.sigSimbolo();
                break;
            case PARENTESIS_IZQ:
                lex.sigSimbolo();
                exp = expresion_stmt();
                comprueba( PARENTESIS_DER );
                break;
            default:
                reportaError();
            }
        }
        return exp;
    }
};

#endif // SINTACTICO_H_INCLUDED
