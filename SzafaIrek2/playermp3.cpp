#include "playermp3.h"

PlayerMp3::PlayerMp3(QObject *parent) :
    QObject(parent)
{
    qDebug () << "PlayerMp3::PlayerMp3";
    obj = new Phonon::MediaObject(this);
    audio=new AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(obj,  audio );
    connect(obj, SIGNAL(stateChanged(Phonon::State, Phonon::State)), this, SLOT(SlotPhononObjStateChanged(Phonon::State, Phonon::State)));
}

void PlayerMp3::stop()
{
    obj->stop();
}

void PlayerMp3::playSong(QString songPath)
{
    src = songPath;
    obj->setCurrentSource( src );

    obj->play();
    qDebug() << "state=" << obj->state();
    qDebug() << "gra";
}


void PlayerMp3::SlotPhononObjStateChanged(Phonon::State newState, Phonon::State oldState)
{
    qDebug() << "obj1SlotStateChanged1";
    qDebug() << "OldState=" << QString::number(oldState);
    qDebug() << "NewState=" << QString::number(newState);
    qDebug() << obj->errorString();

}

void PlayerMp3::setVol(int Volume)
{
    qreal volume = Volume;
    volume /= 30;
    audio->setVolume(volume);
    qDebug() << "demoVol=" << volume;
}

bool PlayerMp3::isPlaying()
{
    return ( obj->state() == PlayingState );
}
