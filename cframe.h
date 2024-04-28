#ifndef CFRAME_H
#define CFRAME_H

#include <QMainWindow>
#include "Lista.h"
#include <nodo.h>
#include <string>

using std::string;

QT_BEGIN_NAMESPACE
namespace Ui { class cframe; }
QT_END_NAMESPACE

class cframe : public QMainWindow
{
    Q_OBJECT

public:
    cframe(QWidget *parent = nullptr);
    ~cframe();

private slots:

    void on_Btn_Guardar_clicked();
    void on_Btn_Crear_clicked();

    void mostrarTWEspacios();
    void mostrarTWDatos();


private:
    Ui::cframe *ui;
    Lista<string> listaRandom;
    Lista<string> listaOrdenada;

    nodo<string> *actPtr;
};
#endif // CFRAME_H
