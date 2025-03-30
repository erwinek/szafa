#include <QtGui>
#include "folder.h"
#include "window.h"
#include "scroll.h"


#include <phonon>
#include <qfiledialog.h>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>

#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>
#include <QUrl>
void RecurseDirectory(const QString& sDir);


folder::folder(QWidget *parent) : QWidget (parent)
{
    AlbumSelector = 0;
    SongSelector = 0;
    PathMp3 = "/home/szafa/mp3/";

    Kredyt = 3;
    //  PHONON
   using namespace Phonon;

   obj = new Phonon::MediaObject(this);
   //obj->setCurrentSource( src );

    //listWidget = new QListWidget(this);



   AudioOutput *audio=new AudioOutput(Phonon::MusicCategory, this);
   Phonon::createPath( obj, audio );
//   obj->play();


   QUrl url2 = QUrl( QLatin1String("/home/szafa/mp3/ABBA - Album1/1.mp3") );

   MediaSource src2( url2 );
   MediaObject *obj2 = new MediaObject(this);
   obj2->setCurrentSource( src2 );


   AudioOutput *audio2=new AudioOutput(Phonon::MusicCategory, this);
   Phonon::createPath( obj2, audio2 );
//   obj2->play();
   audio2->setVolume(0.2);
    obj->setTickInterval(1000);
   // obj->setPrefinishMark(3000);

    connect(obj, SIGNAL(aboutToFinish()), this, SLOT(PlayFinish()));


    QTimer *Tokladka = new QTimer(this);
    connect(Tokladka, SIGNAL(timeout()), this, SLOT(TimerOkladkaTimeout()));
    Tokladka->setInterval(5000);
    Tokladka->start();
    TimerOkladka = Tokladka;


    //-- kredyt
    labelCredit = new QLabel(this);
    labelCredit->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelCredit->setText(QString::number(Kredyt));
    labelCredit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    labelCredit->move(900,20);
    labelCredit->resize(100,100);

    labelCredit->show();
    labelCredit->setStyleSheet("QLabel { \
                                            background-color: rgba(10,20,30,150); \
                                            font: bold 80px; \
                                            color: red;\
                                            border-radius: 6px; \
                                    }");



      labelTerazGrany = new QLabel(this);
         labelTerazGrany->setFrameStyle(QFrame::Panel | QFrame::Sunken);
         labelTerazGrany->setText("Wrzuć Monete");
      //labelTerazGrany->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        labelTerazGrany->move(460,20);
       labelTerazGrany->resize(420,50);
       labelTerazGrany->scroll(-200,0);
               labelTerazGrany->show();
        labelTerazGrany->setStyleSheet("QLabel { \
                                        background-color: rgba(10,20,30,150); \
                                        font: bold 24px; \
                                        color: white;\
                                          border-radius: 6px; \
                                       }");


    labelKolejka = new QLabel(this);
    labelKolejka->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelKolejka->setText(" pierwszy \n drugi \n trzeci \n czwarty \n piaty");
    labelKolejka->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    labelKolejka->move(460,80);
    labelKolejka->resize(420,200);
    labelKolejka->show();
    labelKolejka->setStyleSheet("QLabel { \
                                        background-color: rgba(10,20,30,150); \
                                        font: 24px; \
                                        color: white;\
                                        border-radius: 6px; \
                                        }");


    scrollTerazGrany = new ScrollText(this);
    QFont fontScroll("Times", 30, QFont::Bold);

     scrollTerazGrany->resize(420, 50);
     scrollTerazGrany->move(460, 20);
     scrollTerazGrany->setFont (fontScroll);
      scrollTerazGrany->setText("");
     //scrollTerazGrany->setGeometry(460,20,420,50);

      listAlbum = new QListWidget(this);
      listAlbum->setGeometry( 180, 360, 390, 380 );
      listAlbum->setStyleSheet("QScrollBar:vertical {width: 50px;} \
                                      QScrollBar:vertical:up-arrow { width: 50px;  height: 50px;  background-color: rgba(1,2,3,4);  } \
                                       QListWidget:item:selected { background-color:rgba(100,0,200,200); } \
                                      QListView {color: rgb(230, 230, 230); font-size: 20px; background-color: rgba(10,20,30,150); border-style: none} QListView::item:selected {background-image: url(:/ui_resources/elements-preset_select/highlight_bar_270x30-black_bg.bmp)}");
     listAlbum->raise();
      listAlbum->show();
listAlbum->setSortingEnabled(true);
     listAlbum->setWrapping(0);



for (int i=0;i<10;i++)
{
    listAlbum->addItem("test");
}


    QDir myDir(PathMp3);
   AlbumList = myDir.entryList ();

   AlbumList.removeFirst();  // pomijamy poczatek listy \. i \..
  AlbumList.removeFirst();

  QString SelectedPath = PathMp3 + AlbumList[AlbumSelector];
  QString temp;
  listAlbum->clear();
  int i;
  for (i=0;i<AlbumList.size();i++)
  {
     listAlbum->addItem(AlbumList[i]);
  }
listAlbum->setCurrentRow(0);
{
    listSong = new QListWidget(this);
    listSong->setGeometry( 600, 360, 390, 380 );
    listSong->setStyleSheet("QScrollBar:vertical {width: 50px;} \
                                    QScrollBar:vertical:up-arrow { width: 50px;  height: 50px;  background-color: rgba(1,2,3,4);  } \
                                     QListWidget:item:selected { background-color:rgba(100,0,200,200); } \
                                    QListView {color: rgb(230, 230, 230); font-size: 20px; background-color: rgba(10,20,30,150); border-style: none} QListView::item:selected {background-image: url(:/ui_resources/elements-preset_select/highlight_bar_270x30-black_bg.bmp)}");
   listSong->raise();
    listSong->show();
listSong->setCurrentRow(0);
//listSong->setSortingEnabled(true);
   //listSong->setWrapping(0);

}
                                               QDir SelectedDir(SelectedPath);
                                               SongList = SelectedDir.entryList ();
                                               SongList.removeFirst();  // pomijamy poczatek listy \. i \..
                                               SongList.removeFirst();

                                               listSong->clear();

                                               for (int i=0;i<SongList.size();i++)
                                               {
                                                   temp = SongList[i];
                                                   temp.truncate(temp.length()-4); //odcinamy rozszerzenie mp3
                                                   listSong->addItem(temp);
                                               }

connect(listAlbum, SIGNAL(itemSelectionChanged()), this, SLOT(UpdateSong()));


}

