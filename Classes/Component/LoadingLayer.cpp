#include "LoadingLayer.h"
#include "cocos2d.h"
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
	
	return true;
}

void LoadingLayer::update(float dt)
{

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