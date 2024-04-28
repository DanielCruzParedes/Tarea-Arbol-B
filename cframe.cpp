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

void cframe::on_Btn_Guardar_clicked()
{
    // Guardar info en el nodo disponible
    string data = ui->datoInput->text().toStdString();

    listaRandom.insertarEnLibre(data);
    listaOrdenada.insertarEnLibre(data);

    ui->datoInput->clear();

    ui->TW_Mostrar->setColumnCount(2);
    ui->TW_Mostrar->setHorizontalHeaderLabels(QStringList()<<"Lista Ordenada"<<"Lista Random");
}


void cframe::on_Btn_Crear_clicked()
{
    int nodeSize = stoi( ui->sizeInput->text().toStdString() );
    listaRandom.insertarAlFinal(nodeSize);
    listaOrdenada.insertarAlFinal(nodeSize);

    listaOrdenada.ordenarLista();

    ui->sizeInput->clear();
    // TODO: Mostrar una alerta de que se agrego el nodo
}

