#include "GamingLayer.h"
#include "ControllPanel.h"
#include "cocos2d.h"
#include "Config/NotificationNameConfig.h"
#include "Bullet.h"
#include "GameData/MonsterMrg.h"
#include "GameData/MonsterData.h"
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
	//�����������ˢ��map
	this->m_mMonsterFreshInfo.insert(map<int, int>::value_type(1001, 0));
	this->m_mMonsterFreshInfo.insert(map<int, int>::value_type(1002, 0));
	this->m_mMonsterFreshInfo.insert(map<int, int>::value_type(1003, 0));
	this->m_mMonsterFreshInfo.insert(map<int, int>::value_type(1004, 0));
	this->m_mMonsterFreshInfo.insert(map<int, int>::value_type(1005, 0));
	this->m_mMonsterFreshInfo.insert(map<int, int>::value_type(1006, 0));

	CCLayer::setIsKeypadEnabled(true);
	this->scheduleUpdate();
	return true;
}

//void GamingLayer::onEnter()
//{
//	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(GamingLayer::playerScoreChange), NOTIFY_PLAYER_UPDATEGRADE, NULL);
//}
//
//void GamingLayer::onExit()
//{
//	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_PLAYER_UPDATEGRADE);
//}

void GamingLayer::update(ccTime dt)
{
	CCLog("dt:%f", dt * 1000);
	this->checkMonsterFresh(dt*1000);
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

/*
* ������ˢ��
* ����ֵΪ�����ID
*/
void GamingLayer::checkMonsterFresh(int dt)
{
	//CCLog("checkMonsterFresh:%d",dt);
	for (map<int, int>::iterator it = this->m_mMonsterFreshInfo.begin(); it != this->m_mMonsterFreshInfo.end(); ++it)
	{
		int nCurrentTime = it->second + dt;
		int nMosterId = it->first;
		
		int nFreshSpeed = MonsterData::getInstance()->getFreshSpeed(nMosterId)*1000;	//ת���ɺ���
		CCLog("checkMonsterFresh nCurrentTime:%d, nFreshSpeed:%d", (int)(nCurrentTime), nFreshSpeed);
		if (nCurrentTime >= nFreshSpeed)
		{
			this->freshMonster(nMosterId);
			it->second = 0;
		}
		else
		{
			it->second = nCurrentTime;
		}
	}
}

/*ˢ�¹���*/
void GamingLayer::freshMonster(int monsterId)
{
	MonsterMrg *monster = MonsterMrg::Create(monsterId);
	this->addChild(monster);
}

//��ҷ����ı�
void GamingLayer::playerScoreChange(CCObject *pSender)
{
	
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
		//�����ڿڵ�λ�ú��ڹܵķ��򴴽��ӵ�
		CCPoint p = this->m_pControllPanel->getMuzzleWorldPos();
		float rotation = this->m_pControllPanel->getConnonBarrelRotation();
		pBullet->setPosition(p);
		//CCLog("pBullet rotation:%f",rotation);
		//CCLog("pBullet PositionX:%f,PositionY:%f", p.x,p.y);
		pBullet->setRotation(rotation);
		this->addChild(pBullet,99);
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