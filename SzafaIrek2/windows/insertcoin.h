#ifndef INSERTCOIN_H
#define INSERTCOIN_H

#include <QWidget>
#include <QtGui>

class InsertCoin : public QWidget
{
    Q_OBJECT
public:
    explicit InsertCoin(QWidget *parent = 0);
private:
    QLabel *lTextLabel;
    QLabel *lWrzucMonete;
    QLabel *lInsertCoinGfx;
    QLabel *lAdvert;

    QTimer *tInsertCoin;

signals:
    
private slots:
    void blinkWrzucMonete();
    
};

#endif // INSERTCOIN_H
