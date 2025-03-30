#include "songs.h"
#include "window.h"
#include "songwidget.h"

Songs::Songs(QWidget *parent, Album *album) :
    QWidget(parent)
{
    pageNr = 1;
    lastPageNr = 1;

    QString styleLabelHeader = "QLabel { \
        font: bold 27px; \
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

    Kafelki = new QWidget(this);
    Kafelki->resize(headerImg.width(), 768 - headerImg.height() - labelDownImage.height());
    Kafelki->move(0,headerImg.height());

    gridLayout = new QGridLayout(this);
    Kafelki->setLayout(gridLayout);
    gridLayout->setColumnMinimumWidth(0,150);
    gridLayout->setColumnMinimumWidth(0,150);
    gridLayout->setColumnMinimumWidth(0,150);
    //gridLayout->setSizeConstraint(QLayout::SetMaximumSize);

    for (int i = 0;i< 12;i++) tablicaPiosenek[i]=0;

    for (int row = 0; row < 3; row ++) {
        gridLayout->setRowMinimumHeight(row,220);
    }
    QString buttonStyle = " \
            background-color: rgba(10,20,30,0);";


    QImage bUpImg("gfx/up_button.png");
    pageUp = new QPushButton(this);
    pageUp->setGeometry(135, 768-bUpImg.height()-15, bUpImg.width(),bUpImg.height());
    pageUp->setIcon(QPixmap::fromImage(bUpImg));
    pageUp->setIconSize(bUpImg.size());
    pageUp->setStyleSheet(buttonStyle);
    pageUp->setFocusPolicy(Qt::NoFocus);
    connect(pageUp, SIGNAL(clicked()),this, SLOT(goPageUp()));

    pageDown = new QPushButton(this);
    QImage bDownImg("gfx/down_button.png");
    pageDown->setGeometry(395, 768-bDownImg.height()-15, bDownImg.width(),bDownImg.height());
    pageDown->setIcon(QPixmap::fromImage(bDownImg));
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

    tInsertCoin = new QTimer(this);
    tInsertCoin->setSingleShot(true);
    connect(tInsertCoin, SIGNAL(timeout()), this, SLOT(hideInsertCoin()));

    tImgPath = new QTimer(this);
    connect(tImgPath, SIGNAL(timeout()), this, SLOT(slotSearchImgPath()));

    QTimer *tBlinkButtons = new QTimer(this);
    connect(tBlinkButtons, SIGNAL(timeout()), this, SLOT(slotBlinkButtons()));
    tBlinkButtons->start(400);

    this->resize(1024-230,768);
    this->move(230,0);
}

void Songs::ReloadSongs()
{
    ((Window*)parentWidget())->restartTimeNotTouched();

    for (int i=0;i<SongList.size();i++)
    {
        QString temp = SongList[i];
        temp.truncate(temp.length()-4); //odcinamy rozszerzenie mp3
    }


    for (int i = 0; i < 12; i ++) {
        if (tablicaPiosenek[i]) delete tablicaPiosenek[i];
        tablicaPiosenek[i] = 0;
    }

    int licznik = (pageNr-1) * 12 ;
    int i=0;
    for (int row = 0; row < 3; row ++) {
        for (int col = 0;col < 4; col++) {
            if (licznik < SongList.length()) {
            QString title = SongList.at(licznik);
            tablicaPiosenek[i] = new SongWidget(this, imgPathList.at(licznik), title.simplified());
            gridLayout->addWidget(tablicaPiosenek[i], row  , col);            
            }
            else {
                QWidget *pusty = new QWidget();
                gridLayout->addWidget(pusty, row  , col);
            }
            licznik++;
            i++;
        }
    }

   sliderAlbums->setMaximum(lastPageNr);
   sliderAlbums->setSliderPosition(pageNr);

}



void Songs::showSongs(Album const *album)
{
    QString picPath = album->albumPath;
    QDir SelectedDir(album->albumPath);

    SongList = SelectedDir.entryList ();
    SongList.removeFirst();  // pomijamy poczatek listy \. i \..
    SongList.removeFirst();

    QStringList flacSongList = SongList.filter(".flac", Qt::CaseInsensitive);;
    SongList = SongList.filter(".mp3", Qt::CaseInsensitive);
    SongList += flacSongList;

    if (SongList.length() == 0) {
        SongList = SelectedDir.entryList ();
        SongList = SongList.filter(".avi", Qt::CaseInsensitive);
    }

    for (int i=0;i<SongList.size();i++)
    {
        //QString temp = SongList[i];
        SongList[i].chop(4);
        //SongList = temp.chop(4); //odcinamy rozszerzenie mp3
    }

    imgPathList.clear();
    foreach (QString tempSong, SongList) {
        imgPathList.append(picPath);
    }

    if (album) {
        QString HeaderTxt = album->albumTitle + "\n" + album->albumArtist;
        header->setText(HeaderTxt);
    }

    pageNr=1;
    lastPageNr = (SongList.length() / 12);
    if (SongList.length()%12)  lastPageNr++;

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

    ReloadSongs();

    this->show();
    this->raise();

}



