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
ControWindow::ControWindow(QWidget *parent) :
QWidget(parent)
{
	//-------------------------------------------------------
	//1 //tabwidget
	QTabWidget *tabwidget = new QTabWidget();
	QWidget *widget1 = new QWidget();
	QLabel *volumelab = new QLabel("音量");
	QSlider *volume = new QSlider(Qt::Horizontal);;
	QHBoxLayout *hbox = new QHBoxLayout();
	hbox->addWidget(volumelab);
	hbox->addWidget(volume);
	widget1->setLayout(hbox);

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
	QSlider *brightness = new QSlider(Qt::Horizontal);
	QLabel *huelab = new QLabel("色彩:");
	QSlider *hue = new QSlider(Qt::Horizontal);
	QLabel *contrastlab = new QLabel("灰度:");
	QSlider *contrast = new QSlider(Qt::Horizontal);
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
	QPushButton *seekbeforemi = new QPushButton(">>");
	QPushButton *seekbeforesec = new QPushButton(">");
	QPushButton *seekaftermi = new QPushButton("<");
	QPushButton *seekaftersec = new QPushButton("<<");
	QLabel *speed = new QLabel("播放速度");
	QPushButton *slow = new QPushButton("减慢");
	QPushButton *speedup = new QPushButton("加快");
	QPushButton *defaults = new QPushButton("默认");

	grid4->addWidget(seek, 0, 0);
	grid4->addWidget(seekbeforemi, 0, 1);
	grid4->addWidget(seekbeforesec, 0, 2);
	grid4->addWidget(seekaftermi, 0, 3);
	grid4->addWidget(seekaftersec, 0, 4);
	grid4->addWidget(speed, 1, 0);
	grid4->addWidget(slow, 1, 1);
	grid4->addWidget(speedup, 1, 2);
	grid4->addWidget(defaults, 1, 3);
	widget4->setLayout(grid4);


	QIcon icon1("/User1/tianfeihan/Deaktop/1.png");
	tabwidget->addTab(widget1, icon1, "音频");

	QIcon icon2("/User1/tianfeihan/Deaktop/1.png");
	tabwidget->addTab(widget2, icon2, "字幕");

	QIcon icon3("/User1/tianfeihan/Deaktop/1.png");
	tabwidget->addTab(widget3, icon3, "视频");

	QIcon icon4("/User1/tianfeihan/Deaktop/1.png");
	tabwidget->addTab(widget4, icon4, "播放");

	QHBoxLayout *total = new QHBoxLayout();
	total->addWidget(tabwidget);
	this->setLayout(total);
	this->resize(300, 300);
	this->setWindowTitle("控制面板");



	//volume
	connect(volume, SIGNAL(valueChanged(int)), this, SIGNAL(changeVolume(int)));
	//brightness
	connect(brightness, SIGNAL(valueChanged(int)), this, SIGNAL(changeBrightness(int)));
	//hue
	connect(hue, SIGNAL(valueChanged(int)), this, SIGNAL(changeHue(int)));
	//contrast
	connect(contrast, SIGNAL(valueChanged(int)), this, SIGNAL(changeContrast(int)));
	//show color
	connect(morecolor, SIGNAL(clicked(bool)), this, SLOT(colorshowFUN()));
	//show font
	connect(morefont, SIGNAL(clicked(bool)), this, SLOT(fontshowFUN()));
	//show zimu
	connect(morezimu, SIGNAL(clicked(bool)), this, SLOT(zimushowFUN()));

	connect(seekbeforemi, SIGNAL(clicked(bool)), this, SIGNAL(seekbeforemi()));

	connect(seekbeforesec, SIGNAL(clicked(bool)), this, SIGNAL(seekbeforesec()));
	connect(seekaftersec, SIGNAL(clicked(bool)), this, SIGNAL(seekaftersec()));
	connect(seekaftermi, SIGNAL(clicked(bool)), this, SIGNAL(seekafteremi()));

	connect(slow, SIGNAL(clicked(bool)), this, SIGNAL(slowdown()));

	connect(speedup, SIGNAL(clicked(bool)), this, SIGNAL(spedup()));
	connect(defaults, SIGNAL(clicked(bool)), this, SIGNAL(defaltspeed()));

	//--------------------------------------------------------------
}

ControWindow::~ControWindow()
{
	emit controlWindowClosed();
}

void ControWindow::colorshowFUN()
{
	colorshow->setAutoFillBackground(true);
	QColorDialog dialog(Qt::red, this);
	dialog.setOption(QColorDialog::ShowAlphaChannel);
	dialog.exec();
	QColor color = dialog.currentColor();
	if (color.isValid()){
		colorshow->setPalette(QPalette(color));
	}

}

void ControWindow::fontshowFUN(){
	bool ok;
	QFont  font = QFontDialog::getFont(&ok);
	if (ok){
		QString name = font.family();
		fontshow->setFont(font);
	}
	else {

	}
}

void ControWindow::zimushowFUN()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("打开文件"), "/", tr("字幕(*srt)"));
    //QString filename = QFileDialog::getOpenFileName(this, tr("文件对话框"), "/", tr("视频文件(*mp4)"));
}

void ControWindow::doSome()
{
	int a = 1;
}

void ControWindow::closeEvent(QCloseEvent *event)
{
	emit controlWindowClosed();
}
