#include "albums.h"
#include <QListView>
#include "album.h"
#include "window.h"

Albums* Album::albumsPtr=0;

Albums::Albums(QWidget *parent) :
    QWidget(parent)
{
    QString styleLabelHeader = "QLabel { \
        font: bold 30px; \
        color: white;\
        background-image: url(gfx/Background_category.png);\
    }";

    QImage headerImg("gfx/Background_category.png");
    header = new QLabel("", this);
    header->resize(headerImg.size());
    header->move(0, 0);
    header->setStyleSheet(styleLabelHeader);
    header->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    labelDown = new QLabel(this);
    QImage labelDownImage;
    labelDownImage.load("gfx/down_interface.png");
    labelDown->setPixmap(QPixmap::fromImage(labelDownImage));
    labelDown->resize(labelDownImage.size());
    labelDown->move(0,768-labelDownImage.height());

    Album::albumsPtr = this;
    Kafelki = new QWidget(this);
    Kafelki->resize(headerImg.width(), 768 - headerImg.height() - labelDownImage.height());
    Kafelki->move(0,headerImg.height());

    gridLayout = new QGridLayout(this);
    Kafelki->setLayout(gridLayout);
    gridLayout->setColumnMinimumWidth(0,150);
    gridLayout->setColumnMinimumWidth(0,150);
    gridLayout->setColumnMinimumWidth(0,150);

    for (int i = 0;i< 12;i++) tablicaAlbumow[i]=0;

    for (int row = 0; row < 3; row ++) {
        gridLayout->setRowMinimumHeight(row,220);
    }

    sliderAlbums = new QSlider(Qt::Vertical, this);
    sliderAlbums->setMinimum(1);
    sliderAlbums->setMaximum(2);
    sliderAlbums->setSliderPosition(1);
    sliderAlbums->setInvertedAppearance(true);
    sliderAlbums->setPageStep(3);
    sliderAlbums->move(700, 90);
    sliderAlbums->resize(80, 550);

    connect(sliderAlbums, SIGNAL(valueChanged(int)),this, SLOT(slotValueChanged(int)));

    sliderAlbums->setStyleSheet(" \
    QSlider::handle:vertical {    \
        height: 80px; \
        width: 80px; \
        image: url(gfx/searching_arrow.png);\
        top: 10px;\
        bottom: 10px;\
    }   \
    QSlider::groove:vertical {\
        image: url(gfx/pasek_pod_suwak.png);\
        position: absolute; \
        left: 4px; right: 4px;\
    }\
    ");

    QString buttonStyle = " \
            background-color: rgba(10,20,30,0);";

    QImage bUpImg("gfx/up_button.png");
    pageUp = new QPushButton(this);
    pageUp->setGeometry(135, 768-bUpImg.height()-15, bUpImg.width(),bUpImg.height());
    pageUp->setIcon(QPixmap::fromImage(bUpImg));
    //pageUp->setIconSize(UpDownButtonSize);
    pageUp->setIconSize(bUpImg.size());
    pageUp->setStyleSheet(buttonStyle);
    pageUp->setFocusPolicy(Qt::NoFocus);
    connect(pageUp, SIGNAL(clicked()),this, SLOT(goPageUp()));

    pageDown = new QPushButton(this);
    QImage bDownImg("gfx/down_button.png");
    pageDown->setGeometry(395, 768-bDownImg.height()-15, bDownImg.width(),bDownImg.height());
    pageDown->setIcon(QPixmap::fromImage(bDownImg));
    //pageDown->setIconSize(UpDownButtonSize);
    pageDown->setIconSize(bDownImg.size());
    pageDown->setStyleSheet(buttonStyle);
    pageDown->setFocusPolicy(Qt::NoFocus);
    connect(pageDown, SIGNAL(clicked()),this, SLOT(goPageDown()));


    buttonPowrot = new QPushButton(this);
    QImage bPowrotImg("gfx/back_button.png");
    buttonPowrot->setGeometry(30, 768 - bPowrotImg.height() - 10, bPowrotImg.width(),bPowrotImg.height());
    buttonPowrot->setIcon(QPixmap::fromImage(bPowrotImg));
    buttonPowrot->setIconSize(bPowrotImg.size());
    buttonPowrot->setStyleSheet(buttonStyle);
    buttonPowrot->setFocusPolicy(Qt::NoFocus);
    connect(buttonPowrot, SIGNAL(clicked()),this, SLOT(goBack()));

    pageNr = 1;

    QTimer *tBlinkButtons = new QTimer(this);
    connect(tBlinkButtons, SIGNAL(timeout()), this, SLOT(slotBlinkButtons()));
    tBlinkButtons->start(400);

    this->resize(1024-230,768);
    this->move(230,0);

}


