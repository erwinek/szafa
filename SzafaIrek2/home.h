#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QtGui>
#include "folder.h"
#include "songlistwidget.h"

class Home : public QWidget
{
    Q_OBJECT
public:
    explicit Home(QWidget *parent = 0);
    QListWidget *listKolejka;
    QLabel *labelAdvertisment;
    QLabel *labelInfo;
    QQueue<Song> *MP3_Kolejka;
    Song *playingSong;
    void updateQueue();
    void reloadAdvert();
    QLabel *CzasOdtwarzania;
    SongListWidget *terazGrany;

private:
    QLabel *labelUp;
    QLabel *labelDown;
    QString styleLabelAdvert;
    QString styleLabelInfo;
    QString styleLabelAdvertFreeplay;
    QString styleItemKolejka;
    QString styleListWidget;
    QPixmap picFreeplay;
    QPixmap picDownInterface;
    void loadBorderColor();
signals:
    
public slots:
    
};

#endif // HOME_H
