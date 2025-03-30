
#include <QtGui>
#include <QDir>
#include "widget.h"
#include "window.h"

#include "image.h"
#include "folder.h"
#include "szukaj.h"
#include <phonon>
#include <qfiledialog.h>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <QList>
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>
#include <QUrl>
//! [0]


cd *plytka;
Szukaj *oknoSzukaj;
folder *albums;

#include <QUrl>
Window::Window()
    : QWidget()
{
    QDesktopWidget* desktopWidget = qApp->desktop();
    QRect screenGeometry = desktopWidget->screenGeometry();
    screenWidth = screenGeometry.width();
    screenHeight = screenGeometry.height();

    // layout
    //Image *bar1 = new Image("gfx/lay_1.jpg",this);
    Image *bar1 = new Image("gfx/1.jpg",this);
    bar1->setFixedHeight(screenHeight);
    bar1->setFixedWidth(screenWidth);
    bar1->resize(1024, 768);
    bar1->show();

    plytka = new cd(this);
    plytka->setGeometry(0,0,500,500);
    plytka->raise();    
    plytka->show();
    plytka->raise();

    oknoSzukaj = new Szukaj(this);
    oknoSzukaj->setGeometry(0, 0, 1024, 768);
    oknoSzukaj->setWindowOpacity(0.1);
    oknoSzukaj->hide();

    albums = new folder(this);
    albums->raise();
    albums->show();

    QPushButton *buttonSzukaj = new QPushButton("Szukaj",this);
    buttonSzukaj->resize(140,60); //width, height.
    buttonSzukaj->move(20,20);
    connect(buttonSzukaj, SIGNAL(clicked()),this, SLOT(szukanie()));

    QPushButton *buttonWszystkie = new QPushButton("Wszystkie",this);
    buttonWszystkie->resize(140,60); //width, height.
    buttonWszystkie->move(20,110);
    connect(buttonWszystkie, SIGNAL(clicked()),albums, SLOT(MuzykaWszystkie()));

    QPushButton *buttonMpolska = new QPushButton("Muzyka\nPolska",this);
    buttonMpolska->resize(140,60); //width, height.
    buttonMpolska->move(20,200);
    connect(buttonMpolska, SIGNAL(clicked()),albums, SLOT(MuzykaPolska()));

    QPushButton *buttonMbiesiadna = new QPushButton("Muzyka\nBiesiadna",this);
    buttonMbiesiadna->resize(140,60); //width, height.
    buttonMbiesiadna->move(20,290);
    connect(buttonMbiesiadna, SIGNAL(clicked()),albums, SLOT(MuzykaBiesiadna()));

    QPushButton *buttonMzagraniczna = new QPushButton("Muzyka\nZagraniczna",this);
    buttonMzagraniczna->resize(140,60); //width, height.
    buttonMzagraniczna->move(20, 380);
    connect(buttonMzagraniczna, SIGNAL(clicked()),albums, SLOT(MuzykaZagraniczna()));

    QPushButton *buttonKaraoke = new QPushButton("Karaoke",this);
    buttonKaraoke->resize(140,60); //width, height.
    buttonKaraoke->move(20, 470);
    //connect(buttonMzagraniczna, SIGNAL(clicked()),albums, SLOT(MuzykaZagraniczna()));

    QPushButton *buttonSkladanki = new QPushButton("Składanki",this);
    buttonSkladanki->resize(140,60); //width, height.
    buttonSkladanki->move(20, 560);

    QPushButton *buttonNowosci = new QPushButton("Nowości",this);
    buttonNowosci->resize(140,60); //width, height.
    buttonNowosci->move(20, 650);


    QPushButton *button = new QPushButton("UP",this);
    connect(button, SIGNAL(clicked()),albums, SLOT(AlbumUp()));
    //button->setFlat(true);
    button->setAutoFillBackground(true);
    //button->setIcon(QPixmap::fromImage(szukaj));
    //button->setIconSize(szukaj.size());
    //button->resize(szukaj.size()); //width, height.
    button->resize(300, 25);
    button->move(200,300);
    button->show();


    QPushButton *button_down = new QPushButton("DOWN",this);
    connect(button_down, SIGNAL(clicked()),albums, SLOT(AlbumUp()));
    button_down->resize(300, 25); // first argument is width and second is the height.
    button_down->move(200,730);
    button_down->show();

    QPushButton *button_SongUp = new QPushButton("UP",this);
    connect(button_SongUp, SIGNAL(clicked()),albums, SLOT(SongUpDown()));
    button_SongUp->resize(300, 25); // first argument is width and second is the height.
    button_SongUp->move(600,300);
    button_SongUp->show();

    QPushButton *button_SongDown = new QPushButton("DOWN",this);
    connect(button_SongDown, SIGNAL(clicked()),albums, SLOT(SongUpDown()));
    button_SongDown->resize(300, 25); // first argument is width and second is the height.
    button_SongDown->move(600,730);
    button_SongDown->show();


    QPushButton *button_AddToQueque = new QPushButton("",this);
    //connect(button_AddToQueque, SIGNAL(clicked()),albums, SLOT(Play()));
    connect(button_AddToQueque, SIGNAL(clicked()),this, SLOT(AddToQueueFolder()));
    button_AddToQueque->resize(100, 100);
    button_AddToQueque->move(900,150);
    button_AddToQueque->show();
    QImage playButton("gfx/play.jpg");
    button_AddToQueque->setIcon(QPixmap::fromImage(playButton));
    button_AddToQueque->resize(100,100);
    button_AddToQueque->setIconSize(button_AddToQueque->size());

    connect(oknoSzukaj->buttonPlay, SIGNAL(clicked()),this, SLOT(AddToQueueSearch()));


    QTimer *timer = new QTimer(this);    
    connect(timer, SIGNAL(timeout()), plytka, SLOT(rotate()));    
    timer->start(100);

    QTimer *timer100ms = new QTimer(this);
    connect(timer100ms, SIGNAL(timeout()), albums, SLOT(TimerTick()));
    timer100ms->start(500);

    setWindowTitle(tr("Mr Digital"));


}

