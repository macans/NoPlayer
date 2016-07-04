#ifndef PLAY_CONFIG
#define PLAY_CONFIG

#include <QString>

struct PlayConfig{
	//����
	int secForword;
	int secRewind;
	int rate;

	//�����б�
	QString lastPlayedName;
	int playMethod;

	//��Ļ
	qint64 subDelay;
	QString fontFamily;
	int colorVal;

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