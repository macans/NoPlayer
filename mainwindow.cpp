#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{

	playlistState = false;
	mousePressed = false;
	controlState = false;
	player = new QMediaPlayer(this);
	playlist = new QMediaPlaylist();
	player->setPlaylist(playlist);
	//player->setMedia(QUrl::fromLocalFile("E:\\Flash\\Youtube\\Jiang\\HK.mp4"));
	//播放视频
	playWidget = new VideoWidget(this);
	player->setVideoOutput((QVideoWidget*)playWidget);

	player->setVolume(50);
	player->play();

	playlistModel = new PlaylistModel();
	playlistModel->setPlaylist(playlist);

	playlistView = new QListView();
	playlistView->setModel(playlistModel);
	playlistView->setCurrentIndex(playlistModel->index(playlist->currentIndex(), 0));
	connect(playlistView, SIGNAL(activated(QModelIndex)), this, SLOT(jump(QModelIndex)));
	connect(playlistView, SIGNAL(closeEvent(QCloseEvent*)), this, SLOT(playlistButtonClicked()));
	//下方控制块
	controls = new PlayControls(this);
	controls->setDuration(player->duration());
	controls->setVolume(player->volume());
	controls->setState(player->state());
	connect(controls, SIGNAL(play()), player, SLOT(play()));
	connect(controls, SIGNAL(pause()), player, SLOT(pause()));
	connect(controls, SIGNAL(stop()), player, SLOT(stop()));
	connect(controls, SIGNAL(next()), player, SLOT(nextClicked()));
	connect(controls, SIGNAL(previous()), player, SLOT(previousClicked()));
	connect(controls, SIGNAL(fastforword()), this, SLOT(fastforword()));
	connect(controls, SIGNAL(rewind()), this, SLOT(rewind()));
	connect(controls, SIGNAL(open()), this, SLOT(openFile()));
	connect(controls, SIGNAL(changeVolume(int)), player, SLOT(setVolume(int)));
	connect(controls, SIGNAL(changeMuting(bool)), player, SLOT(setMuted(bool)));
	connect(controls, SIGNAL(playlistButtonClicked()), this, SLOT(playlistButtonClicked()));
	connect(controls, SIGNAL(controlButtonClicked()), this, SLOT(controlButtonClicked()));
	connect(controls, SIGNAL(seek(int)), this, SLOT(seek(int)));
	connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), controls, SLOT(setState(QMediaPlayer::State)));
	connect(player, SIGNAL(mutedChanged(bool)), controls, SLOT(setMuted(bool)));
	//controls->hide();

	controlWidget = new ControlWidget;
	connect(controlWidget, SIGNAL(controlWidgetClosed()), this, SLOT(controlButtonClicked()));
	controlWidget->hide();
	//connect(controlWidget, SIGNAL())
	connect(controlWidget, SIGNAL(changeBrightness(int)), playWidget, SLOT(setBrightness(int)));
	connect(controlWidget, SIGNAL(changeHue(int)), playWidget, SLOT(setHue(int)));
	connect(controlWidget, SIGNAL(changeContrast(int)), playWidget, SLOT(setContrast(int)));

	connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
	connect(player, SIGNAL(positionChanged(qint64)), controls, SLOT(positionChanged(qint64)));
	connect(player, SIGNAL(durationChanged(qint64)), controls, SLOT(durationChanged(qint64)));

	//布局
	QHBoxLayout *displayLayout = new QHBoxLayout;
	displayLayout->addWidget(playWidget);
	playlistView->hide();

	QHBoxLayout *controlLayout = new QHBoxLayout;
	controlLayout->addWidget(controls);
	//controlLayout->addStretch(1);

	QBoxLayout *layout = new QVBoxLayout;
	layout->setMargin(0);
	layout->addLayout(displayLayout, 2);
	layout->addLayout(controlLayout);
	this->setLayout(layout);


	this->mousePressed = false;
	this->setWindowTitle("NoPlayer");
	//this->setWindowIcon();
	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setMouseTracking(true);
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

}

void MainWindow::previousClicked()
{

}

void MainWindow::fastforword()
{

}

void MainWindow::rewind()
{

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
		playlistView->hide();
		playlistState = false;
	}
	else{
		playlistView->show();
		playlistState = true;
	}
}

void MainWindow::openFile()
{
	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Files"));
	addToPlaylist(fileNames);
	int p = playlist->mediaCount();
	playlist->setCurrentIndex(p);
	player->play();
}

void MainWindow::addToPlaylist(QStringList fileNames)
{
	foreach(QString const &argument, fileNames) {
		QFileInfo fileInfo(argument);
		if (fileInfo.exists()) {
			QUrl url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
			if (fileInfo.suffix().toLower() == QLatin1String("m3u")) {
				playlist->load(url);
			}
			else
				playlist->addMedia(url);
		}
		else {
			QUrl url(argument);
			if (url.isValid()) {
				playlist->addMedia(url);
			}
		}
	}
}

void MainWindow::jump(const QModelIndex &index)
{
	if (index.isValid()){
		playlist->setCurrentIndex(index.row());
		player->play();
	}
}

void MainWindow::controlButtonClicked()
{
	if (controlState){
		controlWidget->hide();
		controlState = false;
	}
	else{
		controlWidget->show();
		controlState = true;
	}
}

void MainWindow::seek(int seconds)
{
	player->setPosition(seconds * 1000);
}



/*
	VideoWidget 大小与主窗口保持一致
*/
