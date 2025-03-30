#ifndef FOLDER_H
#define FOLDER_H

#include <qwidget.h>
#include <qlistwidget.h>
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
#include <QQueue>
#include <QLabel>
#include "scroll.h"



using namespace Phonon;

class Song
{
public:
    QString artist;
    QString title;
    QString path;
    QString CdPath;

};


class folder : public QWidget
{
    Q_OBJECT

public:
    folder(QWidget *parent);
    QString CurentPath;
    int AlbumSelector;
    int SongSelector;
    QQueue<Song> Kolejka;
    Song Playing;
    int Kredyt;
    QLabel *labelCredit;
    QListWidget *listAlbum;
    QListWidget *listSong;

private:

    QLabel *labelTerazGrany;
    QLabel *labelKolejka;
    ScrollText *scrollTerazGrany;
    void PrintAlbums(QRect *rect);
    void PrintSongs(QRect *rect);    
    void RecurseDirectory(const QString& sDir);
    QString PathMp3;
    QStringList AlbumList;
    QStringList SongList;
    QStringList Queque;


    MediaSource src;
    MediaObject *obj;
    QTimer *TimerOkladka;
protected:
    void paintEvent(QPaintEvent*);

public slots:        
    void UpdateSong();
    void MuzykaWszystkie();
    void MuzykaPolska();
    void MuzykaBiesiadna();
    void MuzykaZagraniczna();
    void AlbumUp();
    void SongUpDown();
    void Play();
    void TimerTick();
    void TimerOkladkaTimeout();
private slots:
    void PlayFinish();


};


#endif // FOLDER_H
