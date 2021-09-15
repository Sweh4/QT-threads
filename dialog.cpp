#include "dialog.h"
#include "ui_dialog.h"
#include "zajednickevarijable.h"


char buffer[BufferVel];
QSemaphore dostupniBajti(BufferVel);
QSemaphore iskoristeniBajti;
QString slovo;
int brojPozivaPomjeriElement = 0;
int brojPozivaPomjeriElementPotrosaca = -1;
int brojPozivaProizvodjac = 0;


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    mProizvodjac=new Proizvodjac(this);
    mPotrosac=new Potrosac(this);

    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0, 802, 482);
    scene->setBackgroundBrush(Qt::gray);

    QPen crna_boja(Qt::black);
    crna_boja.setWidth(2);
    QPen plava_boja(Qt::blue);
    plava_boja.setWidth(2);
    QBrush zelena_boja(Qt::green);
    QBrush crvena_boja(Qt::red);

    ui->graphicsView->setScene(scene);

    proizvodjacTimer = new QTimer(this);
    potrosacTimer = new QTimer(this);

    connect(proizvodjacTimer, SIGNAL(timeout()),this,SLOT(pomjeriElementProizvodjaca()));
    connect(potrosacTimer,SIGNAL(timeout()),this,SLOT(pomjeriElementPotrosaca()));

    connect(mPotrosac,SIGNAL(promjenaNapunjenihBuffera(int)),this,SLOT(promjenaVrijednostiBuffera(int)));
    connect(mProizvodjac,SIGNAL(promjenaNapunjenihBuffera(int)),this,SLOT(promjenaVrijednostiBuffera(int)));

    connect(mProizvodjac,SIGNAL(kreiranoSlovo(char)),this,SLOT(primiKreiranoSlovo(char)));

    connect(mPotrosac,SIGNAL(promjenaPotrosenihPodataka(int)),this,SLOT(promjenaVrijednostiPotrosaca(int)));
    connect(mProizvodjac,SIGNAL(promjenaProizvedenihPodataka(int)),this,SLOT(promjenaVrijednostiProizvodjaca(int)));


    rect[0] = new QGraphicsRectItem();
    rect[1] = new QGraphicsRectItem();
    rect[2] = new QGraphicsRectItem();
    rect[3] = new QGraphicsRectItem();
    rect[4] = new QGraphicsRectItem();

    Proxy[0] = new QGraphicsProxyWidget(rect[0]);
    Proxy[1] = new QGraphicsProxyWidget(rect[1]);
    Proxy[2] = new QGraphicsProxyWidget(rect[2]);
    Proxy[3] = new QGraphicsProxyWidget(rect[3]);
    Proxy[4] = new QGraphicsProxyWidget(rect[4]);

    animacija1 = new QPropertyAnimation(Proxy[0],"geometry");
    animacija2 = new QPropertyAnimation(Proxy[1],"geometry");
    animacija3 = new QPropertyAnimation(Proxy[2],"geometry");
    animacija4 = new QPropertyAnimation(Proxy[3],"geometry");
    animacija5 = new QPropertyAnimation(Proxy[4],"geometry");
    animacija6 = new QPropertyAnimation(Proxy[0],"geometry");
    animacija7 = new QPropertyAnimation(Proxy[1],"geometry");
    animacija8 = new QPropertyAnimation(Proxy[2],"geometry");
    animacija9 = new QPropertyAnimation(Proxy[3],"geometry");
    animacija10 = new QPropertyAnimation(Proxy[4],"geometry");

    mProizvodjac->start();
    mPotrosac->start();

    proizvodjacPath.addRoundedRect(40,40,100,100,10,10);
    proizvodjacRoundRect=scene->addPath(proizvodjacPath,crna_boja,zelena_boja);
    potrosacPath.addRoundedRect(670,40,100,100,10,10);
    potrosacRoundRect=scene->addPath(potrosacPath,crna_boja,crvena_boja);

    QGraphicsTextItem *proizvodjacTekst = new QGraphicsTextItem("Proizvođač");
    proizvodjacTekst->setFont(QFont("Times New Roman",10,QFont::Bold));
    proizvodjacTekst->setDefaultTextColor(Qt::yellow);
    proizvodjacTekst->setPos(45,70);
    scene->addItem(proizvodjacTekst);

    QGraphicsTextItem *potrosacTekst = new QGraphicsTextItem("Potrošač");
    potrosacTekst->setFont(QFont("Times New Roman",10,QFont::Bold));
    potrosacTekst->setDefaultTextColor(Qt::yellow);
    potrosacTekst->setPos(685,70);
    scene->addItem(potrosacTekst);

    QGraphicsTextItem *bufferTekst = new QGraphicsTextItem("B U F F E R");
    bufferTekst->setFont(QFont("Times New Roman",10,QFont::Bold));
    bufferTekst->setDefaultTextColor(Qt::black);
    bufferTekst->setPos(350,450);
    scene->addItem(bufferTekst);

    linija1=scene->addLine(270,350,270,435,plava_boja);
    linija2=scene->addLine(360,350,360,435,plava_boja);
    linija3=scene->addLine(450,350,450,435,plava_boja);
    linija4=scene->addLine(540,350,540,435,plava_boja);
    linija5=scene->addLine(180,350,180,435,plava_boja);
    linija6=scene->addLine(630,350,630,435,plava_boja);
    linija7=scene->addLine(180,435,630,435,plava_boja);

}

