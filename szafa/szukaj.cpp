#include <QtGui>
#include "szukaj.h"
#include "folder.h"
#include "window.h"

 class Window;
 class folder;



 //extern folder Window::albums;


#define NUM_x 170
#define NUM_y 480

#define Q_x 200
#define Q_y NUM_y+60

#define A_x 230
#define A_y Q_y+60

#define Z_x 260
#define Z_y A_y+60

#define KEY_ODSTEP 60



struct Szukaj::Keyboard keyboard[40] = {

{  NULL, "1", NUM_x+KEY_ODSTEP*0, NUM_y },
{  NULL, "2", NUM_x+KEY_ODSTEP*1, NUM_y },
{  NULL, "3", NUM_x+KEY_ODSTEP*2, NUM_y },
{  NULL, "4", NUM_x+KEY_ODSTEP*3, NUM_y },
{  NULL, "5", NUM_x+KEY_ODSTEP*4, NUM_y },
{  NULL, "6", NUM_x+KEY_ODSTEP*5, NUM_y },
{  NULL, "7", NUM_x+KEY_ODSTEP*6, NUM_y },
{  NULL, "8", NUM_x+KEY_ODSTEP*7, NUM_y },
{  NULL, "9", NUM_x+KEY_ODSTEP*8, NUM_y },
{  NULL, "0", NUM_x+KEY_ODSTEP*9, NUM_y },



{  NULL, "Q", Q_x+KEY_ODSTEP*0, Q_y },
{  NULL, "W", Q_x+KEY_ODSTEP*1, Q_y },
{  NULL, "E", Q_x+KEY_ODSTEP*2, Q_y },
{  NULL, "R", Q_x+KEY_ODSTEP*3, Q_y },
{  NULL, "T", Q_x+KEY_ODSTEP*4, Q_y },
{  NULL, "Y", Q_x+KEY_ODSTEP*5, Q_y },
{  NULL, "U", Q_x+KEY_ODSTEP*6, Q_y },
{  NULL, "I", Q_x+KEY_ODSTEP*7, Q_y },
{  NULL, "O", Q_x+KEY_ODSTEP*8, Q_y },
{  NULL, "P", Q_x+KEY_ODSTEP*9, Q_y },

{  NULL, "A", A_x+KEY_ODSTEP*0, A_y },
{  NULL, "S", A_x+KEY_ODSTEP*1, A_y },
{  NULL, "D", A_x+KEY_ODSTEP*2, A_y },
{  NULL, "F", A_x+KEY_ODSTEP*3, A_y },
{  NULL, "G", A_x+KEY_ODSTEP*4, A_y },
{  NULL, "H", A_x+KEY_ODSTEP*5, A_y },
{  NULL, "J", A_x+KEY_ODSTEP*6, A_y },
{  NULL, "K", A_x+KEY_ODSTEP*7, A_y },
{  NULL, "L", A_x+KEY_ODSTEP*8, A_y },

{  NULL, "Z", Z_x+KEY_ODSTEP*0, Z_y },
{  NULL, "X", Z_x+KEY_ODSTEP*1, Z_y },
{  NULL, "C", Z_x+KEY_ODSTEP*2, Z_y },
{  NULL, "V", Z_x+KEY_ODSTEP*3, Z_y },
{  NULL, "B", Z_x+KEY_ODSTEP*4, Z_y },
{  NULL, "N", Z_x+KEY_ODSTEP*5, Z_y },
{  NULL, "M", Z_x+KEY_ODSTEP*6, Z_y }


};

