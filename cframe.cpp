#include "cframe.h"
#include "ui_cframe.h"
#include <string>

using std::stoi;

cframe::cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cframe)
{
    ui->setupUi(this);
}

cframe::~cframe()
{
    delete ui;
    cout << "Ordenada: \n";
    listaOrdenada.imprimir();

    cout << "\nRandom: \n";
    listaRandom.imprimir();

}


void cframe::on_guardarBtn_clicked()
{
    // Guardar info en el nodo disponible
    int data = stoi( ui->datoInput->text().toStdString() );
    int size = sizeof(data); // o pedir un input del size
}


void cframe::on_pushButton_pressed()
{
    int nodeSize = stoi( ui->sizeInput->text().toStdString() );
    listaRandom.insertarAlFinal(nodeSize);
    listaOrdenada.insertarAlFinal(nodeSize);

    listaOrdenada.ordenarLista();

    ui->sizeInput->clear();
    // TODO: Mostrar una alerta de que se agrego el nodo
}

