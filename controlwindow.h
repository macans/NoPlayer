#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H
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
    explicit ControlWindow(QWidget *parent = 0);
    ~ControlWindow();
	void closeEvent(QCloseEvent *event);
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
	void slowdown();
	void spedup();
	void defaltspeed();
    void ControlWindowClosed();
     void sizeChanged(int);
     void minithenpause(bool);

     void fontChanged(QFont newfont);
 //void fontChanged(QFont newfont);
 void colorchanged(QColor newcolor);
	private slots:

     void colorshowFUN();

     void fontshowFUN();

     void zimushowFUN();
    void showshortcutKey() ;


	void doSome();




private:
	QLabel *colorshow = new QLabel();
	QLabel *fontshow = new QLabel("字体(font)");
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
