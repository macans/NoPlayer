#include "propertywidget.h"

PropertyWidget::PropertyWidget(QWidget *parent,QMediaPlayer *player)
    :QWidget(parent),player(player)
{
    setStyleSheet("background-color:rgb(234,234,234)");
    setAttribute(Qt::WA_QuitOnClose,false);
    setFixedSize(270,190);
    setWindowFlags(Qt::FramelessWindowHint);

    label1 =new QLabel(this);
    label2=new QLabel(this);
    label3=new QLabel(this);
    name_label =new QLabel(this);
    size_label=new QLabel(this);
    date_label=new QLabel(this);

    label1->setGeometry(10,30,45,20);
    label2->setGeometry(10,80,45,20);
    label3->setGeometry(10,130,45,20);
    name_label->setGeometry(70,30,175,20);
    size_label->setGeometry(70,80,175,20);
    date_label->setGeometry(70,130,175,20);

    label1->setText(tr("Name:"));
    label2->setText(tr("Size:"));
    label3->setText(tr("Date:"));

    connect(player,SIGNAL(metaDataAvailableChanged(bool)),this,SLOT(updateInfo()));
}
PropertyWidget::~PropertyWidget()
{
}

void PropertyWidget::updateInfo()
{
    name_label->setText(player->metaData("Author").toString());
    size_label->setText(player->metaData("Size").toString());
    date_label->setText(player->metaData("Date").toString());

}
void PropertyWidget::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);
   painter.drawLine(60,55,250,55);
   painter.drawLine(60,105,250,105);
   painter.drawLine(60,155,250,155);
}



void PropertyWidget::mousePressEvent(QMouseEvent *event)
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

void PropertyWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

