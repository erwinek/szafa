#include "setup.h"
#include "window.h"
#include "stats.h"

typedef bool (*sortingProcedure)(const QPair<QString,int>& , const QPair<QString,int>& );

bool sortingByPlayNumber1(const QPair<QString,int>& e1, const QPair<QString,int>& e2) { // sorting by QHash Value
    if (e1.second < e2.second) return false;
    return true;
}
bool sortingByPlayNumber2(const QPair<QString,int>& e1, const QPair<QString,int>& e2) { // sorting by QHash Value
    if (e1.second > e2.second) return false;
    return true;
}

bool sortingByName1(const QPair<QString,int>& e1, const QPair<QString,int>& e2) {
    if (e1.first < e2.first) return false;
    return true;
}
bool sortingByName2(const QPair<QString,int>& e1, const QPair<QString,int>& e2) {
    if (e1.first > e2.first) return false;
    return true;
}

sortingProcedure sorting=sortingByPlayNumber1;

Stats::Stats(QWidget *parent) :
    QWidget(parent)
{    
    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->resize(1024,768);
    backgroundLabel->move(0,0);
    backgroundLabel->setPixmap(QPixmap("gfx/3/background.jpg"));

    songStatsFile = new QSettings("/home/szafa/stats.ini", QSettings::IniFormat);
    songHistoryFile = new QSettings("/home/szafa/history.ini", QSettings::IniFormat);
    QPushButton *buttonShowSongs= new QPushButton("SONG", this);
    buttonShowSongs->resize(100,50); //width, height.
    buttonShowSongs->move(200, 768-50);
    buttonShowSongs->setStyleSheet("");
    connect(buttonShowSongs, SIGNAL(clicked()),this, SLOT(showSongs()));

    QPushButton *buttonShowAlbums= new QPushButton("ALBUM", this);
    buttonShowAlbums->resize(100,50); //width, height.
    buttonShowAlbums->move(300, 768-50);
    buttonShowAlbums->setStyleSheet("");
    connect(buttonShowAlbums, SIGNAL(clicked()),this, SLOT(showAlbums()));

    QPushButton *buttonShowNotPlayed= new QPushButton("NIE GRANE", this);
    buttonShowNotPlayed->resize(100,50); //width, height.
    buttonShowNotPlayed->move(400, 768-50);
    buttonShowNotPlayed->setStyleSheet("");
    connect(buttonShowNotPlayed, SIGNAL(clicked()),this, SLOT(showNotPlayed()));

    QPushButton *buttonShowHistory= new QPushButton("Historia", this);
    buttonShowHistory->resize(100,50); //width, height.
    buttonShowHistory->move(500, 768-50);
    buttonShowHistory->setStyleSheet("");
    connect(buttonShowHistory, SIGNAL(clicked()),this, SLOT(showHistory()));


    QPushButton *buttonExit= new QPushButton("EXIT", this);
    buttonExit->resize(100,50); //width, height.
    buttonExit->move(600, 768-50);
    buttonExit->setStyleSheet("");
    connect(buttonExit, SIGNAL(clicked()),this, SLOT(exit()));


    QPushButton *buttonSortByName= new QPushButton("Sortuj według Nazwy", this);
    buttonSortByName->resize(300,30); //width, height.
    buttonSortByName->move(0, 0);
    buttonSortByName->setStyleSheet("");
    connect(buttonSortByName, SIGNAL(clicked()),this, SLOT(sortByName()));

    QPushButton *buttonSortByPlay= new QPushButton("Sortuj według Odtwarzania", this);
    buttonSortByPlay->resize(300,30); //width, height.
    buttonSortByPlay->move(300, 0);
    buttonSortByPlay->setStyleSheet("");
    connect(buttonSortByPlay, SIGNAL(clicked()),this, SLOT(sortByPlay()));

    listHistory = new QListWidget(this);
    listHistory->setGeometry(0,30,1024,768-100);
    listHistory->hide();
    listHistory->setWrapping(0);
    listHistory->setSortingEnabled(false);
    listHistory->setStyleSheet(" \
                    QScrollBar:vertical {width: 30px;} \
                    QScrollBar:vertical:up-arrow { width: 30px;  height: 30px;  background-color: rgba(1,2,3,4);  } \
                    QListWidget:item:selected {color: black; background-color: #ff0000; } \
                    QListView {color: rgb(230, 230, 230); border-radius: 6px; font-size: 16px; background-color: rgba(10,20,30,255); border: 3px solid #ff0000;}");


    listAlbumsStat = new QListWidget(this);
    listAlbumsStat->setGeometry(0,30,1024,768-100);
    listAlbumsStat->hide();
    listAlbumsStat->setWrapping(0);
    listAlbumsStat->setSortingEnabled(false);
    listAlbumsStat->setStyleSheet(" \
                    QScrollBar:vertical {width: 30px;} \
                    QScrollBar:vertical:up-arrow { width: 30px;  height: 30px;  background-color: rgba(1,2,3,4);  } \
                    QListWidget:item:selected {color: black; background-color: #ff0000; } \
                    QListView {color: rgb(230, 230, 230); border-radius: 6px; font-size: 16px; background-color: rgba(10,20,30,255); border: 3px solid #ff0000;}");

    listSongStat = new QListWidget(this);
    listSongStat->setGeometry(0,30,1024,768-100);
    listSongStat->show();
    //listWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    listSongStat->setWrapping(0);
    listSongStat->setSortingEnabled(false);
    listSongStat->setStyleSheet(" \
                    QScrollBar:vertical {width: 30px;} \
                    QScrollBar:vertical:up-arrow { width: 30px;  height: 30px;  background-color: rgba(1,2,3,4);  } \
                    QListWidget:item:selected {color: black; background-color: #ff0000; } \
                    QListView {color: rgb(230, 230, 230); border-radius: 6px; font-size: 16px; background-color: rgba(10,20,30,255); border: 3px solid #ff0000;}");

    listNotPlayed = new QListWidget(this);
    listNotPlayed->setGeometry(0,30,1024,768-100);
    listNotPlayed->hide();
    listNotPlayed->setWrapping(0);
    listNotPlayed->setSortingEnabled(false);
    listNotPlayed->setStyleSheet(" \
                    QScrollBar:vertical {width: 30px;} \
                    QScrollBar:vertical:up-arrow { width: 30px;  height: 30px;  background-color: rgba(1,2,3,4);  } \
                    QListWidget:item:selected {color: black; background-color: #ff0000; } \
                    QListView {color: rgb(230, 230, 230); border-radius: 6px; font-size: 16px; background-color: rgba(10,20,30,255); border: 3px solid #ff0000;}");

    //przepisanie wszystkich utworow z setupu do
    QStringList utworyGrane = songStatsFile->allKeys();

    //sortowanie
    QList<QPair<QString,int> > items;    
    QList<QPair<QString,int> > playedAlbums;
    QPair<QString,int> pair;
    QPair<QString,int> albumPair;

    QString title;
    QString albumName;
    QString albumPath;

    stringListAlbumsPlayed = new QStringList();

    foreach (title, utworyGrane) {
        pair.first = title;
        pair.second = songStatsFile->value(title).toInt();
        items.append(pair);

        SearchFile(MP3_PATH, title, albumPath);
        albumName = albumPath.left(albumPath.lastIndexOf("/"));
        albumName = albumName.right(albumName.length() - albumName.lastIndexOf("/") -1);
        bool albumListed = 0;
        for (int cnt = 0; cnt < playedAlbums.length(); cnt++) {
            if(playedAlbums[cnt].first==albumName) {
                playedAlbums[cnt].second += pair.second;
                albumListed = 1;
                break;
            }
        }
        if(!albumListed) {
            albumPair.first =  albumName;
            albumPair.second = pair.second;
            playedAlbums.append(albumPair);
            stringListAlbumsPlayed->append(albumName);
        }

    }

    foreach( pair, playedAlbums )
    {

       QListWidgetItem *item = new QListWidgetItem();
       QWidget *widget = new QWidget();

       int iPlayedCount = pair.second;
       QString val;
       val.setNum(iPlayedCount, 10);
       QLabel *playedCount = new QLabel(val, widget);
       playedCount->setStyleSheet("QLabel { color: white;font: 20px;}");
       listAlbumsStat->addItem(item);

       QLabel *label = new QLabel(pair.first, widget);
       label->setStyleSheet("QLabel { color: white;font: 20px;}");
       QHBoxLayout *layout= new QHBoxLayout();
       layout->setContentsMargins(0,0,0,0);
       layout->addWidget(label);
       layout->addWidget(playedCount);
       widget->setLayout(layout);
       item->setSizeHint(widget->minimumSizeHint());
       listAlbumsStat->setItemWidget(item, widget);

   }


     qSort(items.begin(), items.end(), sorting);

     strListSongsStat = new QStringList();

     foreach( pair, items )
     {

        QListWidgetItem *item = new QListWidgetItem();
        QWidget *widget = new QWidget();

        int iPlayedCount = pair.second;
        QString val;
        val.setNum(iPlayedCount, 10);
        QLabel *playedCount = new QLabel(val, widget);
        playedCount->setStyleSheet("QLabel { color: white;font: 20px;}");
        listSongStat->addItem(item);

        strListSongsStat->append(pair.first);

        QLabel *label = new QLabel(pair.first, widget);
        label->setStyleSheet("QLabel { color: white;font: 20px;}");
        QHBoxLayout *layout= new QHBoxLayout();
        layout->setContentsMargins(0,0,0,0);
        layout->addWidget(label);
        layout->addWidget(playedCount);
        widget->setLayout(layout);
        item->setSizeHint(widget->minimumSizeHint());
        listSongStat->setItemWidget(item, widget);

    }
     fillHistoryList();
     fillNotPlayedList();

}

