#include "songlistwidget.h"

SongListWidget::SongListWidget(QWidget *parent, QString pathOkladka, QString Artist, QString title, QString songTime, bool isFirst) :
    QWidget(parent)
{
    QSize itemSize(700,100);
    labelBackground = new QLabel(this);
    QImage labelBackgroundImage;
    if (isFirst)    labelBackgroundImage.load("gfx/Actually_playing.png");
    else labelBackgroundImage.load("gfx/Background_artist_tittle.png");

    labelBackground->setPixmap(QPixmap::fromImage(labelBackgroundImage).scaled(itemSize));
    labelBackground->resize(itemSize);
    labelBackground->move(0,0);

    okladka = new QLabel(this);
    okladka->resize(80,80);
    okladka->move(15,10);

    QPixmap pixmap(pathOkladka);
    okladka->setPixmap(pixmap.scaled(QSize(70,70)));

    Wykonawca = new QLabel(Artist, this);
    Wykonawca->resize(600,40);
    Wykonawca->move(100,10);

    Tytul = new QLabel(title, this);
    Tytul->resize(600,40);
    Tytul->move(100,50);

    czas = new QLabel(songTime, this);
    czas->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    czas->resize(100,100);
    czas->move(600,5);

    if (isFirst) czas->hide();



}
