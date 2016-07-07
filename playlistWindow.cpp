#include "playlistwindow.h"

PlaylistWindow::PlaylistWindow(QMediaPlaylist *playList, QWidget *parent, int playModel) : QWidget(parent)
{

    this->setWindowTitle("Playlist");
    this->setWindowIcon(QIcon(":/image/playlist.ico"));
	playBackMode = playModel;
	playlist = playList;
	playlist->setPlaybackMode((QMediaPlaylist::PlaybackMode)playBackMode);
	listWidget = new QListWidget(this);
   
	loadPlaylist();

	this->doubleClicked = false;

//----布局---------------------------------------
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(listWidget);
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    playType = new QPushButton(QIcon(":image/seq.png"),"");
    playType->setToolTip("点击切换播放模式");
    search_edit = new QLineEdit();
    search_btn = new QPushButton(QIcon(":image/search.ico"),"");
    search_btn->setToolTip("搜索");
    addBtn = new QPushButton(QIcon(":image/openfile.ico"),"");
    addBtn->setToolTip("添加");
    delBtn = new QPushButton(QIcon(":image/rmfile.ico"), "");
    delBtn->setToolTip("移除");
    clearBtn = new QPushButton(QIcon(":image/clear.ico"),"");
    clearBtn->setToolTip("清空");
    bottomLayout->addWidget(playType);
    bottomLayout->addWidget(search_edit);
    bottomLayout->addWidget(search_btn);
    bottomLayout->addWidget(addBtn);
    bottomLayout->addWidget(delBtn);
    bottomLayout->addWidget(clearBtn);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
    this->setLayout(mainLayout);
	

//-----signal-start------------
    connect(listWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)));
    connect(listWidget,SIGNAL(currentRowChanged(int)),this,SIGNAL(currentRowChanged(int)));
    connect(listWidget,SIGNAL(currentTextChanged(QString)),this,SIGNAL(currentTextChanged(QString)));
    connect(listWidget,SIGNAL(itemActivated(QListWidgetItem*)),this,SIGNAL(itemActivated(QListWidgetItem*)));
    connect(listWidget,SIGNAL(itemChanged(QListWidgetItem*)),this,SIGNAL(itemChanged(QListWidgetItem*)));
    connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SIGNAL(itemClicked(QListWidgetItem*)));
    //connect(listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SIGNAL(itemDoubleClicked(QListWidgetItem*)));
    connect(listWidget,SIGNAL(itemEntered(QListWidgetItem*)),this,SIGNAL(itemEntered(QListWidgetItem*)));
    connect(listWidget,SIGNAL(itemPressed(QListWidgetItem*)),this,SIGNAL(itemPressed(QListWidgetItem*)));
    connect(listWidget,SIGNAL(itemSelectionChanged()),this,SIGNAL(itemSelectionChanged()));

    connect(delBtn,SIGNAL(clicked(bool)),this,SLOT(removeItems()));
    connect(clearBtn,SIGNAL(clicked(bool)),this,SLOT(clear()));
    connect(search_btn,SIGNAL(clicked(bool)),this,SLOT(searchItem()));
    connect(listWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(clearSearch()));
    connect(listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(setPlaylistIndex(QListWidgetItem*)));

    connect(playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(setItemPlay(int)));
    connect(playType,SIGNAL(clicked(bool)),this,SLOT(setPlayMode()));
    connect(addBtn,SIGNAL(clicked(bool)),this,SLOT(openfiles()));
//------signal-end------------

}


//-----------slots-start--------
//清空列表和playlist
void PlaylistWindow::clear()
{
    listWidget->clear();
    bool res = playlist->clear();
    qDebug()<<playlist->currentIndex();
}

