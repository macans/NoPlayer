#include "playlistwidget.h"

PlaylistView::PlaylistView(QMediaPlaylist *playList,QWidget *parent) : QWidget(parent)
{
    playlist = playList;
    listWidget = new QListWidget(this);
    QStringList tempList;
    tempList.append("F://hehe.mp4");
    tempList<<"C://我还能这.mp3";
    tempList.append("C://至少还有你.mp3");
    tempList<<"C://你心永恒.mp3";
    tempList <<"F://hehe.mp4";
    tempList<<"C://我还能这.mp3";
    tempList<<"C://至少还有你.mp3";
    tempList<<"C://你心永恒.mp3";
    tempList <<"F://hehe.mp4";
    tempList<<"C://我还能这.mp3";
    tempList<<"C://至少还有你.mp3";

    this->addItemFromLocal(tempList);
    this->addItemFromLocal(tempList);
    this->addItemFromNet("Beyond-海阔天空","http://yinyueshiting.baidu.com/data2/music/238976206/877578151200128.mp3?xcode=2e844a1506aeb2b1d7984b79751f9d39",1232123);
    this->addItemFromNet("Beyond-海阔天空","http://yinyueshiting.baidu.com/data2/music/238976206/877578151200128.mp3?xcode=2e844a1506aeb2b1d7984b79751f9d39",1232123);
    this->addItemFromNet("Beyond-海阔天空","http://yinyueshiting.baidu.com/data2/music/238976206/877578151200128.mp3?xcode=2e844a1506aeb2b1d7984b79751f9d39",1232123);


//----布局---------------------------------------
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(listWidget);
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    playType = new QPushButton(QIcon(":image/ic6.png"),"");
    playType->setToolTip("点击切换播放模式");
    search_edit = new QLineEdit();

    search_btn = new QPushButton(QIcon(":image/ic7.png"),"");
    search_btn->setToolTip("搜索");
    addBtn = new QPushButton(QIcon(":image/ic4.png"),"");
    addBtn->setToolTip("添加");
    delBtn = new QPushButton(QIcon(":image/ic8.png"),"");
    delBtn->setToolTip("移除");
    clearBtn = new QPushButton(QIcon(":image/ic9.png"),"");
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
    connect(listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SIGNAL(itemDoubleClicked(QListWidgetItem*)));
    connect(listWidget,SIGNAL(itemEntered(QListWidgetItem*)),this,SIGNAL(itemEntered(QListWidgetItem*)));
    connect(listWidget,SIGNAL(itemPressed(QListWidgetItem*)),this,SIGNAL(itemPressed(QListWidgetItem*)));
    connect(listWidget,SIGNAL(itemSelectionChanged()),this,SIGNAL(itemSelectionChanged()));

    connect(delBtn,SIGNAL(clicked(bool)),this,SLOT(removeItems()));
    connect(clearBtn,SIGNAL(clicked(bool)),listWidget,SLOT(clear()));
    connect(search_btn,SIGNAL(clicked(bool)),this,SLOT(searchItem()));
    connect(listWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(clearSearch()));
    connect(listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(setItemPlay(QListWidgetItem*)));

    connect(playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(setItemPlay(int)));
//------signal-end------------

}


//-----------slots-start--------
//清空列表和playlist
void PlaylistView::clear()
{
    listWidget->clear();
    playlist->clear();
}

//移除当前被选中的item
void PlaylistView::removeItems()
{
    if(listWidget->currentItem() == listWidget->item(playlist->currentIndex())) {
       playlist->setCurrentIndex(0);
    }
    int row = listWidget->currentRow();
    listWidget->takeItem(row);
    playlist->removeMedia(row);
    this->updateIndex();
    listWidget->update();

}

//搜索items
void PlaylistView::searchItem()
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
void PlaylistView::clearSearch()
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

//将item设置为播放项，并将原来的项设置为普通状态的样式
void PlaylistView::setItemPlay(QListWidgetItem *item)
{
    if(item != listWidget->item(playlist->currentIndex())) {
        if(listWidget->item(playlist->currentIndex())!=NULL) {
           this->setItemNormalView(listWidget->item(playlist->currentIndex()));
        }
        playlist->setCurrentIndex(listWidget->row(item));
        this->setItemPlayView(item);
    }
}
//将行号为row的设置为播放项
void PlaylistView::setItemPlay(int row)
{
    QListWidgetItem *item = listWidget->item(row);
    this->setItemPlayView(item);
    qDebug("%d",row);
}

//设置播放状态下的样式
void PlaylistView::setItemPlayView(QListWidgetItem *item)
{
    item->setTextColor(ITEM_COLOR_PLAY);
}

//设置普通状态下的样式
void PlaylistView::setItemNormalView(QListWidgetItem *item)
{
    item->setTextColor(ITEM_COLOR_NORMAL);
}

//设置搜索到的item的样式
void PlaylistView::setItemSearchView(QListWidgetItem *item)
{
    item->setTextColor(ITEM_COLOR_SEARCH);
}
//设置播放模式
//void PlaylistView::setPlayMode()
//{
//    if(playBackMode<4) {
//        playBackMode++;
//    } else{
//        playBackMode = 1;
//    }
//    switch(playBackMode) {
//    case 1:
//        playType->setIcon(":image/ic");
//    }
//}

//当列表移除某一项之后，重新更新每一项前面的index
void PlaylistView::updateIndex()
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
            tmpItem->setText(index.append(". ").append(tmpItem->statusTip()));
        }
    }
}



//-----------slots-end------------



//从本地添加items
void PlaylistView::addItemFromLocal(const QStringList &addList,bool playNow)
{
    for(int i=0;i<addList.length();i++) {
        QString label = addList.at(i);
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
        item->setIcon(QIcon(":/image/mp4.png"));
        item->setToolTip(label);
        this->setItemNormalView(item);

        //添加到playlist 并将第一条设置为当前播放item
        playlist->addMedia(QUrl::fromLocalFile(label));
        if(0 == i){
            if(playNow){
                this->setItemPlay(item);
                qDebug("%d",playlist->currentIndex());
            }
        }
    }
}


//添加网络item
void PlaylistView::addItemFromNet(const QString &additem, const QString &link,int id)
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
    item->setIcon(QIcon(":/image/mp4.png"));
    item->setWhatsThis(QString::number(id,10));
    item->setStatusTip(additem);
    this->setItemNormalView(item);

    //添加到playlist 并将第一条设置为当前播放item
    playlist->addMedia(QUrl(link));
    this->setItemPlay(item);
    qDebug("%d",playlist->currentIndex());

}
