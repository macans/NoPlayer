#include "mainwindow.h"
#include "playcontrols.h"
#include "controlwindow.h"
#include "musicwidget.h"
#include "subtitlelabel.h"
#include "searchwindow.h"

#include <QApplication>
#include <QTextCodec>
#include <QMediaPlaylist>
#include <QNetworkReply>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv); 
    //QMediaPlayer *musicplayer = new QMediaPlayer;
    //musicplayer->setMedia(QUrl::fromLocalFile("E:\\QTproject\\music.mp3"));
    //MusicWidget w(0,musicplayer);
    MainWindow w;
	//SearchWindow w;
   // PlayControls w;
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForLocale(codec);
	//ControWindow w;
    w.show();
	QString qss;
    QFile qssFile(":/default.qss");
	qssFile.open(QFile::ReadOnly);
	if (qssFile.isOpen()){
		qss = QLatin1String(qssFile.readAll());
		qApp->setStyleSheet(qss);
		qssFile.close();
	}
   /* 
   QMediaPlayer *musicplayer = new QMediaPlayer;
    //musicplayer->setMedia(QUrl::fromLocalFile("E:\\QTproject\\238976206.mp3"));
    musicplayer->setMedia(QUrl("http://yinyueshiting.baidu.com/data2/music/238976206/8775781467622861128.mp3?xcode=d1e1ecd2f82fa083554bf4edd997f8d2"));
    QString lrclink = "http://musicdata.baidu.com/data2/lrc/238975978/238975978.lrc";
    //MusicWidget w(songinfo,lrclink,0,musicplayer);
    //MusicWidget w(0,musicplayer);
    //MainWindow w;
    //PlayControls w;
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForLocale(codec);
	//ControlWidget w;
    //w.show();
	//>>>>>>> origin/willqi
*/

    return a.exec();
}

/*
	所有的界面类公用同一个 QMediaPlayer
	音量控制 上/下一个 快进快退 都是 QMediaPlayer 直接控制，通过 VideoOutput 体现出来
	更换音频时，QMedia撤销 VideoOuput，更改Playlist和media，改为显示 MusicWidget

	主界面要有播放列表信息 QMediaPlaylist

	主界面
		暂停，快进，快退，上一个，下一个，音量操作，打开控制面板，打开播放列表
		右键响应弹出

	核心
		解析字幕文件，同步设置
		网络搜索		
			利用 网易云音乐API 搜索音乐并播放
			利用 BING API 搜索视频并播放

	最后界面改良也是一个大问题
	待讨论
		打开最近播放
*/
   /* QMediaPlaylist *playlist = new QMediaPlaylist;
    QMediaPlayer *musicPlayer = new QMediaPlayer;
    playlist->addMedia(QUrl::fromLocalFile("E:\\QTproject\\Adele - Hello.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("E:\\QTproject\\test.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("E:\\QTproject\\music.mp3"));
    musicPlayer->setPlaylist(playlist);
    MusicWidget w(0,musicPlayer);
    w.show();
    return a.exec();*/
