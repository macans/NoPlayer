#ifndef WIDGET_H
#define WIDGET_H

#define API_OF_SEARCH		"http://music.baidu.com/search?key=%1&start=%2&size=30&s=1"
#define API_OF_SONGLINK		"http://play.baidu.com/data/music/songlink?songIds=%1&type=m4a,mp3"
#define API_OF_SONGINFO		"http://play.baidu.com/data/music/songinfo?songIds=%1"

#include <QFile>
#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QToolButton>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtNetwork>
#include <QRegularExpression>
#include <QListWidget>
#include <QJsonParseError>
#include <QtScript>

#include "playconfig.h"
class SearchWindow : public QWidget
{
	Q_OBJECT

public:
	SearchWindow(QWidget *parent = 0);
	~SearchWindow();
	QString unifyResult(QString res);
	void getSongInfo(QString songId, bool isNewSong);
signals:
	void getInfoComplete(bool isNewSong, InfoNetMusic &info);
	void searchWindowClosed();
public slots:
	void toolButtonClicked();
	void searchReplyFinished();
	void infoReplyFinished();
	void linkReplyFinished();
	void itemDoubleClicked(QListWidgetItem *item);
	void closeEvent(QCloseEvent *event);
private:
	bool isNewSong;
	InfoNetMusic info;
	QNetworkAccessManager manager;
	QNetworkReply *searchReply;
	QNetworkReply *infoReply;
	QNetworkReply *linkReply;

	QLineEdit *textEdit;
    QPushButton *toolButton;
	QListWidget *listWidget;
	QScriptValue searchResult;
};

#endif // WIDGET_H