void Window::paintEvent(QPaintEvent *event)
{

}

void Window::resizeEvent(QResizeEvent *event)
{
    albums->resize(event->size());
    event->accept();

}

void Window::keyPressEvent(QKeyEvent *event)
{
   if (event->key() == Qt::Key_Escape) {
       qApp->quit();
   }
   if (event->key() == Qt::Key_1) {
       oknoSzukaj->raise();
   }
   if (event->key() == Qt::Key_2) {
       oknoSzukaj->hide();
   }
   if (event->key() == Qt::Key_F12) {
       albums->Kredyt++;
       albums->repaint();
   }

   repaint();
}

void Window::szukanie()
{

    oknoSzukaj->raise();
    oknoSzukaj->show();
}

void Window::AddToQueueSearch()
{

  if(albums->Kredyt)
  {
     albums->Kredyt--;
    Song *piosenka = new Song();
    QString path;
    piosenka->artist = "";
    piosenka->title = oknoSzukaj->listWidget->currentItem()->text();
    oknoSzukaj->SearchFile("/home/erwinek/mp3", piosenka->title, path);

        piosenka->path = path;

    piosenka->CdPath = "/cd.png";


    albums->Kolejka.enqueue(*piosenka);

    oknoSzukaj->hide();
  }
}

void Window::AddToQueueFolder()
{
    if(albums->Kredyt)
    {
     albums->Kredyt--;

     Song *piosenka = new Song();
     QString path;
     piosenka->artist = "";
     piosenka->title = albums->listSong->currentItem()->text();
     oknoSzukaj->SearchFile("/home/erwinek/mp3", piosenka->title, path);
     piosenka->path = path;
     piosenka->CdPath = "/cd.png";
     albums->Kolejka.enqueue(*piosenka);
    }

}

//! [0]
