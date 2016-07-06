#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
	typeAllowed << "mp3" << "mp4" << "mkv" << "flv" << "flac" << "mpg";
	searchState = false;
	playlistState = false;
	mousePressed = false;
	controlState = false;
	menuState = false;
	curPlayFlag = -1;
	loadLocalConfig();

	playWidget = NULL;
	player = new QMediaPlayer(this);
	playList = new QMediaPlaylist();
	player->setPlaylist(playList);
    //player->setMedia(QUrl::fromLocalFile("E:\\test.mkv"));
	
	//播放视频
	playWidget = new VideoWidget(this);
	//playWidget = new MusicWidget(this, player);
	player->setVideoOutput((QVideoWidget*)playWidget);

	player->setVolume(50);
	player->play();

	playlistWindow = new PlaylistWindow(playList);
	connect(playlistWindow, SIGNAL(itemDoubleClicked(QListWidgetItem*, bool)), this, SLOT(itemDoubleClicked(QListWidgetItem*, bool)));
	connect(playlistWindow, SIGNAL(playlistWindowClosed()), this, SLOT(playlistButtonClicked()));

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
    //subLabel->setStyleSheet("color:red;");
    subLabel->setObjectName("subLabel");
    subLabel->hide();

	controlWindow = new ControlWindow;
	//controlWindow;
	connect(controlWindow, SIGNAL(controlWindowClosed()), this, SLOT(controlButtonClicked()));
	connect(controlWindow, SIGNAL(fontChanged(QFont)), this, SLOT(fontChanged(QFont)));
	connect(controlWindow, SIGNAL(colorChanged(QColor)),this, SLOT(colorChanged(QColor)));
	connect(controlWindow, SIGNAL(subtitleChanged(QString)), subLabel, SLOT(subtitleChanged(QString)));

	connect(controlWindow, SIGNAL(rateSlowDown()), this, SLOT(rateSlowDown()));
	connect(controlWindow, SIGNAL(rateSpeedUp()), this, SLOT(rateSpeedUp()));
	connect(controlWindow, SIGNAL(rateDefault()), this, SLOT(initPlaybackRate()));

	connect(controlWindow, SIGNAL(sizeChanged(int)), this, SLOT(sizeChanged(int)));

	connect(controlWindow, SIGNAL(minithenpause(bool)), this, SLOT(setStopWhileMin(bool)));
	connect(controlWindow, SIGNAL(rewindSec(qint64)), this, SLOT(rewind(qint64)));
	connect(controlWindow, SIGNAL(rewindMsec(qint64)), this, SLOT(rewind(qint64)));
	connect(controlWindow, SIGNAL(fastforwordSec()), this, SLOT(fastforword()));
	connect(controlWindow, SIGNAL(fastforwordMsec()), this, SLOT(fastforword(qint64)));

	controlWindow->setHueFUN(playConfig->hue);
	controlWindow->setContrastFUN(playConfig->contrast);
	controlWindow->setBritghtnessFUN(playConfig->brightness);
	controlWindow->hide();
	//connect(controlWindow, SIGNAL())
	

	searchWindow = new SearchWindow;
	searchWindow->hide();
	connect(searchWindow, SIGNAL(getInfoComplete(bool, InfoNetMusic&)), this, SLOT(getInfoComplete(bool, InfoNetMusic&)));
	connect(searchWindow, SIGNAL(searchWindowClosed()), this, SLOT(searchButtonClicked()));

	connect(player, SIGNAL(currentMediaChanged(const QMediaContent&)), this, SLOT(currentMediaChanged(const QMediaContent&)));
	connect(player, SIGNAL(positionChanged(qint64)), subLabel, SLOT(updateSubTitle(qint64)));
	connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
	connect(player, SIGNAL(positionChanged(qint64)), controls, SLOT(positionChanged(qint64)));
	connect(player, SIGNAL(durationChanged(qint64)), controls, SLOT(durationChanged(qint64)));
	connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), controls, SLOT(setState(QMediaPlayer::State)));
	connect(player, SIGNAL(mutedChanged(bool)), controls, SLOT(setMuted(bool)));

    //布局
   //QGridLayout *grid=new QGridLayout();
	playlistWindow->hide();
	layout = 0;
	controlLayout = subLabelLayout = displayLayout = NULL;
	initLayout();
	// this->setWindowFlags(Qt::FramelessWindowHint);


	this->setMouseTracking(true);
	this->mousePressed = false;
	this->setWindowTitle("NoPlayer");
	
	this->resize(QSize(596, 443));

	//初始化右键菜单
	pop_menu = new QMenu();

	file_action = new QAction(this);
	folder_action = new QAction(this);
	word_action = new QAction(this);
	screen_action = new QAction(this);
	nature_action = new QAction(this);
	URLs_action = new QAction(this);
	about_action = new QAction(this);
	quit_action = new QAction(this);

	//pop_menu->size

	pop_menu->setStyleSheet("QMenu{background-color:rgb(234,234,234)}"
		"QMenu::item{padding:3px 60px}"
		"QMenu::item:selected{background-color:rgb(245,255,255)}");
	setTheMenu();

	//连接信号与槽
	connect(file_action, &QAction::triggered, this, &MainWindow::openFile);
	connect(folder_action, &QAction::triggered, this, &MainWindow::openFolder);
	connect(screen_action, &QAction::triggered, this, &MainWindow::changeScreen);
	connect(nature_action, &QAction::triggered, this, &MainWindow::showProperty);
	connect(URLs_action, &QAction::triggered, this, &MainWindow::loadURLs);
	connect(about_action, &QAction::triggered, this, &MainWindow::showAbout);
	connect(quit_action, &QAction::triggered, this, &MainWindow::quitMedia);

}

