#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{

	searchState = false;
	playlistState = false;
	mousePressed = false;
	controlState = false;
	menuState = false;
	loadLocalConfig();

	playWidget = NULL;
	player = new QMediaPlayer(this);
	playList = new QMediaPlaylist();
	player->setPlaylist(playList);
	player->setMedia(QUrl::fromLocalFile("E:\\test.mkv"));
	
	//播放视频
	playWidget = new VideoWidget(this);
	//playWidget = new MusicWidget(this, player);
	player->setVideoOutput((QVideoWidget*)playWidget);

	player->setVolume(50);
	player->play();

	playlistWidget = new QListWidget;

	connect(playlistWidget, SIGNAL(activated(QModelIndex)), this, SLOT(jump(QModelIndex)));
	connect(playlistWidget, SIGNAL(closeEvent(QCloseEvent*)), this, SLOT(playlistButtonClicked()));

	//下方控制块
	controls = new PlayControls(this);
	controls->setDuration(player->duration());
	controls->setVolume(player->volume());
	controls->setState(player->state());
	connect(controls, SIGNAL(play()), player, SLOT(play()));
	connect(controls, SIGNAL(pause()), player, SLOT(pause()));
	connect(controls, SIGNAL(stop()), player, SLOT(stop()));
	connect(controls, SIGNAL(next()), this, SLOT(nextClicked()));
	connect(controls, SIGNAL(previous()), this, SLOT(previousClicked()));
	connect(controls, SIGNAL(fastforword()), this, SLOT(fastforword()));
	connect(controls, SIGNAL(rewind()), this, SLOT(rewind()));
	connect(controls, SIGNAL(open()), this, SLOT(openFile()));
	connect(controls, SIGNAL(changeVolume(int)), player, SLOT(setVolume(int)));
	connect(controls, SIGNAL(changeMuting(bool)), player, SLOT(setMuted(bool)));
	connect(controls, SIGNAL(searchButtonClicked()), this, SLOT(searchButtonClicked()));
	connect(controls, SIGNAL(playlistButtonClicked()), this, SLOT(playlistButtonClicked()));
	connect(controls, SIGNAL(controlButtonClicked()), this, SLOT(controlButtonClicked()));
	connect(controls, SIGNAL(seek(int)), this, SLOT(seek(int)));
	
	//controls->hide();
	
	subLabel = new SubtitleLabel(this, playConfig);
	subLabel->subtitleChanged();

	controlWindow = new ControWindow;
	//controlWindow;
	connect(controlWindow, SIGNAL(controlWindowClosed()), this, SLOT(controlButtonClicked()));
	connect(controlWindow, SIGNAL(fontChanged(QFont)), subLabel, SLOT(fontChanged(QFont)));
	connect(controlWindow, SIGNAL(colorChanged(QColor)), subLabel, SLOT(colorChanged(QColor)));
	connect(controlWindow, SIGNAL(subtitleChanged(QString)), subLabel, SLOT(subtitleChanged(QString)));
	controlWindow->hide();
	//connect(controlWindow, SIGNAL())
	
	menuWidget = new MenuWidget;
	menuWidget->hide();

	searchWindow = new SearchWindow;
	searchWindow->hide();
	connect(searchWindow, SIGNAL(getInfoComplete(QString)), this, SLOT(getInfoComplete(QString)));

	connect(player, SIGNAL(positionChanged(qint64)), subLabel, SLOT(updateSubTitle(qint64)));
	connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
	connect(player, SIGNAL(positionChanged(qint64)), controls, SLOT(positionChanged(qint64)));
	connect(player, SIGNAL(durationChanged(qint64)), controls, SLOT(durationChanged(qint64)));
	connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), controls, SLOT(setState(QMediaPlayer::State)));
	connect(player, SIGNAL(mutedChanged(bool)), controls, SLOT(setMuted(bool)));

	//布局
	displayLayout = new QHBoxLayout;
	displayLayout->addWidget(playWidget);
	playlistWidget->hide();

	controlLayout = new QHBoxLayout;
	controlLayout->addWidget(controls);
	QHBoxLayout *subLayout = new QHBoxLayout;
	subLayout->addWidget(subLabel);
	//controlLayout->addStretch(1);

	layout = new QVBoxLayout;
	layout->setMargin(0);
	layout->addLayout(displayLayout, 2);
	layout->addLayout(subLayout);
	layout->addLayout(controlLayout);
	this->setLayout(layout);


	this->mousePressed = false;
	this->setWindowTitle("NoPlayer");
	//this->setWindowIcon();
	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setMouseTracking(true);
	this->resize(QSize(400, 320));
}

MainWindow::~MainWindow()
{
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){

    }
	if (event->button() == Qt::LeftButton){
		this->mousePressed = true;
	}
}

