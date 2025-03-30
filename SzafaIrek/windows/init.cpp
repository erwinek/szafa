#include <QtGui>
#include "init.h"
#include "window.h"

Init::Init(QWidget *parent) :
    QWidget(parent)
{

    progressBar  = new QProgressBar(this);
    progressBar->show();
    progressBar->resize(400,50); //width, height.
    progressBar->move((1024-400)/2, 768/2);

    progressBar->setRange(1,100);

    QLabel *ver = new QLabel("Mr Digital v1.7 \n 2013.02.15", this);
    ver->resize(100,50); //width, height.
    ver->move((1024-400)/2, 768/3);

    BackgroundImage.load("gfx/szukaj3.jpg");

    QTimer *Tprogress = new QTimer(this);
    connect(Tprogress, SIGNAL(timeout()), this, SLOT(progress()));
    Tprogress->setInterval(200);
    Tprogress->start();
}

void Init::resizeEvent(QResizeEvent *event)
{
    event->accept();
}
void Init::paintEvent(QPaintEvent *event)
{
    event=event;
    QPainter paint( this );
    paint.drawImage(QRect(0, 0, 1024, 768), BackgroundImage);
    paint.end();
}

void Init::progress()
{
    static int progressCount = 0;

    progressBar->setValue(progressCount*10);
    if (progressCount<10) progressCount++;
}
