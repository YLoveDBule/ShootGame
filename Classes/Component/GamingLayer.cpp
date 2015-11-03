#include "GamingLayer.h"
#include "ControllPanel.h"
#include "cocos2d.h"
#include "Config/NotificationNameConfig.h"
#include "Bullet.h"
USING_NS_CC;

GamingLayer* GamingLayer::createGamingLayer()
{
	GamingLayer *pGamingLayer = new GamingLayer();
	if (pGamingLayer && pGamingLayer->initGamingLayer())
	{
		pGamingLayer->autorelease();
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
	CCLayer::setIsKeypadEnabled(true);
	this->scheduleUpdate();
	return true;
}

void GamingLayer::update(ccTime dt)
{
	CCLog("scheduleUpdate:%f",dt);
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
	this->m_pControllPanel = ControllPanel::createControllPanel();
	if (this->m_pControllPanel != NULL) {
		this->m_pControllPanel->autorelease();
		this->addChild(this->m_pControllPanel);
	}
	else
	{
		CCLog("GamingLayer===> ControllPanel is null");
	}
}

bool GamingLayer::keyAllClicked(int iKeyID, CCKeypadStatus key_status)
{
	switch (iKeyID)
	{
	case 'w':
	case 'W':
		//	case KEY_UP:
		onClickW(key_status);
		break;
	case 's':
	case 'S':
		//	case KEY_DOWN:
		onClickS(key_status);
		break;
	case 'a':
	case 'A':
		//	case KEY_LEFT:
		onClickA(key_status);
		break;
	case 'd':
	case 'D':
		//	case KEY_RIGHT:
		onClickD(key_status);
		break;

	case 'i':
	case 'I':
		//	case KEY_A:
		onClickI(key_status);
		break;
	case 'k':
	case 'K':
		//	case KEY_B:
		onClickK(key_status);
		break;
	case 'l':
	case 'L':
		//	case KEY_X:
		onClickL(key_status);
		break;
	case 'j':
	case 'J':
		//	case KEY_Y:
		onClickJ(key_status);
		break;

	default:
		CCLog("-------KeyNotFind----KeyID = %d -------KeyState = %d-----\n", iKeyID, key_status);
		break;
	}

	return true;
}

void GamingLayer::onClickA(CCKeypadStatus key_status)
{
	CCLog("onClickA");
	if (key_status == EVENT_KEY_DOWN){
		CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_TURN_LEFT);
	}
}

void GamingLayer::onClickS(CCKeypadStatus key_status)
{
}

void GamingLayer::onClickW(CCKeypadStatus key_status)
{
	
}

void GamingLayer::onClickD(CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN){
		CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_TURN_RIGHT);
	}
}

void GamingLayer::onClickJ(CCKeypadStatus key_status)
{	
	CCLog("onClickJ==>key_status:%d",key_status);
	if (key_status == EVENT_KEY_DOWN){
		CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_FIRE);
		Bullet* pBullet = Bullet::createBullet(this);
		//根据炮口的位置和炮管的方向创建子弹
		CCPoint p = this->m_pControllPanel->getMuzzleWorldPos();
		float rotation = this->m_pControllPanel->getConnonBarrelRotation();
		pBullet->setPosition(p);
		//CCLog("pBullet rotation:%f",rotation);
		//CCLog("pBullet PositionX:%f,PositionY:%f", p.x,p.y);
		pBullet->setRotation(rotation);
		this->addChild(pBullet);
		m_pBulletVector.push_back(pBullet);
		pBullet->shootBullet();
	}
}

void GamingLayer::onClickK(CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN){
		CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_MAGIC_FIRE);
	}
}

void GamingLayer::onClickL(CCKeypadStatus key_status)
{
}

void GamingLayer::onClickI(CCKeypadStatus key_status)
{
	
}