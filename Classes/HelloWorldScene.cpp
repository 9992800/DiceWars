#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "game/DiceGame.hpp"

enum
{
        kTagTileMap = 1,
};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
        
    // add layer as a child to scene
    scene->addChild(layer); 

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y +closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 3);

    /////////////////////////////
    // 3. add your codes below...
        
        _randomMap = DiceGame::getInstance()->createMap();
        _randomMap->setPosition(Vec2(origin.x, origin.y));
        this->addChild(_randomMap, 2, kTagTileMap);
        
        LayerColor* back_ground = LayerColor::create(Color4B(255,255,255,255.0));
        this->addChild(back_ground);
         Size cs = _randomMap->getContentSize();
        //TODO::why always lost 6 pixels
        _lowestPostion_y = visibleSize.height + origin.y - cs.height - 6;
        
        
        Director::getInstance()->setDepthTest(true);
        
        
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
        listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
                 
        return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}


void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event* event){
        auto touch = touches[0];
        
        auto diff = touch->getDelta();
        diff.x = 0;
        auto node = getChildByTag(kTagTileMap);
        auto currentPos = node->getPosition();
        auto origin = Director::getInstance()->getVisibleOrigin();
        
        auto map_size = _randomMap->getContentSize();
        
        if (origin.y < (currentPos.y + diff.y)){
                diff.y = origin.y - currentPos.y;
        }
        
        if ((currentPos.y + diff.y) < _lowestPostion_y){
                diff.y = _lowestPostion_y - currentPos.y;
        }
        
        node->setPosition(currentPos + diff);
}


void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event *event){
        auto touch = touches[0];
        auto position = touch->getLocation();
        printf("\r\n===position(%f, %f)===",position.x, position.y);
}

