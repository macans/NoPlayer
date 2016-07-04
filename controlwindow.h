#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include<QLabel>

class ControWindow : public QWidget
{
	Q_OBJECT

public:
	explicit ControWindow(QWidget *parent = 0);
	~ControWindow();
	void closeEvent(QCloseEvent *event);
	//void setHue(int d)
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
	void controlWindowClosed();
	void fontChanged(QFont font);
	void subtitleChanged(QString subname);
	void colorChanged(QColor color);
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
