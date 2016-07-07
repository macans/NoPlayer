#ifndef SUBTITLEWIDGET_H
#define SUBTITLEWIDGET_H

#include <QLabel>
#include <QFile>
#include <QTextCodec>

#include "playconfig.h"

struct subItem{
	qint64 msecBegin, msecEnd;
	QString text;
	subItem(qint64 a = 0, qint64 b = 0, QString c = 0) :msecBegin(a), msecEnd(b), text(c){};
	bool operator <(const subItem &b){
		return msecEnd < b.msecEnd;
	}
};

class SubtitleLabel : public QLabel
{
    Q_OBJECT
public:
	explicit SubtitleLabel(QWidget *parent = 0, PlayConfig *config = 0);
	
signals:

public slots:
	void updateSubTitle(qint64 progress);
	void fontChanged(QFont font);
	void colorChanged(QColor color);
	void subtitleChanged(QString subName = "");

private:
	qint64 subDelay;
	QString color;
	QVector<subItem> subtitle;  
};

#endif // SUBTITLEWIDGET_H
/*
	��Ļ��ʼ���� subTitle ��
	ÿ�� positionChanged()��ʱ�� ��Ҫ�ҵ���ȷ�� subItem 
	���ֻ�������
*/
