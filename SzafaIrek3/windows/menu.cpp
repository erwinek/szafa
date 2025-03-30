#include "menu.h"
#include "window.h"

const QSize buttonSize(170,100);
const int buttonSpaceY = 5;

const QSize buttonUpDownSize(160,80);

Menu::Menu(QWidget *parent) :
    QWidget(parent)
{

    startButton=0;
    QImage image("gfx/left_interface.png");

    QLabel *label = new QLabel(this);
    label->setPixmap(QPixmap::fromImage(image));
    label->resize(image.size());
    label->move(0, 0);

    this->resize(image.size());
    this->move(0,0);

    QString gfxPath="gfx/5/";
    QString buttonStyleSheet = " \
            background-color: rgba(10,20,30,0); \
            font-size: 8px; \
            color: white;\
            border-radius: 6px;";

    QImage bSzukajImg(gfxPath + "/b_szukaj.png");
    buttonSzukaj = new QPushButton(this);
    buttonSzukaj->resize(buttonSize); //width, height.
    buttonSzukaj->setIcon(QPixmap::fromImage(bSzukajImg).scaled(buttonSize));
    buttonSzukaj->setIconSize(buttonSize);
    buttonSzukaj->setFocusPolicy(Qt::NoFocus);
    connect(buttonSzukaj, SIGNAL(clicked()),((Window*)parentWidget()), SLOT(szukanie()));
    buttonSzukaj->setStyleSheet( buttonStyleSheet);
    buttonList.append(buttonSzukaj);

    QImage btop10Img(gfxPath + "b_top10.png");
    buttonTop10 = new QPushButton(this);
    buttonTop10->resize(buttonSize); //width, height.
    buttonTop10->move(0, 720);
    buttonTop10->setIcon(QPixmap::fromImage(btop10Img).scaled(buttonSize));
    buttonTop10->setIconSize(buttonSize);
    buttonTop10->setFocusPolicy(Qt::NoFocus);
    buttonTop10->setStyleSheet( buttonStyleSheet);
    connect(buttonTop10, SIGNAL(clicked()),((Window*)parentWidget())->top20, SLOT(show()));
    buttonList.append(buttonTop10);


    QImage bNowosciImg(gfxPath + "b_nowosci.png");
    buttonNowosci = new QPushButton(this);
    buttonNowosci->resize(buttonSize); //width, height.
    buttonNowosci->setIcon(QPixmap::fromImage(bNowosciImg).scaled(buttonSize));
    buttonNowosci->setIconSize(buttonSize);
    buttonNowosci->setFocusPolicy(Qt::NoFocus);
    buttonNowosci->setStyleSheet( buttonStyleSheet);
    connect(buttonNowosci, SIGNAL(clicked()),((Window*)parentWidget())->albums, SLOT(Nowosci()));
    buttonList.append(buttonNowosci);


    QImage bWszystkieImg(gfxPath + "b_wszystkie.png");
    buttonWszystkie = new QPushButton(this);
    buttonWszystkie->resize(buttonSize); //width, height.
    buttonWszystkie->setIcon(QPixmap::fromImage(bWszystkieImg).scaled(buttonSize));
    buttonWszystkie->setIconSize(buttonSize);
    buttonWszystkie->move(30,180);
    buttonWszystkie->setFocusPolicy(Qt::NoFocus);
    buttonWszystkie->setStyleSheet( buttonStyleSheet);
    connect(buttonWszystkie, SIGNAL(clicked()),((Window*)parentWidget())->albums, SLOT(MuzykaWszystkie()));
    buttonList.append(buttonWszystkie);

    QImage bPolskieImg(gfxPath + "b_polskie.png");
    buttonMpolska = new QPushButton(this);
    buttonMpolska->resize(buttonSize); //width, height.
    buttonMpolska->move(0,270);
    buttonMpolska->setIcon(QPixmap::fromImage(bPolskieImg).scaled(buttonSize));
    buttonMpolska->setIconSize(buttonSize);
    buttonMpolska->setFocusPolicy(Qt::NoFocus);
    buttonMpolska->setStyleSheet( buttonStyleSheet);
    connect(buttonMpolska, SIGNAL(clicked()),((Window*)parentWidget())->albums, SLOT(MuzykaPolska()));
    buttonList.append(buttonMpolska);

    QImage bZagranicznaImg(gfxPath + "b_zagraniczne.png");
    buttonMzagraniczna = new QPushButton(this);
    buttonMzagraniczna->resize(buttonSize); //width, height.
    buttonMzagraniczna->setIcon(QPixmap::fromImage(bZagranicznaImg).scaled(buttonSize));
    buttonMzagraniczna->setIconSize(buttonSize);
    buttonMzagraniczna->setFocusPolicy(Qt::NoFocus);
    buttonMzagraniczna->setStyleSheet( buttonStyleSheet);
    connect(buttonMzagraniczna, SIGNAL(clicked()),((Window*)parentWidget())->albums, SLOT(MuzykaZagraniczna()));
    buttonList.append(buttonMzagraniczna);



    QImage bBiesiadneImg(gfxPath + "b_biesiadne.png");
    buttonMbiesiadna = new QPushButton(this);
    buttonMbiesiadna->resize(buttonSize); //width, height.
    buttonMbiesiadna->move(0,360);
    buttonMbiesiadna->setIcon(QPixmap::fromImage(bBiesiadneImg).scaled(buttonSize));
    buttonMbiesiadna->setIconSize(buttonSize);
    buttonMbiesiadna->setFocusPolicy(Qt::NoFocus);
    buttonMbiesiadna->setStyleSheet( buttonStyleSheet);
    connect(buttonMbiesiadna, SIGNAL(clicked()),((Window*)parentWidget())->albums, SLOT(MuzykaBiesiadna()));
    buttonList.append(buttonMbiesiadna);



    QImage bKaraokeImg(gfxPath + "b_karaoke.png");
    buttonKaraoke = new QPushButton(this);
    buttonKaraoke->resize(buttonSize); //width, height.
    buttonKaraoke->setIcon(QPixmap::fromImage(bKaraokeImg).scaled(buttonSize));
    buttonKaraoke->setIconSize(buttonSize);
    buttonKaraoke->setFocusPolicy(Qt::NoFocus);
    buttonKaraoke->setStyleSheet( buttonStyleSheet);
    connect(buttonKaraoke, SIGNAL(clicked()),((Window*)parentWidget())->albums, SLOT(Karaoke()));
    buttonList.append(buttonKaraoke);

    QImage bSkladankiImg(gfxPath + "b_skladanki.png");
    buttonSkladanki = new QPushButton(this);
    buttonSkladanki->resize(buttonSize); //width, height.
    buttonSkladanki->setIcon(QPixmap::fromImage(bSkladankiImg).scaled(buttonSize));
    buttonSkladanki->setIconSize(buttonSize);
    buttonSkladanki->setFocusPolicy(Qt::NoFocus);
    buttonSkladanki->setStyleSheet( buttonStyleSheet);
    connect(buttonSkladanki, SIGNAL(clicked()),((Window*)parentWidget())->albums, SLOT(Skladanki()));
    buttonList.append(buttonSkladanki);








    QImage bUpImg("gfx/up_arrow_interface.png");
    buttonUp = new QPushButton(this);
    buttonUp->resize(buttonUpDownSize); //width, height.
    buttonUp->move(35, 25);
    buttonUp->setIcon(QPixmap::fromImage(bUpImg).scaled(buttonUpDownSize));
    buttonUp->setIconSize(buttonUpDownSize);
    buttonUp->setFocusPolicy(Qt::NoFocus);
    connect(buttonUp, SIGNAL(clicked()),this, SLOT(MenuUp()));
    buttonUp->setStyleSheet( buttonStyleSheet);

    QImage bDownImg("gfx/down_arrow_interface.png");
    buttonDown = new QPushButton(this);
    buttonDown->resize(buttonUpDownSize); //width, height.
    buttonDown->move(35, 660);
    buttonDown->setIcon(QPixmap::fromImage(bDownImg).scaled(buttonUpDownSize));
    buttonDown->setIconSize(buttonUpDownSize);
    buttonDown->setFocusPolicy(Qt::NoFocus);
    connect(buttonDown, SIGNAL(clicked()), this, SLOT(MenuDown()));
    buttonDown->setStyleSheet( buttonStyleSheet);

    QTimer *timerUpDownArrow = new QTimer(this);
    connect(timerUpDownArrow, SIGNAL(timeout()), this, SLOT(flashUpDpwnArrow()));

    timerUpDownArrow->start(400);



    ReloadButtons();

}

