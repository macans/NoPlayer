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
	//playWidget = new VideoWidget(this);
	//playWidget = new MusicWidget(this, player);
	player->setVideoOutput((QVideoWidget*)playWidget);

	player->setVolume(50);
	player->play();

	playlistWindow = new PlaylistWindow(playList);
	connect(playlistWindow, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemDoubleClicked(QListWidgetItem*)));

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

		controlWindow = new ControlWindow;
	//controlWindow;
	connect(controlWindow, SIGNAL(controlWindowClosed()), this, SLOT(controlButtonClicked()));
	connect(controlWindow, SIGNAL(fontChanged(QFont)), subLabel, SLOT(fontChanged(QFont)));
	connect(controlWindow, SIGNAL(colorChanged(QColor)), subLabel, SLOT(colorChanged(QColor)));
	connect(controlWindow, SIGNAL(subtitleChanged(QString)), subLabel, SLOT(subtitleChanged(QString)));
	controlWindow->setHueFUN(playConfig->hue);
	controlWindow->setContrastFUN(playConfig->contrast);
	controlWindow->setBritghtnessFUN(playConfig->brightness);
	controlWindow->hide();
	//connect(controlWindow, SIGNAL())
	

	searchWindow = new SearchWindow;
	searchWindow->hide();
	connect(searchWindow, SIGNAL(getInfoComplete(bool, InfoNetMusic&)), this, SLOT(getInfoComplete(bool, InfoNetMusic&)));

	connect(player, SIGNAL(positionChanged(qint64)), subLabel, SLOT(updateSubTitle(qint64)));
	connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
	connect(player, SIGNAL(positionChanged(qint64)), controls, SLOT(positionChanged(qint64)));
	connect(player, SIGNAL(durationChanged(qint64)), controls, SLOT(durationChanged(qint64)));
	connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), controls, SLOT(setState(QMediaPlayer::State)));
	connect(player, SIGNAL(mutedChanged(bool)), controls, SLOT(setMuted(bool)));

	//布局
	displayLayout = new QHBoxLayout;
	displayLayout->addWidget(playWidget);
	playlistWindow->hide();

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
	savePlayConfig();
	savePlayList();

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
	{
		about->close();
		property->close();
	}
    if(event->button() == Qt::RightButton){
		QRect 
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
	const QRect &rect = controls->geometry();
	
	/*if (this->mousePressed){
		this->move(this->pos() + (event->globalPos() - event->pos()));
	}*/


	/*if (isPosInRect(pos, rect)){
		controls->show();
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
	initPlayWidget(flag, MODEL_LAC);
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
	playConfig->msecForword = val.property("msec_forword").toInt32();
	playConfig->msecRewind = val.property("msec_rewind").toInt32();
	playConfig->subDelay = 0;
	playConfig->hue = 50;
	playConfig->brightness = 50;
	playConfig->contrast = 50;
	playConfig->stopWhenMin = val.property("stop_while_min").toInt32();
	playConfig->subColor = val.property("sub_color").toInt32();
	playConfig->subFont = val.property("sub_font").toString();
}

void MainWindow::initPlayWidget(int isVideo, int isLocal, QString info, QString lrclink)
{
	if (!isLocal){
		delete playWidget;
		playWidget = new MusicWidget(info, lrclink, this, player);
		subLabel->hide();
	}
	else if (isVideo != curPlayFlag){
		delete playWidget;
		if (isVideo == PLAY_MUSIC){
			playWidget = new MusicWidget(this, player);
			curPlayFlag = PLAY_MUSIC;
			subLabel->hide();
		}
		else{
			playWidget = new VideoWidget(this);
			player->setVideoOutput((QVideoWidget*)playWidget);
			curPlayFlag = PLAY_VIDEO;
			subLabel->show();
		}
	}
	player->play();
	displayLayout->addWidget(playWidget);
	connect(controlWindow, SIGNAL(changeBrightness(int)), playWidget, SLOT(setBrightness(int)));
	connect(controlWindow, SIGNAL(changeHue(int)), playWidget, SLOT(setHue(int)));
	connect(controlWindow, SIGNAL(changeContrast(int)), playWidget, SLOT(setContrast(int)));
	connect(playWidget, SIGNAL(rightButtonClicked(QPoint)), this, SLOT(openMenu(QPoint)));
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
	if (flag){
		//将链接加到播放列表
		playlistWindow->addItemFromNet(info.name, info.link, info.id);
	}
	initPlayWidget(PLAY_MUSIC, MODEL_NET, info.info, info.lrclink);
}

void MainWindow::fontChanged(QFont font)
{
	playConfig->subFont = font.family();
}

void MainWindow::colorChanged(QColor color)
{
	playConfig->subColor = color.value();
}

void MainWindow::savePlayConfig()
{
	//保存配置
	QFile *configFile = new QFile("config.ini");
	if (configFile->open(QIODevice::WriteOnly | QIODevice::Text)){
		qDebug() << "save config file failed" << endl;
	}
	QString config;
	config += "{\n";
	config += "msec_forword: " + QString(playConfig->msecForword) + ",\n";
	config += "msec_rewind: " + QString(playConfig->msecRewind) + ",\n";
	config += "sub_font: \"" + playConfig->subFont + "\",\n";
	config += "sub_color: \"" + QString(playConfig->subColor) + "\",\n";
	config += "stop_while_min: " + QString(playConfig->stopWhenMin) + ",\n";
	config += "}";
	configFile->write(config.toLocal8Bit());
	configFile->close();
}

void MainWindow::savePlayList()
{
	//保存播放列表

}

void MainWindow::itemDoubleClicked(QListWidgetItem *item)
{
	int flag = item->statusTip().toInt();
	QString idStr = item->whatsThis();
	if (idStr == ""){
		initPlayWidget(flag, MODEL_LAC);
	}
	else{
		searchWindow->getSongInfo(idStr, false);
	}
}

void MainWindow::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::WindowStateChange){
		if (windowState() & Qt::WindowMinimized){
			if (playConfig->stopWhenMin)
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
			if (curPlayFlag == PLAY_VIDEO && ((QVideoWidget*)playWidget)->isFullScreen()){
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
	qreal rate = player->playbackRate() + step;
	rate = qMin(PLAYRATE_MIN, rate);
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
	savePlayList();
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
	if (curPlayFlag == PLAY_VIDEO){
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
	exit(0);
}

void MainWindow::loadURLs()
{

}


/*
	VideoWidget 大小与主窗口保持一致
*/