MainWindow::~MainWindow()
{
	delete player;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
	{
		about->close();
		property->close();
	}
    if(event->button() == Qt::RightButton){
		//QRect 
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
	const QPoint &pos1 = event->globalPos();
	const QPoint &pos2 = event->pos();
	/*if (this->mousePressed){
		this->move(this->pos() + (event->globalPos() - event->pos()));
	}*/

	const QRect &controlRect = controls->geometry();
    const QRect &rect = this->geometry();
    if (isPosInRect(pos2, controlRect) || abs(pos1.y() - rect.y() - rect.height()) < 40){
		controls->show();
	}
	else{
        controls->hide();
	}
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
	playlistWindow->next();
}

void MainWindow::previousClicked()
{
	playlistWindow->previous();
}

//传过来的是步进的毫秒数
void MainWindow::fastforword(int msec)
{
	qint64 curPos = player->position();
	msec = (msec == 0 ? playConfig->msecForword : msec);
	player->setPosition(curPos + msec);
}

void MainWindow::rewind(int msec)
{
	qint64 curPos = player->position();
	msec = (msec == 0 ? playConfig->msecRewind : msec);
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
		playlistWindow->hide();
		playlistState = false;
	}
	else{
		playlistWindow->show();
		playlistState = true;
	}
}

