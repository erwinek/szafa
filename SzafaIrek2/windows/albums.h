#ifndef ALBUMS_H
#define ALBUMS_H

#include <QWidget>
#include <QtGui>
#include "album.h"

class Albums : public QWidget
{
    Q_OBJECT
public:
    QLabel *header;
    QLabel *labelDown;
    explicit Albums(QWidget *parent = 0);
    QListWidget *listAlbum;
    QScrollArea *m_scrollArea;
    void ShowAlbums(QString path);
    QWidget *Kafelki;
    void ShowFoundAlbums(QStringList foundAlbums);

private:
    QSlider *sliderAlbums;
    QString albumsPath;
    int pageNr;
    int lastPageNr;
    void LoadDirectory(QString path);
    QStringList AlbumList;
    QPushButton *pageUp;
    QPushButton *pageDown;
    QPushButton *buttonPowrot;
    QGridLayout *gridLayout;
    Album *tablicaAlbumow[100];
    void ReloadAlbums();
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
