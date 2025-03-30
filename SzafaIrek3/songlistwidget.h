#ifndef SONGLISTWIDGET_H
#define SONGLISTWIDGET_H

#include <QWidget>
#include <QtGui>

class SongListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SongListWidget(QWidget *parent = 0, QString pathOkladka = "", QString Artist = "", QString title = "", QString czas = "",  bool isFirst = false);
    QLabel *labelBackground;
    QLabel *okladka;
    QLabel *Wykonawca;
    QLabel *Tytul;
    QLabel *czas;
signals:
    
public slots:
    
};

#endif // SONGLISTWIDGET_H
