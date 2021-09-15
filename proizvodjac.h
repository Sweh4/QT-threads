#ifndef PROIZVODJAC_H
#define PROIZVODJAC_H

#include <QThread>
#include <QObject>
#include <QDebug>

class Proizvodjac : public QThread
{
    Q_OBJECT

public:
    explicit Proizvodjac(QObject *parent=0);
    void run();

signals:
    void promjenaProizvedenihPodataka(int);
    void promjenaNapunjenihBuffera(int);
    void kreiranoSlovo(char);

};

#endif // PROIZVODJAC_H
