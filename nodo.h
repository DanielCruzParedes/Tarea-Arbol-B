#ifndef NODO_H
#define NODO_H

#include <iostream>

template< typename Tipo > class Lista;
template< typename Tipo >
class nodo{
    friend class Lista<Tipo>;
public:
    //Nodo( const Tipo &dato );
    nodo(int size);/*constructor para crear un nodo vacio
                   (para hacer nodos ya predefinidos solo con el tamaño)*/

    //SETTERS Y GETTERS
    Tipo getDato() const; // Devuelve "Tipo" porque se puede tener cualquier tipo de dato
    void setDato(const Tipo &newDato);

    int getSize() const;
    void setSize(int nuevoSize);

    bool getEstado() const;
    void setEstado(bool newEstado);

    nodo<Tipo> *getSiguientePtr() const;
    void setSiguientePtr(nodo<Tipo> *newSiguientePtr);

    void setApuntador(nodo<Tipo> *objetivo) {
        this->apuntador = objetivo;
    }


private:
    int size; //Tamaño asignado al nodo
    bool estado; //true = lleno ; false = vacio
    nodo<Tipo> *siguientePtr; //Pointer que apunta al siguiente nodo vacio (CREO)
    nodo<Tipo> *apuntador = nullptr;
    Tipo dato;
};

template<typename Tipo>
nodo<Tipo>::nodo(int size)
{
    this->size = size;
    this->dato = "";
    this->estado = false;
    this->siguientePtr = nullptr;
}

template<typename Tipo>
Tipo nodo<Tipo>::getDato() const
{
    return dato;
}

template<typename Tipo>
int nodo<Tipo>::getSize() const
{
    return size;
}

template<typename Tipo>
void nodo<Tipo>::setSize(int nuevoSize)
{
    size = nuevoSize;
}

template<typename Tipo>
bool nodo<Tipo>::getEstado() const
{
    return estado;
}

template<typename Tipo>
void nodo<Tipo>::setEstado(bool newEstado)
{
    estado = newEstado;
}

template<typename Tipo>
nodo<Tipo> *nodo<Tipo>::getSiguientePtr() const
{
    return siguientePtr;
}

template<typename Tipo>
void nodo<Tipo>::setSiguientePtr(nodo<Tipo> *newSiguientePtr)
{
    siguientePtr = newSiguientePtr;
}

template<typename Tipo>
void nodo<Tipo>::setDato(const Tipo &newDato)
{
    dato = newDato;
}

//// constructor
//template< typename Tipo >
//Nodo<Tipo>::Nodo( const Tipo &dato )
//    : dato( dato ), siguientePtr( 0 ){

//}

#endif
