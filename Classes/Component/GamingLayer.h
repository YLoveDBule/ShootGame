#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GamingLayer : public CCLayer{
public:
	static GamingLayer* createGamingLayer();
	virtual ~GamingLayer();
private:
	GamingLayer();

	CCSprite *m_pBg;		//背景sprite
	CCNode *m_pHud;			//hud节点
	CCNode *m_pControllPanel; //controll Panel

	void initGameBg();		//游戏背景
	void initHudPanel();		//游戏hud Paenl
	void initControllPanel();	//游戏操作panel

	bool initGamingLayer();		//初始化
};