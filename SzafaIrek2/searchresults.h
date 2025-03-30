#ifndef SEARCHRESULTS_H
#define SEARCHRESULTS_H

#include <QWidget>
#include <QtGui>
#include "tile.h"
#include "folder.h"

class SearchResults : public QWidget
{
    Q_OBJECT
public:
    explicit SearchResults(QWidget *parent = 0);
    void ShowResults(QList<Plyta> resultList);

private:
    QGridLayout *gridLayout;
    QWidget *Kafelki;
    QLabel *header;
    QLabel *labelDown;

    QList<Tile*> tileList;
signals:
    
public slots:
    
};

#endif // SEARCHRESULTS_H
