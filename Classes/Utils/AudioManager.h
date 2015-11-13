#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
class AudioManager {
public:
	AudioManager();
	virtual ~AudioManager();
	static AudioManager* getInstance();
	//music
	void playMusic(const char *musicName, bool bIsLoop);
	void pauseMusic();
	void stopMusic();
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
private:
	std::vector<string> m_musicVector;
	
};