void MainWindow::updateWindowSize()
{
	QRect rc = this->geometry();
	QRect rc1 = playWidget->geometry();
	playWidget->setGeometry(rc);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	const QRect &rc = this->geometry();
	qDebug() << this->geometry().x() << this->geometry().y();

	//updateWindowSize();
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	const QPoint &pos = event->pos();
	const QRect &rect = this->geometry();

	if (this->mousePressed){
		//this->move(this->pos() + (event->globalPos() - event->pos()));
	}
	/*if (isPosInRect(pos, rect)){
		this->setWindowFlags(Qt::Window);
		this->show();
	}
	else{
		this->setWindowFlags(Qt::FramelessWindowHint);
	}*/
}

bool MainWindow::isPosInRect(const QPoint &pos, const QRect &rect)
{
	if (pos.x() >= rect.x() && pos.x() <= rect.x() + rect.width()
		&& pos.y() >= rect.y() && pos.y() <= rect.y() + rect.height()){
		return true;
	}
	return false;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton){
		this->mousePressed = false;
	}
}


void MainWindow::nextClicked()
{
	playList->next();
}

void MainWindow::previousClicked()
{
	playList->previous();
}

//传过来的是步进的毫秒数
void MainWindow::fastforword(int msec)
{
	qint64 curPos = player->position();
	msec = (msec == 0 ? playConfig->secForword : msec);
	player->setPosition(curPos + msec);
}

void MainWindow::rewind(int msec)
{
	qint64 curPos = player->position();
	msec = (msec == 0 ? playConfig->secRewind : msec);
	player->setPosition(curPos - msec);
}

void MainWindow::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
	if (player->isMetaDataAvailable()){
		qDebug() << player->metaData("Resolution");
		QSize sz = player->metaData("Resolution").toSize();
		this->resize(sz);
	}
	qDebug() << player->media().canonicalResource().resolution();
}

void MainWindow::playlistButtonClicked()
{
	if (playlistState){
		playlistWidget->hide();
		playlistState = false;
	}
	else{
		playlistWidget->show();
		playlistState = true;
	}
}

void MainWindow::openFile()
{
	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Files"));
	if (playWidget != NULL){
		delete playWidget;
		playWidget = NULL;
	}
	playList->clear();
	playlistWidget->clear();
	addToPlaylist(fileNames);
	int p = playList->mediaCount();
	playList->setCurrentIndex(p - 1);
	player->play();
}

void MainWindow::addToPlaylist(QStringList fileNames)
{
	//playList->clear();
	foreach(QString const &argument, fileNames) {
		QFileInfo fileInfo(argument);
		if (fileInfo.exists()) {
			QUrl url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
			QString suffixName = fileInfo.suffix().toLower();
			if (suffixName == "mp3" || suffixName == "flac") {
				//音频
				if (playWidget == NULL){
					initPlayWidget(PLAY_MUSIC);
				}	
				playlistWidget->addItem(url.toString());
				playList->addMedia(url);
			}
			else{
				if (playWidget == NULL){
					initPlayWidget(PLAY_VIDEO);
				}
				playlistWidget->addItem(url.toString());
				playList->addMedia(url);
			}
		}
		else {
			QUrl url(argument);
			if (url.isValid()) {
				playList->addMedia(url);
			}
		}
	}
}

void MainWindow::jump(const QModelIndex &index)
{
	if (index.isValid()){
		playList->setCurrentIndex(index.row());
		player->play();
	}
}

void MainWindow::controlButtonClicked()
{
	if (controlState){
		controlWindow->hide();
		controlState = false;
	}
	else{
		controlWindow->show();
		controlState = true;
	}
}

void MainWindow::seek(int seconds)
{
	player->setPosition(seconds * 1000);
}

void MainWindow::loadLocalConfig()
{
	//加载本地设置
	playConfig = new PlayConfig;
	playConfig->secForword = 5000;
	playConfig->secRewind = 5000;
	playConfig->rate = 1;
	playConfig->subDelay = 0;
}

void MainWindow::initPlayWidget(int flag)
{
	if (flag == PLAY_MUSIC){
		playWidget = new MusicWidget(this, player);
	}
	if(flag == PLAY_VIDEO){
		playWidget = new VideoWidget(this);
		VideoWidget *v = (VideoWidget*)playWidget;
		player->setVideoOutput((QVideoWidget*)playWidget);
	}
	displayLayout->addWidget(playWidget);
	connect(controlWindow, SIGNAL(changeBrightness(int)), playWidget, SLOT(setBrightness(int)));
	connect(controlWindow, SIGNAL(changeHue(int)), playWidget, SLOT(setHue(int)));
	connect(controlWindow, SIGNAL(changeContrast(int)), playWidget, SLOT(setContrast(int)));
	connect(playWidget, SIGNAL(rightButtonClicked(QPoint)), this, SLOT(openMenu(QPoint)));
}

void MainWindow::openMenu(QPoint pos)
{
	if (menuState){
		menuWidget->hide();
		menuState = false;
	}
	else{
		menuWidget->show();
		menuState = true;
	}
}

void MainWindow::searchButtonClicked()
{
	if (searchState){
		searchWindow->hide();
		searchState = false;
	}
	else{
		searchWindow->show();
		searchState = true;
	}
}

void MainWindow::getInfoComplete(QString res)
{

}



/*
	VideoWidget 大小与主窗口保持一致
*/
