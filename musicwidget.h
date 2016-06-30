#ifndef MUSICWIDGET_H
#define MUSICWIDGET_H

#include <QWidget>
#include <QMediaPlayer>

QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QCheckBox)

class MusicWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicWidget(QWidget *parent = 0,QMediaPlayer *player = 0);

private:
    void createwidgets();

    QMediaPlayer *player;
    qint64 duration;
    QLabel *piclabel;
    QLabel *piclabel2;
    QLabel *timelabel;
    QLabel *infolabel;
    QLabel *ratelabel;
    QCheckBox *lrc;
    QString totaltime;
    QString nowtime;
    QImage *img;

signals:
   // void musicplayed();

public slots:
    //void dealmusic();
    void updateDuration(qint64 duration);
    void updateInfo();
    void updatePosition(qint64 position);
};

#endif // MUSICWIDGET_H
