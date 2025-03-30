#include "insertcoin.h"

InsertCoin::InsertCoin(QWidget *parent) :
    QWidget(parent)
{
    lTextLabel = new QLabel("CHCESZ POSŁUCHAĆ TEJ PIOSENKI ?", this);

    QImage imgBackground("gfx/3/background.jpg");
    QLabel *background = new QLabel(this);
    background->setPixmap(QPixmap::fromImage(imgBackground));
    background->resize(1024,768);
    background->move(0,0);

    QImage imgWrzucMonete("gfx/insert_coin.png");
    lWrzucMonete = new QLabel(this);
    lWrzucMonete->resize(imgWrzucMonete.size());
    lWrzucMonete->move((1024-imgWrzucMonete.width())/2, 50);
    lWrzucMonete->setStyleSheet("QLabel { background-image: url(gfx/insert_coin.png) }");

    //QImage InsertCoinGfx("gfx/insert_coin_gfx.png");
	QMovie *movie = new QMovie("gfx/insert_coin_animated.gif");
    lInsertCoinGfx = new QLabel(this);
    lInsertCoinGfx->move(250, 250);
	lInsertCoinGfx->setMovie(movie);
	movie->start();
		
    QImage Advert("gfx/insert_coin_credits_cost.png");
    lAdvert = new QLabel(this);
    lAdvert->resize(Advert.size());
    lAdvert->move((1024-Advert.width())/2, 600);
    lAdvert->setStyleSheet("QLabel { background-image: url(gfx/insert_coin_credits_cost.png) }");

    tInsertCoin = new QTimer(this);
    connect(tInsertCoin, SIGNAL(timeout()), this, SLOT(blinkWrzucMonete()));
    tInsertCoin->start(1000);

}

void InsertCoin::SwitchOn()
{

}

void InsertCoin::blinkWrzucMonete()
{
    static bool blink = 0;

    if (blink) {
        lWrzucMonete->setStyleSheet("QLabel { background-image: url(gfx/insert_coin.png) }");
        blink = 0;
    }
    else {
        lWrzucMonete->setStyleSheet("QLabel { background-image: url(gfx/insert_coin2.png) }");
        blink = 1;
    }


}

