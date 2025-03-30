#include <QtCore>
#include <QtGui>
#include "szukaj.h"
#include "folder.h"
#include "window.h"

 class Window;
 class folder;



 //extern folder Window::albums;


#define NUM_x 40
#define NUM_y 220

#define KEY_ODSTEP 80

#define Q_x 80
#define Q_y NUM_y + KEY_ODSTEP

#define A_x 120
#define A_y Q_y + KEY_ODSTEP

#define Z_x 160
#define Z_y A_y + KEY_ODSTEP

#define KEY_SIZE_x 70
#define KEY_SIZE_y 70





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


struct Szukaj::Keyboard keyboardAlt[40] = {

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
{  NULL, "Ę", Q_x+KEY_ODSTEP*2, Q_y },
{  NULL, "R", Q_x+KEY_ODSTEP*3, Q_y },
{  NULL, "T", Q_x+KEY_ODSTEP*4, Q_y },
{  NULL, "Y", Q_x+KEY_ODSTEP*5, Q_y },
{  NULL, "U", Q_x+KEY_ODSTEP*6, Q_y },
{  NULL, "I", Q_x+KEY_ODSTEP*7, Q_y },
{  NULL, "Ó", Q_x+KEY_ODSTEP*8, Q_y },
{  NULL, "P", Q_x+KEY_ODSTEP*9, Q_y },

{  NULL, "Ą", A_x+KEY_ODSTEP*0, A_y },
{  NULL, "Ś", A_x+KEY_ODSTEP*1, A_y },
{  NULL, "D", A_x+KEY_ODSTEP*2, A_y },
{  NULL, "F", A_x+KEY_ODSTEP*3, A_y },
{  NULL, "G", A_x+KEY_ODSTEP*4, A_y },
{  NULL, "H", A_x+KEY_ODSTEP*5, A_y },
{  NULL, "J", A_x+KEY_ODSTEP*6, A_y },
{  NULL, "K", A_x+KEY_ODSTEP*7, A_y },
{  NULL, "Ł", A_x+KEY_ODSTEP*8, A_y },

{  NULL, "Ż", Z_x+KEY_ODSTEP*0, Z_y },
{  NULL, "Ź", Z_x+KEY_ODSTEP*1, Z_y },
{  NULL, "Ć", Z_x+KEY_ODSTEP*2, Z_y },
{  NULL, "V", Z_x+KEY_ODSTEP*3, Z_y },
{  NULL, "B", Z_x+KEY_ODSTEP*4, Z_y },
{  NULL, "N", Z_x+KEY_ODSTEP*5, Z_y },
{  NULL, "M", Z_x+KEY_ODSTEP*6, Z_y }


};


