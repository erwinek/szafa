#ifndef SZUKAJ_H
#define SZUKAJ_H
#include <QtGui>
#include <QWidget>
#include "folder.h"
#include "albums.h"
#include "songs.h"

class Szukaj : public QWidget
{
    Q_OBJECT
public:
    QImage SzukajImage;
    int SearchFile(const QString& sDir, QString fileName, QString &wynik);
    static int SearchSong(const QString& sDir, QString fileName, QString &wynik);
    int SearchTagsAndMakeLinks(const QString& sDir, QString fileName, QString &wynik);
    QLineEdit *txtSzukany;
    void ClearSzukanyText();
    explicit Szukaj(QWidget *parent = 0, Albums *albumsScreen = 0, Songs *songsScreen = 0);
    struct Keyboard
    {
        QPushButton *ptr;
        QString txt;
        int pos_x;
        int pos_y;
    };
    //QPushButton *buttonPlay;
    QQueue<Song> m_wynikiWyszukiwania;
    QLabel *lTrwaWyszukiwanie;
    QString szukanyTekst;
signals:
    
public slots:
private:

    bool isAltActive;
    QStringList ArtistSearchResult;
    QStringList TitleSearchResult;
    QStringList ImageSearchResult;
    Albums *albumsWidget;
    Songs *songsWidget;
    bool searchAlbumyTytuly;
    QString styleListWidget;

//    Keyboard ptr_keyboard;
    void PrzeszukajAlbumy(const QString& sDir);
    void PrzeszukajTytuly(const QString& sDir);
    QPushButton *button_artist;
    QPushButton *button_tytuly;
    QString buttonSelectedStyleSheet;
    QString buttonUnSelectedStyleSheet;
    QString buttonStyleSheet;

protected:
    void paintEvent(QPaintEvent *event);


private slots:
    void search();
    void searchAlbumy();
    void searchUtwory();
    void button_clicked();
    void slotBackspace();
    void wyjdz();
    void cursorLeft();
    void cursorRight();
    void alt_clicked();
    
};


#endif // SZUKAJ_H
