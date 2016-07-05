#ifndef PLAY_CONFIG
#define PLAY_CONFIG

#include <QString>

struct PlayConfig{
	//����
	int msecForword = 5000;
	int msecRewind = 5000;

	//�����б�
	int playMethod;

	//��Ļ
	qint64 subDelay;
	QString subFont;
	int subColor;

	//��Ƶ
	int hue;
	int brightness;
	int contrast;

	//����
	int stopWhenMin;
};

typedef struct {
	int id;
	QString name;
	QString link;
	QString lrclink;
	QString info;
}InfoNetMusic;
#endif