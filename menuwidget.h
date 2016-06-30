#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QMediaPlayer>
#include <QWidget>
#include <QToolButton>
#include <QMouseEvent>


class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(QMediaPlayer *thePlayer = 0,QWidget *parent = 0);
    //void paintEvent(QPaintEvent *event);

    QMediaPlayer *player;

    ~MenuWidget();
signals:
    void click();

private slots:
    void searchTheFile();
    void searchTheFolder();
    void ChangeTheSkin();
    void ChangeTheFont();
    void LoadURLs();
    void changeTheScreen();
    void ChangeTheNature();
    void ShowTheAbout();
    void QuitTheMedia();

private:
    QToolButton *butt1;
    QToolButton *butt2;
    QToolButton *butt3;
    QToolButton *butt4;
    QToolButton *butt5;
    QToolButton *butt6;
    QToolButton *butt7;
    QToolButton *butt8;
    QToolButton *butt9;

};

#endif // MENUWIDGET_H