void Dialog::primiKreiranoSlovo(char string)
{
    slovo = string;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::promjenaVrijednostiProizvodjaca(int)
{
    label[0] = new QLabel();
    label[1] = new QLabel();
    label[2] = new QLabel();
    label[3] = new QLabel();
    label[4] = new QLabel();

    qDebug() << "Kreirano slovo: " << slovo;

    QPixmap labelPix(70,70);
    labelPix.fill(Qt::yellow);
    labels = new QPainter(&labelPix);
    labels->setPen(Qt::blue);
    labels->setFont(QFont("Times New Roman", 16, QFont::Bold));

    if( brojPozivaProizvodjac == 0)
    {
        labels->drawText(labelPix.rect(),Qt::AlignCenter, slovo);
        label[0]->setPixmap(labelPix);
        Proxy[0]->setWidget(label[0]);
        Proxy[0]->setPos(-200,-200);
        scene->addItem(rect[0]);

    }

    if( brojPozivaProizvodjac == 1)
    {
        labels->drawText(labelPix.rect(),Qt::AlignCenter, slovo);
        label[1]->setPixmap(labelPix);
        Proxy[1]->setWidget(label[1]);
        Proxy[1]->setPos(-200,-200);
        scene->addItem(rect[1]);
    }

    if( brojPozivaProizvodjac == 2)
    {
        labels->drawText(labelPix.rect(),Qt::AlignCenter, slovo);
        label[2]->setPixmap(labelPix);
        Proxy[2]->setWidget(label[2]);
        Proxy[2]->setPos(-200,-200);
        scene->addItem(rect[2]);

     }

    if( brojPozivaProizvodjac == 3)
    {
        labels->drawText(labelPix.rect(),Qt::AlignCenter, slovo);
        label[3]->setPixmap(labelPix);
        Proxy[3]->setWidget(label[3]);
        Proxy[3]->setPos(-200,-200);
        scene->addItem(rect[3]);
    }

    if( brojPozivaProizvodjac == 4)
    {
        labels->drawText(labelPix.rect(),Qt::AlignCenter, slovo);
        label[4]->setPixmap(labelPix);
        Proxy[4]->setWidget(label[4]);
        Proxy[4]->setPos(-200,-200);
        scene->addItem(rect[4]);

     }

    brojPozivaProizvodjac++;

     if(brojPozivaProizvodjac == 5)
        brojPozivaProizvodjac = 0;


     QPen crna_boja(Qt::black);
     crna_boja.setWidth(2);
     QPen plava_boja(Qt::blue);
     plava_boja.setWidth(2);
     QBrush zelena_boja(Qt::green);
     QBrush crvena_boja(Qt::red);

     proizvodjacPath.addRoundedRect(40,40,100,100,10,10);
     proizvodjacRoundRect=scene->addPath(proizvodjacPath,crna_boja,zelena_boja);

     potrosacPath.addRoundedRect(670,40,100,100,10,10);
     potrosacRoundRect=scene->addPath(potrosacPath,crna_boja,crvena_boja);

     QGraphicsTextItem *proizvodjacTekst = new QGraphicsTextItem("Proizvođač");
     proizvodjacTekst->setFont(QFont("Times New Roman",10,QFont::Bold));
     proizvodjacTekst->setDefaultTextColor(Qt::yellow);
     proizvodjacTekst->setPos(45,70);
     scene->addItem(proizvodjacTekst);

     QGraphicsTextItem *potrosacTekst = new QGraphicsTextItem("Potrošač");
     potrosacTekst->setFont(QFont("Times New Roman",10,QFont::Bold));
     potrosacTekst->setDefaultTextColor(Qt::yellow);
     potrosacTekst->setPos(685,70);
     scene->addItem(potrosacTekst);

     QGraphicsTextItem *bufferTekst = new QGraphicsTextItem("B U F F E R");
     bufferTekst->setFont(QFont("Times New Roman",10,QFont::Bold));
     bufferTekst->setDefaultTextColor(Qt::black);
     bufferTekst->setPos(350,450);
     scene->addItem(bufferTekst);

     if(dostupniBajti.available() > 0){
         proizvodjacTimer->singleShot(200,this,SLOT(pomjeriElementProizvodjaca()));
     }else{
         qDebug() << "U bufferu nema slobodnih mjesta";
  }
}

void Dialog::pomjeriElementProizvodjaca()
{

    if(brojPozivaPomjeriElement == 0 )
    {
        animacija1->setDuration(1000);
        animacija1->setStartValue(QRect(100,50,70,70));
        animacija1->setKeyValueAt(0.3,QRect(190,50,70,70));
        animacija1->setEndValue(QRect(190,355,70,70));
        animacija1->start();
    }

    if(brojPozivaPomjeriElement == 1 )
    {
        animacija2->setDuration(1000);
        animacija2->setStartValue(QRect(100,50,70,70));
        animacija2->setKeyValueAt(0.3,QRect(280,50,70,70));
        animacija2->setEndValue(QRect(280,355,70,70));
        animacija2->start();
    }

    if(brojPozivaPomjeriElement == 2 )
    {
        animacija3->setDuration(1000);
        animacija3->setStartValue(QRect(100,50,70,70));
        animacija3->setKeyValueAt(0.3,QRect(370,50,70,70));
        animacija3->setEndValue(QRect(370,355,70,70));
        animacija3->start();
    }

    if(brojPozivaPomjeriElement == 3 )
    {
        animacija4->setDuration(1000);
        animacija4->setStartValue(QRect(100,50,70,70));
        animacija4->setKeyValueAt(0.3,QRect(460,50,70,70));
        animacija4->setEndValue(QRect(460,355,70,70));
        animacija4->start();
    }

    if(brojPozivaPomjeriElement == 4 )
    {
        animacija5->setDuration(1000);
        animacija5->setStartValue(QRect(100,50,70,70));
        animacija5->setKeyValueAt(0.6,QRect(550,50,70,70));
        animacija5->setEndValue(QRect(550,355,70,70));
        animacija5->start();
    }

    brojPozivaPomjeriElement++;

    if (brojPozivaPomjeriElement == 5)
         brojPozivaPomjeriElement = 0;

}

void Dialog::pomjeriElementPotrosaca()
{
    //qDebug() << "Pomjeri Element potrosaca pozvan : " << brojPozivaPomjeriElementPotrosaca;

    if(brojPozivaPomjeriElementPotrosaca == 1)
    {
        animacija6->setDuration(2000);
        animacija6->setStartValue(QRect(190,355,70,70));
        animacija6->setKeyValueAt(0.6,QRect(190,50,70,70));
        animacija6->setEndValue(QRect(680,50,70,70));
        animacija6->start();
    }

    if(brojPozivaPomjeriElementPotrosaca == 2)
    {
        animacija7->setDuration(2000);
        animacija7->setStartValue(QRect(280,360,70,70));
        animacija7->setKeyValueAt(0.6,QRect(280,50,70,70));
        animacija7->setEndValue(QRect(680,50,70,70));
        animacija7->start();
    }

    if(brojPozivaPomjeriElementPotrosaca == 3)
    {
        animacija8->setDuration(2000);
        animacija8->setStartValue(QRect(370,355,70,70));
        animacija8->setKeyValueAt(0.6,QRect(370,50,70,70));
        animacija8->setEndValue(QRect(680,50,70,70));
        animacija8->start();
    }

    if(brojPozivaPomjeriElementPotrosaca == 4)
    {
        animacija9->setDuration(2000);
        animacija9->setStartValue(QRect(460,355,70,70));
        animacija9->setKeyValueAt(0.6,QRect(460,50,70,70));
        animacija9->setEndValue(QRect(680,50,70,70));
        animacija9->start();

    }

    if(brojPozivaPomjeriElementPotrosaca == 5)
    {
        animacija10->setDuration(2000);
        animacija10->setStartValue(QRect(550,355,70,70));
        animacija10->setKeyValueAt(0.6,QRect(550,50,70,70));
        animacija10->setEndValue(QRect(680,50,70,70));
        animacija10->start();

    }

    if(brojPozivaPomjeriElementPotrosaca == 6)
       brojPozivaPomjeriElementPotrosaca = 0;


}

void Dialog::promjenaVrijednostiBuffera(int)
{


}

void Dialog::promjenaVrijednostiPotrosaca(int)
{
    if(iskoristeniBajti.available() < 5){

        if(!buffer[0] == '\0' || !buffer[1] == '\0' || !buffer[2] == '\0'
                ||
           !buffer[3] == '\0' || !buffer[4] == '\0')
            {
                potrosacTimer->singleShot(0,this,SLOT(pomjeriElementPotrosaca()));
            }

        brojPozivaPomjeriElementPotrosaca++;

        if(brojPozivaPomjeriElementPotrosaca == 6){
            brojPozivaPomjeriElementPotrosaca = 1;
        }
        qDebug() << "Buffer je prazan";
    }else{
        qDebug() << "Buffer pun";
    }

}
