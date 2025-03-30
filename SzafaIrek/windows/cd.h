#ifndef CD_H
#define CD_H

#include <QWidget>
#include <QtGui>

class cd : public QWidget
{
    Q_OBJECT
public:
    //void wyswietl();
    explicit cd(QWidget *parent = 0);
    void NewOkladka(QString path);
    bool cd_okladka;

    bool loadCdImage(QString path);
    //QPixmap CdPixmap;
private:
     QImage sourceImage;
     QImage destinationImage;
    QImage CdImage;
    QImage resultImage;
    qreal angle;    
    QImage Okladka;



protected:
    void paintEvent(QPaintEvent *event);
public slots:

    void rotate();
    
};

#endif // CD_H
