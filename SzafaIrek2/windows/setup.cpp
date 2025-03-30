#include "setup.h"
#include "window.h"


Setup::Setup(QWidget *parent) :
    QWidget(parent)
{    
    const QString& labeCss = "\
            QLabel { \
                background-color: rgba(10,10,10,150); \
                font: bold 20px; \
                color: red;\
                border-radius: 16px; \
            }";



    Screen = settings.value("Setup/styl").toInt();

    QLabel *lStyle = new QLabel("Styl", this);
    lStyle->resize(200,100);
    lStyle->move(300,50);
    lStyle->setStyleSheet(labeCss);
    lStyle->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    styl = new QComboBox(this);
    styl->addItem("Fortepian");
    styl->addItem("Nuty");
    styl->addItem("Skrzypce");
    styl->addItem("Czarny");
    styl->addItem("MenuKolor");
    styl->resize(200,100);
    styl->move(500,50);


    //--- Darmowy kredyt i freeplay
    QLabel *lFreeCredit= new QLabel("Free Credit", this);
    lFreeCredit->resize(200,100);
    lFreeCredit->move(300,160);
    lFreeCredit->setStyleSheet(labeCss);
    lFreeCredit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QPushButton *buttonFreeCredit= new QPushButton("Credit + 1", this);
    buttonFreeCredit->resize(200,100); //width, height.
    buttonFreeCredit->move(500, 160);
    buttonFreeCredit->setStyleSheet("");
    connect(buttonFreeCredit, SIGNAL(clicked()),this, SLOT(AddCredit()));

    lFreePlay= new QLabel("Free Play Off", this);
    lFreePlay->resize(200,100);
    lFreePlay->move(300,270);
    lFreePlay->setStyleSheet(labeCss);
    lFreePlay->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QPushButton *buttonFreePLay= new QPushButton("Freeplay", this);
    buttonFreePLay->resize(200, 100); //width, height.
    buttonFreePLay->move(500, 270);
    buttonFreePLay->setStyleSheet("");
    connect(buttonFreePLay, SIGNAL(clicked()),this, SLOT(FreePlay()));

    if ("ON" == settings.value("Setup/FreePlay"))
    {
        lFreePlay->setText("FreePlay ON");
        freePlayOnOff = true;
    }
    else
    {
        lFreePlay->setText("FreePlay OFF");
        freePlayOnOff = false;
    }

    QObject::connect(styl, SIGNAL(activated(int)),this, SLOT(StyleChange()));

    switch (Screen)
    {
        case Setup::FORTEPIAN:
            SetupImage = new QImage("gfx/0/background.jpg");
            break;
        case Setup::NUTKI:
            SetupImage = new QImage("gfx/1/background.jpg");
            break;
        case Setup::SKRZYPCE:
            SetupImage = new QImage("gfx/2/background.jpg");
            break;
        case Setup::CZARNY:
            SetupImage = new QImage("gfx/3/background.jpg");
            break;
        case Setup::MENU_KOLOR:
            SetupImage = new QImage("gfx/4/background.jpg");
            break;
    }

    QString exitStyleSheet = " \
                      color: black;\
                      background-color: rgba(255,255,255,255); \
                      font-size: 40px; \
                      border-radius: 6px; \
                       ";

    bExit = new QPushButton("SAVE\nEXIT", this);
    bExit->move(270,650);
    bExit->resize(220,100);
    bExit->setStyleSheet(exitStyleSheet);
    connect(bExit, SIGNAL(clicked()),this, SLOT(ExitSetup()));

    bExitWithoutSave = new QPushButton("EXIT", this);
    bExitWithoutSave->move(510,650);
    bExitWithoutSave->resize(220,100);
    bExitWithoutSave->setStyleSheet(exitStyleSheet);
    connect(bExitWithoutSave, SIGNAL(clicked()),this, SLOT(ExitSetupWithoutSave()));


    //--- Password
    QLabel *lPassword= new QLabel("Password", this);
    lPassword->resize(200,100);
    lPassword->move(300,380);
    lPassword->setStyleSheet(labeCss);
    lPassword->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    editPass = new QLineEdit(this);
    editPass->show();
    editPass->raise();

    editPass->resize(100,100);
    editPass->move(500,380);
    editPass->setText(settings.value("Setup/Password").toString());
    connect(editPass, SIGNAL(editingFinished()),this, SLOT(HideKeyboard()));

    QPushButton *buttonChangePassword = new QPushButton("Change", this);
    buttonChangePassword->resize(100, 100); //width, height.
    buttonChangePassword->move(600,380);
    buttonChangePassword->setStyleSheet("");
    connect(buttonChangePassword, SIGNAL(clicked()),this, SLOT(EditPassword()));

    //--- COM port number
    QLabel *lComPort = new QLabel("COM Port", this);
    lComPort->resize(200,100);
    lComPort->move(300,490);
    lComPort->setStyleSheet(labeCss);
    lComPort->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    comPortSelect = new QComboBox(this);
    comPortSelect->addItem("/dev/ttyS0");
    comPortSelect->addItem("/dev/ttyS1");
    comPortSelect->addItem("/dev/ttyS2");
    comPortSelect->addItem("/dev/ttyS3");
    comPortSelect->addItem("/dev/ttyS4");
    comPortSelect->addItem("/dev/ttyUSB0");
    comPortSelect->addItem("/dev/ttyUSB1");
    comPortSelect->addItem("/dev/ttyUSB2");
    comPortSelect->addItem("/dev/ttyUSB3");
    comPortSelect->addItem("/dev/ttyUSB4");
    comPortSelect->resize(200,100);
    comPortSelect->move(500,490);

    QString storedPortNumberTxt = settings.value("Setup/ComPort", "/dev/ttyS0").toString();
    for (int i=0;i<4;i++) {
        if(comPortSelect->itemText(i) == storedPortNumberTxt) {
            comPortSelect->setCurrentIndex(i);
            break;
        }
    }


    keyboard = new Keyboard(this, editPass);
    keyboard->hide();
	
	//settings.setValue("Setup/Password", "");
}

