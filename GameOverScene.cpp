#include "GameOverScene.h"
#include "GameScene.h"
#include "WelcomeScene.h"

using namespace CocosDenshion;
//修改了分支
Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

bool GameOver::init()
{
	if( !Layer::init() ){
		return false;
	}

	TTFConfig config("fonts/yuehei.otf",48);

	// Ìí¼Ó±³¾°Í¼Æ¬
    auto sprite = Sprite::create("scene_end.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
    this->addChild(sprite);

	// Ìí¼ÓÖØÐÂ¿ªÊ¼°´Å¥
	auto restartItem = MenuItemImage::create(
                                           "btn_restart01.png",
                                           "btn_restart02.png",
										   CC_CALLBACK_1(GameOver::menuRestartCallback, this));
    
	restartItem->setPosition(Vec2(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/6));

	// Ìí¼Ó·µ»ØÖ÷²Ëµ¥°´Å¥
	auto backItem = MenuItemImage::create(
                                           "btn_back01.png",
                                           "btn_back02.png",
										   CC_CALLBACK_1(GameOver::menuBackCallback, this));
    
	backItem->setPosition(Vec2(GAME_SCREEN_WIDTH/2,backItem->getContentSize().height/2 ));
    
	// Ìí¼ÓÍË³öÓÎÏ·°´Å¥
	auto exitItem = MenuItemImage::create(
											"btn_exit01.png",
											"btn_exit02.png",
											CC_CALLBACK_1(GameOver::menuExitCallback,this));
	exitItem->setPosition(Vec2( GAME_SCREEN_WIDTH-exitItem->getContentSize().width/2 ,exitItem->getContentSize().height/2 ));

	auto menu = Menu::create(restartItem,backItem,exitItem, NULL);
    menu->setPosition(Vec2::ZERO);
	this -> addChild( menu );

	// ·ÖÊý
	auto labelScore = Label::createWithTTF(config, "  0  ");
	labelScore -> setPosition(Point( GAME_SCREEN_WIDTH/2 , GAME_SCREEN_HEIGHT/1.4));
	labelScore -> setTag(13);
	this->addChild(labelScore);

	return true;
}

void GameOver::menuRestartCallback(Ref *pSender)
{
	auto scene = GameScene::createScene();
	CCTransitionScene* reScene = CCTransitionMoveInL::create(1.0f, scene);
	CCDirector::sharedDirector()->replaceScene(reScene);
}

void GameOver::menuBackCallback( Ref *pSender )
{
	auto scene = WelcomeScene::createScene();
	CCTransitionScene* reScene = CCTransitionSplitRows::create(1.0f, scene);
	CCDirector::sharedDirector()->replaceScene(reScene);
}

void GameOver::menuExitCallback( Ref *pSender )
{
	Director::getInstance()->end();
}

void GameOver::setScore( int sc )
{
	auto labelScore = (Label *)this -> getChildByTag(13);
	labelScore -> setString( StringUtils::format(" %d ",sc));

	if( userDefault->getIntegerForKey("Int") < sc ){

		// ÐÂ¼ÍÂ¼
		auto newRecord = Sprite::create("sprite_newRecord.png");
		newRecord -> setPosition(Point( GAME_SCREEN_WIDTH/3.05 , GAME_SCREEN_HEIGHT/1.22));
		newRecord->setScale(10.0f);// start size
		newRecord->runAction(ScaleTo::create(1.2f, 1.0));

		this->addChild(newRecord);

		// ÒôÐ§
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {                      
			SimpleAudioEngine::getInstance()->playEffect("music_win.wav",false);  
		}
		userDefault->setIntegerForKey("Int",sc);
	}
	else
	{
		// ÒôÀÖ
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {                      
			SimpleAudioEngine::getInstance()->playEffect("music_fail.mp3",false);  
		}
	}
}