Szukaj::Szukaj(QWidget *parent, Albums *albumsScreen, Songs *songsScreen) :
    QWidget(parent)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    albumsWidget = albumsScreen;
    songsWidget = songsScreen;

    QString lRamkaStyle =" \
                                     border-radius: 10px; \
                                     border: 3px solid #ffffff; \
                                     ";

    QLabel *lRamka =new QLabel(this);
    lRamka->resize(1024-20,768-20);
    lRamka->move(0,0);
    lRamka->setStyleSheet(lRamkaStyle);

    lTrwaWyszukiwanie = new QLabel("TRWA WYSZUKIWANIE...", this);
    lTrwaWyszukiwanie->resize(500, 50);
    lTrwaWyszukiwanie->move(300, 150);
    lTrwaWyszukiwanie->hide();
    lTrwaWyszukiwanie->setStyleSheet(" QLabel { \
                       color: white;\
                       font-size: 40px; \
                       background-color: rgba(0,0,0,0); \
    }");


    buttonStyleSheet = buttonStyleSheet.sprintf(" \
                                     color: black;\
                                     background-color: rgba(214,214,206,255); \
                                     font: bold 50px; \
                                     border-radius: 6px; \
                                     ");

    buttonSelectedStyleSheet = " \
                              color: red;\
                              background-color: rgba(255,255,255,255); \
                              font-size: 40px; \
                              border-radius: 6px; \
                              border: 6px solid red; \
                         ";

     buttonUnSelectedStyleSheet = " \
                                color: black;\
                                background-color: rgba(214,214,206,255); \
                                font: bold 40px; \
                                border-radius: 6px; \
                                 ";



    SzukajImage.load(((Window*)parentWidget())->gfxPath + "background.jpg");

    QString text = "1234567890QWĘRTYUIÓPĄŚDFGHJKŁŻŹĆVBŃM";
    for (int i =0;i<36;i++)
    {
        keyboardAlt[i].txt = text.at(i);
        keyboardAlt[i].ptr = new QPushButton(text.at(i), this);
        keyboardAlt[i].ptr->move(keyboardAlt[i].pos_x, keyboardAlt[i].pos_y);
        keyboardAlt[i].ptr->resize(KEY_SIZE_x, KEY_SIZE_y);
        keyboardAlt[i].ptr->setStyleSheet(buttonStyleSheet);
        keyboardAlt[i].ptr->setFocusPolicy(Qt::NoFocus);
        connect(keyboardAlt[i].ptr, SIGNAL(clicked()),this, SLOT(button_clicked()));
    }


     for (int i =0;i<36;i++)
     {
         keyboard[i].ptr = new QPushButton(keyboard[i].txt, this);
         keyboard[i].ptr->move(keyboard[i].pos_x, keyboard[i].pos_y);
         keyboard[i].ptr->resize(KEY_SIZE_x, KEY_SIZE_y);
         keyboard[i].ptr->setStyleSheet(buttonStyleSheet);
         keyboard[i].ptr->setFocusPolicy(Qt::NoFocus);
         connect(keyboard[i].ptr, SIGNAL(clicked()),this, SLOT(button_clicked()));
     }



     txtSzukany = new QLineEdit(this);
     txtSzukany->setText("");
     txtSzukany->setAlignment(Qt::AlignTop | Qt::AlignLeft);
     txtSzukany->move(150,50);
     txtSzukany->setFont(QFont("SansSerif", 40));
     txtSzukany->resize(700,75);
