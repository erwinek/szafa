#include "credit.h"
#include "window.h"

Credit::Credit(QWidget *parent) :
    QWidget(parent)
{
    KaraokeCredit = 1;
    QImage imageBackground("gfx/credit.png");
    QString styleLabelCredit;
    styleLabelCredit = styleLabelCredit.sprintf("QLabel { \
        background-color: rgba(10,20,30,0); \
        font: bold 60px; \
        color: white;\
        background-image: url(gfx/credit.png);\
    }");

    labelCredit = new QLabel(this);
    labelCredit->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelCredit->setText(QString::number(Kredyt));
    labelCredit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    labelCredit->resize(imageBackground.size());
    labelCredit->show();
    labelCredit->setStyleSheet(styleLabelCredit);

    Kredyt = ((Window*)parentWidget())->settings->value("Setup/Credit").toInt();

    labelCredit->setText(QString::number(Kredyt));

    this->move(1024-122,768-116);
    if (((Window*)parentWidget())->setup->freePlayOnOff) this->hide();
    else this->show();
}

bool Credit::isCredit()
{
    if(Kredyt>0) return true;
    return false;
}
void Credit::decrCredit()
{
    if (Kredyt>0) Kredyt--;
    qWarning() << "decrCredit Kredyt=" << Kredyt;
    ((Window*)parentWidget())->settings->setValue("Setup/Credit", Kredyt);
    ((Window*)parentWidget())->serialPort->decrCredit++;
    labelCredit->setText(QString::number(Kredyt));
}

void Credit::incrCredit()
{
    Kredyt++;
    qWarning() << "incrCredit Kredyt=" << Kredyt;
    ((Window*)parentWidget())->settings->setValue("Setup/Credit", Kredyt);
    ((Window*)parentWidget())->serialPort->incrCredit++;
    labelCredit->setText(QString::number(Kredyt));
    ((Window*)parentWidget())->slideshowScreen->resetCounter();
}
void Credit::incrLimited()
{
    qWarning() << "incrCredit Kredyt=" << Kredyt;
    uint32_t limit=0;
    limit = ((Window*)parentWidget())->settings->value("Setup/CreditsToday").toInt();
    qWarning() << "limit=" << limit;
    if(limit==0) {

        QString setup = ((Window*)parentWidget())->settings->value("Setup/CreditDayLimitDate").toString();
        QString curr = QDate::currentDate().toString();
        qWarning() << "setup date=" << setup;
        qWarning() << "curr date=" << curr;
        if ( setup != curr ) {
            limit = ((Window*)parentWidget())->settings->value("Setup/CreditDayLimit", 5).toInt();
           ((Window*)parentWidget())->settings->setValue("Setup/CreditsToday", limit);
        }
    }

    if (limit > 0) {
        Kredyt++;
        limit--;
        ((Window*)parentWidget())->serialPort->incrCredit++;
        labelCredit->setText(QString::number(Kredyt));
        ((Window*)parentWidget())->slideshowScreen->resetCounter();
        ((Window*)parentWidget())->settings->setValue("Setup/CreditDayLimitDate", QDate::currentDate().toString().toAscii().data());
    }
    ((Window*)parentWidget())->settings->setValue("Setup/CreditsToday", limit);
}

quint16 Credit::getCredit()
{
    qWarning() << "getCredit Kredyt=" << Kredyt;
    return Kredyt;
}

void Credit::setCredit(quint16 newKredyt)
{
    if (((Window*)parentWidget())->setup->freePlayOnOff) this->hide();
    if (Kredyt!=newKredyt) {
        ((Window*)parentWidget())->slideshowScreen->resetCounter();
        Kredyt=newKredyt;
        qWarning() << "setCredit Kredyt=" << Kredyt;
        ((Window*)parentWidget())->settings->setValue("Setup/Credit", Kredyt);
        labelCredit->setText(QString::number(Kredyt));
    }
}
