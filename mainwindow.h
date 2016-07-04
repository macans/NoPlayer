#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define PLAYLOOP	0x01
#define PLAYORDER	0x02
#define PLAYSINGLE	0x03
#define PLAYRANDOM	0x04

#define PLAY_MUSIC	true
#define PLAY_VIDEO	false

#define VOLUME_STEP	10
#define VOLUME_MAX	100
#define VOLUME_MIN	0

#define PLAYRATE_STEP	0.1
#define PLAYRATE_INIT	1
#define PLAYRATE_MIN	0.2

#define SUBDELAY_STEP	500

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QBoxLayout>
#include <QAbstractItemView>
#include <QListView>
#include <QFileDialog>
#include <QPixmap>
#include <QMenu>
#include <QListWidget>


#include "videowidget.h"
#include "playcontrols.h"
#include "controlwindow.h"
#include "musicwidget.h"
#include "menuwidget.h"
#include "playlistwindow.h"
#include "playconfig.h"
#include "subtitlelabel.h"
#include "searchwindow.h"


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	//继承的响应事件
	void resizeEvent(QResizeEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void loadLocalConfig();
	//自定义函数
    void updateWindowSize();
	bool isPosInRect(const QPoint &pos, const QRect &rect);
	void initPlayWidget(int flag);
	void savePlayConfig();
	void savePlayList();
	void raiseVolume(int step);
	void raisePlaybackRate(qreal step);
	void raiseSubtitleDelay(qint64 step);
	void initPlaybackRate();
public slots:
	//播放列表
	void itemDoubleClicked(QListWidgetItem *item);
	//控制面板
	void fontChanged(QFont font);
	void colorChanged(QColor color);

	//搜索
	void getInfoComplete(bool flag, QString info, QString link);

	//控制栏
	void nextClicked();
	void previousClicked();
	void fastforword(int msec = 0);
	void rewind(int msec = 0);
	void openFile();
	void controlButtonClicked();
	void searchButtonClicked();
	void playlistButtonClicked();
	void seek(int seconds);
	
	//MediaPlayer
	void mediaStatusChanged(QMediaPlayer::MediaStatus status);

	//PlayWidget
	void openMenu(QPoint pos);

	//主界面
	void changeEvent(QEvent *event);
private:
	QWidget *playWidget;
	QMediaPlayer *player;
	QMediaPlaylist *playList;
	PlaylistWindow *playlistWindow;
	PlayControls *controls;
	ControlWindow *controlWindow;
	SearchWindow *searchWindow;
	MenuWidget *menuWidget;
	SubtitleLabel *subLabel;
	QSize wndSize;
	PlayConfig *playConfig;

	bool mousePressed;
	bool playlistState;
	bool searchState;
	bool controlState;
	bool menuState;
	bool curPlayFlag;
	QHBoxLayout *displayLayout, *controlLayout;
	QVBoxLayout *layout;
};

#endif // MAINWINDOW_H
