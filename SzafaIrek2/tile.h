#ifndef TILE_H
#define TILE_H

#include <QWidget>
#include <QtGui>

class Songs;

class Tile : public QWidget
{
    Q_OBJECT
public:
    Tile( QWidget *parent = 0, QString path = "", QString Artist = "", QString title = "", QPixmap okladkaImg = QPixmap());

    QLabel *okladka;
    QLabel *Wykonawca;
    QLabel *Tytul;
    QString albumPath;
    QString albumArtist;
    QString albumTitle;
    static Songs *songsPtr;

private:

    QPushButton *button;
    QTimer *loadImagesTimer;
    static const QSize Size;
    QPixmap *pixmap;
signals:
    
public slots:
    virtual void buttonClick();
    void loadImages();
};

class SongTile : public Tile
{
    Q_OBJECT

public:
      SongTile( QWidget *parent = 0, QString path = "", QString Artist = "", QString title = "", QPixmap okladkaImg = QPixmap()) :
          Tile(parent, path, Artist, title, okladkaImg)
    {

    };
public slots:
    virtual void buttonClick();
};

class AlbumTile : public Tile
{
    Q_OBJECT

public:
      AlbumTile( QWidget *parent = 0, QString path = "", QString Artist = "", QString title = "", QPixmap okladkaImg = QPixmap()) :
          Tile(parent, path, Artist, title, okladkaImg)
    {

    };
public slots:
    virtual void buttonClick();
};

#endif // TILE_H