void folder::paintEvent(QPaintEvent*) {

        QPainter painter(this);
        QPen pen(Qt::black, 6, Qt::SolidLine);
        QPen pen_blue(Qt::blue, 2, Qt::SolidLine);
        QPen pen_txt(Qt::darkBlue, 6, Qt::SolidLine);

        labelCredit->setText(QString::number(Kredyt));

        QFont serifFont("Times", 16);

        QFont QueueFont("Times", 20);

        QString temp;



             painter.setPen(pen_blue);
             QRect rect( 180, 380, 360, 350 ); //QRect::QRect ( int x, int y, int width, int height )
             //painter.drawRect(rect);
             QPixmap pix( 1, 1 );
             pix.fill( Qt::transparent );
             painter.drawPixmap( rect, pix );
             //painter.setOpacity( 0.5 );


             painter.setPen(pen_txt);
             painter.setFont(serifFont);

             QDir myDir(PathMp3);
             AlbumList = myDir.entryList ();

             AlbumList.removeFirst();  // pomijamy poczatek listy \. i \..
             AlbumList.removeFirst();


             AlbumSelector = listAlbum->currentRow();
             QString SelectedPath = PathMp3 + AlbumList[AlbumSelector];







        painter.setPen(pen_blue);
        QRect rect2( 600, 380, 360, 350 ); //QRect::QRect ( int x, int y, int width, int height )
        //painter.drawRect(rect2);
        //pix.fill( Qt::transparent );
//        painter.drawPixmap( rect2, pix );
//        painter.setOpacity( 0.5 );

//        painter.setOpacity( 1 );


//        painter.setPen(pen_txt);
//        painter.setFont(serifFont);

        QDir SelectedDir(SelectedPath);
        SongList = SelectedDir.entryList ();
        SongList.removeFirst();  // pomijamy poczatek listy \. i \..
        SongList.removeFirst();

        //listSong->clear();

        for (int i=0;i<SongList.size();i++)
        {
            temp = SongList[i];
            temp.truncate(temp.length()-4); //odcinamy rozszerzenie mp3
            //listSong->addItem(temp);
        }


        //Teraz Grany
        if(obj->state()==PlayingState)
        {
        labelTerazGrany->setText(Playing.title);
        //scrollTerazGrany->setText(Playing.title + "                  ");
        }
        else labelTerazGrany->setText("Wrzuć Monete");



        //Kolejka
        QString TextKolejka="";
        if(!Kolejka.isEmpty())
        {
            for(int i=0;i<Kolejka.length();i++)
            {
                TextKolejka.append(Kolejka[i].title + "\n");
                if (i>=7) break;
            }
        }

        labelKolejka->setText(TextKolejka);




        //plytka->NewOkladka(SelectedPath+"/"+"okladka.jpg");




    painter.end();

}

void folder::MuzykaWszystkie()
{

    AlbumSelector=0;
    PathMp3 = "/home/szafa/mp3/";


    //wyswietlenie okladki i restart timera
    plytka->cd_okladka = 0; //wyswietl okladke
    //QTimer::singleShot(5000, this, SLOT(TimerOkladkaTimeout()));

    TimerOkladka->start();
    repaint();
}


