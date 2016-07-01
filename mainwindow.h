#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define PLAYLOOP	0x01
#define PLAYORDER	0x02
#define PLAYSINGLE	0x03
#define PLAYRANDOM	0x04

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

#include "videowidget.h"
#include "playcontrols.h"
#include "playlistmodel.h"
#include "ControlWidget.h"
#include "musicwidget.h"

class PlayConfig{
private:
	int sec_forword;
	int sec_rewind;
	int rate;
	QString lastPlayedName;
	int playMethod;
	
public:
	int Sec_forword() const { return sec_forword; }
	void Sec_forword(int val) { sec_forword = val; }

	int Sec_rewind() const { return sec_rewind; }
	void Sec_rewind(int val) { sec_rewind = val; }

	int Rate() const { return rate; }
	void Rate(int val) { rate = val; }

	QString LastPlayedName() const { return lastPlayedName; }
	void LastPlayedName(QString val) { lastPlayedName = val; }

	int PlayMethod() const { return playMethod; }
	void PlayMethod(int val) { playMethod = val; }
};

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
private slots:
	void playlistButtonClicked();
	void mediaStatusChanged(QMediaPlayer::MediaStatus status);
	void nextClicked();
	void previousClicked();
	void fastforword();
	void rewind();
	void openFile();
	void controlButtonClicked();
	void jump(const QModelIndex &index);
	void seek(int seconds);
private:
	QWidget *playWidget;
	QMediaPlayer *player;
	QMediaPlaylist *playlist;
	QAbstractItemView *playlistView;
	PlaylistModel *playlistModel;
	PlayControls *controls;
	ControlWidget *controlWidget;
	QSize wndSize;
	PlayConfig *playConfig;
	bool mousePressed;
	bool playlistState;
	bool controlState;
};

#endif // MAINWINDOW_H
