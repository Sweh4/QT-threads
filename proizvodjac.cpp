#include "proizvodjac.h"
#include "zajednickevarijable.h"

Proizvodjac::Proizvodjac(QObject *parent) : QThread(parent)
{

}

void Proizvodjac::run()
{
    for(int i = 0; i < DataSize; ++i)
    {

       char randomLetter;
       int randomNumber;

       dostupniBajti.acquire();

       randomNumber = qrand() % 26;
       randomLetter = 'A' + randomNumber;
       buffer[i%BufferVel] = randomLetter;
       emit kreiranoSlovo(randomLetter);

       iskoristeniBajti.release();

       this->msleep(3000);

       emit promjenaNapunjenihBuffera(iskoristeniBajti.available());
       emit promjenaProizvedenihPodataka(i);

    }
}


