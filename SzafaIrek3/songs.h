#ifndef SONGS_H
#define SONGS_H

#include <QWidget>
#include <QtGui>
#include "songwidget.h"
#include "album.h"

class Songs : public QWidget
{
    Q_OBJECT
public:
    explicit Songs(QWidget *parent = 0, Album *album = 0);
    void showSongs(Album const *album);
    void showTop20(QStringList songTop20);
    QLabel *header;
    void showFoundSongs(QString title, QStringList foundSongs, QStringList imagesPaths);

private:    
    int pageNr;
    int lastPageNr;
    QSlider *sliderAlbums;
    QLabel *labelDown;
    QWidget *Kafelki;
    QGridLayout *gridLayout;
    QStringList SongList;
    QStringList imgPathList;
    int imagePathIndex;
    SongWidget *tablicaPiosenek[50];

    QPushButton *pageUp;
    QPushButton *pageDown;
    QPushButton *buttonPowrot;

    QTimer *tInsertCoin;
    QTimer *tImgPath;

    void ReloadSongs();

public slots:
    void songClick(SongWidget* item);

private slots:
    void hideInsertCoin();
    void slotSearchImgPath();
    void goPageUp();
    void goPageDown();
    void goBack();
    void slotValueChanged(int val);
    void slotBlinkButtons();


};

#endif // SONGS_H
