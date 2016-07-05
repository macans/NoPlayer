#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
#include <QPushButton>

class AboutWidget : public QWidget
{
    Q_OBJECT
public:
    AboutWidget(QWidget *parent = 0);
    ~AboutWidget();

    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

private:
        QPoint dragPosition;
};

#endif // ABOUTWIDGET_H
