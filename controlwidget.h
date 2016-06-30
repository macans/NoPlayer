#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include<QLabel>

class ControlWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ControlWidget(QWidget *parent = 0);
	~ControlWidget();
	void closeEvent(QCloseEvent *event);
signals:
	void changeVolume(int);
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
	void controlWidgetClosed();
	private slots:
	void colorshowFUN();

	void fontshowFUN();

	void zimushowFUN();
	void doSome();




private:
	QLabel *colorshow = new QLabel();
	QLabel *fontshow = new QLabel("字体(font)");
};

#endif // CONTROLWIDGET_H
