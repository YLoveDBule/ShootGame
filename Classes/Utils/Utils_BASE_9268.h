#include "cocos2d.h"
USING_NS_CC;
class Utils {
public:
	static bool IsRectCollision(CCNode* obj1, CCNode* obj2);
	static bool IsRectContianPointCollision(CCNode* obj1, CCNode* obj2);
};