Szukaj::Szukaj(QWidget *parent) :
    QWidget(parent)
{
     SzukajImage.load("gfx/2.jpg");

     for (int i =0;i<36;i++)
     {
         keyboard[i].ptr = new QPushButton(keyboard[i].txt, this);
         keyboard[i].ptr->move(keyboard[i].pos_x, keyboard[i].pos_y);
         keyboard[i].ptr->resize(50,50);
         keyboard[i].ptr->setStyleSheet("QPushButton { \
                                        background-color: rgba(0,0,0,150); \
                                        font:bold 24px; \
                                        border-radius: 6px; \
                                }");
         connect(keyboard[i].ptr, SIGNAL(clicked()),this, SLOT(button_clicked()));
     }


     listWidget = new QListWidget(this);
     listWidget->setSortingEnabled(true);
     listWidget->setGeometry(10,10,900,400);
     listWidget->hide();
     //listWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
     listWidget->setWrapping(0);
     listWidget->setStyleSheet("QScrollBar:vertical {width: 50px;} \
                               QScrollBar:vertical:up-arrow { width: 50px;  height: 50px;  background-color: rgba(1,2,3,4);  } \
                                QListWidget:item:selected { background-color:rgba(100,0,200,200); } \
                               QListView {color: rgb(230, 230, 230); font-size: 24px; background-color: rgba(10,20,30,30); border-style: none} QListView::item:selected {background-image: url(:/ui_resources/elements-preset_select/highlight_bar_270x30-black_bg.bmp)}");

     //listWidget->setStyleSheet("Q");
//border: none;
//	width: 30px;
//	margin: 30px 0px 30px 0px;}

     QPushButton *button_enter = new QPushButton("ENTER",this);
     connect(button_enter, SIGNAL(clicked()),this, SLOT(search()));
     button_enter->resize(120, 50); // first argument is width and second is the height.
     button_enter->move(A_x+KEY_ODSTEP*9,A_y);
     button_enter->show();
     button_enter->setStyleSheet("QPushButton { \
                                 background-color: rgba(0,0,0,150); \
                                 font-size: 24px; \
                                 border-radius: 6px; \
                                 }");

     QPushButton *button_space = new QPushButton("SPACE",this);
     connect(button_space, SIGNAL(clicked()),this, SLOT(search()));
     button_space->resize(360, 50); // first argument is width and second is the height.
     button_space->move(Z_x + 30, Z_y+60);
     button_space->show();
     button_space->setStyleSheet("QPushButton { \
                                        background-color: rgba(0,0,0,150); \
                                        font-size: 24px; \
                                        border-radius: 6px; \
                                        }");

     QPushButton *button_backspace = new QPushButton("BACKSPACE",this);
     connect(button_backspace, SIGNAL(clicked()),this, SLOT(button_clicked()));
     button_backspace->resize(120, 50); // first argument is width and second is the height.
     button_backspace->move( NUM_x+KEY_ODSTEP*10,NUM_y);
     button_backspace->show();
     button_backspace->setStyleSheet("QPushButton { \
                                        background-color: rgba(0,0,0,150); \
                                        font-size: 20px; \
                                        border-radius: 6px; \
                                        }");

    //Window *pointer=parent;
    //QWidget
    //QObject *obj = parent;

    Window *w_ptr = qobject_cast<Window *>(parent);
    //folder *f_ptr = qobject_cast<folder *>(w_ptr->albums);
    //f_ptr->Kredyt = 0;


    buttonPlay = new QPushButton("",this);
    //connect(buttonPlay, SIGNAL(clicked()),albums, SLOT(Play()));
    buttonPlay->resize(100, 100);
    buttonPlay->move(900,150);
    buttonPlay->show();
    QImage playButton("gfx/play.jpg");
    buttonPlay->setIcon(QPixmap::fromImage(playButton));
    buttonPlay->resize(100,100);
    buttonPlay->setIconSize(buttonPlay->size());

}

void Szukaj::paintEvent(QPaintEvent *event)
{
QPainter paint( this );
    paint.setRenderHints(QPainter::Antialiasing, 1);
    paint.setRenderHints(QPainter::SmoothPixmapTransform, 1);

    paint.drawImage(QRect(0, 0, 1024, 768), SzukajImage);

    QPen pen_txt(Qt::darkBlue, 6, Qt::SolidLine);
    QFont serifFont("Times", 24);
    paint.setPen(pen_txt);
    paint.setFont(serifFont);
    paint.drawText(1024/2,450,(const QString) szukanyTekst);

    paint.end();
}

void Szukaj::search()
{
    //this->lower();
    listWidget->clear();
    RecurseDirectory("/home/erwinek/mp3/");
    listWidget->raise();
    listWidget->show();

    repaint();
}

void Szukaj::button_clicked()
{
    QPushButton *nadawca = (QPushButton*)sender();

    for(int i=0;i<36;i++)
    {
        if(nadawca->text() == keyboard[i].txt)       szukanyTekst.append(keyboard[i].txt);
    }

    if(nadawca->text() == "BACKSPACE") szukanyTekst.chop(1);

    repaint();
}



void Szukaj::RecurseDirectory(const QString& sDir)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QStringList wynik;
    QDir dir(sDir);
    QFileInfoList list = dir.entryInfoList();
    for (int iList=0;iList<list.count();iList++)
    {
        QFileInfo info = list[iList];

        QString sFilePath = info.filePath();
        if (info.isDir())
        {
            // recursive
            if (info.fileName()!=".." && info.fileName()!=".")
            {
                RecurseDirectory(sFilePath);
            }
        }
        else
        {
            // Do something with the file here

            QString szukanyTekstLower = szukanyTekst.toLower();
            QString nazwa_pliku = info.fileName();
            QString nazwaPlikuLower = nazwa_pliku.toLower();
            //QString text_pl = QString::fromUtf8(ptr);
            if (nazwaPlikuLower.contains(szukanyTekstLower) )
            {
                if (nazwaPlikuLower.contains(".mp3") )
                {

                    Song piosenka;

                    piosenka.artist = "";
                    piosenka.path = info.filePath();
                    nazwa_pliku.chop(4);

                    piosenka.title = nazwa_pliku;
                    piosenka.title.truncate(piosenka.title.length()-4); //odcinamy rozszerzenie mp3

                    piosenka.CdPath = info.path() + "/cd.png";

                    m_wynikiWyszukiwania.enqueue(piosenka);



                    //if(nazwa_pliku.length() > 60)            nazwa_pliku.truncate(60);
                    listWidget->addItem(nazwa_pliku);

                }
            }
        }
    }
}


int Szukaj::SearchFile(const QString& sDir, QString fileName, QString &wynik)
{
    int found=0;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QDir dir(sDir);
    QFileInfoList list = dir.entryInfoList();
    for (int iList=0;iList<list.count();iList++)
    {
        QFileInfo info = list[iList];

        QString sFilePath = info.filePath();
        if (info.isDir())
        {
            // recursive
            if (info.fileName()!=".." && info.fileName()!=".")
            {
                found=SearchFile(sFilePath, fileName, wynik);
            }
        }
        else
        {
            // Do something with the file here

            if (info.fileName().contains(fileName))
            {
                 wynik=info.filePath();
                 found=1;
                 return 1;
            }
        }
    }
    return found;
}