void Albums::LoadDirectory(QString path)
{
    QDir myDir(path);
    QStringList AlbumList = myDir.entryList ();

    AlbumList.removeFirst();  // pomijamy poczatek listy \. i \..
    AlbumList.removeFirst();

    listaPlyt.clear();

    for (int i=0;i<AlbumList.length();i++) {
        Plyta *ptr = new Plyta();
        ptr->artist = AlbumList.at(i);
        listaPlyt.append(*ptr);
    }
}

void Albums::ShowSongScreen(Album *pAlbum)
{
    this->hide();
    //((Window*)parentWidget())->songScreen->album = pAlbum;
    Album::albumsPtr = this;

    ((Window*)parentWidget())->songScreen->showSongs(pAlbum);
}

void Albums::ShowAlbums(QString path)
{
    LoadDirectory(path);
    albumsPath = path;
    pageNr = 1;
    int licznik = (pageNr-1) * 12 ;

    for (int i = 0; i < 12; i ++) {
        if (tablicaAlbumow[i]) delete tablicaAlbumow[i];
        tablicaAlbumow[i] = 0;
    }
    int i=0;
    for (int row = 0; row < 3; row ++) {
        for (int col = 0;col < 4; col++) {
            if (licznik < listaPlyt.length())  {
                tablicaAlbumow[i] = new Album(0, "", listaPlyt.at(licznik).artist, listaPlyt.at(licznik).title, ListaOkladek.at(licznik));
                gridLayout->addWidget(tablicaAlbumow[i], row  , col);
            }
            else {
                QWidget *pusty = new QWidget(0);
                gridLayout->addWidget(pusty, row  , col);
            }
            licznik++;
            i++;
        }
    }
    lastPageNr = (listaPlyt.length() / 12) + 1;

    this->show();
    this->raise();

    if (lastPageNr<2) {
        sliderAlbums->hide();
        pageUp->hide();
        pageDown->hide();
    }
    else {
        pageUp->show();
        pageDown->show();
        sliderAlbums->show();
        sliderAlbums->setMaximum(lastPageNr);
        sliderAlbums->setSliderPosition(pageNr);
    }

}

void Albums::ShowAlbumsList(QList<Plyta> lPlyt)
{

    listaPlyt = lPlyt;
    pageNr = 1;
    int licznik = (pageNr-1) * 12 ;

    for (int i = 0; i < 12; i ++) {
        if (tablicaAlbumow[i]) delete tablicaAlbumow[i];
        tablicaAlbumow[i] = 0;
    }
    int i=0;
    int len = listaPlyt.length();
    for (int row = 0; row < 3; row ++) {
        for (int col = 0;col < 4; col++) {
            if (licznik < len)  {
                tablicaAlbumow[i] = new Album(0, listaPlyt.at(licznik).path, listaPlyt.at(licznik).artist, listaPlyt.at(licznik).title, QImage());
            gridLayout->addWidget(tablicaAlbumow[i], row  , col);
            }
            else {
                QWidget *pusty = new QWidget(0);
                gridLayout->addWidget(pusty, row  , col);
            }
            licznik++;
            i++;
        }
    }
    lastPageNr = (len / 12) + 1;

    this->show();
    this->raise();

    if (lastPageNr<2) {
        sliderAlbums->hide();
        pageUp->hide();
        pageDown->hide();
    }
    else {
        pageUp->show();
        pageDown->show();
        sliderAlbums->show();
        sliderAlbums->setMaximum(lastPageNr);
        sliderAlbums->setSliderPosition(pageNr);
    }

}



