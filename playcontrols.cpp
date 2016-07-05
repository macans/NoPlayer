#include "playcontrols.h"

PlayControls::PlayControls(QWidget *parent) :QWidget(parent)
{
	playerMuted = 0;
    playButton = new QPushButton(this);
     playButton->setObjectName("playButton");
    //playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playButton, SIGNAL(clicked()), this, SLOT(playClicked()));

    stopButton = new QPushButton(this);
    stopButton->setObjectName("stopButton");
    //stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setEnabled(false);
    connect(stopButton, SIGNAL(clicked()), this, SIGNAL(stop()));

    nextButton = new QPushButton(this);
    nextButton->setObjectName("nextButton");
    //nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    connect(nextButton, SIGNAL(clicked()), this, SIGNAL(next()));

    previousButton = new QPushButton(this);
    previousButton->setObjectName("previousButton");
    //previousButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    connect(previousButton, SIGNAL(clicked()), this, SIGNAL(previous()));

    openButton = new QPushButton(this);
    openButton->setObjectName("openButton");
    //openButton->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
    connect(openButton, SIGNAL(clicked()), this, SIGNAL(open()));

    muteButton = new QPushButton(this);
    muteButton->setObjectName("muteButton");
    //muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    connect(muteButton, SIGNAL(clicked()), this, SLOT(muteClicked()));

    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    connect(volumeSlider, SIGNAL(valueChanged(int)), this, SIGNAL(changeVolume(int)));

    searchButton = new QPushButton(this);
      searchButton->setObjectName("searchButton");
    connect(searchButton, SIGNAL(clicked()), this, SIGNAL(searchButtonClicked()));

    playlistButton = new QPushButton(this);
    playlistButton->setObjectName("playlistButton");
    //playlistButton->setWindowIcon(style()->standardIcon(QStyle::SP_ComputerIcon));
    connect(playlistButton, SIGNAL(clicked()), this, SIGNAL(playlistButtonClicked()));

    controlButton = new QPushButton(this);
    controlButton->setObjectName(tr("controlButton"));
    //controlButton->setWindowIcon(style()->standardIcon(QStyle::SP_DialogOkButton));
    connect(controlButton, SIGNAL(clicked()), this, SIGNAL(controlButtonClicked()));

	slider = new QSlider(Qt::Horizontal, this);
	connect(slider, SIGNAL(sliderMoved(int)), this, SIGNAL(seek(int)));
	labelDuration = new QLabel(this);
	QBoxLayout *slidersLayout = new QHBoxLayout;
	slidersLayout->addWidget(slider, 2);
	slidersLayout->addWidget(muteButton);
	slidersLayout->addWidget(volumeSlider);

	QBoxLayout *widgetsLayout = new QHBoxLayout;
	widgetsLayout->setMargin(0);
	widgetsLayout->addWidget(playButton);
	widgetsLayout->addWidget(stopButton);
	widgetsLayout->addWidget(previousButton);
	widgetsLayout->addWidget(nextButton);
	widgetsLayout->addWidget(openButton);
	widgetsLayout->addWidget(labelDuration);
	widgetsLayout->addWidget(searchButton);
	widgetsLayout->addWidget(playlistButton);
	widgetsLayout->addWidget(controlButton);
	
	QBoxLayout *layout = new QVBoxLayout;
	layout->addLayout(slidersLayout);
	layout->addLayout(widgetsLayout);
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

void PlayControls::setDuration(qint64 duration)
{
	if (slider){
		this->duration = duration;
		slider->setRange(0, duration / 1000);
	}
}

void PlayControls::positionChanged(qint64 progress)
{
	if (!slider->isSliderDown()) {
		slider->setValue(progress / 1000);
	}
	updateDurationInfo(progress / 1000);
}

void PlayControls::updateDurationInfo(qint64 currentInfo)
{
	QString tStr;
	if (currentInfo || duration) {
		QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60, currentInfo % 60, (currentInfo * 1000) % 1000);
		QTime totalTime((duration / 3600) % 60, (duration / 60) % 60, duration % 60, (duration * 1000) % 1000);
		QString format = "mm:ss";
		if (duration > 3600)
			format = "hh:mm:ss";
		tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
	}
	labelDuration->setText(tStr);
}

void PlayControls::durationChanged(qint64 duration)
{
	this->duration = duration / 1000;
	slider->setMaximum(duration / 1000);
}


