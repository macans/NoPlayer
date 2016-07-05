#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
#include <QPushButton>
#include <QLabel>
#include <QMediaPlayer>
#include <QMediaMetaData>

class PropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertyWidget(QWidget *parent = 0,QMediaPlayer *player = 0);
    ~PropertyWidget();

    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void updateInfo();
private:
        QPoint dragPosition;
        QMediaPlayer *player;
        QLabel *label1;
        QLabel *label2;
        QLabel *label3;
        QLabel *name_label;
        QLabel *size_label;
        QLabel *date_label;
};

#endif // PROPERTYWIDGET_H
