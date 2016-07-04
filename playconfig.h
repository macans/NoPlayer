#ifndef PLAY_CONFIG
#define PLAY_CONFIG

#include <QString>

struct PlayConfig{
	int secForword;
	int secRewind;
	int rate;
	QString lastPlayedName;
	int playMethod;
	qint64 subDelay;
	QString fontFamily;

};

#endif