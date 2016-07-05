#include "controlwindow.h"

#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QIcon>
#include <QVideoWidget>
#include <QColorDialog>
#include <QFont>
#include <QFontDialog>
#include <QPalette>
#include <QFileDialog>
#include <QString>
#include <QGridLayout>
#include <QSlider>
#include <QRadioButton>
#include <QComboBox>
#include <QMessageBox>
ControlWindow::ControlWindow(QWidget *parent) :
QWidget(parent)
{
	//-------------------------------------------------------
    //1 //tabwidget
    QTabWidget *tabwidget = new QTabWidget();

	QWidget *widget1 = new QWidget();
    QGridLayout *grid1 = new QGridLayout();
    QLabel *Lmini_pause = new QLabel("Stop");
    QLabel *Lsize = new QLabel("Size while open");
    QPushButton *Lshortcut_key = new QPushButton("View shorcut");
    QRadioButton *Cmini_pause=new QRadioButton();
    QComboBox *Csize=new QComboBox();
    //QIcon icon5(":/image/sound.png");
    Csize->addItem("默认尺寸");
    //QIcon icon6(":/image/sound.png");
    Csize->addItem("视频尺寸");
    //QIcon icon7(":/image/sound.png");
    Csize->addItem("全屏");

    /*QLabel *play_pause = new QLabel("播放／暂停 :");
    QLabel *exit = new QLabel("退出:");
    QLabel *slow_down= new QLabel("快进:");
    QLabel *speed_up = new QLabel("快退:");

    QLabel *Lplay_pause = new QLabel("space");
    QLabel *Lexit = new QLabel("ctr+q");
    QLabel *Lslow_down= new QLabel(">");
    QLabel *Lspeed_up = new QLabel("<");*/

    //grid1->addWidget(volumelab, 0,0);
    //grid1->addWidget(volume,0,1,1,2);
    grid1->addWidget(Cmini_pause, 0,1);
    grid1->addWidget(Lmini_pause,0,0);
    grid1->addWidget(Lsize, 1,0);
    grid1->addWidget(Csize, 1,1,1,2);
    grid1->addWidget(Lshortcut_key, 2,0);

    /*grid1->addWidget(play_pause,2,1);
    grid1->addWidget(Lplay_pause,2,2);

    grid1->addWidget(exit, 3,1);
    grid1->addWidget(Lexit, 3,2);

    grid1->addWidget(slow_down, 4,1);
    grid1->addWidget(Lslow_down, 4,2);
    grid1->addWidget(speed_up, 5,1);
    grid1->addWidget(Lspeed_up, 5,2);*/

    widget1->setLayout(grid1);

	//2
	QWidget *widget2 = new QWidget();
	QGridLayout *grid2 = new QGridLayout();
	QLabel *color = new QLabel("颜色:");
	QLabel *fontchange = new QLabel("字体:");
	QLabel *zimufile = new QLabel("文件:");
	//QLabel *colorshow=new QLabel();
	//QLabel *fontshow=new QLabel("字体(font)");
	QPushButton *morecolor = new QPushButton("更多颜色");
	QPushButton *morefont = new QPushButton("更多字体");
	QPushButton *morezimu = new QPushButton("更多字幕");
	grid2->addWidget(color, 0, 0);
	grid2->addWidget(colorshow, 0, 1);
	grid2->addWidget(morecolor, 0, 2);
	grid2->addWidget(fontchange, 1, 0);
	grid2->addWidget(fontshow, 1, 1);
	grid2->addWidget(morefont, 1, 2);
	grid2->addWidget(zimufile, 2, 0);
	grid2->addWidget(morezimu, 2, 2);
	widget2->setLayout(grid2);
	//3
	QGridLayout *grid3 = new QGridLayout();
	QWidget *widget3 = new QWidget();
	QLabel *brightnesslab = new QLabel("亮度:");
	brightness->setRange(-100, 100);
    //QSlider *brightness = new QSlider(Qt::Horizontal);
	QLabel *huelab = new QLabel("色彩:");
	hue->setRange(-100, 100);
    //QSlider *hue = new QSlider(Qt::Horizontal);
    QLabel *contrastlab = new QLabel(" 对比度:");
	contrast->setRange(-100, 100);
    //QSlider *contrast = new QSlider(Qt::Horizontal);
	grid3->addWidget(brightnesslab, 0, 0);
	grid3->addWidget(brightness, 0, 1);
	grid3->addWidget(huelab, 1, 0);
	grid3->addWidget(hue, 1, 1);
	grid3->addWidget(contrastlab, 2, 0);
	grid3->addWidget(contrast, 2, 1);
	widget3->setLayout(grid3);

	//4
    QGridLayout *grid4 = new QGridLayout();
    QWidget *widget4 = new QWidget();
    QLabel *seek = new QLabel("搜索");
    QPushButton *seekbeforemi = new QPushButton("<<");
       seekbeforemi->setObjectName("seekbeforemi");
    QPushButton *seekbeforesec = new QPushButton("<");
    seekbeforesec->setObjectName("seekbeforesec");
    QPushButton *seekaftermi = new QPushButton(">");
    seekaftermi->setObjectName("seekaftermi");
    QPushButton *seekaftersec = new QPushButton(">>");
     seekaftersec->setObjectName("seekaftersec");
    QLabel *speed = new QLabel("播放速度");
    QPushButton *slow = new QPushButton("减慢");
    slow->setObjectName("slow");
    QPushButton *speedup = new QPushButton("加快");
    speedup->setObjectName("speedup");
    QPushButton *defaults = new QPushButton("默认");
    defaults->setObjectName("defaults");

    grid4->addWidget(seek, 0, 0);
    grid4->addWidget(seekbeforemi, 0, 1,1,2);
    grid4->addWidget(seekbeforesec, 0, 3,1,2);
    grid4->addWidget(seekaftermi, 0, 5,1,2);
    grid4->addWidget(seekaftersec, 0, 7,1,2);
    grid4->addWidget(speed, 1, 0);
    grid4->addWidget(slow, 1, 2,1,2);
    grid4->addWidget(speedup, 1, 4,1,2);
    grid4->addWidget(defaults, 1, 6,1,2);
    widget4->setLayout(grid4);


    QIcon icon1(":/image/sound.png");
    tabwidget->addTab(widget1, icon1, "常规");

    QIcon icon2(":/image/subtitle.png");
	tabwidget->addTab(widget2, icon2, "字幕");

    QIcon icon3(":/image/video.png");
	tabwidget->addTab(widget3, icon3, "视频");

    QIcon icon4(":/image/play.png");
	tabwidget->addTab(widget4, icon4, "播放");

	QHBoxLayout *total = new QHBoxLayout();
	total->addWidget(tabwidget);
	this->setLayout(total);
    this->setFixedSize(400, 300);//fix size
	this->setWindowTitle("控制面板");


	//volume
    //connect(volume, SIGNAL(valueChanged(int)), this, SIGNAL(changeVolume(int)));
	//brightness
	connect(brightness, SIGNAL(valueChanged(int)), this, SIGNAL(changeBrightness(int)));
	//hue
	connect(hue, SIGNAL(valueChanged(int)), this, SIGNAL(changeHue(int)));
	//contrast
	connect(contrast, SIGNAL(valueChanged(int)), this, SIGNAL(changeContrast(int)));
	//show color
    connect(morecolor, SIGNAL(clicked(bool)), this, SLOT(colorshowFUN()));
    //------------------------------------------
	//show font
    connect(morefont, SIGNAL(clicked(bool)), this, SLOT(fontshowFUN()));
	//show zimu
    connect(morezimu, SIGNAL(clicked(bool)), this, SLOT(zimushowFUN()));
    //-------------------------------------------

	connect(seekbeforemi, SIGNAL(clicked(bool)), this, SIGNAL(seekbeforemi()));

	connect(seekbeforesec, SIGNAL(clicked(bool)), this, SIGNAL(seekbeforesec()));
	connect(seekaftersec, SIGNAL(clicked(bool)), this, SIGNAL(seekaftersec()));
	connect(seekaftermi, SIGNAL(clicked(bool)), this, SIGNAL(seekafteremi()));

	connect(slow, SIGNAL(clicked(bool)), this, SIGNAL(slowdown()));

	connect(speedup, SIGNAL(clicked(bool)), this, SIGNAL(spedup()));
	connect(defaults, SIGNAL(clicked(bool)), this, SIGNAL(defaltspeed()));
    //when video opened,the size
    connect(Csize,SIGNAL(currentIndexChanged(int)),this,SIGNAL(sizeChanged(int)));

    //minisize then pause
    //connect(Cmini_pause,SIGNAL(currentIndexChanged(int)),this,SIGNAL(sizeChanged(int)));
    //


    connect(Cmini_pause,SIGNAL(clicked(bool)),this,SIGNAL(minithenpause(bool)));

    connect(Lshortcut_key,SIGNAL(clicked(bool)),this,SLOT(showshortcutKey()));
	//--------------------------------------------------------------
}

