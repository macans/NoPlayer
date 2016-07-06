#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define PLAYLOOP	0x01
#define PLAYORDER	0x02
#define PLAYSINGLE	0x03
#define PLAYRANDOM	0x04

#define PLAY_MUSIC	0x00
#define PLAY_VIDEO	0x01

#define VOLUME_STEP	10
#define VOLUME_MAX	100
#define VOLUME_MIN	0

#define PLAYRATE_STEP	0.1
#define PLAYRATE_INIT	1
#define PLAYRATE_MIN	0.2

#define SUBDELAY_STEP	500

#define MODEL_LAC		1
#define MODEL_NET		0

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QBoxLayout>
#include <QGridLayout>
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
#include "playlistwindow.h"
#include "playconfig.h"
#include "subtitlelabel.h"
#include "searchwindow.h"
#include "aboutwidget.h"
#include "propertywidget.h"


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
	void closeEvent(QCloseEvent *event);
	//自定义函数
    void updateWindowSize();
	bool isPosInRect(const QPoint &pos, const QRect &rect);
	void initPlayWidget(int isVideo, int isLocal, QString info = "", QString lrclink = "");
	void savePlayConfig();
	void savePlayList();
	void raiseVolume(int step);
	void raiseSubtitleDelay(qint64 step);
	void raisePlaybackRate(qreal step);
	void initPlaybackRate();
	void loadLocalConfig();
	void initLayout();

	//右键功能
	void openFolder();
	void changeScreen();
	void showProperty();
	void loadURLs();
	void showAbout();
	void quitMedia();
	void playFile(const QString &);
	void contextMenuEvent(QContextMenuEvent *event);
	void setTheMenu();
	void getMediaList(QString path);

public slots:
	//播放列表
	void itemDoubleClicked(QListWidgetItem *item, bool doubleClicked);

	//控制面板
	void fontChanged(QFont font);
	void colorChanged(QColor color);

	void rateSlowDown();
	void rateSpeedUp();
	//搜索
	void getInfoComplete(bool flag, InfoNetMusic &info);

	//控制栏
	void nextClicked();
	void previousClicked();
	void fastforword(int msec = 1000);
	void rewind(int msec = 0);
	void openFile();
	void controlButtonClicked();
	void searchButtonClicked();
	void playlistButtonClicked();
	void seek(int seconds);
	
	//MediaPlayer
	void mediaStatusChanged(QMediaPlayer::MediaStatus status);

	//PlayWidget
	

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
	SubtitleLabel *subLabel;
	QSize wndSize;
	PlayConfig *playConfig;

	bool mousePressed;
	bool playlistState;
	bool searchState;
	bool controlState;
	bool menuState;
	int curPlayFlag;
	QStringList typeAllowed;
	QHBoxLayout *displayLayout, *controlLayout, *subLabelLayout;
	QVBoxLayout *layout;
    QGridLayout *grid;

	//右键菜单
	QMenu *pop_menu;
	QAction *file_action;
	QAction *folder_action;
	QAction *word_action;
	QAction *screen_action;
	QAction *nature_action;
	QAction *URLs_action;
	QAction *about_action;
	QAction *quit_action;

	AboutWidget *about = new AboutWidget();
	PropertyWidget *property = new PropertyWidget();
};

#endif // MAINWINDOW_H
