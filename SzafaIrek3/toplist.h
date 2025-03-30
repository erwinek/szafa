#ifndef TOPLIST_H
#define TOPLIST_H

#include <QWidget>

class Toplist : public QWidget
{
    Q_OBJECT
public:
    explicit Toplist(QStringList *songList, QWidget *parent = 0);
    QStringList imgTop20PathList;
    QString GetTopSongPath();

private:
    QStringList *strListTop20;

signals:
    
public slots:
    void show();
};

#endif // TOPLIST_H