void MainWindow::openFile()
{
	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Files"));
	if (fileNames.count() == 0){
		return;
	}
	//添加播放列表
	int flag = playlistWindow->addItemFromLocal(fileNames);
	//initPlayWidget(flag, MODEL_LAC);
	player->play();
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
	QFile *configFile = new QFile("config.ini");
	if (!configFile->open(QIODevice::ReadWrite | QIODevice::Text)){
		qDebug() << "config file open failed" << endl;
	}
	QString config = configFile->readAll();
	QScriptEngine engine;
	QScriptValue val = engine.evaluate("value=" + config);
	qDebug() << val.toString();
	playConfig = new PlayConfig;

	int msecForword = val.property("msec_forword").toInt32();
	int msecRewind = val.property("msec_rewind").toInt32();
	if (msecForword != 0){
		playConfig->msecForword = msecForword;
	}
	else{
		playConfig->msecForword = 5000;
	}
	if (msecRewind != 0){
		playConfig->msecRewind = msecRewind;
	}
	else{
		playConfig->msecRewind = 5000;
	}
	playConfig->subDelay = 0;
	playConfig->hue = 50;
	playConfig->brightness = 50;
	playConfig->contrast = 50;
	playConfig->stopWhileMin = val.property("stop_while_min").toInt32();
	QString sizeWhileOpen = val.property("size_while_open").toString();
	if (sizeWhileOpen.isEmpty()){
		playConfig->sizeWhileOpen = SIZE_ORIG;
	}
	else{
		playConfig->sizeWhileOpen = sizeWhileOpen.toInt();
	}
	QString color = val.property("sub_color").toString();
	if (color == ""){
		playConfig->subColor = "black";
	}
	else{
		playConfig->subColor = color;
	}
	playConfig->subFont = val.property("sub_font").toString();
}

