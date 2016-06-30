#ifndef ABOUT_UI_H
#define ABOUT_UI_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class About_ui;
}

class About_ui : public QWidget
{
    Q_OBJECT

public:
    explicit About_ui(QWidget *parent = 0);
    ~About_ui();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint dragPosition;

private:
    Ui::About_ui *ui;
};

#endif // ABOUT_UI_H
