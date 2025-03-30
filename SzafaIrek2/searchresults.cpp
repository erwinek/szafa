#include "window.h"
#include "searchresults.h"
#include "tile.h"


SearchResults::SearchResults(QWidget *parent) :
    QWidget(parent)
{
    this->resize(1024-230,768);
    this->move(230,0);

    QString styleLabelHeader = "QLabel { \
        font: bold 30px; \
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

    Kafelki  = new QWidget(this);
    Kafelki->resize(headerImg.width(), 768 - headerImg.height() - labelDownImage.height());
    Kafelki->move(0,headerImg.height());

    gridLayout = new QGridLayout();
    Kafelki->setLayout(gridLayout);

    // TODO REMOVE set black background
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    this->show();

    gridLayout->setColumnMinimumWidth(0,150);
    gridLayout->setColumnMinimumWidth(1,150);
    gridLayout->setColumnMinimumWidth(2,150);

    for (int row = 0; row < 3; row ++) {
        gridLayout->setRowMinimumHeight(row,220);
    }

}

void SearchResults::ShowResults(QList<Plyta> resultList)
{
    this->raise();
    this->show();

    while(!tileList.isEmpty())
    {
        Tile *ptr = tileList.takeFirst();
        delete ptr;
    }

    int i=0;
    for(int row=0;row<3;row++)
    {
        for(int col=0;col<4;col++)
        {
            AlbumTile *ptr = new AlbumTile(this, resultList.at(i).path, resultList.at(i).artist, resultList.at(i).title);
            tileList.append(ptr);
            gridLayout->addWidget(ptr, row, col);
            if (i < resultList.length()-1) i++;
            else return;
        }
    }
    this->show();
    this->raise();
}
