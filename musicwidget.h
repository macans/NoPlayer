#ifndef MUSICWIDGET_H
#define MUSICWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QtNetwork>

QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QCheckBox)
QT_FORWARD_DECLARE_CLASS(QBoxLayout)

struct lrcItem{
    qint64 lrctime;
    QString text;
    lrcItem(qint64 a = 0,QString b = 0) :lrctime(a), text(b){}
    bool operator <(const lrcItem &b){
            return lrctime < b.lrctime;
    }
};

class MusicWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicWidget(QWidget *parent = 0,QMediaPlayer *player = 0);
    explicit MusicWidget(QString musicinfo,QString lrclink, QWidget *parent = 0,QMediaPlayer *player = 0);

private:
    void createwidgets();
    void getlrc();
    QString musicinfo;
    QMediaPlayer *player;
    qint64 duration;
    QLabel *piclabel;
    QLabel *piclabel2;
    QLabel *timelabel;
    QLabel *infolabel;
    QLabel *ratelabel;
    QLabel *lrclabel;
    QString totaltime;
    QString nowtime;
    QString songinfo;
    QString lrclink;
    QImage *localimg;
    QVector<lrcItem> lrctitle;
	QTime curTime;

signals:
   // void musicplayed();
	void rightButtonClicked(QPoint pos);

public slots:
    //void dealmusic();
    void updateDuration(qint64 duration);
    void updateInfo();
    void updateNetinfo();
    void updatePosition(qint64 position);
    void showlrc();
};

#endif // MUSICWIDGET_H