void folder::MuzykaPolska()
{

    AlbumSelector=0;
    PathMp3 = "/home/szafa/mp3/MuzykaPolska/";

    //wyswietlenie okladki i restart timera
    plytka->cd_okladka = 0; //wyswietl okladke
    //QTimer::singleShot(5000, this, SLOT(TimerOkladkaTimeout()));

    TimerOkladka->start();
    repaint();
}

void folder::MuzykaBiesiadna()
{

    AlbumSelector=0;
    PathMp3 = "/home/szafa/mp3/MuzykaBiesiadna/";

    //wyswietlenie okladki i restart timera
    plytka->cd_okladka = 0; //wyswietl okladke
    //QTimer::singleShot(5000, this, SLOT(TimerOkladkaTimeout()));

    TimerOkladka->start();
    repaint();
}

void folder::MuzykaZagraniczna()
{

    AlbumSelector=0;
    PathMp3 = "/home/szafa/mp3/MuzykaZagraniczna/";


    //wyswietlenie okladki i restart timera
    plytka->cd_okladka = 0; //wyswietl okladke
    //QTimer::singleShot(5000, this, SLOT(TimerOkladkaTimeout()));

    TimerOkladka->start();
    repaint();
}

void folder::AlbumUp()
{
    QPushButton *nadawca = (QPushButton*)sender();
    if(nadawca->text() == "UP")
    {
        if(AlbumSelector>0) AlbumSelector--;
        else AlbumSelector=AlbumList.size()-1;
    }
    else
    {
        if(AlbumSelector<AlbumList.size()-1) AlbumSelector++;
        else AlbumSelector=0;
    }
    //wyswietlenie okladki i restart timera

    plytka->cd_okladka = 0; //wyswietl okladke
    //QTimer::singleShot(5000, this, SLOT(TimerOkladkaTimeout()));

    TimerOkladka->start();
    repaint();


}


void folder::SongUpDown()
{
    QPushButton *nadawca = (QPushButton*)sender();
    if(nadawca->text() == "UP")
    {
        if(SongSelector>0) SongSelector--;
        else SongSelector=SongList.size()-1;
    }
    else
    {
        if(SongSelector<SongList.size()-1) SongSelector++;
        else SongSelector=0;
    }
    repaint();
}

void folder::Play()
{

    Song piosenka;

    piosenka.artist = AlbumList[AlbumSelector];
    piosenka.title = SongList[SongSelector];
    piosenka.title.truncate(piosenka.title.length()-4); //odcinamy rozszerzenie mp3
    piosenka.path = PathMp3 + AlbumList[AlbumSelector] + "/" + SongList[SongSelector];
    piosenka.CdPath = PathMp3 + AlbumList[AlbumSelector] + "/cd.png";

    Kolejka.enqueue(piosenka);

    repaint();
}


void folder::PlayFinish()
{

}

void folder::TimerTick()
{
    //if (!Kolejka.isEmpty() && (obj->state() != PlayingState))
    if((obj->state() != PlayingState))
    {
        if (!Kolejka.isEmpty())
        {
            Playing = Kolejka.dequeue();
            src = Playing.path;
            obj->setCurrentSource( src );
            obj->play();
            repaint();
            plytka->cd_okladka = 1; //wyswietl cd
            if(!plytka->CdImage.load(Playing.CdPath))
            {
                plytka->CdImage.load("gfx/puste_cd.png");
            }
        }
        else
        {
            //plytka->cd_okladka = 0; //wyswietl okladke
        }
    }

}


void folder::TimerOkladkaTimeout()
{
    if((obj->state() == PlayingState)) plytka->cd_okladka = 1; //wyswietl cd
}



//void test()
//{
//    QDir currentDir;
//    QString fileName="*.mp3";
//    currentDir = QDir("/home/szafa/mp3/MuzykaPolska/");
//    qt files;
//    if (fileName.isEmpty())   fileName = "*";
//    files = currentDir.entryList(QStringList(fileName),  QDir::Files | QDir::NoSymLinks);
//}





void folder::UpdateSong()
{

    QDir myDir(PathMp3);
   AlbumList = myDir.entryList ();

   AlbumList.removeFirst();  // pomijamy poczatek listy \. i \..
  AlbumList.removeFirst();


  AlbumSelector = listAlbum->currentRow();
  QString SelectedPath = PathMp3 + AlbumList[AlbumSelector];
  QString temp;

  plytka->NewOkladka(SelectedPath+"/"+"okladka.jpg");
  plytka->cd_okladka = 0; //wyswietl okladke
  TimerOkladka->start();
  repaint();

    QDir SelectedDir(SelectedPath);
    SongList = SelectedDir.entryList ();
    SongList.removeFirst();  // pomijamy poczatek listy \. i \..
    SongList.removeFirst();

    listSong->clear();

    for (int i=0;i<SongList.size();i++)
    {
        temp = SongList[i];
        temp.truncate(temp.length()-4); //odcinamy rozszerzenie mp3
        listSong->addItem(temp);
    }
}
