#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GamingLayer : public CCLayer{
public:
	static GamingLayer* createGamingLayer();
	virtual ~GamingLayer();
private:
	GamingLayer();

	CCSprite *m_pBg;		//����sprite
	CCNode *m_pHud;			//hud�ڵ�
	CCNode *m_pControllPanel; //controll Panel

	void initGameBg();		//��Ϸ����
	void initHudPanel();		//��Ϸhud Paenl
	void initControllPanel();	//��Ϸ����panel

	bool initGamingLayer();		//��ʼ��
};