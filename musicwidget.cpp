#include "musicwidget.h"

#include <QDebug>
#include <QTime>
#include <QtWidgets>
#include <QTScript>

MusicWidget::MusicWidget(QWidget *parent,QMediaPlayer *player) : QWidget(parent),player(player),piclabel(0)
  ,piclabel2(0),timelabel(0),infolabel(0),ratelabel(0),lrclabel(0)
{
    createwidgets();
	this->curPlayModel = MODEL_LAC;
    player->play();
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(updateDuration(qint64)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(updatePosition(qint64)));
    connect(player,SIGNAL(metaDataAvailableChanged(bool)),this,SLOT(updateInfo()));
}

MusicWidget::MusicWidget(QString musicinfo, QString lrclink, QWidget *parent, QMediaPlayer *player):musicinfo(musicinfo),lrclink(lrclink),QWidget(parent),player(player),piclabel(0)
  ,piclabel2(0),timelabel(0),infolabel(0),ratelabel(0),lrclabel(0)
{
	QNetworkProxy proxy;
	proxy.setType(QNetworkProxy::Socks5Proxy);
	proxy.setHostName("127.0.0.1");
	proxy.setPort(1080);
	QNetworkProxy::setApplicationProxy(proxy);
    createwidgets();
	this->curPlayModel = MODEL_NET;

	curTime = QTime::currentTime();
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(updateDuration(qint64)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(updatePosition(qint64)));
    connect(player,SIGNAL(metaDataAvailableChanged(bool)),this,SLOT(updateNetinfo()));
    getlrc();
	qDebug() << curTime.toString();
	player->play();
}
void MusicWidget::updateDuration(qint64 duration){
    //总时间
	qDebug() << curTime.toString();
    this->duration=duration;
    QTime total(0, duration / 60000, qRound((duration % 60000) / 1000.0));
    totaltime=total.toString(tr("mm:ss"));
}

void MusicWidget::updateInfo(){
    //获取歌曲名和歌手
	qDebug() << curTime.toString();
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
    *img2=img->scaled(70,70,Qt::KeepAspectRatio);
    if(!img->isNull()){
    piclabel->setPixmap(QPixmap::fromImage(*img));
    piclabel2->setPixmap(QPixmap::fromImage(*img2));
    }
}

void MusicWidget::updatePosition(qint64 position){
    //当前播放时间
	qDebug() << curTime.toString();
    QTime now(0, position / 60000, qRound((position % 60000) / 1000.0));
    nowtime=now.toString(tr("mm:ss"));
    QStringList timeinfo;
    timeinfo += nowtime;
    timeinfo += totaltime;
    timelabel->setText(timeinfo.join(tr("/")));
	if (curPlayModel == MODEL_LAC) return;

    QVector <lrcItem>::iterator it = qLowerBound(lrctitle.begin(),lrctitle.end(),lrcItem(position,""));
	QString text = (*it).text;
    if((*it).lrctime==position){
		lrclabel->setText(text);
    }
	else{
		if (it != lrctitle.begin())
			it--;
		text = (*it).text;
		lrclabel->setText(text);
	}
}

void MusicWidget::updateNetinfo(){
    //获取歌曲名和歌手
	qDebug() << curTime.toString();
    QStringList info;
    QString author=player->metaData("Author").toString();
    info += author;
    QString title =player->metaData("Title").toString();
    info += title;
    if (!info.isEmpty())
        infolabel->setText(info.join(tr("-")));
    //获取比特率/频率
    QStringList info2;
    //int bitrate= player->metaData("AudioBitRate").toInt()/1000;
    //int rate=player->metaData("SampleRate").toInt()/1000;
    QString sbitrate =  QString(tr("128kbps"));
    info2 += sbitrate;
    QString srate =  QString(tr("44kHz"));
    info2 += srate;
    ratelabel->setText(info2.join(tr("|")));
    //解析musicinfo，获取专辑图片
    QScriptEngine engine;
    QScriptValue sc =  engine.evaluate("value=" + musicinfo);
    qDebug()<<sc.property("data").property("songList").isArray()<<endl;
    QScriptValueIterator songlist(sc.property("data").property("songList"));
    songlist.next();
    QString imglink = songlist.value().property("songPicRadio").toString();
    qDebug()<<"jpg:"<<imglink<<endl;
    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(imglink)));
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QByteArray jpgData = reply->readAll();
    QPixmap pixmap,pixmap2;
    pixmap.loadFromData(jpgData);
    pixmap2=pixmap.scaled(70,70,Qt::KeepAspectRatio);
    if(!pixmap.isNull()){
        piclabel->setPixmap(pixmap);
        piclabel2->setPixmap(pixmap2);
    }
}

void MusicWidget::createwidgets(){

    piclabel = new QLabel(this);
    piclabel2 = new QLabel(this);
    localimg=new QImage(":/image/logo.png");
    QImage *img2=new QImage;
    piclabel->setPixmap(QPixmap::fromImage(*localimg));
    *img2=localimg->scaled(70,70,Qt::KeepAspectRatio);
    piclabel2->setPixmap(QPixmap::fromImage(*img2));
    timelabel = new QLabel(tr("00:00/00:00"),this);
    infolabel = new QLabel(this);
    ratelabel = new QLabel(this);
	lrclabel = new QLabel(this);
    QBoxLayout *infoLayout = new QVBoxLayout();
    infoLayout->addWidget(infolabel);
    infoLayout->addWidget(ratelabel);
    QBoxLayout *musicLayout = new QHBoxLayout();
    musicLayout->addWidget(piclabel2);
    musicLayout->addWidget(timelabel);
    musicLayout->addLayout(infoLayout);
    QBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(piclabel, 2,Qt::AlignCenter);
    layout->addLayout(musicLayout);
	layout->addWidget(lrclabel);
}



void MusicWidget::showlrc(){

}

void MusicWidget::getlrc(){
    lrctitle.clear();
    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(lrclink)));
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QString lrcData = reply->readAll();

    if(lrcData.isNull()){
        lrclabel->setText("no lyric file!");
        return;
    }

    QStringList lines = lrcData.split("\n");
    QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
    foreach(QString oneline, lines) {
        QString temp = oneline;
        temp.replace(rx, "");//用空字符串替换正则表达式中所匹配的地方,这样就获得了歌词文本
        //indexIn()为返回第一个匹配的位置，如果返回为-1，则表示没有匹配成功
        //正常情况下pos后面应该对应的是歌词文件
        int pos = rx.indexIn(oneline, 0);
        while (pos != -1) { //表示匹配成功
            QString cap = rx.cap(0);//返回第0个表达式匹配的内容
            // 将时间标签转换为时间数值，以毫秒为单位
            QRegExp regexp;
            regexp.setPattern("\\d{2}(?=:)");
            regexp.indexIn(cap);
            int minute = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\.)");
            regexp.indexIn(cap);
            int second = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\])");
            regexp.indexIn(cap);
            int millisecond = regexp.cap(0).toInt();
            qint64 time = minute * 60000 + second * 1000 + millisecond * 10;
            lrcItem lrctemp;
            lrctemp.lrctime=time;
            lrctemp.text=temp;
            qDebug()<<temp<<endl;
            // 插入到subtitle
            lrctitle.push_back(lrctemp);
            pos += rx.matchedLength();
            pos = rx.indexIn(oneline, pos);//匹配全部
        }
    }
}
