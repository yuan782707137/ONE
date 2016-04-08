#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class WelcomeScene : public cocos2d::Layer
{
public:
	/***** ��ʼ������ *****/
    static cocos2d::Scene* createScene();
	virtual bool init();  
	CREATE_FUNC(WelcomeScene);
	virtual void onEnterTransitionDidFinish();
	virtual void cleanup();

	/***** ��ť���� *****/
	void menuStartCallback( Ref* pSender );
	
};

#endif // __WELCOME_SCENE_H__