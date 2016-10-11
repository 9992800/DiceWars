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
        
        

        
        SimpleMapInfoBean simpleBean;
        int row = 32, columns = 3;
        MapBasicBean mapBasic = {row, columns, 20, 20, 10, "x", "even", "hexagonal", "right-down"};
        simpleBean.mapBasicBean = mapBasic;
        
        TileSetBean tileSet = {"MapTest", 20, 20, 2, 2, {"hexa-axis-x.png", 40, 20}};
        simpleBean.tileSetBean = tileSet;
        
        LayerBean layer = {"map", row, columns, 1.0};
        std::vector<int> datas;
        for (int i = 0; i < row * columns; i++){
                int value = random<int>(1, 2);
                datas.push_back(value);
        }
        layer.datas = datas;
        simpleBean.layerBean = layer;
        
        RandomMap* mapxml = RandomMap::create(simpleBean);
        
        std::string xmls = mapxml->getXmlString();
        printf("---test=%s---", xmls.c_str());
//        auto map = TMXTiledMap::createWithXML(xmls, "maps");
        auto map = TMXTiledMap::create("maps/issue16105.tmx");
//        map->setAnchorPoint(Vec2(0.0, -0.0));
        
        
        Size cs = map->getContentSize();
        map->setPosition(Vec2(origin.x, origin.y));
        auto color = LayerColor::create( Color4B(64,0,0,255), cs.width, cs.height);
        map->addChild(color, -1);
        
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
