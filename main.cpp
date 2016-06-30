#include "mainwindow.h"
#include "musicwidget.h"
#include <QApplication>
#include <QMediaPlaylist>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMediaPlaylist *playlist = new QMediaPlaylist;
    QMediaPlayer *musicPlayer = new QMediaPlayer;
    playlist->addMedia(QUrl::fromLocalFile("E:\\QTproject\\Adele - Hello.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("E:\\QTproject\\test.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("E:\\QTproject\\music.mp3"));
    musicPlayer->setPlaylist(playlist);
    MusicWidget w(0,musicPlayer);
    w.show();
    return a.exec();
}