void MainWindow::initPlayWidget(int playModel, int isLocal, QString info, QString lrclink)
{
	if (!isLocal){
		delete playWidget;
		playWidget = new MusicWidget(info, lrclink, this, player);
		((MusicWidget*)playWidget)->updateDuration(player->duration());
		subLabel->hide();
	}
	else{
		delete playWidget;
		
		if (playModel == MEDIA_TYPE_MUSIC){
			playWidget = new MusicWidget(this, player);
			curPlayFlag = MEDIA_TYPE_MUSIC;
			subLabel->hide();
		}
		else{
			playWidget = new VideoWidget(this);
			player->setVideoOutput((QVideoWidget*)playWidget);
			curPlayFlag = MEDIA_TYPE_VIDEO;
			subLabel->show();
		}
	}
	//player->play();
	
	initLayout();
	connect(controlWindow, SIGNAL(changeBrightness(int)), playWidget, SLOT(setBrightness(int)));
	connect(controlWindow, SIGNAL(changeHue(int)), playWidget, SLOT(setHue(int)));
	connect(controlWindow, SIGNAL(changeContrast(int)), playWidget, SLOT(setContrast(int)));
	if (playModel == MEDIA_TYPE_VIDEO){
		if (playConfig->sizeWhileOpen == SIZE_ORIG){
			//this->resize(QSize(ORIG_WIDTH, ORIG_HEIGHT));
			qDebug() << player->metaData("Resolution").toSize();
			qDebug() << player->media().canonicalResource().resolution();
		}
		else{
			this->resize(QSize(ORIG_WIDTH, ORIG_HEIGHT));
			if (playConfig->sizeWhileOpen == SIZE_FULL){
				((VideoWidget*)playWidget)->setFullScreen(true);
			}
		}
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

void MainWindow::getInfoComplete(bool flag, InfoNetMusic &info)
{
	qDebug() << info.id << endl;
	qDebug() << info.name << endl;
	qDebug() << info.link << endl;
	qDebug() << info.lrclink << endl;
	qDebug() << info.info << endl;
	int id;
	//flag = true 是新添加的歌曲
	initPlayWidget(MEDIA_TYPE_MUSIC, MODEL_NET, info.info, info.lrclink);
	if (flag){
		//将链接加到播放列表
		playlistWindow->addItemFromNet(info.name, info.link, info.id);
	}
	
}

void MainWindow::fontChanged(QFont font)
{
	playConfig->subFont = font.family();
	subLabel->fontChanged(font);
}

void MainWindow::colorChanged(QColor color)
{
	playConfig->subColor = color.value();
	subLabel->colorChanged(color);
}

void MainWindow::savePlayConfig()
{
	//保存配置
	QFile *configFile = new QFile("config.ini");
	if (!configFile->open(QIODevice::WriteOnly | QIODevice::Text)){
		qDebug() << "save config file failed" << endl;
	}
	QString config;
	config += "{\n";
	config += "\"msec_forword\": " + QString::number(playConfig->msecForword) + ",\n";
	config += "\"msec_rewind\": " + QString::number(playConfig->msecRewind) + ",\n";
	config += "\"sub_font\": \"" + playConfig->subFont + "\",\n";
	config += "\"sub_color\": \"" + playConfig->subColor + "\",\n";
	config += "\"stop_while_min\": " + QString::number(playConfig->stopWhileMin) + ",\n";
	config += "\"size_while_open\": \"" + QString::number(playConfig->sizeWhileOpen) + "\",\n";
	config += "}";
	configFile->write(config.toLocal8Bit());
	configFile->close();
}


void MainWindow::itemDoubleClicked(QListWidgetItem *item, bool doubleClicked)
{
	int flag = item->statusTip().toInt();
	QString idStr = item->whatsThis();
	QString name = item->toolTip();
	if (idStr == ""){
		initPlayWidget(flag, MODEL_LAC);
		if (flag == MEDIA_TYPE_VIDEO){
			subLabel->subtitleChanged(name);
		}
		player->play();
	}
	else if (doubleClicked){
		searchWindow->getSongInfo(idStr, false);
	}
}

void MainWindow::changeEvent(QEvent *event)

{
	if (event->type() == QEvent::WindowStateChange){
		if (windowState() & Qt::WindowMinimized){
			if (playConfig->stopWhileMin)
			player->pause();
		}
	}
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()){
		case Qt::Key_Space: 
			if (player->state() == QMediaPlayer::PlayingState){
				player->pause();
			}
			else{
				player->play();
			}
			break;
		case Qt::Key_Left:
			rewind(playConfig->msecRewind);
			break;
		case Qt::Key_Right:
			fastforword(playConfig->msecRewind);
			break;
		case Qt::Key_Up:
			raiseVolume(VOLUME_STEP);
			break;
		case Qt::Key_Down:
			raiseVolume(-VOLUME_STEP);
			break;
		case Qt::Key_Escape:
			if (curPlayFlag == MEDIA_TYPE_VIDEO && ((QVideoWidget*)playWidget)->isFullScreen()){
				((QVideoWidget*)playWidget)->setFullScreen(false);
			}
			break;
		case Qt::Key_C:
			raisePlaybackRate(PLAYRATE_STEP);
			break;
		case Qt::Key_X:
			raisePlaybackRate(-PLAYRATE_STEP);
			break;
		case Qt::Key_Z:
			initPlaybackRate();
			break;
		case Qt::Key_M:
			raiseSubtitleDelay(SUBDELAY_STEP);
			break;
		case Qt::Key_N:
			raiseSubtitleDelay(-SUBDELAY_STEP);
			break;
	}
	
}

void MainWindow::raiseVolume(int step)
{
	int vol = player->volume() + step;
	vol = qMin(vol, VOLUME_MAX);
	vol = qMax(vol, VOLUME_MIN);
	player->setVolume(vol);
}

void MainWindow::raisePlaybackRate(qreal step)
{
	qreal rate = player->playbackRate();
	rate += step;
	rate = qMax(PLAYRATE_MIN, rate);
	player->setPlaybackRate(rate);
}

void MainWindow::initPlaybackRate()
{
	player->setPlaybackRate(PLAYRATE_INIT);
}

void MainWindow::raiseSubtitleDelay(qint64 step)
{
	playConfig->subDelay += step;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	savePlayConfig();
	playlistWindow->savePlaylist();
	playlistWindow->close();
	searchWindow->close();
	controlWindow->close();
}


void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
	//清除原有菜单
	pop_menu->clear();
	pop_menu->addAction(file_action);
	pop_menu->addAction(folder_action);
	pop_menu->addAction(URLs_action);
	pop_menu->addAction(screen_action);
	pop_menu->addAction(nature_action);
	pop_menu->addAction(about_action);
	pop_menu->addAction(quit_action);
	//菜单出现的位置为当前鼠标的位置
	pop_menu->exec(QCursor::pos());
	event->accept();
}

