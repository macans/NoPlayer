#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
	player = new QMediaPlayer(this);
	playlist = new QMediaPlaylist();
	player->setPlaylist(playlist);
	//播放视频
    videoWidget = new VideoWidget(this);
    player->setVideoOutput(videoWidget);
    videoWidget->show();

	playlistModel = new PlaylistModel();
	playlistModel->setPlaylist(playlist);
	playlist->setCurrentIndex(playlistModel->index(playlist->currentIndex(), 0));

	playlistView = new QListView(this);
	playlistView->setModel(playlistModel);
	player->setVolume(50);
    player->play();

	//下方控制块
	PlayControls *controls = new PlayControls(this);
	controls->setVolume(player->volume());
	controls->setState(player->state());
	connect(controls, SIGNAL(play()), player, SLOT(play()));
	connect(controls, SIGNAL(pause()), player, SLOT(pause()));
	//connect(controls, SIGNAL(pause()), this, SLOT(pauseSlot()));
	connect(controls, SIGNAL(stop()), player, SLOT(stop()));
	connect(controls, SIGNAL(next()), player, SLOT(nextClicked()));
	connect(controls, SIGNAL(previous()), player, SLOT(previousClicked()));
	connect(controls, SIGNAL(fastforword()), this, SLOT(fastforword()));
	connect(controls, SIGNAL(rewind()), this, SLOT(rewind()));
	connect(controls, SIGNAL(changeVolume(int)), player, SLOT(setVolume(int)));
	connect(controls, SIGNAL(changeMuting(bool)), player, SLOT(setMuted(bool)));

	connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), controls, SLOT(setState(QMediaPlayer::State)));
	connect(player, SIGNAL(mutedChanged(bool)), controls, SLOT(setMuted(bool)));
	controls->show();

	//布局
	QBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(videoWidget);
	layout->addWidget(controls);

	ui->setupUi(this);
	this->mousePressed = false;
	this->setWindowTitle("NoPlayer");
	//this->setWindowIcon();
	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
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
	QRect rc1 = videoWidget->geometry();
	videoWidget->setGeometry(rc);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	const QRect &rc = this->geometry();
	qDebug() << this->geometry().x() << this->geometry().y();
	
	//updateWindowSize();
}

void MainWindow::durationChanged(qint64 duration)
{
	this->duration = duration / 1000;
	const QMediaContent x = player->currentMedia();
	this->wndSize = player->currentMedia().canonicalResource().resolution();
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


/*
	VideoWidget 大小与主窗口保持一致
*/
