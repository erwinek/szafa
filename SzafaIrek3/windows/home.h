#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QtGui>
#include "folder.h"

class Home : public QWidget
{
    Q_OBJECT
public:
    explicit Home(QWidget *parent = 0);
    //QLabel *labelTerazGrany;
    //QLabel *labelKolejka;
    QListWidget *listKolejka;
    QLabel *labelAdvertisment;
    QQueue<Song> *MP3_Kolejka;
    Song *playingSong;
    void updateQueue();
    void reloadAdvert();
    QLabel *CzasOdtwarzania;
private:
    QLabel *labelUp;
    QLabel *labelDown;
    QString styleLabelAdvert;
    QString styleLabelAdvertFreeplay;
    QString styleItemKolejka;
    QString styleListWidget;
    void loadBorderColor();
signals:
    
public slots:
    
};

#endif // HOME_H
