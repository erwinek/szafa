#ifndef SZUKAJ_H
#define SZUKAJ_H
#include <QtGui>
#include <QWidget>
#include "folder.h"

class Szukaj : public QWidget
{
    Q_OBJECT
public:
    int SearchFile(const QString& sDir, QString fileName, QString &wynik);
    QListWidget *listWidget;
    explicit Szukaj(QWidget *parent = 0);
    struct Keyboard
    {
        QPushButton *ptr;
        QString txt;
        int pos_x;
        int pos_y;
    };
    QPushButton *buttonPlay;
    QQueue<Song> m_wynikiWyszukiwania;
signals:
    
public slots:
private:
    QString szukanyTekst;
    QImage SzukajImage;

    Keyboard ptr_keyboard;
    void RecurseDirectory(const QString& sDir);

protected:
    void paintEvent(QPaintEvent *event);


private slots:
    void search();
    void button_clicked();

    
};


#endif // SZUKAJ_H