//     txtSzukany->setCursorPosition(0);
     txtSzukany->setStyleSheet("QLabel { \
                               background-color: rgba(214,214,206,255); \
                               font: bold 60px; \
                               color: black;\
                               qproperty-alignment: AlignCenter;\
                               border-radius: 10px; \
                           }");



    QString enterStyleSheet = " \
                                     color: black;\
                                     background-color: rgba(214,214,206,255); \
                                     font: bold 30px; \
                                     border-radius: 6px; \
                                     ";

     QPushButton *button_enter = new QPushButton("SZUKAJ",this);
     connect(button_enter, SIGNAL(clicked()),this, SLOT(search()));
     button_enter->resize(140, KEY_SIZE_y); // first argument is width and second is the height.
     button_enter->move(A_x+KEY_ODSTEP*9,A_y);
     button_enter->show();
     button_enter->setStyleSheet(enterStyleSheet);
     button_enter->setFocusPolicy(Qt::NoFocus);

     QPushButton *button_enter2 = new QPushButton(this);
     connect(button_enter2, SIGNAL(clicked()),this, SLOT(search()));
     button_enter2->resize(100, KEY_SIZE_y+20); // first argument is width and second is the height.
     button_enter2->move(Q_x+KEY_ODSTEP*10,Q_y);
     button_enter2->show();
     button_enter2->setStyleSheet(buttonStyleSheet);
     button_enter2->setFocusPolicy(Qt::NoFocus);


     QPushButton *button_wyjdz = new QPushButton(this);
     connect(button_wyjdz, SIGNAL(clicked()),this, SLOT(wyjdz()));
     button_wyjdz->resize(200, 80); // first argument is width and second is the height.
     button_wyjdz->move(30, 660);
     button_wyjdz->show();
     button_wyjdz->setStyleSheet(buttonStyleSheet);
     button_wyjdz->setFocusPolicy(Qt::NoFocus);
     QImage bWyjdzImg("gfx/keyWyjdz.png");
     button_wyjdz->setIcon(QPixmap::fromImage(bWyjdzImg).scaled(button_wyjdz->size(), Qt::IgnoreAspectRatio));
     button_wyjdz->setIconSize(button_wyjdz->size());

     QPushButton *button_space = new QPushButton("SPACE",this);
     connect(button_space, SIGNAL(clicked()),this, SLOT(button_clicked()));
     button_space->resize(500, KEY_SIZE_y); // first argument is width and second is the height.
     button_space->move(Z_x + 30, Z_y + KEY_ODSTEP);
     button_space->show();
     button_space->setStyleSheet(buttonStyleSheet);
     button_space->setFocusPolicy(Qt::NoFocus);


     isAltActive = 0;
     QPushButton *button_alt = new QPushButton("ALT",this);
     connect(button_alt, SIGNAL(clicked()),this, SLOT(alt_clicked()));
     button_alt->resize(KEY_SIZE_x*2, KEY_SIZE_y); // first argument is width and second is the height.
     button_alt->move(Z_x - KEY_SIZE_x - KEY_ODSTEP + 30, Z_y + KEY_ODSTEP);
     button_alt->show();
     button_alt->setStyleSheet(buttonStyleSheet);
     button_alt->setFocusPolicy(Qt::NoFocus);



     QPushButton *button_left = new QPushButton(this);
     QImage bLeftImg("gfx/keyLeft.png");
     connect(button_left, SIGNAL(clicked()),this, SLOT(cursorLeft()));
     button_left->resize(KEY_SIZE_x, KEY_SIZE_y);
     //button_left->move(button_space->pos().rx() + button_space->width() + KEY_ODSTEP, + Z_y + KEY_ODSTEP);
     button_left->move(button_space->pos().rx() + button_space->width() + 10, + Z_y + KEY_ODSTEP);
     button_left->setIcon(QPixmap::fromImage(bLeftImg).scaled(button_left->size()));
     button_left->setIconSize(button_left->size());
     button_left->show();
     button_left->setStyleSheet(buttonStyleSheet);
     button_left->setFocusPolicy(Qt::NoFocus);

     QPushButton *button_right = new QPushButton(this);
     connect(button_right, SIGNAL(clicked()),this, SLOT(cursorRight()));
     button_right->resize(KEY_SIZE_x, KEY_SIZE_y); // first argument is width and second is the height.
     //button_right->move(button_left->pos().rx() + button_left->width() + KEY_ODSTEP, + Z_y + KEY_ODSTEP);
     button_right->move(button_left->pos().rx() + button_left->width() + 10, + Z_y + KEY_ODSTEP);

     button_right->show();
     QImage bRightImg("gfx/keyRight.png");
     button_right->setIcon(QPixmap::fromImage(bRightImg).scaled(button_right->size()));
     button_right->setIconSize(button_right->size());
     button_right->setStyleSheet(buttonStyleSheet);
     button_right->setFocusPolicy(Qt::NoFocus);

     button_artist = new QPushButton("AUTOR",this);
     connect(button_artist, SIGNAL(clicked()),this, SLOT(searchAlbumy()));
     button_artist->resize(200, 80);
     button_artist->move(300 , 660);
     button_artist->show();
     button_artist->setStyleSheet(buttonSelectedStyleSheet);
     searchAlbumyTytuly = 1;

     button_artist->setFocusPolicy(Qt::NoFocus);

     button_tytuly = new QPushButton("TYTUŁ",this);
     connect(button_tytuly, SIGNAL(clicked()),this, SLOT(searchUtwory()));
     button_tytuly->resize(200, 80);
     button_tytuly->move(520 , 660);
     button_tytuly->show();
     button_tytuly->setStyleSheet(buttonUnSelectedStyleSheet);
     button_tytuly->setFocusPolicy(Qt::NoFocus);


     QPushButton *button_backspace = new QPushButton(this);
     connect(button_backspace, SIGNAL(clicked()),this, SLOT(slotBackspace()));
     button_backspace->resize(140, KEY_SIZE_y); // first argument is width and second is the height.
     button_backspace->move( NUM_x+KEY_ODSTEP*10,NUM_y);
     button_backspace->show();
     button_backspace->setStyleSheet(buttonStyleSheet);
     QImage bBackspaceImg("gfx/keyBackspace.png");
     button_backspace->setIcon(QPixmap::fromImage(bBackspaceImg).scaled(button_backspace->size()));
     button_backspace->setIconSize(button_backspace->size());

     button_backspace->setFocusPolicy(Qt::NoFocus);

}

