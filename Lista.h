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

    // Simulador de manejo de memoria en nodos

    void actualizarLibre() {
        nodo<Tipo> *actual = primeroPtr;

        while (actual != nullptr) {
            // Loopear hasta encontrar un nodo que este lleno | getEstado() = false
            if (!actual->getEstado()) {
                libre = actual;
                break;
            }
        }

        // No se encontraron libres
        libre = nullptr;
    };

    /*
     * Inserta el dato especificado en el nodo marcado como libre.
     * Retorna true si la operacion se hizo con exito.
     */
    bool insertarEnLibre(Tipo data) {
        if (libre == nullptr)
            return false;

        libre->setDato(data);
        libre->setEstado(true);
        actualizarLibre();
        return true;
    };

    /*
     * Ordena los datos de la lista en orden ascendente.
     */
    void ordenarLista() {
        // 1 - 3 - 4 - 2 - null;

        nodo<Tipo> *nodoI = primeroPtr;

        // Iterar toda la lista de nodos
        while (nodoI != nullptr) {
            nodo<Tipo> *actual = nodoI;

            while (actual != nullptr) {
                if (actual->siguientePtr == nullptr) {
                    break;
                }

                cout << "Actual: " << actual->getSize() << "\n";
                cout << "Sig: " << actual->siguientePtr->getSize() << "\n";

                // Ordenar si es mayor
                if (actual->getSize() > actual->getSiguientePtr()->getSize() ) {
                    cout << "Encontrado size menor!\n";
                    Tipo actDato = actual->getDato();
                    nodo<Tipo> *apuntador = actual->apuntador;
                    bool actEstado = actual->getEstado();
                    int size = actual->getSize();

                    nodo<Tipo> *sig = actual->siguientePtr;

                    // Reemplazar los valores actuales del nodo actual
                    actual->setDato( sig->getDato() );
                    actual->setSize( sig->getSize() );
                    actual->setEstado( sig->getEstado() );
                    actual->setApuntador( sig->apuntador );

                    // Reemplazar los valores del siguiente nodo
                    nodo<Tipo> *siguiente = actual->siguientePtr;

                    siguiente->setDato(actDato);
                    siguiente->setApuntador(apuntador);
                    siguiente->setEstado(actEstado);
                    siguiente->setSize(size);
                }

                actual = actual->siguientePtr;
            }

            nodoI = nodoI->siguientePtr;
        }
    };
private:
    nodo< Tipo > *primeroPtr;
    nodo< Tipo > *crearNuevoNodo( const Tipo &size ); //crear un nuevo nodo con tamaño ya definido
    nodo< Tipo > *ultimoPtr;
    nodo< Tipo > *libre;

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
    nodo< Tipo > *nuevoPtr = crearNuevoNodo( valor );
    if ( estaVacia() )
        primeroPtr = ultimoPtr = nuevoPtr;
    else{
        ultimoPtr->siguientePtr = nuevoPtr;
        ultimoPtr = nuevoPtr;
    }

    cout << "[insertarFinal] Actualizando libre...\n";
    actualizarLibre();
    cout << "[insertarFinal] Done!\n";
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
        cout << actualPtr->dato << "| Size: " << actualPtr->getSize() << "\t";
        actualPtr = actualPtr->siguientePtr;
    }
    cout << "\n\n";
}
#endif
