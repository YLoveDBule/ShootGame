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
#include "ResulitLayer.h"
#include "Utils/AudioManager.h"
#include <sstream>
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

GamingLayer::GamingLayer(){
	
}

GamingLayer::~GamingLayer(){
	/*PlayerMrg::getInstance()->Delete();*/
}

bool GamingLayer::initGamingLayer()
{
	_isCanTouch = true;
	m_pBullets = CCArray::array();
	m_pBullets->retain();
	m_pMonsters = CCArray::array();
	m_pMonsters->retain();
	//初始化大招状态
	m_bIsMagicFireIng = false;
	this->initGameBg();
	this->initHudPanel();
	this->initControllPanel();
	m_mMonsterFreshInfo.clear();

	//填充怪物进怪物刷新map
	updateMonsterFreshPool(NULL);

	CCLayer::setIsKeypadEnabled(true);
	this->scheduleUpdate();

	//玩家的分数
	InitPlayerGradeUI();
	//玩家血量
	InitPlayerHpUI();
	return true;
}

void GamingLayer::onEnter()
{
	CCLayer::onEnter();
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(GamingLayer::playerScoreChange), NOTIFY_PLAYER_UPDATEUIGRADE, NULL);
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(GamingLayer::updateMonsterFreshPool), NOTIFY_MONSTER_UPDATEFRESHPOOL, NULL);
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(GamingLayer::resumeGame), NOTIFY_RESUME_GAME, NULL);
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(GamingLayer::ShowResulitLayer), NOTIFY_GETRESLUT, NULL);
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(GamingLayer::pauseGame), NOTIFY_PAUSE_GAME, NULL);
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(GamingLayer::createBullet), NOTIFY_BARREL_FIRE, NULL);
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(GamingLayer::createMagicFire), NOTIFY_BARREL_MAGIC_FIRE, NULL);
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(GamingLayer::UpdatePlayerNowHpUI), NOTIFY_PLAYER_UPDATEUINOWHP, NULL);
}

void GamingLayer::onExit()
{
	CCLayer::onExit();
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_PLAYER_UPDATEUIGRADE);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_MONSTER_UPDATEFRESHPOOL);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_RESUME_GAME);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_GETRESLUT);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_PAUSE_GAME);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_BARREL_FIRE);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_BARREL_MAGIC_FIRE);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_PLAYER_UPDATEUINOWHP);
}

void GamingLayer::update(ccTime dt)
{
	this->checkMonsterFresh(dt*1000);
	if (!m_bIsMagicFireIng)
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
	m_pBg = CCSprite::spriteWithFile("actor_gamingbg.png");
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
		//if (nMosterId == 1002)
		//	CCLog("checkMonsterFresh monsterId: %d,nCurrentTime:%d, nFreshSpeed:%d", nMosterId, nCurrentTime, nFreshSpeed);
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
			if (pMonster->m_bIsDead)
				continue;
			if (Utils::IsRectContianPointCollision(pBullet, pMonster))
			{
				bIsHit = true;
				//pMonster->setmonsterHp(pMonster->getmonsterHp()-1);
				/*if (pMonster->getmonsterHp() <= 0)
				{
					pMonster->DestroyMonster();
					break;
				}	*/
				AudioManager::getInstance()->playEffect("audio/hit.mp3");
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
	stringstream ss;
	ss << PlayerMrg::getInstance()->getPlayer()->getPlayerGrade();
	_gradeLabel->setString(ss.str().c_str());
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
		//CCLog("MonsterData::getInstance()->getFreshSpeed(*%d):%d", *it,MonsterData::getInstance()->getFreshSpeed(*it));
		this->m_mMonsterFreshInfo.insert(map<int, int>::value_type(*it, MonsterData::getInstance()->getFreshSpeed(*it)*1000));
		//CCLog("id:%d, time:%d",*it,this->m_mMonsterFreshInfo[*it]);
	}
}

void GamingLayer::pauseGame(CCObject *pSender)
{
	if (!_isCanTouch)
	{
		return;
	}
	//添加pause界面
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	PauseLayer *pPauseLayer = PauseLayer::Create();
	CCDirector::sharedDirector()->getRunningScene()->addChild(pPauseLayer,TOP_ZORDER);

	//禁用按钮功能
	CCLayer::setIsKeypadEnabled(false);
	CCDirector::sharedDirector()->pause();
	bIsPaused = true;
}

