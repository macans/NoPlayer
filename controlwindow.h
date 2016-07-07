#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H
#include "playconfig.h"
#include "shortcut.h"
#include <QWidget>
#include<QLabel>
#include <QSlider>
#include <QFont>
#include<QColor>
class ControlWindow : public QWidget
{
	Q_OBJECT

public:
    explicit ControlWindow(PlayConfig *config = 0, QWidget *parent = 0);
    ~ControlWindow();
    //void setVolume(int number1);
     void setHueFUN(int number2);
      void setContrastFUN(int number3);
       void setBritghtnessFUN(int number4);


signals:
    //void changeVolume(int);
	void changeBrightness(int);
	void changeHue(int);
	void changeContrast(int);
	void seekbeforemi();
	void seekbeforesec();
	void seekafteremi();
	void seekaftersec();
	void rateSlowDown();
	void rateSpeedUp();
	void rateDefault();
	void rewindSec(qint64 sec = -SRCH_STEP_MIN);
	void rewindMsec(qint64 msec = -SRCH_STEP_SEC);
	void fastforwordSec();
	void fastforwordMsec(qint64 msec = SRCH_STEP_MIN);
    void controlWindowClosed();
     void sizeChanged(int);
     void skinChanged(int);
     void minithenpause(bool);
     void fontChanged(QFont newfont);
	//void fontChanged(QFont newfont);
	void colorChanged(QColor newcolor);
	void subtitleChanged(QString name);
	
private slots:
	void closeEvent(QCloseEvent *event);
     void colorshowFUN();

     void fontshowFUN();

     void zimushowFUN();
    void showshortcutKey() ;


	void doSome();




private:
	QLabel *colorshow = new QLabel();
	QLabel *fontshow = new QLabel("字体(font)");
	static const int stepSec;
    int thenumber1;
    int thenumber2;
    int thenumber3;
    int thenumber4;

    //QSlider *volume = new QSlider(Qt::Horizontal);
    QSlider *brightness = new QSlider(Qt::Horizontal);

    QSlider *hue = new QSlider(Qt::Horizontal);

    QSlider *contrast = new QSlider(Qt::Horizontal);
};

#endif // CONTROLWIDGET_H
