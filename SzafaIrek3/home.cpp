#include "home.h"
#include "window.h"


Home::Home(QWidget *parent) :
    QWidget(parent)
{
    loadBorderColor();

    labelUp = new QLabel(this);
    QImage labelUpImage;
    labelUpImage.load("gfx/Background_queue_tittle.png");
    labelUp->setPixmap(QPixmap::fromImage(labelUpImage));
    labelUp->resize(labelUpImage.size());
    labelUp->move(230,0);

    labelDown = new QLabel(this);
    QImage labelDownImage;
    labelDownImage.load("gfx/down_interface.png");
    labelDown->setPixmap(QPixmap::fromImage(labelDownImage));
    labelDown->resize(labelDownImage.size());
    labelDown->move(230,768-labelDownImage.height());

    terazGrany = new SongListWidget(this, "", "", "", "", true);
    terazGrany->move(250, 120);
	terazGrany->setStyleSheet(styleItemKolejka);

    listKolejka  = new QListWidget(this);
    listKolejka->move(250,220);
    listKolejka->resize(730,400);
    listKolejka->show();
    listKolejka->setStyleSheet(styleListWidget);

    labelAdvertisment = new QLabel(this);
    labelAdvertisment->move(280,665);
    labelAdvertisment->resize(600,90);
    labelAdvertisment->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    labelAdvertisment->show();

    labelInfo = new QLabel(this);
    labelInfo->move(520,730);
    labelInfo->resize(400,30);
    labelInfo->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    labelInfo->show();

    reloadAdvert();

    MP3_Kolejka = &((Window*)parentWidget())->albums->Kolejka;
    playingSong = &((Window*)parentWidget())->albums->Playing;

    CzasOdtwarzania = new QLabel("0:00", this);
    CzasOdtwarzania->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    CzasOdtwarzania->move(250+600+10, 130);
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

    listKolejka->clear();

    if (((playingSong->title.length()>0)))
    {
        if (terazGrany) delete terazGrany;
        terazGrany = new SongListWidget(this, playingSong->CdPath, playingSong->artist, playingSong->title, playingSong->songLength, true);
        terazGrany->move(250, 120);
        terazGrany->setStyleSheet(styleItemKolejka);
        terazGrany->show();
        CzasOdtwarzania->raise();
        CzasOdtwarzania->show();
    }

    if(!MP3_Kolejka->isEmpty())
    {
        SongListWidget *albi;
        QSettings *queueFile = new QSettings("queue.ini", QSettings::IniFormat);
        queueFile->clear();
        queueFile->beginWriteArray("kolejka");
        queueFile->sync();

        for(int i=0;(i<MP3_Kolejka->length());i++)
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
        QSettings *queueFile = new QSettings("queue.ini", QSettings::IniFormat);
        queueFile->clear();

    }
    if (!((Window*)parentWidget())->albums->isPlaying) {
        CzasOdtwarzania->hide();
        listKolejka->clear();
        terazGrany->hide();
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

    styleLabelInfo = styleLabelInfo.sprintf("QLabel { \
        background-color: rgba(0,0,0,0); \
        font: 20px; \
        color: white;\
    }");

    styleItemKolejka = styleItemKolejka.sprintf("QLabel { \
        font: 24px; \
        color: black;\
    }");


    styleListWidget = styleListWidget.sprintf(" \
        QListView {color: rgb(230, 230, 230); border-radius: 16px; font-size: 16px; background-color: rgba(10,20,30,0); } \
        QScrollBar:vertical { border: none; background-color: rgba(10,20,30,0);; width: 30px;  } \
                                              QScrollBar::handle:vertical,\
                                              QScrollBar::handle:pressed{\
                                                  border-image: url(gfx/slider.png);\
                                                  max-height: 30px; \
                                              } \
                                              ");




}

void Home::reloadAdvert()
{
    QString Reklama;
    if (((Window*)parentWidget())->setup->freePlayOnOff) {
        Reklama = "";
        QImage labelDownImage;
        labelDownImage.load("gfx/freeplay.png");
        labelDown->setPixmap(QPixmap::fromImage(labelDownImage));
    }
    else {
        Reklama = ((Window*)parentWidget())->settings->value("reklama").toString();


        labelAdvertisment->setStyleSheet(styleLabelAdvert);
        labelAdvertisment->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        QImage labelDownImage;
        labelDownImage.load("gfx/down_interface.png");
        labelDown->setPixmap(QPixmap::fromImage(labelDownImage));
    }

    QString tekstInfo = ((Window*)parentWidget())->settings->value("TekstInfo").toString();
    if ((tekstInfo.length() < 1)) {
        tekstInfo = " ";
        ((Window*)parentWidget())->settings->setValue("TekstInfo", tekstInfo);
    }

    labelInfo->setStyleSheet(styleLabelInfo);
    labelInfo->setText(tekstInfo);
    labelAdvertisment->setText(Reklama);
}
