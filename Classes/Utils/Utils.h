#include "cocos2d.h"
USING_NS_CC;
class Utils {
public:
	static bool IsRectCollision(CCNode* obj1, CCNode* obj2);					//�����������ײ
	static bool IsRectContianPointCollision(CCNode* obj1, CCNode* obj2);		//һ�������Ƿ��������һ�������������ײ
	static float getPointToPointDisatance(CCPoint point1, CCPoint point2);		//�������ľ��빫ʽ
};