void Stats::SaveSongHistory(QString songTitle)
{
    QDateTime now = QDateTime::currentDateTime();
    songHistoryFile->setValue(now.toString("yyyy.MM.dd_hh.mm.ss.zzz"),songTitle);
}

void Stats::incrSongStats(QString songTitle)
{
    int played = songStatsFile->value(songTitle).toInt();
    played++;
    songStatsFile->setValue(songTitle, played);
}


void Stats::resetStats(QSettings *settings)
{

    settings->remove("");
    songStatsFile->remove("");

}

void Stats::showSongs()
{
    listSongStat->show();
    listAlbumsStat->hide();    
    listNotPlayed->hide();
}

void Stats::showAlbums()
{
    listAlbumsStat->show();
    listSongStat->hide();
    listNotPlayed->hide();
}

void Stats::showNotPlayed()
{
    listNotPlayed->show();
    listAlbumsStat->hide();
    listSongStat->hide();

}

void Stats::showHistory()
{
    fillHistoryList();
    listHistory->show();
    listNotPlayed->hide();
    listAlbumsStat->hide();
    listSongStat->hide();

}

void Stats::exit()
{
    this->hide();
}

bool Stats::SearchFile(const QString& sDir, QString fileName, QString &wynik)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QDir dir(sDir);
    QFileInfoList list = dir.entryInfoList();
    bool found = 0;
    for (int iList=0;iList<list.count();iList++)
    {
        QFileInfo info = list[iList];

        QString sFilePath = info.filePath();
        if (info.isDir())
        {
            // recursive
            if (info.fileName()!=".." && info.fileName()!=".")
            {
                found=SearchFile(sFilePath, fileName, wynik);
            }
        }
        else
        {
            // Do something with the file here

            if (info.fileName().contains(fileName))
            {
                 wynik=info.filePath();
                 found = 1;
                 return found;
            }
        }
    }
    return found;
}


