#pragma once
#include "cocos2d.h"

USING_NS_CC;

class AudioManager {
public:
	AudioManager();
	virtual ~AudioManager();
	static AudioManager* getInstance();
	//music
	void playMusic(const char *musicName, bool bIsLoop);
	void pauseMusic();
	void stopMusic();
	void resumeMusic();
	bool isMusicPlay();
	void preLoadMusic(const char *musicName);
	void setMusicVolume(float volume);
	float getMusicVolume();
	void addMusicVolume();
	void subMusicVolume();
	//effect
	void preLoadEffect(const char *effectName);
	void playEffect(const char *effectName);
	void pauseAllEffects();
	void resumeAllEffects();
	void setEffectVolume(const float volume);
	float getEffectVolume();
	void addEffectVolume();
	void subEffectVolume();
	void stopAllEffects();

	CC_SYNTHESIZE(bool, m_bIsMusicON, MusicState);
	CC_SYNTHESIZE(bool, m_bIsEffectON, EffectState);
private:
	std::vector<string> m_musicVector;
};