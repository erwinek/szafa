#ifndef STATS_H
#define STATS_H

#include <QWidget>
#include <QtGui>
#include "image.h"

class Stats : public QWidget
{
    Q_OBJECT
public:
    explicit Stats(QWidget *parent = 0);
    void SaveSongHistory(QString songTitle);
    void incrSongStats(QString songTitle);
    void addSongToStatFile(QString title);
    QSettings *statsFile;
    QStringList *strListSongsStat;
private:
    QSettings *songStatsFile;
    QSettings *songHistoryFile;
    QListWidget *listSongStat;
    QListWidget *listAlbumsStat;
    QStringList *stringListAlbumsPlayed;    
    QListWidget *listNotPlayed;
    QListWidget *listHistory;
    void resetStats(QSettings *settings);
    Image *background;
    bool SearchFile(const QString& sDir, QString fileName, QString &wynik);
    void fillAlbumList();
    void fillSongList();
    void fillHistoryList();
    void fillNotPlayedList();
signals:
    
private slots:
    void showAlbums();
    void showNotPlayed();
    void showHistory();
    void showSongs();
    void exit();
    void sortByName();
    void sortByPlay ();
    
};

#endif // STATS_H
