#include "LoadingLayer.h"
#include "cocos2d.h"
#include "Utils/Utils.h"
#include "Utils/AudioManager.h"
#include "LoginScene.h"
#include "Config/BaseConfig.h"
USING_NS_CC;
bool LoadingLayer::init()
{
	if (!CCLayer::init())
		return false;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//背景
	CCSprite *bgSprite = CCSprite::spriteWithFile("loading/bg.png");
	this->addChild(bgSprite);
	bgSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	//loading条
	CCSprite *loadingSprite = CCSprite::spriteWithFile("loading/loading_1.png");
	this->addChild(loadingSprite);
	loadingSprite->setPosition(ccp(bgSprite->getContentSize().width / 2 + 120, bgSprite->getContentSize().height/4-16));
	//loading动画
	//加入textrue
	CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(3);
	char str[25] = {};
	for (size_t i = 1; i <= 3; ++i)
	{
		sprintf(str, "loading/loading_%d.png", i);
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(str);
		CCSpriteFrame *frame = CCSpriteFrame::frameWithTexture(texture, CCRect(0, 0, 39, 16));
		animFrames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::animationWithFrames(animFrames, 0.2);
	CCActionInterval*  action = CCAnimate::actionWithAnimation(animation, true);
	loadingSprite->runAction(CCRepeatForever::actionWithAction(action));
	CheckLanguage();
	this->schedule(schedule_selector(LoadingLayer::update),0.5);
	return true;
}

void LoadingLayer::update(float dt)
{
	if (_index <= 5)
	{
		Utils::InitLoadPlist(_Effect.at(_index).c_str());
		++_index;
	}
	else if (_index <= 12)
	{
		AudioManager::getInstance()->preLoadMusic(_Audio.at(_index - 6).c_str());
		++_index;
	}
	else if (_index == 13)
	{
		Utils::InitLoadAoeEffect();
		++_index;
	}
	else
	{
		CCScene *sence = LoginScene::scene();
		CCDirector::sharedDirector()->replaceScene(sence);
	}
}

CCScene* LoadingLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();

	// 'layer' is an autorelease object
	LoadingLayer *layer = LoadingLayer::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

LoadingLayer::LoadingLayer()
{
	_Effect.push_back("Monster");
	_Effect.push_back("shouji");
	_Effect.push_back("dazhao1");
	_Effect.push_back("dazhao2");
	_Effect.push_back("siwang");
	_Effect.push_back("diaoxue");
	_Audio.push_back("audio/background.mp3");
	_Audio.push_back("audio/dead1.mp3");
	_Audio.push_back("audio/dead2.mp3");
	_Audio.push_back("audio/escape.mp3");
	_Audio.push_back("audio/hit.mp3");
	_Audio.push_back("audio/magic.mp3");
	_Audio.push_back("audio/shoot.mp3");
	_index = 0;
}

LoadingLayer::~LoadingLayer()
{
	this->unschedule(schedule_selector(LoadingLayer::update));
}

void LoadingLayer::CheckLanguage()
{
	//判断中文英文
	ccLanguageType language_id = CCApplication::getCurrentLanguage();
	switch (language_id)
	{
	case kLanguageEnglish:
		s_language = "En/";
		break;
	case kLanguageChinese:
		s_language = "En/";
		break;
	case kLanguageGerman:
		s_language = "German/";
		break;
	case kLanguageFrench:
	case kLanguageItalian:
	case kLanguageSpanish:
	case kLanguageRussian:
		s_language = "En/";
		break;
	default:break;
	}

}