void Menu::ReloadButtons()
{
    for (int i =0; i<buttonList.count();i++) {
        if ((i >= startButton) && (i < (startButton + 5))) {
                //show
            buttonList[i]->move(30, 125 + (buttonSpaceY + buttonSize.height()) * (i - startButton));
            buttonList[i]->show();
        }
        else
        {
            //hide
            buttonList[i]->hide();
        }
    }
}

void Menu::MenuUp()
{
    if (startButton>0) startButton--;
    ReloadButtons();

}

void Menu::MenuDown()
{
    if(startButton < buttonList.length() - 5) startButton++;
    ReloadButtons();
}

void Menu::ReloadButtonImage()
{
    /*
    QString *StyleNum = new QString();
    StyleNum->setNum(((Window*)parentWidget())->setup->Screen);
    QString gfxPath = "gfx/" + *StyleNum + "/";

    QImage bSzukajImg(gfxPath + "/b_szukaj.png");
    buttonSzukaj->setIcon(QPixmap::fromImage(bSzukajImg));

    QImage bWszystkieImg(gfxPath + "b_wszystkie.png");
    buttonWszystkie->setIcon(QPixmap::fromImage(bWszystkieImg));

    QImage bMpolskaImg(gfxPath + "b_polskie.png");
    buttonMpolska->setIcon(QPixmap::fromImage(bMpolskaImg));

    QImage bMbiesiadnaImg(gfxPath + "b_biesiadne.png");
    buttonMbiesiadna->setIcon(QPixmap::fromImage(bMbiesiadnaImg));

    QImage bZagranicznaImg(gfxPath + "b_zagraniczna.png");
    buttonMzagraniczna->setIcon(QPixmap::fromImage(bZagranicznaImg));

    QImage bKaraokeImg(gfxPath + "b_karaoke.png");
    buttonKaraoke->setIcon(QPixmap::fromImage(bKaraokeImg));

    QImage bSkladankiImg(gfxPath + "b_skladanki.png");
    buttonSkladanki->setIcon(QPixmap::fromImage(bSkladankiImg));

    QImage bNowosciImg(gfxPath + "b_nowosci.png");
    buttonNowosci->setIcon(QPixmap::fromImage(bNowosciImg));

    QImage bTop10Img(gfxPath + "b_top10.png");
    buttonTop10->setIcon(QPixmap::fromImage(bTop10Img));
*/
}

void Menu::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    ((Window*)parentWidget())->slideshowScreen->resetCounter();
}

void Menu::flashUpDpwnArrow()
{
    static bool flag=0;

    if (flag) {
        flag=0;
        QImage bUpImg("gfx/up_arrow_interface.png");
        buttonUp->setIcon(QPixmap::fromImage(bUpImg).scaled(buttonUpDownSize));

        QImage bDownImg("gfx/down_arrow_interface.png");
        buttonDown->setIcon(QPixmap::fromImage(bDownImg).scaled(buttonUpDownSize));
    }
    else {
        flag = 1;

        QImage bUpImg("gfx/up_arrow_interface2.png");
        buttonUp->setIcon(QPixmap::fromImage(bUpImg).scaled(buttonUpDownSize));

        QImage bDownImg("gfx/down_arrow_interface2.png");
        buttonDown->setIcon(QPixmap::fromImage(bDownImg).scaled(buttonUpDownSize));
    }
}
