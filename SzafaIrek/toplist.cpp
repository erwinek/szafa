#include "window.h"
#include "toplist.h"


Toplist::Toplist(QStringList *songList, QWidget *parent) :
    QWidget(parent)
{
    strListTop20 = new QStringList();

    for(int i=0;i<20;i++) {
        if (i >= songList->length()) break;
        strListTop20->append(songList->at(i));
    }

    imgTop20PathList.clear();
    foreach (QString tempSong, *strListTop20) {
        QString picPath;
        ((Window*)parentWidget())->oknoSzukaj->SearchFile(MP3_PATH, tempSong, picPath);
        imgTop20PathList.append(picPath.left(picPath.lastIndexOf("/")) + "/");
    }
}

void Toplist::show()
{
    ((Window*)parentWidget())->restartTimeNotTouched();
    ((Window*)parentWidget())->playScreen->hide();
    ((Window*)parentWidget())->slideshowScreen->resetCounter();
    ((Window*)parentWidget())->homeScreen->hide();
    ((Window*)parentWidget())->albumsScreen->hide();
    ((Window*)parentWidget())->creditWidget->raise();
	((Window*)parentWidget())->creditWidget->show();
    ((Window*)parentWidget())->songScreen->showTop20(*strListTop20);	
}

QString Toplist::GetTopSongPath()
{
    return imgTop20PathList[0] + strListTop20->at(0);
}
