#include "GamingLayer.h"
#include "ControllPanel.h"
#include "cocos2d.h"
#include "Config/NotificationNameConfig.h"
#include "Config/BaseConfig.h"
#include "Bullet.h"
#include "GameData/MonsterMrg.h"
#include "GameData/MonsterData.h"
#include "Utils/Utils.h"
#include "GameData/PlayerMrg.h"
#include "Component/PauseLayer.h"
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
	updateMonsterFreshPool(NULL);

	CCLayer::setIsKeypadEnabled(true);
	this->scheduleUpdate();
	return true;
}

void GamingLayer::onEnter()
{
	CCLayer::onEnter();
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(GamingLayer::playerScoreChange), NOTIFY_PLAYER_UPDATEGRADE, NULL);
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(GamingLayer::updateMonsterFreshPool), NOTIFY_MONSTER_UPDATEFRESHPOOL, NULL);
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(GamingLayer::resumeGame), NOTIFY_RESUME_GAME, NULL);
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(GamingLayer::restartGame), NOTIFY_RESTART_GAME, NULL);

}

void GamingLayer::onExit()
{
	CCLayer::onExit();
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_PLAYER_UPDATEGRADE);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_MONSTER_UPDATEFRESHPOOL);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_RESUME_GAME);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_RESTART_GAME);

}

void GamingLayer::update(ccTime dt)
{
	this->checkMonsterFresh(dt*1000);
	this->checkHitMonster();
}

void GamingLayer::daZhaoEffect()
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(4);
	char str[20] = {};
	for (size_t i = 0; i < 12; ++i)
	{
		sprintf(str, "%s_%d.png", "zibao", i);
		CCSpriteFrame *frame = cache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::animationWithFrames(animFrames, 0.2);
	CCAnimate* animate = CCAnimate::actionWithAnimation(animation);
	CCSprite * dazhao = CCSprite::spriteWithSpriteFrameName("zibao_0.png");
	dazhao->setPosition(ccp(1024/ 2, 600 / 2));
	addChild(dazhao,100);
	CCCallFuncN *callback = CCCallFuncN::actionWithTarget(this, callfuncN_selector(GamingLayer::RemovedaZhaoEffect));
	CCFiniteTimeAction *seq = CCSequence::actions(animate, callback, NULL);
	dazhao->runAction(seq);
}

void GamingLayer::RemovedaZhaoEffect(CCNode *pSender)
{
	((CCSprite *)pSender)->removeFromParentAndCleanup(true);
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
		this->addChild(this->m_pControllPanel,CONTROLLPANEL_ZORDER);
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
	this->addChild(pMonster,MONSTER_ZORDER);
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
			if (Utils::IsRectContianPointCollision(pBullet, pMonster))
			{
				bIsHit = true;
				//pMonster->setmonsterHp(pMonster->getmonsterHp()-1);
				/*if (pMonster->getmonsterHp() <= 0)
				{
					pMonster->DestroyMonster();
					break;
				}	*/
				pMonster->freshMonsterHp(PlayerMrg::getInstance()->getPlayer()->getPlayerNowAtt());
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

//更新怪物刷新池
void GamingLayer::updateMonsterFreshPool(CCObject *pSender)
{
	MonsterKindVector *pMonsterKindVector = PlayerMrg::getInstance()->_monsterkindVec;
	vector<int> vMosterKindId = pMonsterKindVector->getMonsterKindId();
	vector<int> diffKindId;
	//筛选出pool里没有的kindId;
	for (vector<int>::iterator it = vMosterKindId.begin(); it != vMosterKindId.end(); it++)
	{
		bool bIsfound = false;
		for (map<int, int>::iterator poolIt = this->m_mMonsterFreshInfo.begin(); poolIt != this->m_mMonsterFreshInfo.end(); poolIt++)
		{
			if ((*it) == poolIt->first)
			{
				bIsfound = true;
				break;
			}
		}
		if (!bIsfound)
			diffKindId.push_back(*it);
	}
	//将没有的kindId添加进pool并立即刷新;
	for (vector<int>::iterator it = diffKindId.begin(); it != diffKindId.end(); it++)
	{
		this->m_mMonsterFreshInfo.insert(map<int, int>::value_type(*it, MonsterData::getInstance()->getFreshSpeed(*it)));
		
	}
}

void GamingLayer::pauseGame()
{
	//添加pause界面
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	PauseLayer *pPauseLayer = PauseLayer::Create();
	CCDirector::sharedDirector()->getRunningScene()->addChild(pPauseLayer);

	//禁用按钮功能
	CCLayer::setIsKeypadEnabled(false);
	CCDirector::sharedDirector()->pause();

}

void GamingLayer::resumeGame(CCObject *pSender)
{
	//恢复按钮功能
	CCLayer::setIsKeypadEnabled(true);
	CCDirector::sharedDirector()->resume();
}

void GamingLayer::restartGame(CCObject *pSender)
{
	CCLog("restartGame");
	CCDirector::sharedDirector()->resume();
	this->removeFromParentAndCleanup(true);
	PlayerMrg::getInstance()->Delete();
	PlayerMrg::getInstance()->Init();
	GamingLayer*layer = GamingLayer::createGamingLayer();
	CCDirector::sharedDirector()->getRunningScene()->removeAllChildrenWithCleanup(true);
	CCScene *scene = CCScene::node();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(scene);

}

//设置子弹的状态，0为暂停，1为继续
void GamingLayer::setBulletsState(int state)
{
	CCObject *pBulletObj = NULL;
	CCARRAY_FOREACH(m_pBullets, pBulletObj)
	{
		Bullet *pBullet = (Bullet*)pBulletObj;
		if (state == 0)
			pBullet->pause();
		else if (state == 1)
			pBullet->resume();
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
	/*CCDirector::sharedDirector()->pause();*/
}

void GamingLayer::onClickW(CCKeypadStatus key_status)
{
	/*CCDirector::sharedDirector()->resume();*/
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
		//CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_FIRE);
		Bullet* pBullet = Bullet::createBullet(this);
		//根据炮口的位置和炮管的方向创建子弹
		CCPoint p = this->m_pControllPanel->getMuzzleWorldPos();
		float rotation = this->m_pControllPanel->getConnonBarrelRotation();
		pBullet->setPosition(p);
		pBullet->setRotation(rotation);
		this->addChild(pBullet,BULLET_ZORDER);
		this->m_pBullets->addObject(pBullet);
		//m_pBulletVector.push_back(pBullet);
		pBullet->shootBullet();
	}
}

void GamingLayer::onClickK(CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN){
		CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_TO_ZERO);
		//CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_MAGIC_FIRE);
		
	}
}

void GamingLayer::onClickL(CCKeypadStatus key_status)
{
	this->pauseGame();
	
}

void GamingLayer::onClickI(CCKeypadStatus key_status)
{
		
}