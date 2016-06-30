#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QMouseEvent>
#include <QBoxLayout>
#include <QAbstractItemView>
#include <QListView>
#include <QFileDialog>
#include "videowidget.h"
#include "playcontrols.h"
#include "playlistmodel.h"
#include "ControlWidget.h"
namespace Ui {
class MainWindow;
}

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
    Ui::MainWindow *ui;
	QSize wndSize;
	bool mousePressed;
	bool playlistState;
	bool controlState;
};

#endif // MAINWINDOW_H
