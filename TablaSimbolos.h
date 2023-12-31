#ifndef TABLASIMBOLOS_H_INCLUDED
#define TABLASIMBOLOS_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <deque>
#include <vector>

using namespace std;

enum TipoDato {T_INT, T_FLOAT, T_VACIO, T_ERROR};

class EntradaTS {
private:
public:
    string simbolo;
    TipoDato dato;

    EntradaTS( string simbolo, TipoDato dato ) {
        this->simbolo = simbolo;;
        this->dato = dato;
    }
};

class TablaSimbolos {
private:
    static TablaSimbolos* instancia;
    vector<EntradaTS*> tabla;

    TablaSimbolos() {}

public:
    static TablaSimbolos* instance() {
        if ( !instancia ) {
            instancia = new TablaSimbolos;
        }
        return instancia;
    }
    vector<string> listaSim(){
        vector<string> lista;
        for( EntradaTS* e : tabla ) {
            lista.push_back(e->simbolo);
        }
        return lista;
    }
    bool agregarVariable( string simbolo, TipoDato dato ) {
        if( !existe( simbolo ) ) {
            tabla.push_back( new EntradaTS( simbolo, dato ) );
        }
        return true;
    }
    TipoDato tipoSim( string simbolo ) {
        for( EntradaTS* e : tabla ) {
            if( e->simbolo == simbolo ) {
                return e->dato;
            }
        }
        return T_ERROR;
    }
    bool existe( string simbolo ) {
        for( EntradaTS* e : tabla ) {
            if( e->simbolo == simbolo ) {
                return true;
            }
        }
        return false;
    }
    void print() {
        stringstream ss;
        string tipoDato[] = {"int", "float"};

        ss << setw( 20 ) << "Tabla de simbolos" << std::left << endl;
        ss << setw( 20 )  << "SIMBOLO" << setw( 10 ) << "T_DATO" << endl;

        for( EntradaTS* e : tabla ) {
            ss << setw( 20 )  << e->simbolo << setw( 10 ) << tipoDato[e->dato] << endl;
        }

        cout << ss.str() << endl;
    }
};


#endif // TABLASIMBOLOS_H_INCLUDED
