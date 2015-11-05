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
	m_pBullets = CCArray::array();
	m_pBullets->retain();
	m_pMonsters = CCArray::array();
	m_pMonsters->retain();

	this->initGameBg();
	this->initHudPanel();
	this->initControllPanel();
	//填充怪物进怪物刷新map
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

void GamingLayer::onEnter()
{
	CCLayer::onEnter();
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(GamingLayer::playerScoreChange), NOTIFY_PLAYER_UPDATEGRADE, NULL);
}

void GamingLayer::onExit()
{
	CCLayer::onExit();
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_PLAYER_UPDATEGRADE);
}

void GamingLayer::update(ccTime dt)
{
	this->checkMonsterFresh(dt*1000);
	this->checkHitMonster();
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
* 检测怪物刷新
* 返回值为怪物的ID
*/
void GamingLayer::checkMonsterFresh(int dt)
{
	//CCLog("checkMonsterFresh:%d",dt);
	for (map<int, int>::iterator it = this->m_mMonsterFreshInfo.begin(); it != this->m_mMonsterFreshInfo.end(); ++it)
	{
		int nCurrentTime = it->second + dt;
		int nMosterId = it->first;
		
		int nFreshSpeed = MonsterData::getInstance()->getFreshSpeed(nMosterId)*1000;	//转换成毫秒
		//CCLog("checkMonsterFresh nCurrentTime:%d, nFreshSpeed:%d", (int)(nCurrentTime), nFreshSpeed);
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

/*刷新怪物*/
void GamingLayer::freshMonster(int monsterId)
{
	MonsterMrg *pMonster = MonsterMrg::Create(monsterId, this);
	this->addChild(pMonster);
	this->m_pMonsters->addObject(pMonster);
	//this->m_pMonsterVector.push_back(pMonster);
}

/*
*检测是否击中怪物
*/

void GamingLayer::checkHitMonster()
{
	CCObject *pBulletObj = NULL;
	CCObject *pMonsterObj = NULL;
	CCARRAY_FOREACH(m_pBullets, pBulletObj)
	{
		Bullet *pBullet = (Bullet*)pBulletObj;
		if (pBullet->getHit())
			continue;
		bool bIsHit = false;
		CCARRAY_FOREACH(m_pMonsters, pMonsterObj)
		{
			MonsterMrg *pMonster = (MonsterMrg*)pMonsterObj;
			if (CCRect::CCRectIntersectsRect(pBullet->boundingBox(), pMonster->boundingBox()))
			{
				bIsHit = true;
				pMonster->setmonsterHp(pMonster->getmonsterHp()-1);
				if (pMonster->getmonsterHp() <= 0)
				{
					pMonster->DestroyMonster();
					break;
				}					
			}
		}
		if (bIsHit)
			pBullet->collision();
		
	}

	//Bullet* bullet = nullptr;
	//MonsterMrg* monster = nullptr;
	//vector<int> destroyBulletIndex;
	//vector<int> destroyMonsterIndex;
	//for (int i = 0; i < m_pBulletVector.size(); i++)
	//{
	//	for (int j = 0; j < m_pMonsterVector.size(); j++)
	//	{	
	//		if (CCRect::CCRectIntersectsRect(m_pBulletVector[i]->boundingBox(), m_pMonsterVector[j]->boundingBox()))
	//		{
	//			CCLog("hit monster!");		
	//			destroyBulletIndex.push_back(i);
	//			/*(*monsterIt)->setmonsterHp((*monsterIt)->getmonsterHp() - 1);
	//			if ((*monsterIt)->getmonsterHp() <= 0)
	//				(*monsterIt)->DestroyMonster();*/
	//		}
	//	}			
	//}

	//for (int i = 0; i < destroyBulletIndex.size(); i++)
	//{
	//	int nIdx = destroyBulletIndex[i];
	//	CCLog("nIdx:%d",nIdx);
	//	bullet = m_pBulletVector[i];
	//	
	//	m_pBulletVector.erase(m_pBulletVector.begin()+nIdx);
	//	bullet->removeFromParentAndCleanup(true);
	//}
}

//玩家分数改变
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
		//根据炮口的位置和炮管的方向创建子弹
		CCPoint p = this->m_pControllPanel->getMuzzleWorldPos();
		float rotation = this->m_pControllPanel->getConnonBarrelRotation();
		pBullet->setPosition(p);
		pBullet->setRotation(rotation);
		this->addChild(pBullet,99);
		this->m_pBullets->addObject(pBullet);
		//m_pBulletVector.push_back(pBullet);
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