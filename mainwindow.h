#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event);

    void initWindowSize();

private:
	QMediaPlayer *player;
	QVideoWidget *videoWidget;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
