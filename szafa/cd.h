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
    QImage CdImage;
    //QPixmap CdPixmap;
private:

    qreal angle;    
    QImage Okladka;



protected:
    void paintEvent(QPaintEvent *event);
public slots:

    void rotate();
    
};

#endif // CD_H
