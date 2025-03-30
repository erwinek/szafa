#ifndef SONGWIDGET_H
#define SONGWIDGET_H

#include <QWidget>
#include <QtGui>
//#include "songs.h"

class Songs;

class SongWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SongWidget( QWidget *parent = 0, QString pathOkladka = "", QString title = "");
    QLabel *okladka;
    QLabel *Tytul;
    QLabel *Tytul2;
    QString albumPath;
    QString songTitle;
    Songs* songsPtr;

signals:
    
public slots:
    void clickSong();
    
};

#endif // SONGWIDGET_H