void Szukaj::paintEvent(QPaintEvent *event)
{
    event=event;
    QPainter paint( this );
    paint.drawImage(QRect(0, 0, 1024, 768), SzukajImage);

    paint.end();
}

void Szukaj::wyjdz()
{
    this->hide();

    ((Window*)parentWidget())->homeScreen->show();
    ((Window*)parentWidget())->menu->show();

    szukanyTekst="";
    txtSzukany->setText(szukanyTekst);

}

void Szukaj::search()
{


    QCoreApplication::processEvents();
    if (szukanyTekst == "VOL") {
        ((Window*)parentWidget())->enterVolumeSetup();
        return;
    }

    lTrwaWyszukiwanie->setText("TRWA WYSZUKIWANIE...");
    lTrwaWyszukiwanie->show();
    repaint();

    if(searchAlbumyTytuly) {
        PrzeszukajAlbumy(MP3_PATH);
        QString naglowek = "Wyniki Wyszukiwania: " + szukanyTekst;
        albumsWidget->header->setText(naglowek);
        albumsWidget->ShowFoundAlbums(ArtistSearchResult);
    }
    else {
        TitleSearchResult.clear();
        ImageSearchResult.clear();
        PrzeszukajTytuly(MP3_PATH);
        if (TitleSearchResult.length()==0) {
            lTrwaWyszukiwanie->setText("Nic nie znaleziono");
            lTrwaWyszukiwanie->show();
            return;
        }
        else{
            ((Window*)parentWidget())->songScreen->showFoundSongs(szukanyTekst, TitleSearchResult, ImageSearchResult);
        }
    }

    this->hide();
    lTrwaWyszukiwanie->hide();
    ((Window*)parentWidget())->creditWidget->raise();
    ((Window*)parentWidget())->creditWidget->show();

    repaint();

    szukanyTekst="";
    txtSzukany->setText(szukanyTekst);
}

void Szukaj::searchAlbumy()
{
    button_artist->setStyleSheet(buttonSelectedStyleSheet);
    button_tytuly->setStyleSheet(buttonUnSelectedStyleSheet);
    searchAlbumyTytuly = 1;
}

void Szukaj::searchUtwory()
{
    button_artist->setStyleSheet(buttonUnSelectedStyleSheet);
    button_tytuly->setStyleSheet(buttonSelectedStyleSheet);
    searchAlbumyTytuly = 0;
}

void Szukaj::slotBackspace()
{
    txtSzukany->backspace();
    szukanyTekst = txtSzukany->text();
}

void Szukaj::button_clicked()
{
    QPushButton *nadawca = (QPushButton*)sender();

    for(int i=0;i<36;i++)
    {
        if(isAltActive) {
            if(nadawca->text() == keyboardAlt[i].txt) txtSzukany->insert(keyboardAlt[i].txt);    //  szukanyTekst.append(keyboard[i].txt);
        }
        else {
            if(nadawca->text() == keyboard[i].txt) txtSzukany->insert(keyboard[i].txt);    //  szukanyTekst.append(keyboard[i].txt);
        }
    }

    if(nadawca->text() == "SPACE") txtSzukany->insert(" ");
	
	szukanyTekst = txtSzukany->text();
    repaint();

    if(isAltActive) {
        isAltActive = 0;
        for(int i=0;i<36;i++)
        {
            keyboard[i].ptr->show();
            keyboardAlt[i].ptr->hide();
        }

    }
}
void Szukaj::cursorLeft()
{
    int cursorPos = txtSzukany->cursorPosition();
    cursorPos--;
    txtSzukany->cursorBackward(0,1);
    txtSzukany->setCursorPosition(cursorPos);

}
void Szukaj::cursorRight()
{
    int cursorPos = txtSzukany->cursorPosition();
    cursorPos++;
    txtSzukany->cursorForward(0,1);
    txtSzukany->setCursorPosition(cursorPos);
}


