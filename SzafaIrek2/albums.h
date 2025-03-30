#ifndef ALBUMS_H
#define ALBUMS_H

#include <QWidget>
#include <QtGui>
#include "album.h"
#include "folder.h"

class Albums : public QWidget
{
    Q_OBJECT
public:
    QLabel *header;
    QLabel *labelDown;
    explicit Albums(QWidget *parent = 0);
    QListWidget *listAlbum;
    void ShowAlbums(QString path);
    QWidget *Kafelki;
    void ShowFoundAlbums(QList<Plyta> lPlyt);
    void ShowAlbumsList(QStringList albumsList);
    void ShowAlbumsList(QList<Plyta> lPlyt);
    QList<QImage> ListaOkladek;
private:
    QSlider *sliderAlbums;
    QString albumsPath;
    int pageNr;
    int lastPageNr;
    void LoadDirectory(QString path);
    QList<Plyta> listaPlyt;
    QList<Plyta> listaZnalezionychAlbumow;
    QPushButton *pageUp;
    QPushButton *pageDown;
    QPushButton *buttonPowrot;
    QGridLayout *gridLayout;
    Album *tablicaAlbumow[100];
    void ReloadAlbums();

    QPixmap picUp1;
    QPixmap picUp2;

    QPixmap picDown1;
    QPixmap picDown2;

signals:

public slots:
    void ShowSongScreen(Album *pAlbum);

private slots:
    void goPageUp();
    void goPageDown();
    void goBack();
    void slotValueChanged(int);
    void slotBlinkButtons();
};

#endif // ALBUMS_H