ControlWindow::~ControlWindow()
{
    emit ControlWindowClosed();
}

void ControlWindow::colorshowFUN()
{
	colorshow->setAutoFillBackground(true);
	QColorDialog dialog(Qt::red, this);
	dialog.setOption(QColorDialog::ShowAlphaChannel);
	dialog.exec();
	QColor color = dialog.currentColor();
	if (color.isValid()){
		colorshow->setPalette(QPalette(color));
        emit colorchanged(color);
	}

}

void ControlWindow::fontshowFUN(){
	bool ok;
	QFont  font = QFontDialog::getFont(&ok);
	if (ok){
        QString fontname=font.family();
		fontshow->setFont(font);
        emit fontChanged(font);
	}
	else {

	}
}

void ControlWindow::zimushowFUN()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("打开文件"), "/", tr("字幕(*srt)"));

}

void ControlWindow::doSome()
{
	int a = 1;
}

void ControlWindow::closeEvent(QCloseEvent *event)
{
    emit ControlWindowClosed();
}

/*void ControlWindow::setVolume(int number1){
    thenumber1=number1;
    volume->setValue(thenumber1);
}*/

void ControlWindow::setHueFUN(int number2){
    thenumber2=number2;
    hue->setValue(thenumber2);
}
 void ControlWindow::setContrastFUN(int number3){
     thenumber3=number3;
     contrast->setValue(thenumber3);
 }
  void ControlWindow::setBritghtnessFUN(int number4){
      thenumber4=number4;
      brightness->setValue(thenumber4);

  }

   void ControlWindow::showshortcutKey()
      {
      shortcut *shortcu=new shortcut();
       shortcu->show();
   }


