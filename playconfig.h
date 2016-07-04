#ifndef PLAY_CONFIG
#define PLAY_CONFIG

#include <QString>

struct PlayConfig{
	//播放
	int secForword;
	int secRewind;
	int rate;

	//播放列表
	QString lastPlayedName;
	int playMethod;

	//字幕
	qint64 subDelay;
	QString fontFamily;
	int colorVal;

	//视频
	int hue;
	int brightness;
	int contrast;

	//常规
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