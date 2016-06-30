#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{

    player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile("E:\\Flash\\Youtube\\Jiang\\HK.mp4"));
    videoWidget = new QVideoWidget(this);
    player->setVideoOutput(videoWidget);
	
	//ct .canonicalResource()
    initWindowSize();
    videoWidget->show();
    player->play();
	//QSize sz = player->media().canonicalResource().resolution();
	QVariant sz = player->metaData("Resolution");

}

MainWindow::~MainWindow()
{
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){

    }
}

void MainWindow::initWindowSize()
{

}
