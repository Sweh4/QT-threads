#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "proizvodjac.h"
#include "potrosac.h"
#include "zajednickevarijable.h"
#include <QSemaphore>
#include <QLabel>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QDebug>
#include <QPropertyAnimation>

#include <QGraphicsProxyWidget>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void promjenaVrijednostiBuffera(int);
    void promjenaVrijednostiProizvodjaca(int);
    void promjenaVrijednostiPotrosaca(int);
    void primiKreiranoSlovo(char string);
    void pomjeriElementProizvodjaca();
    void pomjeriElementPotrosaca();

private:
    Ui::Dialog *ui;
    Proizvodjac *mProizvodjac;
    Potrosac *mPotrosac;

    QGraphicsScene *scene;
    QTimer *proizvodjacTimer;
    QTimer *potrosacTimer;

    QGraphicsLineItem *linija1, *linija2, *linija3, *linija4, *linija5, *linija6, *linija7;
    QGraphicsPathItem *proizvodjacRoundRect, *potrosacRoundRect;
    QPainterPath proizvodjacPath, potrosacPath, bufferPath;

    QGraphicsProxyWidget *Proxy[5];
    QGraphicsRectItem *rect[5];
    QLabel *label[5];
    QPropertyAnimation *animacija1, *animacija2, *animacija3, *animacija4, *animacija5, *animacija6, *animacija7, *animacija8, *animacija9, *animacija10;

    QPainter *labels;
};

#endif // DIALOG_H
