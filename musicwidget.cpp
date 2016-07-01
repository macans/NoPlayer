#include "musicwidget.h"
#include <QDebug>
#include <QTime>
#include <QtWidgets>

MusicWidget::MusicWidget(QWidget *parent,QMediaPlayer *player) : QWidget(parent),player(player),piclabel(0)
  ,piclabel2(0),timelabel(0),infolabel(0),ratelabel(0)
{
    createwidgets();
    player->setVolume(30);
    player->play();
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(updateDuration(qint64)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(updatePosition(qint64)));
    connect(player,SIGNAL(metaDataAvailableChanged(bool)),this,SLOT(updateInfo()));
}

void MusicWidget::updateDuration(qint64 duration){
    //总时间
    this->duration=duration;
    QTime total(0, duration / 60000, qRound((duration % 60000) / 1000.0));
    totaltime=total.toString(tr("mm:ss"));
}

void MusicWidget::updateInfo(){
    //获取歌曲名和歌手
    QStringList info;
    QString author=player->metaData("Author").toString();
    info += author;
    QString title =player->metaData("Title").toString();
    info += title;
    if (!info.isEmpty())
        infolabel->setText(info.join(tr("-")));
    //获取比特率/频率
    QStringList info2;
    int bitrate= player->metaData("AudioBitRate").toInt()/1000;
    int rate=player->metaData("SampleRate").toInt()/1000;
    QString sbitrate = QString::number(bitrate) + QString(tr("kbps"));
    info2 += sbitrate;
    QString srate = QString::number(rate) + QString(tr("kHz"));
    info2 += srate;
    ratelabel->setText(info2.join(tr("|")));
    //获取专辑图片
    QImage *img=new QImage;
    QImage *img2=new QImage;
     *img =player->metaData("ThumbnailImage").value<QImage>();
    //*img2=img->scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);
    piclabel->setPixmap(QPixmap::fromImage(*img));
    *img2=img->scaled(70,70,Qt::KeepAspectRatio);
    piclabel2->setPixmap(QPixmap::fromImage(*img2));
}

void MusicWidget::updatePosition(qint64 position){
    //当前播放时间
    QTime now(0, position / 60000, qRound((position % 60000) / 1000.0));
    nowtime=now.toString(tr("mm:ss"));
    QStringList timeinfo;
    timeinfo += nowtime;
    timeinfo += totaltime;
    timelabel->setText(timeinfo.join(tr("/")));
}

void MusicWidget::createwidgets(){
    piclabel = new QLabel(this);
    piclabel2 = new QLabel(this);
    timelabel = new QLabel(tr("00:00/00:00"),this);
    infolabel = new QLabel(this);
    ratelabel = new QLabel(this);
    lrc = new QCheckBox(tr("歌词"),this);
    QBoxLayout *infoLayout = new QVBoxLayout();
    infoLayout->addWidget(infolabel);
    infoLayout->addWidget(ratelabel);
    QBoxLayout *musicLayout = new QHBoxLayout();
    musicLayout->addWidget(piclabel2);
    musicLayout->addWidget(timelabel);
    musicLayout->addLayout(infoLayout);
    musicLayout->addWidget(lrc);
    QBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(piclabel, 2,Qt::AlignCenter);
    layout->addLayout(musicLayout);
}

void MusicWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton){
		emit rightButtonClicked(event->pos());
	}
}

