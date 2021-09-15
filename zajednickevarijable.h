#ifndef ZAJEDNICKEVARIJABLE
#define ZAJEDNICKEVARIJABLE
#include <QSemaphore>

const int DataSize=100;
const int BufferVel=5;

extern char buffer[BufferVel];

extern int brojPozivaPomjeriElement;
extern int brojPozivaPomjeriElementPotrosaca;
extern int brojPozivaProizvodjac;
extern QString slovo;
extern QSemaphore dostupniBajti;
extern QSemaphore iskoristeniBajti;

#endif // ZAJEDNICKEVARIJABLE

