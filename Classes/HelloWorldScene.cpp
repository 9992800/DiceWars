#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "RandomMap/RandomMap.hpp"

USING_NS_CC;

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
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
        
//        auto map = TMXTiledMap::create("maps/hexa-axis-x.tmx");
//
//        this->addChild(map, 2);
        
        SimpleMapInfoBean simpleBean;
        MapBasicBean mapBasic = {32, 28, 80, 80, 40, "x", "odd", "hexagonal", "right-down"};
        simpleBean.mapBasicBean = mapBasic;
        
        TileSetBean tileSet = {"MapTest", 80, 80, 2, 2, {"hexa-axis-x.png", 160, 80}};
        simpleBean.tileSetBean = tileSet;
        
        LayerBean layer = {"map", 3, 3, 0.2};
        std::vector<int> datas;
        datas.push_back(1);
        datas.push_back(2);
        datas.push_back(1);
        datas.push_back(2);
        datas.push_back(2);
        datas.push_back(1);
        datas.push_back(1);
        datas.push_back(1);
        datas.push_back(2);
        datas.push_back(2);
        layer.datas = datas;
        simpleBean.layerBean = layer;
        
        RandomMap* mapxml = RandomMap::create(simpleBean);
        
        std::string xmls = mapxml->getXmlString();
        printf("---test=%s---", xmls.c_str());
        auto map = TMXTiledMap::createWithXML(xmls, "maps");
        
        this->addChild(map, 2);
    
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
