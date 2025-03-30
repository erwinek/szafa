#ifndef PLAYERMP3_H
#define PLAYERMP3_H

#include <QObject>


#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>

using namespace Phonon;

class PlayerMp3 : public QObject
{
    Q_OBJECT
public:
    explicit PlayerMp3(QObject *parent = 0);
    void playSong(QString songPath);
    void stop();
    void setVol(int vol);
private:
    MediaObject *obj;
    AudioOutput *audio;
    MediaSource src;
signals:
    
private slots:
    void SlotPhononObjStateChanged(Phonon::State, Phonon::State);
};

#endif // PLAYERMP3_H
