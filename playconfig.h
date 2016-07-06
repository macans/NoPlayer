#ifndef PLAY_CONFIG
#define PLAY_CONFIG

#define PLAYRANDOM	0x04

#define PLAY_MUSIC	0x00
#define PLAY_VIDEO	0x01

#define VOLUME_STEP	10
#define VOLUME_MAX	100
#define VOLUME_MIN	0

#define PLAYRATE_STEP	0.1
#define PLAYRATE_INIT	1
#define PLAYRATE_MIN	0.2

#define SUBDELAY_STEP	500

#define MODEL_LAC		1
#define MODEL_NET		0

#define SRCH_STEP_SEC	10000
#define SRCH_STEP_MIN	120000

#define ITEM_COLOR_NORMAL "#f68"
#define ITEM_COLOR_PLAY "#129"
#define ITEM_COLOR_SEARCH "#19c"
#define CUR_ITEM_LOOP 0x1
#define SEQUENTIAL 0x2
#define LOOP 0x3
#define RANDOM 0x4
#define MEDIA_TYPE_MUSIC 0
#define MEDIA_TYPE_VIDEO 1

#define SIZE_DEFT	0
#define SIZE_ORIG	1
#define SIZE_FULL	2

#define ORIG_HEIGHT	600
#define ORIG_WIDTH	800


#include <QString>

struct PlayConfig{
	//播放
	int msecForword = 5000;
	int msecRewind = 5000;

	//播放列表
	int playMethod;

	//字幕
	int subDelay;
	QString subFont;
	QString subColor;

	//视频
	int hue;
	int brightness;
	int contrast;

	//常规
	int stopWhileMin;
	int sizeWhileOpen;
};


typedef struct {
	int id;
	QString name;
	QString link;
	QString lrclink;
	QString info;
}InfoNetMusic;
#endif