void GamingLayer::resumeGame(CCObject *pSender)
{
	//恢复按钮功能
	CCLayer::setIsKeypadEnabled(true);
	CCDirector::sharedDirector()->resume();
	bIsPaused = false;
}

void GamingLayer::ShowResulitLayer(CCObject *pSender)
{
	ResulitLayer *relustlayer = ResulitLayer::create();
	CCDirector::sharedDirector()->getRunningScene()->addChild(relustlayer);

	CCLayer::setIsKeypadEnabled(false);
	CCDirector::sharedDirector()->pause();
	_isCanTouch = false;
}

void GamingLayer::InitPlayerGradeUI()
{
	stringstream ss;
	ss << PlayerMrg::getInstance()->getPlayer()->getPlayerGrade();
	_gradeLabel = CCLabelAtlas::labelWithString(ss.str().c_str(), "grade.png", 32, 45, '/');//CCLabelTTF::labelWithString(ss.str().c_str(), "Arial", 30);
	_gradeLabel->setScale(0.75);
	std::string str = s_language + "score.png";
	CCSprite *gradeBg = CCSprite::spriteWithFile(str.c_str());
	gradeBg->setAnchorPoint(ccp(0, 1));
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	gradeBg->setPosition(ccp(10, size.height - 10));
	addChild(gradeBg,100);
	_gradeLabel->setAnchorPoint(ccp(0, 1));
	_gradeLabel->setPosition(ccp(15 + gradeBg->getContentSize().width, size.height - 10));
	addChild(_gradeLabel,100);
}

void GamingLayer::InitPlayerHpUI()
{
	stringstream ss;
	ss << PlayerMrg::getInstance()->getPlayer()->getPlayerNowHp();
	ss << "/";
	ss << PlayerMrg::getInstance()->getPlayer()->getPlayerHpLimit();
	_PlayerCurHpLabel = CCLabelAtlas::labelWithString(ss.str().c_str(), "grade.png", 32, 45, '/');//CCLabelTTF::labelWithString(ss.str().c_str(), "Arial", 30);
	_PlayerCurHpLabel->setScale(0.75);
	CCSprite *hpBg = CCSprite::spriteWithFile("shouzi.png");
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	hpBg->setAnchorPoint(ccp(0, 1));
	hpBg->setPosition(ccp(size.width / 2 - 50, size.height - 10));
	addChild(hpBg, 100);

	_PlayerCurHpLabel->setAnchorPoint(ccp(0, 1));
	_PlayerCurHpLabel->setPosition(ccp(size.width / 2 - 45 + hpBg->getContentSize().width, size.height - 10));
	addChild(_PlayerCurHpLabel,100);
}

void GamingLayer::UpdatePlayerNowHpUI(CCObject *pSender)
{
	stringstream ss;
	ss << PlayerMrg::getInstance()->getPlayer()->getPlayerNowHp();
	ss << "/";
	ss << PlayerMrg::getInstance()->getPlayer()->getPlayerHpLimit();
	_PlayerCurHpLabel->setString(ss.str().c_str());
}

