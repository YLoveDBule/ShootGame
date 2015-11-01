#include "GamingLayer.h"
#include "ControllPanel.h"
#include "cocos2d.h"

GamingLayer* GamingLayer::createGamingLayer()
{
	GamingLayer *pGamingLayer = new GamingLayer();
	if (pGamingLayer && pGamingLayer->initGamingLayer())
	{
		return pGamingLayer;
	}
	else
	{
		CC_SAFE_DELETE(pGamingLayer);
		return NULL;
	}
}

GamingLayer::GamingLayer(){}

GamingLayer::~GamingLayer(){}

bool GamingLayer::initGamingLayer()
{
	this->initGameBg();
	this->initHudPanel();
	this->initControllPanel();
	return true;
}

void GamingLayer::initGameBg() 
{
	m_pBg = CCSprite::spriteWithFile("common/actor_gamingbg.png");
	this->addChild(this->m_pBg);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_pBg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
}

void GamingLayer::initHudPanel()
{
	
}

void GamingLayer::initControllPanel()
{
	m_pControllPanel = ControllPanel::createControllPanel();
	if (m_pControllPanel != NULL) {
		this->addChild(m_pControllPanel);
	}
	else
	{
		CCLog("GamingLayer===> ControllPanel is null");
	}
}