void MainWindow::setTheMenu()
{
	file_action->setText(tr("打开文件"));
	folder_action->setText(tr("打开文件夹啊"));
	//word_action->setIcon(QIcon(":/image/ic4.png"));
	URLs_action->setText(tr("打开链接"));
	nature_action->setText(tr("信息"));
	screen_action->setText(tr("全屏"));
	screen_action->setIcon(QIcon(":/image/ic6.png"));
	about_action->setText(tr("关于"));
	quit_action->setText(tr("结束"));
}

void MainWindow::playFile(const QString &filePath)
{
	//playButton->setEnabled(true);
	player->setMedia(QUrl::fromLocalFile(filePath));
	player->play();
}
//获取全部音频文件
void MainWindow::openFolder()
{
	QString folderPath = QFileDialog::getExistingDirectory(this, tr("OpenDictory"));
	if (folderPath.length() != 0)
		getMediaList(folderPath);
}

void MainWindow::getMediaList(QString path)
{
	QStringList fileList;
	QDirIterator it(path, QDir::Files | QDir::NoSymLinks, QDirIterator::NoIteratorFlags);
	while (it.hasNext())
	{
		QString mediaFile = it.next();
		QStringList list = mediaFile.split('.');

		QString last = list.takeLast(); // 文件后缀名
		if (typeAllowed.indexOf(last) != -1)
			fileList << mediaFile;
	}
	int flag = playlistWindow->addItemFromLocal(fileList);
	initPlayWidget(flag, MODEL_LAC);
	player->play();
}


//发送全屏信号
void MainWindow::changeScreen()
{
	if (curPlayFlag == MEDIA_TYPE_VIDEO){
		((QVideoWidget*)playWidget)->setFullScreen(playWidget->isFullScreen());
	}
}

void MainWindow::showProperty()
{
	property->update();
	property->show();
	property->setGeometry(QCursor::pos().x(), QCursor::pos().y(), 220, 190);
}

void MainWindow::showAbout()
{
	about->update();
	about->show();
	about->setGeometry(QCursor::pos().x(), QCursor::pos().y(), 596, 443);
}


void MainWindow::quitMedia()
{
	this->close();
}

void MainWindow::loadURLs()
{

}

void MainWindow::initLayout()
{
	delete controlLayout;
	delete subLabelLayout;
	delete displayLayout;
	delete grid;
	delete layout;


    //grid = new QGridLayout;
    displayLayout = new QHBoxLayout;
    displayLayout->addWidget(playWidget);
    //grid->addWidget(playWidget, 0, 0, 100, 100， );
    //grid->addWidget(subLabel, 78, 19, 5, 60, Qt::AlignTop);

	controlLayout = new QHBoxLayout;
	controlLayout->addWidget(controls);
    subLabelLayout = new QHBoxLayout;
    subLabelLayout->addWidget(subLabel);
    //controlLayout->addStretch(1);
    /*grid->addLayout(displayLayout, 0, 0, 100, 100);
	grid->addLayout(subLabelLayout, 78, 19, 5, 60, Qt::AlignBottom);
    grid->addLayout(controlLayout, 79, 19, 20, 60, Qt::AlignTop);*/
    layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addLayout(displayLayout, 3);
    layout->addLayout(subLabelLayout);
    layout->addLayout(controlLayout);
    //grid->setMargin(0);

    this->setLayout(layout);
}

void MainWindow::rateSlowDown()
{
	raisePlaybackRate(-PLAYRATE_STEP);
}

void MainWindow::rateSpeedUp()
{
	raisePlaybackRate(PLAYRATE_STEP);
}

void MainWindow::setStopWhileMin(bool status)
{
	playConfig->stopWhileMin = status;
}

void MainWindow::sizeChanged(int status)
{
	playConfig->sizeWhileOpen = status;
}

void MainWindow::currentMediaChanged(const QMediaContent& media)
{
	qDebug() << media.canonicalResource().resolution();
}



/*
	VideoWidget 大小与主窗口保持一致
*/