void GamingLayer::AllMaigicFireEffect()
{
	CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(24);
	char str[20] = {};
	for (size_t i = 0; i < 24; ++i)
	{
		sprintf(str, "aoe/aoe_%d.png", i);
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(str);
		CCSpriteFrame *frame = CCSpriteFrame::frameWithTexture(texture, CCRect(0, 0, 1024, 600));
		animFrames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::animationWithFrames(animFrames, 0.1);
	CCAnimate* animate = CCAnimate::actionWithAnimation(animation);
	CCSprite *sprite = CCSprite::spriteWithFile("aoe/aoe_0.png");
	addChild(sprite,200);
	//CCSize size = CCDirector::sharedDirector()->getWinSize();
//	sprite->setPosition(ccp(100, 300));
	sprite->setAnchorPoint(ccp(0, 0));
	sprite->runAction(animate);
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

void GamingLayer::createBullet(CCObject *pSender)
{
	//CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_FIRE);
	AudioManager::getInstance()->playEffect("audio/shoot.mp3");
	Bullet* pBullet = Bullet::createBullet(this);
	//根据炮口的位置和炮管的方向创建子弹
	CCPoint p = this->m_pControllPanel->getMuzzleWorldPos();
	float rotation = this->m_pControllPanel->getConnonBarrelRotation();
	pBullet->setPosition(p);
	pBullet->setRotation(rotation);
	this->addChild(pBullet, BULLET_ZORDER);
	this->m_pBullets->addObject(pBullet);
	//m_pBulletVector.push_back(pBullet);
	pBullet->shootBullet();
}

void GamingLayer::createMagicFire(CCObject *pSender)
{
	if (!_isCanTouch)
	{
		return;
	}
	AudioManager::getInstance()->playEffect("audio/magic.mp3");
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_TO_ZERO);
	//全屏伤害
	hurtAllMonster();
	AllMaigicFireEffect();
}

void GamingLayer::hurtAllMonster()
{
	m_bIsMagicFireIng = true;
	CCObject *pMonsterObj;
	CCARRAY_FOREACH(m_pMonsters, pMonsterObj)
	{
		MonsterMrg *pMonster = (MonsterMrg*)pMonsterObj;	
		if (pMonster->m_bIsDead)
			continue;
		pMonster->freshMonsterHp(PlayerMrg::getInstance()->getPlayer()->getPlayerNowAtt());
	}
	m_bIsMagicFireIng = false;
}

bool GamingLayer::keyAllClicked(int iKeyID, CCKeypadStatus iKeyState)
{

	if (iKeyID == 'w' || iKeyID == 'W' || iKeyID == HANDSET_UP || iKeyID == HANDSET_DOWN_ || iKeyID == KEY_UP)
	{
		onClickW(iKeyState);
	}
	else if (iKeyID == 's' || iKeyID == 'S' || iKeyID == HANDSET_DOWN || iKeyID == HANDSET_DOWN_ || iKeyID == KEY_DOWN)
	{
		onClickS(iKeyState);
	}
	else if (iKeyID == 'a' || iKeyID == 'A' || iKeyID == HANDSET_LEFT || iKeyID == HANDSET_LEFT_ || iKeyID == KEY_LEFT)
	{
		onClickA(iKeyState);
	}
	else if (iKeyID == 'd' || iKeyID == 'D' || iKeyID == HANDSET_RIGHT || iKeyID == HANDSET_RIGHT_ || iKeyID == KEY_RIGHT)
	{
		onClickD(iKeyState);
	}
	else if (iKeyID == 'j' || iKeyID == 'J' || iKeyID == HANDSET_Y || iKeyID == HANDSET_Y_ || iKeyID == KEY_Y)
	{
		onClickJ(iKeyState);
	}
	else if (iKeyID == 'i' || iKeyID == 'I' || iKeyID == HANDSET_A || iKeyID == HANDSET_A_ || iKeyID == KEY_A)
	{
		onClickI(iKeyState);
	}
	else if (iKeyID == 'k' || iKeyID == 'K' || iKeyID == HANDSET_B || iKeyID == HANDSET_B_ || iKeyID == KEY_B)
	{
		onClickK(iKeyState);
	}
	else if (iKeyID == 'l' || iKeyID == 'L' || iKeyID == HANDSET_X || iKeyID == HANDSET_X_ || iKeyID == KEY_X)
	{
		onClickL(iKeyState);
	}
	else
	{
		CCLog("-------KeyNotFind----KeyID = %d -------KeyState = %d-----\n", iKeyID, iKeyState);
		return false;
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
		createBullet(NULL);
	}
}

void GamingLayer::onClickK(CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN){
		//createMagicFire(NULL);
		if (!this->m_pControllPanel->getMagicCD()){
			CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_MAGIC_FIRE);
		}	
	}
}

void GamingLayer::onClickL(CCKeypadStatus key_status)
{
	this->pauseGame(NULL);
}

void GamingLayer::onClickI(CCKeypadStatus key_status)
{
		
}