void Stats::sortByName()
{
    if(sorting==sortingByName1)  {
        sorting=sortingByName2;
    }
    else {
        sorting=sortingByName1;
    }
    fillSongList();
}
void Stats::sortByPlay()
{
    if(sorting==sortingByPlayNumber1) {
        sorting=sortingByPlayNumber2;
    }
    else sorting=sortingByPlayNumber1;

    fillSongList();
}

void Stats::fillSongList()
{

    //((Setup*)parentWidget())->settings.beginGroup("Stat");

    //przepisanie wszystkich utworow z setupu do
    QStringList utworyGrane = songStatsFile->allKeys();

    //sortowanie
    QList<QPair<QString,int> > items;
    QList<QPair<QString,int> > playedAlbums;
    QPair<QString,int> pair;
    QPair<QString,int> albumPair;

    QString title;
    QString albumName;
    QString albumPath;

    foreach (title, utworyGrane) {
        pair.first = title;
        pair.second = songStatsFile->value(title).toInt();
        items.append(pair);

        SearchFile(MP3_PATH, title, albumPath);
        albumName = albumPath.left(albumPath.lastIndexOf("/"));
        albumName = albumName.right(albumName.length() - albumName.lastIndexOf("/") -1);
        bool albumListed = 0;
        for (int cnt = 0; cnt < playedAlbums.length(); cnt++) {
            if(playedAlbums[cnt].first==albumName) {
                playedAlbums[cnt].second += pair.second;
                albumListed = 1;
                break;
            }
        }
        if(!albumListed) {
            albumPair.first =  albumName;
            albumPair.second = pair.second;
            playedAlbums.append(albumPair);
        }

    }

    listSongStat->clear();
    listAlbumsStat->clear();
     qSort(items.begin(), items.end(), sorting);
     qSort(playedAlbums.begin(), playedAlbums.end(), sorting);

     foreach( pair, items )
     {
        QListWidgetItem *item = new QListWidgetItem();
        QWidget *widget = new QWidget();

        int iPlayedCount = pair.second;
        QString val;
        val.setNum(iPlayedCount, 10);
        QLabel *playedCount = new QLabel(val, widget);
        playedCount->setStyleSheet("QLabel { color: white;font: 20px;}");
        listSongStat->addItem(item);

        QLabel *label = new QLabel(pair.first, widget);
        label->setStyleSheet("QLabel { color: white;font: 20px;}");
        QHBoxLayout *layout= new QHBoxLayout();
        layout->setContentsMargins(0,0,0,0);
        layout->addWidget(label);
        layout->addWidget(playedCount);
        widget->setLayout(layout);
        item->setSizeHint(widget->minimumSizeHint());
        listSongStat->setItemWidget(item, widget);
    }

     foreach( pair, playedAlbums )
     {

        QListWidgetItem *item = new QListWidgetItem();
        QWidget *widget = new QWidget();

        int iPlayedCount = pair.second;
        QString val;
        val.setNum(iPlayedCount, 10);
        QLabel *playedCount = new QLabel(val, widget);
        playedCount->setStyleSheet("QLabel { color: white;font: 20px;}");
        listAlbumsStat->addItem(item);

        QLabel *label = new QLabel(pair.first, widget);
        label->setStyleSheet("QLabel { color: white;font: 20px;}");
        QHBoxLayout *layout= new QHBoxLayout();
        layout->setContentsMargins(0,0,0,0);
        layout->addWidget(label);
        layout->addWidget(playedCount);
        widget->setLayout(layout);
        item->setSizeHint(widget->minimumSizeHint());
        listAlbumsStat->setItemWidget(item, widget);

    }

}

void Stats::fillHistoryList()
{

    QStringList playingTimeTable = songHistoryFile->allKeys();
    QString playTime;

    foreach (playTime, playingTimeTable) {
        QString temp =  playTime + "          " ;
        temp = temp + songHistoryFile->value(playTime).toString();
        listHistory->insertItem(0, temp);
    }
}

void Stats::fillNotPlayedList()
{
    bool played;

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QDir dir("/home/szafa/mp3");
    QFileInfoList list = dir.entryInfoList();

    for (int iList=0;iList<list.count();iList++)
    {
        QFileInfo info = list[iList];
        played = false;

        if (info.isDir())
        {
            if (info.fileName()!=".." && info.fileName()!=".")
            {
                if(!stringListAlbumsPlayed->contains(info.fileName())) {
                    listNotPlayed->addItem(info.fileName());
                }
//                QString albumName;
//                foreach (albumName, stringListAlbumsPlayed) {
//                    if(info.fileName()==albumName) { //was played before
//                        played = true;
//                        break;
//                    }
//                }
//                if (!played) {
//                    listNotPlayed->addItem(info.fileName());
//                }
            }
        }
    }
}
