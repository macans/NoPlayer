#include "searchwindow.h"

SearchWindow::SearchWindow(QWidget *parent)
: QWidget(parent)
{

	QNetworkProxy proxy;
	proxy.setType(QNetworkProxy::Socks5Proxy);
	proxy.setHostName("127.0.0.1");
	proxy.setPort(1080);
	QNetworkProxy::setApplicationProxy(proxy);
	textEdit = new QTextEdit(this);
	toolButton = new QToolButton(this);
	listWidget = new QListWidget(this);
	connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemDoubleClicked(QListWidgetItem*)));
	connect(toolButton, SIGNAL(clicked()), this, SLOT(toolButtonClicked()));
	QHBoxLayout *searchLayout = new QHBoxLayout;
	QHBoxLayout *resultLayout = new QHBoxLayout;
	resultLayout->addWidget(listWidget);
	searchLayout->addWidget(textEdit);
	searchLayout->addWidget(toolButton);
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addLayout(searchLayout);
	layout->addLayout(resultLayout);
	this->setLayout(layout);
}

SearchWindow::~SearchWindow()
{

}

void SearchWindow::toolButtonClicked()
{
	QString keyword = textEdit->toPlainText();
	QString str = QString(API_OF_SEARCH).arg(keyword).arg(0);
	QUrl url(str);
	QNetworkRequest request;
	request.setUrl(url);
	//searchReply = manager->get(QNetworkRequest(url));
	searchReply = manager.get(request);
	connect(searchReply, SIGNAL(finished()), this, SLOT(searchReplyFinished()));
}

void SearchWindow::searchReplyFinished()
{
	QString res = searchReply->readAll();
	QFile *file = new QFile("resul.txt");
	bool f = file->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text);
	//file->write(res.toLocal8Bit());
	QStringList songList;
	QRegularExpression reg("<li data-songitem = '(.+?)'");
	QRegularExpressionMatchIterator it = reg.globalMatch(res);
	while (it.hasNext()){
		QRegularExpressionMatch match = it.next();
		QString songData = match.captured(1);
		songData = songData.replace("&quot;", "\"").replace("&lt;em&gt;", "").replace("&lt;\\/em&gt;", "");
		songList.push_back(songData);
		//file->write(songData.toLatin1());
		qDebug() << songData << endl;
	}
	QString songArray = "[" + songList.join(",") + "]";
	QString result = unifyResult(songArray);
	//QString src("{\"a\":\"some string\",\"b\":21}");
	qDebug() << result;
	QString str = "{\"name\":12, \"age\":\"23\"}";
	QScriptEngine engine;
	this->searchResult = engine.evaluate("value=" + result);
	int cnt = 0;
	QScriptValue cur = searchResult.property(cnt++);
	QScriptValue first = searchResult.property(0).property("songItem");
	qDebug() << first.property("author").toString();
	QListWidgetItem *listItem;
	while (cur.isValid()){
		QScriptValue item = cur.property("songItem");
		QString name = item.property("sname").toString();
		QString author = item.property("author").toString();
		QString id = item.property("sid").toString();
		listItem = new QListWidgetItem;
		listItem->setText(name + "    " + author);
		listItem->setWhatsThis(id);
		listWidget->addItem(listItem);
		cur = searchResult.property(cnt++);
	}
}

QString SearchWindow::unifyResult(QString res)
{
	return res.replace(QRegularExpression("songid | songId | sid"), "song_id").replace(QRegularExpression("author | artistname"), "singer").replace(QRegularExpression("songname | songName | sname"), "name");
}

void SearchWindow::itemDoubleClicked(QListWidgetItem *item)
{
	QString songId = item->whatsThis();
	getSongInfo(songId, true);
}

//在搜索结果中双击调用 getSongLink 时需要在播放列表中新增
//在播放列表中双击网络文件调用 getSongLink 时不需要新增
void SearchWindow::getSongInfo(QString songId, bool isNewSong)
{
	this->isNewSong = isNewSong;
	QUrl url(QString(API_OF_SONGLINK).arg(songId));
	QNetworkRequest request;
	request.setUrl(url);
	link = info = ""; 
	if (isNewSong){
		linkReply = manager.get(request);
		connect(linkReply, SIGNAL(finished()), this, SLOT(linkReplyFinished()));
	}
	url = QUrl(QString(API_OF_SONGINFO).arg(songId));
	request.setUrl(url);
	infoReply = manager.get(request);
	connect(infoReply, SIGNAL(finished()), this, SLOT(infoReplyFinished()));
}

void SearchWindow::infoReplyFinished()
{
	info = infoReply->readAll();
	info = info.replace("\\", "");
	qDebug() << info << endl;
	if (!isNewSong){
		//在播放列表中打开
		emit getInfoComplete(false, info);
	}
	else if (link != ""){
		emit getInfoComplete(true, info, link);
	}
}

void SearchWindow::linkReplyFinished()
{
	QString res = linkReply->readAll();
	res = res.replace("\\", "");
	qDebug() << res << endl;
	QScriptEngine engine;
	QScriptValue val = engine.evaluate("value=" + res);
	qDebug() << val.toString() << endl;
	int code = val.property("errorCode").toInt32();
	qDebug() << code << endl;
	QString songList = val.property("songList").toString();
	qDebug() << songList << endl;
	link = val.property("data").property("songList").property(0).property("songLink").toString();
	qDebug() << link << endl;
	if (info != ""){
		emit getInfoComplete(true, info, link);
	}
}


/*
"{
"errorCode":22000,
"data":{
"time":3600,
"xcode":"5e1c6a138c5fff25d5e619cc3993179e",
"songList":[
{
"queryId":"877578",
"status":1,
"songId":877578,
"songName":"\u6d77\u9614\u5929\u7a7a",
"artistId":"130",
"artistName":"beyond",
"albumId":197864,
"albumName":"\u6d77\u9614\u5929\u7a7a",
"lrcLink":"http:\/\/musicdata.baidu.com\/data2\/lrc\/238975978\/238975978.lrc",
"time":322,
"linkCode":22000,
"linkinfo":null,
"version":"",
"copyType":1,
"enhancement":"0.000000",
"songLink":"http:\/\/yinyueshiting.baidu.com\/data2\/music\/238976206\/877578151200128.mp3?xcode=86904f27ff35a703a0cc505dc0621a48",
"showLink":"http:\/\/pan.baidu.com\/share\/link?shareid=275831144&uk=1716766033",
"format":"mp3",
"rate":128,
"size":5163113,
"format_arr":{
"mp3":{
"songLink":"http:\/\/yinyueshiting.baidu.com\/data2\/music\/238976206\/877578151200128.mp3?xcode=86904f27ff35a703a0cc505dc0621a48",
"showLink":"http:\/\/pan.baidu.com\/share\/link?shareid=275831144&uk=1716766033",
"format":"mp3",
"rate":128,
"size":5163113
}
}
}
]
}
}"

*/