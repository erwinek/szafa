#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>
#include <QtGui>

class Credit : public QWidget
{
    Q_OBJECT
public:
    explicit Credit(QWidget *parent = 0);
    bool isCredit();
    void decrCredit();
    void incrCredit();
    quint16 getCredit();
    void setCredit(quint16 Kredyt);
    int KaraokeCredit;

private:
    QLabel *labelCredit;
    quint16 Kredyt;

signals:
    
public slots:
    
};

#endif // CREDIT_H
