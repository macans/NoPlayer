#include "videowidget.h"

VideoWidget::VideoWidget(QWidget *parent) : QVideoWidget(parent)
{
	
	QPixmap pixmap(":/image/logo.png");
	QPalette palette;
	palette.setBrush(this->backgroundRole(), QBrush(pixmap));	
	palette.setBrush(QPalette::Window, QBrush(pixmap));
	this->setPalette(palette);
	//this->setStyleSheet("background-color:black");
	this->setAutoFillBackground(true);
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton) return;
	setFullScreen(!isFullScreen());
	event->accept();
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton){
		emit rightButtonClicked(event->pos());
	}
}