void Setup::paintEvent(QPaintEvent *event)
{
    event=event; //warning

    QPainter paint( this );    
    paint.setRenderHints(QPainter::Antialiasing, 1);
    paint.setRenderHints(QPainter::SmoothPixmapTransform, 1);

    paint.drawImage(QRect(0, 0, 1024, 768), *SetupImage);

    styl->setCurrentIndex(settings.value("Setup/styl").toInt());


    paint.end();
}

void Setup::Init()
{
    this->show();
    this->raise();


}
void Setup::ExitSetupWithoutSave()
{
    this->hide();
    ((Window*)parentWidget())->homeScreen->show();
    ((Window*)parentWidget())->menu->show();

}
void Setup::ExitSetup()
{
    QString comPortNumberString = comPortSelect->itemText(comPortSelect->currentIndex());
    settings.setValue("Setup/ComPort", comPortNumberString);
    editPass->setText(editPass->text().toUpper());
    settings.setValue("Setup/Password", editPass->text());
    ((Window*)parentWidget())->serialPort->setLedProgram = true;

    if (lFreePlay->text()=="FreePlay ON") {
        settings.setValue("Setup/FreePlay", "ON");
    }
    else {
        settings.setValue("Setup/FreePlay", "OFF");
    }

    Screen = settings.value("Setup/styl").toInt();
    ((Window*)parentWidget())->reloadPictures();
    ((Window*)parentWidget())->menu->ReloadButtonImage();
    this->hide();
    ((Window*)parentWidget())->homeScreen->show();
    ((Window*)parentWidget())->menu->show();

}


void Setup::StyleChange()
{
    static int indexBak;
    switch (styl->currentIndex()) {
        case FORTEPIAN:
            SetupImage = new QImage("gfx/0/background.jpg");
            ((Window*)parentWidget())->tlo->qimage->load("gfx/0/background.jpg");
            settings.setValue("Setup/styl", FORTEPIAN);
        break;
        case NUTKI:
            SetupImage = new QImage("gfx/1/background.jpg");
            ((Window*)parentWidget())->tlo->qimage->load("gfx/1/background.jpg");
            settings.setValue("Setup/styl", NUTKI);
        break;
        case SKRZYPCE:
            SetupImage = new QImage("gfx/2/background.jpg");
            ((Window*)parentWidget())->tlo->qimage->load("gfx/2/background.jpg");
            settings.setValue("Setup/styl", SKRZYPCE);
        break;
        case CZARNY:
            SetupImage = new QImage("gfx/3/background.jpg");
            ((Window*)parentWidget())->tlo->qimage->load("gfx/3/background.jpg");
            settings.setValue("Setup/styl", CZARNY);
        break;            
        case MENU_KOLOR:
            SetupImage = new QImage("gfx/4/background.jpg");
            ((Window*)parentWidget())->tlo->qimage->load("gfx/4/background.jpg");
            settings.setValue("Setup/styl", MENU_KOLOR);
        break;
    }

    if (indexBak != styl->currentIndex())
    {
        indexBak = styl->currentIndex();
        repaint();
    }
}



void Setup::AddCredit()
{
    ((Window*)parentWidget())->creditWidget->incrCredit();
}


void Setup::FreePlay()
{
    if (lFreePlay->text()=="FreePlay ON") {
        freePlayOnOff = false;
        settings.setValue("Setup/FreePlay", "OFF");
        lFreePlay->setText("FreePlay OFF");
        ((Window*)parentWidget())->creditWidget->show();
    }
    else {
        freePlayOnOff = true;
        settings.setValue("Setup/FreePlay", "ON");
        lFreePlay->setText("FreePlay ON");

        ((Window*)parentWidget())->creditWidget->hide();
    }
    ((Window*)parentWidget())->homeScreen->reloadAdvert();
}

void Setup::EditPassword()
{
    keyboard->show();
}

void Setup::HideKeyboard()
{

    keyboard->hide();

}