//移除当前被选中的item
void PlaylistWindow::removeItems()
{
	if (listWidget->count() > 0 && listWidget->currentItem() != NULL &&  playlist->mediaCount() > 0) {
		int listWidgetRow = listWidget->currentRow();
		int playlistRow = playlist->currentIndex();
		if (playlistRow > listWidgetRow) {
			playlist->setCurrentIndex(0);
		}
		listWidgetRow = listWidget->currentRow();
		playlistRow = playlist->currentIndex();
		if (listWidgetRow == playlistRow && listWidgetRow != 0) {
			playlist->setCurrentIndex(0);
		}

		playlist->removeMedia(listWidgetRow);
		listWidget->takeItem(listWidgetRow);
		if (listWidgetRow == playlistRow && listWidgetRow == 0) {
			if (playlist->mediaCount() > 0) {
				playlist->setCurrentIndex(0);
				this->setItemPlay(0);
			}
			else {
				playlist->setCurrentIndex(-1);
			}
		}
		int row = playlist->currentIndex();
		this->updateIndex();
		listWidget->update();
	}

}

//搜索items
void PlaylistWindow::searchItem()
{
    this->clearSearch();
    QString str= search_edit->text();
    if(""==str) return;
    searchList.clear();
    searchList = listWidget->findItems(str,Qt::MatchContains);
    for(int i=0;i<searchList.length();i++) {
        searchList.at(i)->setTextColor(ITEM_COLOR_SEARCH);
        if( 0==i ) {
            listWidget->setCurrentItem(searchList.at(i));
            search_flag = true;
        }
    }
}
//清除搜索状态
void PlaylistWindow::clearSearch()
{
    if(search_flag) {
        search_flag = false;
        for(int i=0;i<listWidget->count();i++) {
            this->setItemNormalView(listWidget->item(i));
        }
        //将播放项设置为播放状态
        if(listWidget->item(playlist->currentIndex()) != NULL) {
            this->setItemPlayView(listWidget->item(playlist->currentIndex()));
        }
    }
}

//将行号为row的设置为播放项
void PlaylistWindow::setItemPlay(int row)
{
	if (row == -1) return;
	int cnt = playlist->mediaCount();
    QListWidgetItem *item = listWidget->item(row);
	emit itemDoubleClicked(item, doubleClicked);
	doubleClicked = true;
    this->setItemPlayView(item);
    qDebug("setItemPlay %d",row);
}

//设置播放状态下的样式
void PlaylistWindow::setItemPlayView(QListWidgetItem *item)
{
	for (int i = 0; i < listWidget->count(); ++i){
		if (listWidget->item(i) != item){
			setItemNormalView(listWidget->item(i));
		}
	}
	item->setTextColor(ITEM_COLOR_PLAY);
}

//设置普通状态下的样式
void PlaylistWindow::setItemNormalView(QListWidgetItem *item)
{
    item->setTextColor(ITEM_COLOR_NORMAL);
}

//设置搜索到的item的样式
void PlaylistWindow::setItemSearchView(QListWidgetItem *item)
{
    item->setTextColor(ITEM_COLOR_SEARCH);
}
//设置播放模式
void PlaylistWindow::setPlayMode()
{
    if(playBackMode<4) {
        playBackMode++;
    } else{
        playBackMode = 1;
    }

    switch(playBackMode) {
    case CUR_ITEM_LOOP:
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        playType->setIcon(QIcon(":image/itemloop.ico"));
        playType->setToolTip("单曲循环");
        break;
    case SEQUENTIAL:
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
        playType->setIcon(QIcon(":image/seq.png"));
        playType->setToolTip("顺序播放");
        break;
    case LOOP:
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        playType->setIcon(QIcon(":image/listloop.ico"));
        playType->setToolTip("列表循环");
        break;
    case RANDOM:
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        playType->setIcon(QIcon(":image/random.ico"));
        playType->setToolTip("随机播放");
        break;
    default:
        break;
    }
}
//下一曲
void PlaylistWindow::next()
{
    //this->setItemNormalView(listWidget->item(playlist->currentIndex()));
    playlist->next();
	int index = playlist->currentIndex();
	if (index == -1){
		index = 0;
		playlist->setCurrentIndex(index);
	}
	
	int mode = playlist->playbackMode();
	//QListWidgetItem *item = listWidget->item(index);
	//emit itemDoubleClicked(item);
}
//上一曲
void PlaylistWindow::previous()
{
	
    //this->setItemNormalView(listWidget->item(playlist->currentIndex()));
    playlist->previous();
	int index = playlist->currentIndex();
	int cnt = playlist->mediaCount();
	if (index == -1){
		index = playlist->mediaCount() - 1;
		playlist->setCurrentIndex(index);
	}
	//QListWidgetItem *item = listWidget->item(index);
	//emit itemDoubleClicked(item);
}

