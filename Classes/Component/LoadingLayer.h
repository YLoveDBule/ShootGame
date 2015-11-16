#pragma once
#include "cocos2d.h"
USING_NS_CC;
class LoadingLayer : public CCLayer{
public:
	virtual bool init();
	static CCScene* scene();
	LAYER_NODE_FUNC(LoadingLayer);
	LoadingLayer();
	virtual ~LoadingLayer();
private:
	virtual void update(float dt);
private:
	std::vector<string> _Effect;
	std::vector<string> _Audio;
	int _index;
};