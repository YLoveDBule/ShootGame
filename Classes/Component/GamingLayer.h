#pragma once
#include "cocos2d.h"
#include "ControllPanel.h"
//#include <vector>
USING_NS_CC;
class Bullet;
class GamingLayer : public CCLayer, public CCKeypadDelegate{
public:
	static GamingLayer* createGamingLayer();
	virtual ~GamingLayer();
	virtual bool keyAllClicked(int iKeyID, CCKeypadStatus key_status);
	vector<Bullet*> m_pBulletVector;
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

	void initGameBg();		//游戏背景
	void initHudPanel();		//游戏hud Paenl
	void initControllPanel();	//游戏操作panel

	bool initGamingLayer();		//初始化
};