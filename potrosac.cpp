#include "potrosac.h"
#include "zajednickevarijable.h"

Potrosac::Potrosac(QObject *parent) : QThread(parent)
{

}

void Potrosac::run()
{
    for(int i = 0; i < DataSize; ++i)
    {
        iskoristeniBajti.acquire();
        fprintf(stderr,"%c",buffer[i%BufferVel]);


        if(dostupniBajti.available() == 5)
        {
            qDebug() << "Buffer je prazan totalno.";
        }else{
            dostupniBajti.release();

            this->msleep(3000);

            emit promjenaNapunjenihBuffera(iskoristeniBajti.available());
            emit promjenaPotrosenihPodataka(i);
        }

    }
        fprintf(stderr,"\n");
}
