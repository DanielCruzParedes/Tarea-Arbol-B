#include "cframe.h"
#include "ui_cframe.h"
#include <nodo.h>
#include <string>
#include <QMessageBox>

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

void cframe::on_Btn_Guardar_clicked()
{
    // Guardar info en el nodo disponible
    string data = ui->datoInput->text().toStdString();

    listaRandom.insertarEnLibre(data);
    listaOrdenada.insertarEnLibre(data);

    ui->datoInput->clear();

    ui->tw_Acciones->setColumnCount(2);
    ui->tw_Acciones->setHorizontalHeaderLabels(QStringList()<<"Lista Random"<<"Lista Aleatorio");
    ui->tw_Acciones->setRowCount(listaOrdenada.getCantidadDeNodos());
}


void cframe::on_Btn_Crear_clicked()
{
    int nodeSize = stoi( ui->sizeInput->text().toStdString() );
    listaRandom.insertarAlFinal(nodeSize);
    listaOrdenada.insertarAlFinal(nodeSize);

    listaOrdenada.ordenarLista();

    ui->sizeInput->clear();
    listaOrdenada.sumarUnoACantidadNodos();
    listaRandom.sumarUnoACantidadNodos();

    QMessageBox::information(this,"Exito","Nodo creado con exito.");

    //Que aparezcan en los table widget
    ui->tw_Espacios->setColumnCount(2);
    ui->tw_Espacios->setHorizontalHeaderLabels(QStringList()<<"Lista Random"<<"Lista Ordenada");
    ui->tw_Espacios->setRowCount(listaOrdenada.getCantidadDeNodos());
    mostrarTWEspacios();

}

void cframe::mostrarTWEspacios()
{
    //Mostrar en la columna random
    actPtr = listaRandom.primeroPtr;
    int i = 0;
    while ( actPtr != 0 ) {
        ui->tw_Espacios->setItem(i,0, new QTableWidgetItem(QString::number(actPtr->getSize())));
        actPtr = actPtr->getSiguientePtr();
        i++;
    }

    //Mostrar en la columna ordenada
    actPtr = listaOrdenada.primeroPtr;
    int j = 0;
    while ( actPtr != 0 ) {
        ui->tw_Espacios->setItem(j,1, new QTableWidgetItem(QString::number(actPtr->getSize())));
        actPtr = actPtr->getSiguientePtr();
        j++;
    }
}

void cframe::mostrarTWAcciones()
{
    //Mostrar en la columna random
    actPtr = listaRandom.primeroPtr;
    int i = 0;
    while ( actPtr != 0 ) {
        ui->tw_Acciones->setItem(i,0, new QTableWidgetItem(QString::number(actPtr->getSize())));
        actPtr = actPtr->getSiguientePtr();
        i++;
    }

    //Mostrar en la columna ordenada
    actPtr = listaOrdenada.primeroPtr;
    int j = 0;
    while ( actPtr != 0 ) {
        ui->tw_Espacios->setItem(j,1, new QTableWidgetItem(QString::number(actPtr->getSize())));
        actPtr = actPtr->getSiguientePtr();
        j++;
    }
}