void Songs::showTop20(QStringList songTop20)
{
    QStringList top20Songs;
    for(int i=0;i<songTop20.length();i++) {
        QString temp = songTop20.at(i);
        temp.chop(4);
        top20Songs.append(temp);
    }
    SongList = top20Songs;

    QString HaederTxt = "TOP 20";
    header->setText(HaederTxt);

    pageNr=1;
    lastPageNr = 2;

    imgPathList = ((Window*)parentWidget())->top20->imgTop20PathList;

    ReloadSongs();

    this->show();
    //this->raise();


}

void Songs::showFoundSongs(QString title, QStringList foundSongs, QStringList imagesPaths)
{
    //QString tempSong;
    SongList = foundSongs;
    imgPathList = imagesPaths;

    header->setText("Wyniki Wyszukiwania: " + title);

    pageNr=1;
    lastPageNr = (SongList.length() / 12);
    if (SongList.length()%12)  lastPageNr++;

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

    ReloadSongs();

    this->show();
    this->raise();

    imagePathIndex = 12;
    tImgPath->start(200);

}

void Songs::songClick(SongWidget* item)
{
    qDebug() << "songClick";

    Song song;
    song.title = item->songTitle;
    qDebug() << "song.title=" << item->songTitle;
    qDebug() << "song.path=" << item->albumPath;
    QString path;
    if ((item->albumPath.length() > 3)) {
        ((Window*)parentWidget())->oknoSzukaj->SearchFile(item->albumPath, song.title, path);
    }
    else {
        ((Window*)parentWidget())->oknoSzukaj->SearchFile(MP3_PATH, song.title, path);
    }
    //SongWidget::songsPtr = this;
    song.path = path;

    if(song.path.contains(".avi")) {
        if (((Window*)parentWidget())->creditWidget->getCredit() < ((Window*)parentWidget())->creditWidget->KaraokeCredit) {
            ((Window*)parentWidget())->insertCoinScreen->raise();
            ((Window*)parentWidget())->insertCoinScreen->show();
            //jesli nie gra muza dzwiek monety
            if (!((Window*)parentWidget())->albums->isPlaying) {
            Phonon::MediaObject *music =
                 Phonon::createPlayer(Phonon::MusicCategory,
                                      Phonon::MediaSource("gfx/insert_coin_sound.mp3"));
            music->play();
            }
            tInsertCoin->start(5000); //czas wyświetlania screenu z wrzuć monetę
        }
        else {

        }
    }

    int minKredyt = 1;
    if(song.path.toLower().contains(".avi")) minKredyt=((Window*)parentWidget())->creditWidget->KaraokeCredit;

    if ( (((Window*)parentWidget())->creditWidget->getCredit() >= minKredyt) || (((Window*)parentWidget())->setup->freePlayOnOff==true) ) {

        QString temp = path;
        temp.chop(path.length() - path.lastIndexOf("/"));

        song.CdPath = temp + "/pic.png";

        temp = temp.right(temp.length() - temp.lastIndexOf("/") - 1);
        song.artist = temp.left(temp.indexOf("-"));

        this->hide();
        ((Window*)parentWidget())->menu->hide();
        ((Window*)parentWidget())->playScreen->showSong(song);
    }
    else {
        ((Window*)parentWidget())->insertCoinScreen->raise();
        ((Window*)parentWidget())->insertCoinScreen->show();
        //jesli nie gra muza dzwiek monety
        if (!((Window*)parentWidget())->albums->isPlaying) {
        Phonon::MediaObject *music =
             Phonon::createPlayer(Phonon::MusicCategory,
                                  Phonon::MediaSource("gfx/insert_coin_sound.mp3"));
        music->play();
        }
        tInsertCoin->start(5000); //czas wyświetlania screenu z wrzuć monetę

    }
}

void Songs::hideInsertCoin()
{
    ((Window*)parentWidget())->insertCoinScreen->hide();
    this->show();
}

void Songs::slotSearchImgPath()
{

}


void Songs::goPageUp()
{
    if(pageNr > 1)  {
        pageNr--;

        ReloadSongs();
    }

}
void Songs::goPageDown()
{
    if(pageNr < lastPageNr) {
        pageNr++;

        ReloadSongs();
    }
}
void Songs::goBack()
{
    this->hide();
    ((Window*)parentWidget())->albumsScreen->raise();
    ((Window*)parentWidget())->creditWidget->raise();
    ((Window*)parentWidget())->albumsScreen->show();
    ((Window*)parentWidget())->creditWidget->raise();
    ((Window*)parentWidget())->creditWidget->show();
}

void Songs::slotValueChanged(int val)
{
    pageNr = val;
    ReloadSongs();
}

void Songs::slotBlinkButtons()
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
