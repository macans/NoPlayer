#include "subtitlelabel.h"

SubtitleLabel::SubtitleLabel(QWidget *parent, PlayConfig *config) : QLabel(parent)
{
	this->subDelay = config->subDelay;
	this->color = "<font color=" + config->subColor + ">%1</font>";
    this->setAlignment(Qt::AlignCenter);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    QPalette pa;
    pa.setColor(QPalette::Background, QColor(0x00,0xff,0x00,0x00));
    //this->setPalette(pa);
    //this->setText("HELLO");
    //QSize sz = this->size();
    //this->resize(QSize(sz.width(), 20));
}

void SubtitleLabel::subtitleChanged(QString subName)
{
	subName = subName.left(subName.lastIndexOf('.')) + ".srt";
	QFile file(subName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		subtitle.clear();
        this->hide();
		return;
	}
	int hBegin, mBegin, sBegin, msBegin;
	int hEnd, mEnd, sEnd, msEnd;
	int L, R;
	subtitle.clear();
	QByteArray line;
	while (file.readLine().length() == 0);
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	while (!file.atEnd()){
		line = file.readLine();
		subItem temp;
		L = 0, R = line.indexOf(":", L);
		hBegin = line.mid(L, R - L).toInt();
		L = R + 1, R = line.indexOf(":", L);
		mBegin = line.mid(L, R - L).toInt();
		L = R + 1, R = line.indexOf(",", L);
		sBegin = line.mid(L, R - L).toInt();
		L = R + 1, R = line.indexOf(" ", L);
		msBegin = line.mid(L, R - L).toInt();
		L = line.indexOf(" ", R + 1) + 1, R = line.indexOf(":", L);
		hEnd = line.mid(L, R - L).toInt();
		L = R + 1, R = line.indexOf(":", L);
		mEnd = line.mid(L, R - L).toInt();
		L = R + 1, R = line.indexOf(",", L);
		sEnd = line.mid(L, R - L).toInt();
		msEnd = line.mid(R + 1).toInt();
		temp.msecBegin = (((hBegin * 60) + mBegin) * 60 + sBegin) * 1000 + msBegin;
		temp.msecEnd = (((hEnd * 60) + mEnd) * 60 + sEnd) * 1000 + msEnd;

		line = file.readLine();
		QString str = codec->toUnicode(line);
		int len;
		while (str[0] != '\n'){
			temp.text += str;
			temp.text.append("<br/>");
			line = file.readLine();
			if (file.atEnd()) break;
			str = codec->toUnicode(line);
			len = str.length();
		}
		int pos = temp.text.indexOf('{');
		temp.text = temp.text.left(pos) + temp.text.right(temp.text.length() - pos - 7);
		subtitle.push_back(temp);
		file.readLine();
	}
}


void SubtitleLabel::updateSubTitle(qint64 progress)
{
    if (subtitle.size() == 0){
        this->hide();
        return;
    }
	progress += subDelay;
	QVector<subItem>::iterator it = qLowerBound(subtitle.begin(), subtitle.end(), subItem(0, progress, ""));
	if (it == subtitle.end()) return;
	if ((*it).msecBegin < progress){
		QString text = this->color.arg((*it).text);
		this->setText(text);
	}
	else{
		this->setText("");
	}
}

void SubtitleLabel::fontChanged(QFont font)
{
	this->setFont(font);
}

void SubtitleLabel::colorChanged(QColor color)
{
	QString name = color.name();
	this->color = "<font color=" + name + ">%1</font>";
}

