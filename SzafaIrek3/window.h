/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <phonon>
#include <qfiledialog.h>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
//#include "helper.h"
#include "folder.h"
#include "cd.h"
#include "szukaj.h"
#include "setup.h"
#include "image.h"
#include "comport.h"
#include "credit.h"
#include "home.h"
#include "albums.h"
#include "songs.h"
#include "playsong.h"
#include "menu.h"
#include "toplist.h"
#include "slideshow.h"
#include "volsetup.h"
#include "menusetup.h"
#include "setupcounter.h"
#include "insertcoin.h"
#include "playermp3.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QWidget;
QT_END_NAMESPACE

extern QString PathMp3;

using namespace Phonon;

extern cd *plytka;
extern Szukaj *oknoSzukaj;
//------- Global Settings ----------------
extern QString MP3_PATH;
extern QString ZDJECIA_PATH;
extern QString DEFAULT_SETUP_PASS;
//----------------------------------------

enum state {
    HOME,
    ALBUMS,
    SONGS,
    PLAY,
    SLIDESHOW,
    SETUP
};

//! [0]
class Window : public QWidget
{
    Q_OBJECT
signals:
   void mySignal(int myParameter);

public:
   void setGameState(state newState);
   void RecoverSettings(void);
   state gameState;

   static QString SoftwareVersion;
   QSettings *setupPath;

   int volEnable;

    int timeoutNotTouched;

    SetupCounter *setupCounterScreen;
    Toplist *top20;
    Menu *menu;
    PlaySong *playScreen;
    Songs *songScreen;
    Albums *albumsScreen;
    Home *homeScreen;
    Szukaj *oknoSzukaj;
    Slideshow *slideshowScreen;
    InsertCoin *insertCoinScreen;
    PlayerMp3 *playerMp3Obj;
    QLabel *ipSystem;
    QLabel *licenceScreen;
    //bool enablePlayButton;
    ComPort *serialPort;
    int screenWidth;
    int screenHeight;
    Image *tlo;
    Window();
    folder *albums;
    QString gfxPath;
    QSettings *settings;
    Setup *setup;
    VolSetup *VolSetupScreen;
    MenuSetup *MenuSetupScreen;
    Stats *statScreen;
    QTimer *timerAddQueueDelay;
    QTimer *tNotTouched;
    void restartTimeNotTouched();
    Credit *creditWidget;
    QPushButton *buttonWszystkie;
    QPushButton *buttonMpolska;
    QPushButton *buttonMbiesiadna;
    QPushButton *buttonMzagraniczna;
    QPushButton *buttonKaraoke;
    QPushButton *buttonSkladanki;
    QPushButton *buttonNowosci;
    int slideshowCounter;
    void mousePressEvent(QMouseEvent *);

    void hideAll();
protected:    
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent * event);

public slots:
    void reloadPictures();
    void showSlideshow();
    void enterSetup();
    void enterVolumeSetup();
    void enterMenuSetup();
    void enterStat();
    void enterSetupCounter();
    void slotNotTouched();

private slots:    
    void szukanie();

};
//! [0]

#endif






