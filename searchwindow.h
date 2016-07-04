#ifndef WIDGET_H
#define WIDGET_H

#define API_OF_SEARCH		"http://music.baidu.com/search?key=%1&start=%2&size=5&s=1"
#define API_OF_SONGLINK		"http://play.baidu.com/data/music/songlink?songIds=%1&type=m4a,mp3"
#define API_OF_SONGINFO		"http://play.baidu.com/data/music/songinfo?songIds=%1"

#include <QFile>
#include <QWidget>
#include <QTextEdit>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtNetwork>
#include <QRegularExpression>
#include <QListWidget>
#include <QJsonParseError>
#include <QtScript>
class SearchWindow : public QWidget
{
	Q_OBJECT

public:
	SearchWindow(QWidget *parent = 0);
	~SearchWindow();
	QString unifyResult(QString res);
	void getSongInfo(QString songId, bool isNewSong);
signals:
	void getInfoComplete(bool isNewSong, QString info, QString link = "");
	public slots:
	void toolButtonClicked();
	void searchReplyFinished();
	void infoReplyFinished();
	void linkReplyFinished();
	void itemDoubleClicked(QListWidgetItem *item);
private:
	bool isNewSong;
	QString link, info;
	QNetworkAccessManager manager;
	QNetworkReply *searchReply;
	QNetworkReply *infoReply;
	QNetworkReply *linkReply;

	QTextEdit *textEdit;
	QToolButton *toolButton;
	QListWidget *listWidget;
	QScriptValue searchResult;
};

#endif // WIDGET_H
