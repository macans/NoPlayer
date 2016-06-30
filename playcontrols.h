#ifndef PLAYCTRLWIDGET_H
#define PLAYCTRLWIDGET_H


#include <QWidget>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QAbstractButton>
#include <QToolButton>
#include <QStyle>
#include <QSlider>
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
	void fastforword();
	void rewind();
	void changeVolume(int);
	void changeMuting(bool);
	void playlistButtonClicked();

public slots:
	void setState(const QMediaPlayer::State state);
	void setVolume(int volume);
	void setMuted(bool muted);

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
	QAbstractSlider *volumeSlider;
	QMediaPlayer::State playerState;
	bool playerMuted;
};

#endif // PLAYCTRLWIDGET_H
