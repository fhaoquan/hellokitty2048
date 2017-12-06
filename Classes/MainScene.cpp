#include "MainScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("1080.jpg");
	bg->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	addChild(bg);

	auto title = Label::createWithTTF("2 0 4 8","fonts/HelloKitty.ttf",150);
	title->setPosition(Point(visibleSize.width/2, visibleSize.height*3/4));
	addChild(title);

	auto normalSprite = Sprite::create("000.png");
	auto selectSprite = Sprite::create("001.png");
	auto closeItem = MenuItemSprite::create(normalSprite,selectSprite,NULL,CC_CALLBACK_0(MainScene::nextscene,this));
	closeItem->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	auto menu = Menu::createWithItem(closeItem);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);

	SimpleAudioEngine::getInstance() -> preloadEffect("move.mp3");  

    return true;
}


void MainScene::nextscene()
{
	Director::getInstance()->replaceScene(TransitionFadeTR::create(0.5, GameScene::createScene()));
}

void MainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
