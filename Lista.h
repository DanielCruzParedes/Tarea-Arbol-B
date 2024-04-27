#ifndef LISTA_H
#define LISTA_H
#include <nodo.h>
#include <iostream>
using std::cout;

template< typename Tipo >
class Lista{
public:
    Lista();
    ~Lista();
    void insertarAlFrente( const Tipo & );
    void insertarEnPenultimo(const Tipo & );
    void insertarAlFinal( const Tipo & );
    bool eliminarDelFrente( Tipo & );
    bool eliminarDelPenultimo( Tipo & );
    bool eliminarDelFinal( Tipo & );
    bool estaVacia() const;
    void imprimir() const;
private:
    nodo< Tipo > *primeroPtr;
    nodo< Tipo > *crearNuevoNodo( const Tipo &size ); //crear un nuevo nodo con tamaño ya definido
    nodo< Tipo > *ultimoPtr;

};

// constructor predeterminado
template< typename Tipo >
Lista< Tipo >::Lista()
    : primeroPtr( 0 ), ultimoPtr( 0 ){ }

// destructor
template< typename Tipo >
Lista< Tipo >::~Lista(){
    if ( !estaVacia() )
    {
        cout << "Destruyendo nodos ...\n";
        nodo<Tipo> *actualPtr = primeroPtr;
        nodo<Tipo> *tempPtr;
        while ( actualPtr != 0 ){
            tempPtr = actualPtr;
            cout << tempPtr->dato << "\t";
            actualPtr = actualPtr->siguientePtr;
            delete tempPtr;
        }
    }
    cout << "Se destruyeron todos los nodos\n\n";
}


template< typename Tipo >
void Lista< Tipo >::insertarAlFrente( const Tipo &valor ){
    nodo< Tipo > *nuevoPtr = obtenerNuevoNodo( valor );
    if ( estaVacia() )
        primeroPtr = ultimoPtr = nuevoPtr;
    else{
        nuevoPtr->siguientePtr = primeroPtr;
        primeroPtr = nuevoPtr;
    }
}

template< typename Tipo >
void Lista< Tipo >::insertarEnPenultimo( const Tipo &valor ){
    nodo< Tipo > *nuevoPtr = obtenerNuevoNodo( valor );
    if ( estaVacia() )
        primeroPtr = ultimoPtr = nuevoPtr;
    else{
        if(primeroPtr == ultimoPtr){
            nuevoPtr->siguientePtr = primeroPtr;
            primeroPtr = nuevoPtr;
        }else if(primeroPtr->siguientePtr == ultimoPtr){
            nuevoPtr->siguientePtr = ultimoPtr;
            primeroPtr->siguientePtr = nuevoPtr;
        }else{
            nodo<Tipo>*PenulPtr = primeroPtr;
            while(PenulPtr->siguientePtr != ultimoPtr){
                PenulPtr = PenulPtr->siguientePtr;
            }
            nuevoPtr->siguientePtr = ultimoPtr;
            PenulPtr->siguientePtr = nuevoPtr;
        }
    }
}

template< typename Tipo >
void Lista< Tipo >::insertarAlFinal( const Tipo &valor ){
    nodo< Tipo > *nuevoPtr = obtenerNuevoNodo( valor );
    if ( estaVacia() )
        primeroPtr = ultimoPtr = nuevoPtr;
    else{
        ultimoPtr->siguientePtr = nuevoPtr;
        ultimoPtr = nuevoPtr;
    }
}

template< typename Tipo >
bool Lista< Tipo >::eliminarDelFrente( Tipo &valor ){
    if ( estaVacia() )
        return false;
    else{
        nodo< Tipo > *tempPtr = primeroPtr;
        if ( primeroPtr == ultimoPtr )
            primeroPtr = ultimoPtr = 0;
        else
            primeroPtr = primeroPtr->siguientePtr; // apunta al nodo que antes era el segundo
        valor = tempPtr->dato;
        delete tempPtr;
        return true;
    }
}


template< typename Tipo >
bool Lista< Tipo >::eliminarDelPenultimo( Tipo &valor ){
    if ( estaVacia() )
        return false;
    else{
        nodo<Tipo> *tempPtr = primeroPtr;
        if ( primeroPtr == ultimoPtr )
            primeroPtr = ultimoPtr = 0;
        else if(primeroPtr->siguientePtr == ultimoPtr){
            primeroPtr = primeroPtr->siguientePtr;
        }else{
            nodo< Tipo > *actualPtr = primeroPtr;
            while ( actualPtr->siguientePtr->siguientePtr != ultimoPtr ){
                actualPtr = actualPtr->siguientePtr;
            }
            tempPtr = actualPtr->siguientePtr;//Penultima
            actualPtr->siguientePtr = ultimoPtr;
        } // fin de else
        valor = tempPtr->dato;
        delete tempPtr;
        return true;
    }
}

template< typename Tipo >
bool Lista< Tipo >::eliminarDelFinal( Tipo &valor ){
    if ( estaVacia() )
        return false;
    else{
        nodo< Tipo > *tempPtr = ultimoPtr;
        if ( primeroPtr == ultimoPtr )
            primeroPtr = ultimoPtr = 0;
        else{
            nodo< Tipo > *actualPtr = primeroPtr;
            // localiza el pen�ltimo elemento
            while ( actualPtr->siguientePtr != ultimoPtr )
                actualPtr = actualPtr->siguientePtr;
            ultimoPtr = actualPtr;
            actualPtr->siguientePtr = 0;
        } // fin de else
        valor = tempPtr->dato;
        delete tempPtr;
        return true;
    }
}

// esta la Lista vacia?
template< typename Tipo >
bool Lista< Tipo >::estaVacia() const{
    return primeroPtr == 0;
} // fin de la funcion estaVacia

template< typename Tipo >
nodo< Tipo > *Lista< Tipo >::crearNuevoNodo(const Tipo &size ){
    return new nodo< Tipo >( size );
}


template< typename Tipo >
void Lista< Tipo >::imprimir() const{
    if ( estaVacia() ) {
        cout << "La lista esta vacia\n\n";
        return;
    }
    nodo< Tipo > *actualPtr = primeroPtr;
    cout << "La lista es: ";
    while ( actualPtr != 0 ) {
        cout << actualPtr->dato << "\t";
        actualPtr = actualPtr->siguientePtr;
    }
    cout << "\n\n";
}
#endif
