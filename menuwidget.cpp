#include "menuwidget.h"
#include "about_ui.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>


MenuWidget::MenuWidget(QMediaPlayer *thePlayer ,QWidget *parent) :
    QWidget(parent)
{
    player = thePlayer;
    setFixedSize(160,270);
    setWindowFlags(Qt::FramelessWindowHint);
    butt1=new QToolButton(this);
    butt1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    butt1->setIcon(QIcon(":./img/image/ic1.jpg"));
    butt1->setText("     file");
    butt1->setGeometry(0,0,220,30);
    butt1->setStyleSheet("QToolButton { background-color: rgb(234, 234, 234); border-radius: 3px; color: rgb(0, 0, 0);}"
                         "QToolButton:hover { background-color: rgb(143, 214, 214); }");
    butt2=new QToolButton(this);
    butt2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    butt2->setIcon(QIcon(":./img/image/ic2.png"));
    butt2->setText("    folder");
    butt2->setGeometry(0,30,220,30);
    butt2->setStyleSheet("QToolButton { background-color: rgb(234, 234, 234); border-radius: 3px; color: rgb(0, 0, 0);}"
                         "QToolButton:hover { background-color: rgb(143, 214, 214); }");
    butt3=new QToolButton(this);
    butt3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    butt3->setIcon(QIcon(":./img/image/ic3.png"));
    butt3->setText("     skin");
    butt3->setGeometry(0,60,220,30);
    butt3->setStyleSheet("QToolButton { background-color: rgb(234, 234, 234); border-radius: 3px; color: rgb(0, 0, 0);}"
                         "QToolButton:hover { background-color: rgb(143, 214, 214); }");
    butt4=new QToolButton(this);
    butt4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    butt4->setIcon(QIcon(":./img/image/ic4.png"));
    butt4->setText("     font");
    butt4->setGeometry(0,90,220,30);
    butt4->setStyleSheet("QToolButton { background-color: rgb(234, 234, 234); border-radius: 3px; color: rgb(0, 0, 0);}"
                         "QToolButton:hover { background-color: rgb(143, 214, 214); }");
    butt5=new QToolButton(this);
    butt5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    butt5->setIcon(QIcon(":./img/image/ic5.png"));
    butt5->setText("     URLs");
    butt5->setGeometry(0,120,220,30);
    butt5->setStyleSheet("QToolButton { background-color: rgb(234, 234, 234); border-radius: 3px; color: rgb(0, 0, 0);}"
                         "QToolButton:hover { background-color: rgb(143, 214, 214); }");
    butt6=new QToolButton(this);
    butt6->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    butt6->setIcon(QIcon(":./img/image/ic6.png"));
    butt6->setText("    screen");
    butt6->setGeometry(0,150,220,30);
    butt6->setStyleSheet("QToolButton { background-color: rgb(234, 234, 234);border-radius: 3px; color: rgb(0, 0, 0);}"
                         "QToolButton:hover { background-color: rgb(143, 214, 214); }");
    butt7=new QToolButton(this);
    butt7->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    butt7->setIcon(QIcon(":./img/image/ic7.png"));
    butt7->setText("    nature");
    butt7->setGeometry(0,180,220,30);
    butt7->setStyleSheet("QToolButton { background-color: rgb(234, 234, 234); border-radius: 3px; color: rgb(0, 0, 0);}"
                         "QToolButton:hover { background-color: rgb(143, 214, 214); }");
    butt8=new QToolButton(this);
    butt8->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    butt8->setIcon(QIcon(":./img/image/ic8.png"));
    butt8->setText("     about");
    butt8->setGeometry(0,210,220,30);
    butt8->setStyleSheet("QToolButton { background-color: rgb(234, 234, 234); border-radius: 3px; color: rgb(0, 0, 0);}"
                         "QToolButton:hover { background-color: rgb(143, 214, 214); }");
    butt9=new QToolButton(this);
    butt9->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    butt9->setIcon(QIcon(":./img/image/ic9.png"));
    butt9->setText("     quit");
    butt9->setGeometry(0,240,220,30);
    butt9->setStyleSheet("QToolButton { background-color: rgb(234, 234, 234); border-radius: 3px; color: rgb(0, 0, 0);}"
                         "QToolButton:hover { background-color: rgb(143, 214, 214); }");
    connect(butt1,SIGNAL(clicked()),this,SLOT(searchTheFile()));
    connect(butt2,SIGNAL(clicked()),this,SLOT(searchTheFolder()));
    connect(butt3,SIGNAL(clicked()),this,SLOT(ChangeTheSkin()));
    connect(butt4,SIGNAL(clicked()),this,SLOT(ChangeTheFont()));
    connect(butt5,SIGNAL(clicked()),this,SLOT(LoadURLs()));
    connect(butt6,SIGNAL(clicked()),this,SLOT(changeTheScreen()));
    connect(butt7,SIGNAL(clicked()),this,SLOT(ChangeTheNature()));
    connect(butt8,SIGNAL(clicked()),this,SLOT(ShowTheAbout()));
    connect(butt9,SIGNAL(clicked()),this,SLOT(QuitTheMedia()));

}

MenuWidget::~MenuWidget()
{

}
/*
void MenuWidget::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.setPen(Qt::red);
    paint.drawLine(30,0,30,270);
}
*/

void MenuWidget::searchTheFile()
{
    //this->close();
    QString filePath=QFileDialog::getOpenFileName(this,tr("Open Media"),".",
                 tr("image Files(*.mpg *.mp3 *.mp4 *.avi *.flv)"));
    if(filePath.length()!=0)
    {
        //player->setMedia(QUrl::fromLocalFile(filePath));

    }

}

void MenuWidget::searchTheFolder()
{
     QString folderPath=QFileDialog::getExistingDirectory(this,tr("OpenDictory"));
     if(folderPath.length()!=0)
     {
     }
}


void MenuWidget::ChangeTheSkin()
{

}


void MenuWidget::ChangeTheFont()
{
    //this->close();
    bool ok;
    QFont font=QFontDialog::getFont(&ok,QFont("times",12),this);
    if(ok)
    {
    }
}
void MenuWidget::LoadURLs()
{

}
void MenuWidget::changeTheScreen()
{

}
void MenuWidget::ChangeTheNature()
{

}

void MenuWidget::ShowTheAbout()
{
    //this->close()
    About_ui *the_ui=new About_ui();
    the_ui->show();

}

void MenuWidget::QuitTheMedia()
{
    exit(0);
}

