#ifndef LISTA_H
#define LISTA_H
#include <nodo.h>

#include <iostream>
#include <QMessageBox>
#include <qmessagebox.h>
using std::cout;

template< typename Tipo >
class Lista{
    friend class cframe;
public:
    Lista();
    ~Lista();
    void insertarAlFrente( const Tipo & );
    void insertarEnPenultimo(const Tipo & );
    void insertarAlFinal( int size );
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
            if (actual->getEstado() == false) {
                libre = actual;
                cout << "[actualizarLibre] Se actualizo libre.\n";
                return;
            }
            actual = actual->siguientePtr;
        }

        // No se encontraron libres
        libre = nullptr;
        cout << "[actualizarLibre] Libre ahora es null\n";
    };

    /*
     * Inserta el dato especificado en el nodo marcado como libre.
     * Retorna true si la operacion se hizo con exito.
     */
    bool insertarEnLibre(Tipo data) {
        if (libre == nullptr) {
            cout << "[insertFree] Libre is null.\n";
            //QMessageBox::information(this, "Información", "No hay nodos disponibles.");
            return false;
        }

        if (libre->getSize() >= sizeof(data)) {
            cout << "Tamanio del dato es: " << sizeof (data);
            libre->setDato(data);
            libre->setEstado(true);
            libre->setApuntador(nullptr);
            actualizarLibre();
            return true;
        }

        cout << "No hay suficiente size. Size de libre:" <<libre->getSize() <<  ". Buscando nuevo nodo para guardar: " << data << "...\n";


        nodo<Tipo> *encontrado = buscarNodoLibre(sizeof(data));

        if (encontrado == nullptr) return false;

        cout << "encontrado con size: " << encontrado->getSize() << "\n";
        encontrado->setDato(data);
        encontrado->setEstado(true);
        encontrado->setApuntador(nullptr);
        return true;
        actualizarLibre();

    };


    /*
     * Busca un nodo libre con tamano mayor o igual al especificado
     */
    nodo<Tipo>* buscarNodoLibre(int size) {
        nodo<Tipo> *act = primeroPtr;

        while (act != nullptr) {
           if (act->getEstado() == false && act->getSize() >= size) return act;

           act = act->siguientePtr;
        }

        return nullptr;
    }

    /*
     * Ordena los datos de la lista en orden ascendente.
     */
    void ordenarLista() {
        cout << "ANTES DE ORDENAR: \n";
        imprimir();

        cout << "=====================================\n";

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
                    cout << "Encontrado size menor!\nz";
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
        imprimir();
        cout << "=====================================\n";
    };
    int getCantidadDeNodos();
    void sumarUnoACantidadNodos();

private:
    nodo< Tipo > *primeroPtr;
    nodo< Tipo > *crearNuevoNodo( int size ); //crear un nuevo nodo con tamaño ya definido
    nodo< Tipo > *ultimoPtr;
    nodo< Tipo > *libre;
    int cantidadDeNodos;

};

// constructor predeterminado
template< typename Tipo >
Lista< Tipo >::Lista(): primeroPtr( 0 ), ultimoPtr( 0 ), cantidadDeNodos( 0 ){
    this->libre = nullptr;
}

// destructor
template< typename Tipo >
Lista< Tipo >::~Lista(){
    if ( !estaVacia() ){
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
void Lista< Tipo >::insertarAlFinal( int size ){
    // Insertar un nodo del size especificado al final
    nodo< Tipo > *nuevoPtr = crearNuevoNodo( size );
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
nodo< Tipo > *Lista< Tipo >::crearNuevoNodo( int size ){
    return new nodo< Tipo >( size );
}

template< typename Tipo >
int Lista< Tipo >::getCantidadDeNodos()
{
    return cantidadDeNodos;
}

template<typename Tipo>
void Lista<Tipo>::sumarUnoACantidadNodos()
{
    cantidadDeNodos++;
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
