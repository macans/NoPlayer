#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define PLAYLOOP	0x01
#define PLAYORDER	0x02
#define PLAYSINGLE	0x03
#define PLAYRANDOM	0x04

#define PLAY_MUSIC	0x01
#define PLAY_VIDEO	0x02

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QMouseEvent>
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
	void loadLocalConfig();
	//自定义函数
    void updateWindowSize();
	bool isPosInRect(const QPoint &pos, const QRect &rect);
	void addToPlaylist(QStringList fileNames);
	void initPlayWidget(int flag);
public slots:
	void getInfoComplete(bool flag, QString info, QString link);
	void playlistButtonClicked();
	void mediaStatusChanged(QMediaPlayer::MediaStatus status);
	void nextClicked();
	void previousClicked();
	void fastforword(int msec = 0);
	void rewind(int msec = 0);
	void openFile();
	void controlButtonClicked();
	void searchButtonClicked();
	void jump(const QModelIndex &index);
	void seek(int seconds);
	void openMenu(QPoint pos);
private:
	QWidget *playWidget;
	QMediaPlayer *player;
	QMediaPlaylist *playList;
	QListWidget *playlistWidget;
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
	QHBoxLayout *displayLayout, *controlLayout;
	QVBoxLayout *layout;
};

#endif // MAINWINDOW_H
