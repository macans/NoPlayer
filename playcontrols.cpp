#include "playcontrols.h"

PlayControls::PlayControls(QWidget *parent) :QWidget(parent)
{
	playerMuted = 0;
	playButton = new QToolButton(this);
	playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	connect(playButton, SIGNAL(clicked()), this, SLOT(playClicked()));

	stopButton = new QToolButton(this);
	stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
	stopButton->setEnabled(false);
	connect(stopButton, SIGNAL(clicked()), this, SIGNAL(stop()));

	nextButton = new QToolButton(this);
	nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
	connect(nextButton, SIGNAL(clicked()), this, SIGNAL(next()));

	previousButton = new QToolButton(this);
	previousButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
	connect(previousButton, SIGNAL(clicked()), this, SIGNAL(previous()));
	
	openButton = new QToolButton(this);
	openButton->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
	connect(openButton, SIGNAL(clicked()), this, SIGNAL(open()));

	muteButton = new QToolButton(this);
	muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
	connect(muteButton, SIGNAL(clicked()), this, SLOT(muteClicked()));

	volumeSlider = new QSlider(Qt::Horizontal, this);
	volumeSlider->setRange(0, 100);
	connect(volumeSlider, SIGNAL(valueChanged(int)), this, SIGNAL(changeVolume(int)));

	playlistButton = new QToolButton(this);
	playlistButton->setWindowIcon(style()->standardIcon(QStyle::SP_ComputerIcon));
	connect(playlistButton, SIGNAL(clicked()), this, SIGNAL(playlistButtonClicked()));
	QBoxLayout *layout = new QHBoxLayout;
	layout->setMargin(0);
	layout->addWidget(openButton);
	layout->addWidget(playlistButton);
	layout->addWidget(stopButton);
	layout->addWidget(previousButton);
	layout->addWidget(playButton);
	layout->addWidget(nextButton);
	layout->addWidget(muteButton);
	layout->addWidget(volumeSlider);
	setLayout(layout);
}

void PlayControls::setVolume(int volume)
{
	volumeSlider->setValue(volume);
}

void PlayControls::playClicked()
{
	switch (playerState){
	case QMediaPlayer::PlayingState:
		emit pause();
		break;
	case QMediaPlayer::PausedState:
		emit play();
		break;
	}
}

void PlayControls::mousePressEvent(QMouseEvent *event)
{
	QRect rect;
	if (event->button() == Qt::RightButton){
		const QPoint &pos = event->pos();
		rect = playButton->geometry();
		if (isPosInRect(pos, nextButton->geometry())){
			//ÓÒ¼ü nextButton ¿ì½ø
			emit fastforword();
		}
		else if (isPosInRect(pos, previousButton->geometry())){
			//ÓÒ¼ü previousButton ¿ìÍË
			emit rewind();
		}
	}
}

bool PlayControls::isPosInRect(const QPoint &pos, const QRect &rect)
{
	if (pos.x() >= rect.x() && pos.x() <= rect.x() + rect.width()
		&& pos.y() >= rect.y() && pos.y() <= rect.y() + rect.height()){
		return true;
	}
	return false;
}

void PlayControls::setState(const QMediaPlayer::State state)
{
	if (state != playerState) {
		playerState = state;
		switch (state) {
		case QMediaPlayer::StoppedState:
			stopButton->setEnabled(false);
			playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
			break;
		case QMediaPlayer::PlayingState:
			stopButton->setEnabled(true);
			playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
			break;
		case QMediaPlayer::PausedState:
			stopButton->setEnabled(true);
			playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
			break;
		}
	}
}

void PlayControls::muteClicked()
{
	emit changeMuting(!playerMuted);
}

void PlayControls::setMuted(bool muted)
{
	if (muted != playerMuted) {
		this->playerMuted = muted;
		muteButton->setIcon(style()->standardIcon(muted
			? QStyle::SP_MediaVolumeMuted
			: QStyle::SP_MediaVolume));
	}
}


