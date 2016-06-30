#include "mainwindow.h"
#include "playcontrols.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	//PlayControls w;
    w.show();

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
		打开Youtube 视频链接并播放
		解析字幕文件，同步设置

	待讨论
		打开最近播放
*/
