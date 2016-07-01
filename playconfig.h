#ifndef PLAY_CONFIG
#define PLAY_CONFIG

#include <QString>

class PlayConfig{
private:
	int secForword;
	int secRewind;

	int rate;
	QString lastPlayedName;
	int playMethod;
	QString fontFamily;
	QString FontFamily() const { return fontFamily; }
	void FontFamily(QString val) { fontFamily = val; }

public:
	int SecForword() const { return secForword; }
	void SecForword(int val) { secForword = val; }
	int SecRewind() const { return secRewind; }
	void SecRewind(int val) { secRewind = val; }

	int Rate() const { return rate; }
	void Rate(int val) { rate = val; }

	QString LastPlayedName() const { return lastPlayedName; }
	void LastPlayedName(QString val) { lastPlayedName = val; }

	int PlayMethod() const { return playMethod; }
	void PlayMethod(int val) { playMethod = val; }
};

#endif