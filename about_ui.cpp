#include "about_ui.h"
#include "ui_about_ui.h"

About_ui::About_ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About_ui)
{
    ui->setupUi(this);
    setWindowOpacity(1);
    setFixedSize(850,450);
    setWindowFlags(Qt::FramelessWindowHint);
    setAutoFillBackground(true);

    QPalette palette;
    QPixmap pixmap(":/img/image/1.jpg");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(palette);
}

About_ui::~About_ui()
{
    delete ui;
}
void About_ui::mousePressEvent(QMouseEvent *event)
{
        if (event->button()==Qt::LeftButton)
        {
            dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
        else if(event->button()==Qt::RightButton)
        {
        this->close();
        }
}
void About_ui::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}
