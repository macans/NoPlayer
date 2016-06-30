#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoWidget>
#include <QMouseEvent>

class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = 0);

signals:

public slots:
protected:
	void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // VIDEOWIDGET_H