void PlaylistWindow::openfiles()
{
    QStringList fileList = QFileDialog::getOpenFileNames(0,tr("文件选择"),".",tr("media file(*.mp3 *.flac *.wmv *.mp4 *.avi)"));
    if(!fileList.isEmpty()) {
        addItemFromLocal(fileList, false);
    }
}

//当列表移除某一项之后，重新更新每一项前面的index
void PlaylistWindow::updateIndex()
{
    QString index="";
    for(int i=0; i<listWidget->count();i++) {
        index="";
        if(i<9) {
            index.append("0").append(QString::number(1+i,10));
        } else {
            index.append(QString::number(1+i,10));
        }
        QListWidgetItem *tmpItem= listWidget->item(i);
        if(tmpItem->whatsThis()=="") {
            tmpItem->setText(index.append(". ").append(tmpItem->toolTip().split("/").last()));
        } else {
            tmpItem->setText(index.append(". ").append(tmpItem->toolTip()));
        }
    }
}

//获取文件类型是music还是video
int PlaylistWindow::getMediaType(const QString fileName)
{
    QFileInfo fileInfo(fileName);
    if (fileInfo.exists()) {
         QString suffixName = fileInfo.suffix().toLower();
        if (suffixName == "mp3" || suffixName == "flac" ||suffixName == "wmv") {
            return MEDIA_TYPE_MUSIC;
        } else if(suffixName == "mp4" ||suffixName == "avi" || suffixName == "mkv") {
            return MEDIA_TYPE_VIDEO;
        } else {
            return -1;
        }
    }
}



//-----------slots-end------------


//从本地添加items
int PlaylistWindow::addItemFromLocal(const QStringList &addList,bool playNow)
{

    int mediaType;
    bool flag=true;
    for(int i=0;i<addList.length();i++) {

        QString label = addList.at(i);
        QFileInfo fileInfo(label);
        if(fileInfo.exists()) {
            QStringList list = label.split("/");
            QListWidgetItem *item = new QListWidgetItem(list.last(),listWidget);
            int row = listWidget->row(item);

            //添加索引字符
            QString index = "";
            if(row<9) {
                index.append("0").append(QString::number(row+1,10).append(". "));
            } else {
                  index = QString::number(row+1,10).append(". ");
            }
            item->setText(index.append(item->text()));
            //设置item高度
            item->setSizeHint(QSize(100,30));
            item->setToolTip(label);
            //设置media的类型
            int type = getMediaType(label);

            if(type != -1){
                if(type == MEDIA_TYPE_MUSIC){
                    item->setIcon(QIcon(":/image/music.gif"));
                }
                else{
                    item->setIcon(QIcon(":/image/video.ico"));
                }
                item->setStatusTip(QString::number(type,10));
            }
            this->setItemNormalView(item);
            //添加到playlist 并将第一条设置为当前播放item
			qDebug() << playlist->mediaCount();
            playlist->addMedia(QUrl::fromLocalFile(label));
            if(flag){
                flag=false;
                mediaType = type;
                if(playNow){
                    //this->setItemPlay(row);
					playlist->setCurrentIndex(row);

                }else{
                    listWidget->setCurrentItem(item);
                }
            }
        } else {
            continue;
        }
    }

	return mediaType;
}


