#include "AudioManager.h"

static AudioManager* s_audioInstance = NULL;
AudioManager* AudioManager::getInstance()
{
	if (!s_audioInstance)
	{
		s_audioInstance = new AudioManager;
	}
	return s_audioInstance;
}

AudioManager::AudioManager(){}
AudioManager::~AudioManager(){
	SimpleAudioEngine::sharedEngine()->end();
}

void AudioManager::preLoadMusic(const char* musicName)
{
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::fullPathFromRelativePath(musicName));
	m_musicVector.push_back(musicName);
}

void AudioManager::playMusic(const char *musicName, bool bIsLoop)
{	
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(musicName, bIsLoop);
}

void AudioManager::pauseMusic()
{
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AudioManager::stopMusic()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

bool AudioManager::isMusicPlay()
{
	return SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying();
}

void AudioManager::setMusicVolume(float volume)
{
	assert(volume >= 0.0 && volume <= 1.0, "music volume is'nt in 0.0 -> 1.0");
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}

float AudioManager::getMusicVolume()
{
	return SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
}

void AudioManager::addMusicVolume()
{
	float volume = getMusicVolume() + 0.1;
	volume = volume > 1.0 ? 1.0 : volume;
	setMusicVolume(volume);
}

void AudioManager::subMusicVolume()
{
	float volume = getMusicVolume() - 0.1;
	volume = volume < 0.0 ? 0.0 : volume;
	setMusicVolume(volume);
}

/*******************************************	effect   ***********************************************/


void AudioManager::preLoadEffect(const char *effectName)
{
	SimpleAudioEngine::sharedEngine()->preloadEffect(effectName);
}

void AudioManager::playEffect(const char *effectName)
{
	SimpleAudioEngine::sharedEngine()->playEffect(effectName);
}

void AudioManager::pauseAllEffects()
{
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

void AudioManager::resumeAllEffects()
{
	SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

void AudioManager::setEffectVolume(const float volume)
{
	assert(volume >= 0.0 && volume <= 1.0, "effect volume is'nt in 0.0 -> 1.0");
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}

float AudioManager::getEffectVolume()
{
	return SimpleAudioEngine::sharedEngine()->getEffectsVolume();
	
}

void AudioManager::addEffectVolume()
{
	float volume = getEffectVolume() + 0.1;
	volume = volume > 1.0 ? 1.0 : volume;
	setEffectVolume(volume);
}

void AudioManager::subEffectVolume()
{
	float volume = getEffectVolume() - 0.1;
	volume = volume > 1.0 ? 1.0 : volume;
	setEffectVolume(volume);
}


