#pragma once
#include "cocos2d.h"
USING_NS_CC;
class LoadingLayer : public CCLayer{
public:
	virtual bool init();
	static CCScene* scene();
	LAYER_NODE_FUNC(LoadingLayer);
private:
	virtual void update(float dt);
};