//添加网络item
int PlaylistWindow::addItemFromNet(const QString &additem, const QString &link,int id, bool playNow)
{

    QListWidgetItem *item = new QListWidgetItem(additem,listWidget);
    int row = listWidget->row(item);
    //添加索引字符
    QString index = "";
    if(row<9) {
        index.append("0").append(QString::number(row+1,10).append(". "));
    } else {
          index = QString::number(row+1,10).append(". ");
    }
    item->setText(index.append(item->text()));
    //设置item高度
    item->setSizeHint(QSize(100,30));
    item->setIcon(QIcon(":/image/net.ico"));
    item->setWhatsThis(QString::number(id,10));
    item->setToolTip(additem);
    //设置media的类型
    item->setStatusTip(QString::number(MEDIA_TYPE_MUSIC,10));
    this->setItemNormalView(item);

    //添加到playlist 并将第一条设置为当前播放item
    playlist->addMedia(QUrl(link));
//	this->setItemPlay(row);
	if (playNow){
		this->doubleClicked = false;
		playlist->setCurrentIndex(row);
	}
    //qDebug("%d",playlist->currentIndex());
    return MEDIA_TYPE_MUSIC;

}

void PlaylistWindow::setPlaylistIndex(QListWidgetItem *item)
{
	this->doubleClicked = true;
	int origin = playlist->currentIndex();
	int cnt = playlist->mediaCount();
	//setItemNormalView(listWidget->item(origin));
	int row = listWidget->row(item);
	playlist->setCurrentIndex(row);
}

void PlaylistWindow::closeEvent(QCloseEvent *event)
{
	emit playlistWindowClosed();
}

void PlaylistWindow::savePlaylist()
{
	//保存配置
	QFile *playlistFile = new QFile("playlist.txt");
	if (!playlistFile->open(QIODevice::WriteOnly | QIODevice::Text)){
		qDebug() << "save playlist file failed" << endl;
	}
	QString playlistStr = "{\nplaylist:\n[\n";
	for (int i = 0; i < listWidget->count(); i++) {
		QString listitem = "{\n";
		QListWidgetItem *item = listWidget->item(i);
		if (item->whatsThis() == "") {
			//local file
			listitem += "\"is_local\":\"1\",\n";
			listitem += "\"name\":\"" + QString(item->toolTip()) + "\"\n";

		}
		else {
			listitem += "\"is_local\": \"0\",\n";
			listitem += "\"name\":\"" + QString(item->toolTip()) + "\",\n";
			listitem += "\"link\":\"" + QString(playlist->media(i).canonicalUrl().toString()) + "\",\n";
			listitem += "\"id\":\"" + QString(item->whatsThis()) + "\"\n";
		}
		listitem += "},\n";
		playlistStr += listitem;
	}

	playlistStr += "]\n}";

	playlistFile->write(playlistStr.toLocal8Bit());
	playlistFile->close();
}

void PlaylistWindow::loadPlaylist()
{
	//加载本地设置
	QFile *playlistFile = new QFile("playlist.txt");
	if (!playlistFile->open(QIODevice::ReadWrite | QIODevice::Text)){
		qDebug() << "config file open failed" << endl;
	}
	else {
		QString playlistStr = playlistFile->readAll();
		QScriptEngine engine;
		QScriptValue val = engine.evaluate("value=" + playlistStr);
		QScriptValueIterator it(val.property("playlist"));

		QStringList locallist;
		while (it.hasNext())
		{
			it.next();
			locallist.clear();
			if (it.value().property("is_local").toString() == "1")
			{
				qDebug() << "name :" << it.value().property("name").toString();
				locallist.append(it.value().property("name").toString());
				addItemFromLocal(locallist, false);
			}
			else if (it.value().property("is_local").toString() == "0") {
				addItemFromNet(it.value().property("name").toString(), it.value().property("link").toString(), it.value().property("id").toInt32(), false);
			}
		}
		
	}
}
