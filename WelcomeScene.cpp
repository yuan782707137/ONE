
#include "WelcomeScene.h"
#include "GameDefine.h"
#include "GameScene.h"

using namespace CocosDenshion;

Scene* WelcomeScene::createScene()	{
    auto scene = Scene::create();
    auto layer = WelcomeScene::create();
    scene->addChild(layer);
	return scene;
}

// ��ӭ���� ��ʼ������
bool WelcomeScene::init()	{
	// �ȳ�ʼ�����࣬���ɹ�����false
	if( !Layer::init() )	{
		return false;
	}


	// ��ӱ���ͼƬ
    auto sprite = Sprite::create("scene_sta.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
    this->addChild(sprite);

	// ��ӿ�ʼ��ť
	auto startItem = MenuItemImage::create(
                                           "btn_start01.png",
                                           "btn_start02.png",
										   CC_CALLBACK_1(WelcomeScene::menuStartCallback, this));
    
	startItem->setPosition(Vec2(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/6));

	
	
	auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2::ZERO);
	this -> addChild( menu );

	return true;
}

void WelcomeScene::menuStartCallback( Ref* pSender )
{
	// ��ת����Ϸ����
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void WelcomeScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();  
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {                      
        SimpleAudioEngine::getInstance()->playBackgroundMusic("music_mainScene.mp3", true);  
    } 
}

void WelcomeScene::cleanup()
{
	Layer::cleanup();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("music_mainScene.mp3");
}