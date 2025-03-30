#ifndef ALBUM_H
#define ALBUM_H

#include <QWidget>
#include <QtGui>
class Albums;

class Album : public QWidget
{
    Q_OBJECT
public:
    explicit Album( QWidget *parent = 0, QString pathOkladka = "", QString Artist = "", QString title = "");
    QLabel *okladka;
    QLabel *Wykonawca;
    QLabel *Tytul;
    QString albumPath;
    QString albumArtist;
    QString albumTitle;
    static Albums *albumsPtr;
signals:
    
public slots:
    void openAlbum();
};

#endif // ALBUM_H
