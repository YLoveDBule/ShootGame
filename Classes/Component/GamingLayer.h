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

	CCSprite *m_pBg;		//����sprite
	CCNode *m_pHud;			//hud�ڵ�
	ControllPanel* m_pControllPanel; //controll Panel
	map<int, int> m_mMonsterFreshInfo;		//����ˢ����Ϣ
	bool m_bIsMagicFireIng;		//�Ƿ����ڴ�����

	virtual void onEnter();
	virtual void onExit();

	void initGameBg();		//��Ϸ����
	void initHudPanel();		//��Ϸhud Paenl
	void initControllPanel();	//��Ϸ����panel

	bool initGamingLayer();		//��ʼ��

	void playerScoreChange(CCObject *pSender);

	
	void checkMonsterFresh(int dt);					//������ˢ��
	void freshMonster(int monsterId);					//ˢ�¹���
	void checkHitMonster();						//����Ƿ���й���
	void updateMonsterFreshPool(CCObject* pSender);	//���¹���ˢ�³�

	void pauseGame(CCObject *pSender);
	void resumeGame(CCObject *pSender);
	void setBulletsState(int state);
	void update(ccTime dt);

	void createBullet(CCObject *pSender);	//�����ӵ�
	void createMagicFire(CCObject *pSender);	//ħ������

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