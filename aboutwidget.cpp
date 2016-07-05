#include "aboutwidget.h"

AboutWidget::AboutWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_QuitOnClose,false);
    setFixedSize(596,443);
    setWindowFlags(Qt::FramelessWindowHint);
}
AboutWidget::~AboutWidget()
{
}

void AboutWidget::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);
   painter.drawPixmap(0,0,width(),height(),QPixmap(":/image/x.png"));
}



void AboutWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    if (event->button() == Qt::RightButton)
    {
        this->close();
    }
}

void AboutWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}


