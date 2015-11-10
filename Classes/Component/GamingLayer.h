#pragma once
#include "cocos2d.h"
#include "ControllPanel.h"
#include <vector>
#include <map>
USING_NS_CC;
class Bullet;
class MonsterMrg;
class GamingLayer : public CCLayer, public CCKeypadDelegate{
public:
	static GamingLayer* createGamingLayer();
	virtual ~GamingLayer();
	virtual bool keyAllClicked(int iKeyID, CCKeypadStatus key_status);
	//vector<Bullet*> m_pBulletVector;
	//vector<MonsterMrg*> m_pMonsterVector;
	CCArray *m_pBullets;
	CCArray *m_pMonsters;
	//CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pBullets, Bullets);
	//CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pMonsters, Monsters);
protected:
	void onClickA(cocos2d::CCKeypadStatus key_status);
	void onClickS(cocos2d::CCKeypadStatus key_status);
	void onClickD(cocos2d::CCKeypadStatus key_status);
	void onClickW(cocos2d::CCKeypadStatus key_status);

	void onClickI(cocos2d::CCKeypadStatus key_status);
	void onClickL(cocos2d::CCKeypadStatus key_status);
	void onClickJ(cocos2d::CCKeypadStatus key_status);
	void onClickK(cocos2d::CCKeypadStatus key_status);
private:
	GamingLayer();

	CCSprite *m_pBg;		//背景sprite
	CCNode *m_pHud;			//hud节点
	ControllPanel* m_pControllPanel; //controll Panel
	map<int, int> m_mMonsterFreshInfo;		//怪物刷新信息
	bool m_bIsMagicFireIng;		//是否正在大招中

	virtual void onEnter();
	virtual void onExit();

	void initGameBg();		//游戏背景
	void initHudPanel();		//游戏hud Paenl
	void initControllPanel();	//游戏操作panel

	bool initGamingLayer();		//初始化

	void playerScoreChange(CCObject *pSender);

	
	void checkMonsterFresh(int dt);					//检查怪物刷新
	void freshMonster(int monsterId);					//刷新怪物
	void checkHitMonster();						//检测是否击中怪物
	void updateMonsterFreshPool(CCObject* pSender);	//更新怪物刷新池

	void pauseGame(CCObject *pSender);
	void resumeGame(CCObject *pSender);
	void setBulletsState(int state);
	void update(ccTime dt);

	void createBullet(CCObject *pSender);	//创建子弹
	void createMagicFire(CCObject *pSender);	//魔法攻击

	void hurtAllMonster();

	void daZhaoEffect();
	void RemovedaZhaoEffect(CCNode *pSender);
	void ShowResulitLayer(CCObject *pSender);

	void InitPlayerGradeUI();
	void InitPlayerHpUI();

	void UpdatePlayerNowHpUI(CCObject *pSender);
	void AllMaigicFireEffect();
private:
	CCLabelAtlas* _gradeLabel;
	CCLabelAtlas* _PlayerCurHpLabel;
};