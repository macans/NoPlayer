#ifndef PLAYCTRLWIDGET_H
#define PLAYCTRLWIDGET_H


#include <QWidget>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QAbstractButton>
#include <QToolButton>
#include <QPushButton>
#include <QStyle>
#include <QSlider>
#include <QLabel>
#include <QTime>
#include <QBoxLayout>

class PlayControls : public QWidget
{
	Q_OBJECT
public:
	explicit PlayControls(QWidget *parent = 0);
	
	bool isPosInRect(const QPoint &pos, const QRect &rect);
signals :
	void play();
	void pause();
	void stop();
	void next();
	void previous();
	void open();
	void fastforword(int msec = 0);
	void rewind(int msec = 0);
	void changeVolume(int);
	void changeMuting(bool);
	void playlistButtonClicked();
	void controlButtonClicked();
	void searchButtonClicked();
	void seek(int progress);
public slots:
	void setState(const QMediaPlayer::State state);
	void setVolume(int volume);
	void setMuted(bool muted);
	void setDuration(qint64 duration);
	void positionChanged(qint64 progress);
	void durationChanged(qint64 duration);
	void updateDurationInfo(qint64 currentInfo);

private slots:
	void playClicked();
	void muteClicked();
	void  mousePressEvent(QMouseEvent *event);


private:
	QAbstractButton *playButton;
	QAbstractButton *stopButton;
	QAbstractButton *nextButton;
	QAbstractButton *previousButton;
	QAbstractButton *muteButton;
	QAbstractButton *openButton;
	QAbstractButton *playlistButton;
	QAbstractButton *controlButton;
	QAbstractButton *searchButton;
	QAbstractSlider *volumeSlider;
	QSlider *slider;
	QLabel *labelDuration;
	QMediaPlayer::State playerState;
	bool playerMuted;
	qint64 duration;
};

#endif // PLAYCTRLWIDGET_H