void Szukaj::PrzeszukajAlbumy(const QString& sDir)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QStringList wynik;
    QDir dir(sDir);
    QFileInfoList list = dir.entryInfoList();

    ArtistSearchResult.clear();

    for (int iList=0;iList<list.count();iList++)
    {
        QFileInfo info = list[iList];

        QString sFilePath = info.filePath();
        if (info.isDir())
        {
            QString szukanyTekstLower = szukanyTekst.toLower();
            QString nazwa_pliku = info.fileName();
            QString nazwaPlikuLower = nazwa_pliku.toLower();
            nazwaPlikuLower = nazwaPlikuLower.left(nazwaPlikuLower.indexOf("-")); //wyciecie tylko artysty przed -ani
            if (nazwaPlikuLower.contains(szukanyTekstLower) )
            {
                ArtistSearchResult.append(nazwa_pliku);
            }
        }
    }
}

void Szukaj::PrzeszukajTytuly(const QString& sDir)
{
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
                PrzeszukajTytuly(sFilePath);
            }
        }
        else
        {
            // Do something with the file here

            QString szukanyTekstLower = szukanyTekst.toLower();
            QString nazwa_pliku = info.fileName();
            QString sciezka_pliku = info.path();
            QString nazwaPlikuLower = nazwa_pliku.toLower();
            //QString text_pl = QString::fromUtf8(ptr);
            if (nazwaPlikuLower.contains(szukanyTekstLower) )
            {
                if ((nazwaPlikuLower.contains(".MP3")) ||
                    (nazwaPlikuLower.contains(".mp3")) ||
                    (nazwaPlikuLower.contains(".flac")) ||
                    (nazwaPlikuLower.contains(".FLAC"))  )
                {

                    Song piosenka;

                    piosenka.artist = "";
                    piosenka.path = info.filePath();
                    nazwa_pliku.chop(4);

                    piosenka.title = nazwa_pliku.remove(0,3); //odcinamy 3 pierwsze znaki
                    piosenka.title.truncate(piosenka.title.length()-4); //odcinamy rozszerzenie mp3

                    //piosenka.CdPath = info.path() + "/cd.png";
                    TitleSearchResult.append(nazwa_pliku);
                    ImageSearchResult.append(sciezka_pliku);

                    //m_wynikiWyszukiwania.enqueue(piosenka);

                    //if(nazwa_pliku.length() > 60)            nazwa_pliku.truncate(60);
                    //songListWidget->addItem(nazwa_pliku);

                }
            }
        }
    }
}

void Szukaj::ClearSzukanyText()
{
    szukanyTekst="";
    txtSzukany->setText(szukanyTekst);
}

int Szukaj::SearchTagsAndMakeLinks(const QString& sDir, QString fileName, QString &wynik)
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
                found=SearchTagsAndMakeLinks(sFilePath, fileName, wynik);
            }
        }
        else
        {
            // Do something with the file here

            if (info.fileName().contains(fileName))
            {


                 //wynik=info.filePath();
//                 QProcess *p = new QProcess();
//                 QString makeLink = "ln -s \"";
                 QString targetPath = info.path();
                 //targetPath.append("\"");
                 //targetPath.prepend("\"");
                 QString PlaceToPut = "/home/szafa/KATEGORIE/" + fileName + targetPath.mid(targetPath.lastIndexOf("/"));


                if (false==QFile::link(targetPath, PlaceToPut)) {
                    QByteArray text = "/bin/ln -s \"";
                    //QFile::FileError err= testFile.error();
                }



//                QProcess *sh = new QProcess();
//                 sh->start("sh");
//                 sh->write(text);
//                 sh->waitForFinished();
//                QByteArray output = sh->readAll();
//                sh->close();

            }
        }
    }
    return found;
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

int Szukaj::SearchSong(const QString& sDir, QString fileName, QString &wynik)
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
                found=SearchSong(sFilePath, fileName, wynik);
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

void Szukaj::alt_clicked()
{
    if(isAltActive) {
        isAltActive=0;
        for(int i=0;i<36;i++)
        {
            keyboard[i].ptr->show();
            keyboardAlt[i].ptr->hide();
        }

    }
    else {
        isAltActive=1;
        for(int i=0;i<36;i++)
        {
            keyboardAlt[i].ptr->show();
            keyboard[i].ptr->hide();
        }
    }

}