void Albums::ShowFoundAlbums(QList<Plyta> lPlyt)
{

    listaPlyt = lPlyt;
    pageNr = 1;
    int licznik = (pageNr-1) * 12 ;

    //AlbumList = foundAlbums;

    for (int i = 0; i < 12; i ++) {
        if (tablicaAlbumow[i]) delete tablicaAlbumow[i];
        tablicaAlbumow[i] = 0;
    }

    int i=0;
    for (int row = 0; row < 3; row ++) {
        for (int col = 0;col < 4; col++) {
            if (licznik < listaPlyt.length())  {
                tablicaAlbumow[i] = new Album(0, listaPlyt.at(licznik).path, listaPlyt.at(licznik).artist, listaPlyt.at(licznik).title, QImage());
            gridLayout->addWidget(tablicaAlbumow[i], row  , col);
            }
            else {
                QWidget *pusty = new QWidget(0);
                gridLayout->addWidget(pusty, row  , col);
            }
            licznik++;
            i++;
        }
    }

    lastPageNr = (listaPlyt.length() / 12) + 1;

    this->show();
    this->raise();

    if (lastPageNr<2) {
        sliderAlbums->hide();
        pageUp->hide();
        pageDown->hide();
    }
    else {
        pageUp->show();
        pageDown->show();
        sliderAlbums->show();
        sliderAlbums->setMaximum(lastPageNr);
        sliderAlbums->setSliderPosition(pageNr);
    }


}

void Albums::ReloadAlbums()
{
    int licznik = (pageNr-1) * 12 ;

    ((Window*)parentWidget())->restartTimeNotTouched();

    for (int i = 0; i < 12; i ++) {
        if (tablicaAlbumow[i]) delete tablicaAlbumow[i];
        tablicaAlbumow[i] = 0;
    }
    int AlbumsCnt = 0;
    for (int row = 0; row < 3; row ++) {
        for (int col = 0;col < 4; col++) {
            if (licznik < listaPlyt.length()) {
                tablicaAlbumow[AlbumsCnt] = new Album(0, listaPlyt.at(licznik).path, listaPlyt.at(licznik).artist, listaPlyt.at(licznik).title, QImage());
                gridLayout->addWidget(tablicaAlbumow[AlbumsCnt], row  , col);
            }
            else {
                QWidget *pusty = new QWidget(0);
                gridLayout->addWidget(pusty, row  , col);
            }

            licznik++;
            AlbumsCnt++;
        }
    }

    if (lastPageNr<2) {
        sliderAlbums->hide();
        pageUp->hide();
        pageDown->hide();
    }
    else {
        pageUp->show();
        pageDown->show();
        sliderAlbums->show();
        sliderAlbums->setMaximum(lastPageNr);
        sliderAlbums->setSliderPosition(pageNr);
    }
}

void Albums::goPageUp()
{
    ((Window*)parentWidget())->restartTimeNotTouched();
    if(pageNr > 1)  {
        pageNr--;
        ReloadAlbums();
    }

}
void Albums::goPageDown()
{
    ((Window*)parentWidget())->restartTimeNotTouched();
    if(pageNr < lastPageNr) {
        pageNr++;
        ReloadAlbums();
    }
}
void Albums::goBack()
{
    ((Window*)parentWidget())->restartTimeNotTouched();
    this->hide();
    ((Window*)parentWidget())->homeScreen->show();
}

void Albums::slotValueChanged(int val)
{
    pageNr = val;
    ReloadAlbums();
}

void Albums::slotBlinkButtons()
{
    static bool flag=0;

    if (flag) {
        flag=0;
        QImage bUpImg("gfx/up_button.png");
        pageUp->setIcon(QPixmap::fromImage(bUpImg));

        QImage bDownImg("gfx/down_button.png");
        pageDown->setIcon(QPixmap::fromImage(bDownImg));
    }
    else {
        flag = 1;

        QImage bUpImg("gfx/up_button_2.png");
        pageUp->setIcon(QPixmap::fromImage(bUpImg));

        QImage bDownImg("gfx/down_button_2.png");
        pageDown->setIcon(QPixmap::fromImage(bDownImg));
    }
}
