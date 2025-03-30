#include "home.h"
#include "window.h"
#include "songlistwidget.h"

Home::Home(QWidget *parent) :
    QWidget(parent)
{
    loadBorderColor();

    labelUp = new QLabel(this);
    QImage labelUpImage;
    //labelUpImage.load("gfx/Background_category.png");
    labelUpImage.load("gfx/Background_queue_tittle.png");
      labelUp->setPixmap(QPixmap::fromImage(labelUpImage));
    labelUp->resize(labelUpImage.size());
    labelUp->move(230,0);

   // labelUp->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
   // labelUp->setText("TERAZ GRANE");
   // labelUp->setStyleSheet("QLabel {\
   //                        font: bold 40px; \
   //                        color: black;\
   //                        background-image: url(gfx/Background_category.png);\
   // }");

    labelDown = new QLabel(this);
    QImage labelDownImage;
    labelDownImage.load("gfx/down_interface.png");
    labelDown->setPixmap(QPixmap::fromImage(labelDownImage));
    labelDown->resize(labelDownImage.size());
    labelDown->move(230,768-labelDownImage.height());

    listKolejka  = new QListWidget(this);
    listKolejka->move(280,120);
    listKolejka->resize(700,600);
    listKolejka->show();
    listKolejka->setStyleSheet(styleListWidget);

    labelAdvertisment = new QLabel(this);
    labelAdvertisment->move(280,665);
    labelAdvertisment->resize(600,80);
    labelAdvertisment->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    labelAdvertisment->show();


    reloadAdvert();

    MP3_Kolejka = &((Window*)parentWidget())->albums->Kolejka;
    playingSong = &((Window*)parentWidget())->albums->Playing;

    CzasOdtwarzania = new QLabel("0:00", this);
    CzasOdtwarzania->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    CzasOdtwarzania->move(280+600+10, 130);
    CzasOdtwarzania->resize(80, 80);
    CzasOdtwarzania->hide();

    QString styleCzasOdtwarzania;
    styleCzasOdtwarzania = styleCzasOdtwarzania.sprintf("QLabel { \
        background-color: rgba(10,20,30,0); \
        font: bold 24px; \
        color: red;\
        border-radius: 16px; \
    }");

    CzasOdtwarzania->setStyleSheet(styleCzasOdtwarzania);

    updateQueue();


}

void Home::updateQueue()
{

    SongListWidget *albi;

    listKolejka->clear();

    if (((playingSong->title.length()>0)))
    {
        CzasOdtwarzania->show();
        albi = new SongListWidget(this, playingSong->CdPath, playingSong->artist, playingSong->title, playingSong->songLength, true);
        albi->setStyleSheet(styleItemKolejka);
        QListWidgetItem *item=new QListWidgetItem();
        item->setSizeHint(QSize(200,100));

        listKolejka->addItem(item);
        listKolejka->setItemWidget(item, albi);
    }

    if(!MP3_Kolejka->isEmpty())
    {
        QSettings *queueFile = new QSettings("/home/szafa/queue.ini", QSettings::IniFormat);
        queueFile->clear();
        queueFile->beginWriteArray("kolejka");

        for(int i=0;(i<MP3_Kolejka->length()) && (i < 4);i++)
        {
            queueFile->setArrayIndex(i);
            queueFile->setValue("artist", MP3_Kolejka->at(i).artist);
            queueFile->setValue("title", MP3_Kolejka->at(i).title);
            queueFile->setValue("path", MP3_Kolejka->at(i).path);
            queueFile->setValue("CdPath", MP3_Kolejka->at(i).CdPath);
            queueFile->setValue("songLength", MP3_Kolejka->at(i).songLength);

            albi = new SongListWidget(this, MP3_Kolejka->at(i).CdPath, MP3_Kolejka->at(i).artist, MP3_Kolejka->at(i).title, MP3_Kolejka->at(i).songLength);
            albi->setStyleSheet(styleItemKolejka);
            QListWidgetItem *item=new QListWidgetItem();
            item->setSizeHint(QSize(200,100));

            listKolejka->addItem(item);
            listKolejka->setItemWidget(item, albi);

        }
        queueFile->endArray();
    }
    else {
        QSettings *queueFile = new QSettings("/home/szafa/queue.ini", QSettings::IniFormat);
        queueFile->clear();
    }
    if (!((Window*)parentWidget())->albums->isPlaying) {
        CzasOdtwarzania->hide();
        listKolejka->clear();
    }


}

void Home::loadBorderColor()
{
    styleLabelAdvert = styleLabelAdvert.sprintf("QLabel { \
        background-color: rgba(0,0,0,0); \
        font: bold 24px; \
        color: black;\
    }");

    styleLabelAdvertFreeplay = styleLabelAdvertFreeplay.sprintf("QLabel { \
        background-color: rgba(0,0,0,0); \
        font: bold 80px; \
        color: green;\
    }");

    styleItemKolejka = styleItemKolejka.sprintf("QLabel { \
        font: 24px; \
        color: black;\
    }");


    styleListWidget = styleListWidget.sprintf(" \
        QListView {color: rgb(230, 230, 230); border-radius: 16px; font-size: 16px; background-color: rgba(10,20,30,0); }");

}

void Home::reloadAdvert()
{
    QString Reklama;
    if (((Window*)parentWidget())->setup->freePlayOnOff) {
        Reklama = "";
        //labelAdvertisment->setStyleSheet(styleLabelAdvertFreeplay);
        //labelAdvertisment->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        QImage labelDownImage;
        labelDownImage.load("gfx/freeplay.png");
        labelDown->setPixmap(QPixmap::fromImage(labelDownImage));
    }
    else {
        Reklama = " 1zł - 1 Utwór \n 2zł - 3 Utwory \n 5zł - 8 Utworów";
        //Reklama = " 1zł - 1 Utwór     2zł - 3 Utwory     5zł - 8 Utworów";
        labelAdvertisment->setStyleSheet(styleLabelAdvert);
        labelAdvertisment->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        QImage labelDownImage;
        labelDownImage.load("gfx/down_interface.png");
        labelDown->setPixmap(QPixmap::fromImage(labelDownImage));
    }
    labelAdvertisment->setText(Reklama);
}
