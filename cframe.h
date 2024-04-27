#ifndef CFRAME_H
#define CFRAME_H

#include <QMainWindow>
#include "Lista.h"

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
    void on_guardarBtn_clicked();

    void on_pushButton_pressed();

private:
    Ui::cframe *ui;
    Lista<int> listaRandom;
    Lista<int> listaOrdenada;
};
#endif // CFRAME_H
