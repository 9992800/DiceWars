#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "game/DiceGame.hpp"

USING_NS_CC;
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
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
        
        std::string xmls = DiceGame::getInstance()->createMapXMLString();

        _randomMap = TMXTiledMap::createWithXML(xmls, "maps");
        _randomMap->setPosition(Vec2(origin.x, origin.y));
        this->addChild(_randomMap, 2, kTagTileMap);
        
         Size cs = _randomMap->getContentSize();
        _lowestPostion_y = visibleSize.height + origin.y - cs.height;
        
        
        Director::getInstance()->setDepthTest(true);
        
        
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        
        auto node = DrawNode::create();
        node->drawLine(Vec2(0, 0), Vec2(500, 500), Color4F(1.0, 0.0, 0.0, 1.0));
        this->addChild(node);
        
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


void HelloWorld::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event){
        auto touch = touches[0];
        
        auto diff = touch->getDelta();
        diff.x = 0;
        auto node = getChildByTag(kTagTileMap);
        auto currentPos = node->getPosition();
        auto origin = Director::getInstance()->getVisibleOrigin();
        
        auto map_size = _randomMap->getContentSize();
        auto visibleSize = Director::getInstance()->getVisibleSize();
        
        
        printf("\r\n-------currentPos(%f, diff=%f)==origin=%f==_lowestPostion_y=%f map_size=%f)++++visibleSize=%f=====",
               currentPos.y, diff.y, origin.y, _lowestPostion_y, map_size.height, visibleSize.height);
        
        if (origin.y < (currentPos.y + diff.y)){
                diff.y = origin.y - currentPos.y;
        }
        
//        if ((currentPos.y + diff.y) < _lowestPostion_y){
//                diff.y = _lowestPostion_y - currentPos.y;
//        }
        
        node->setPosition(currentPos + diff);
}
