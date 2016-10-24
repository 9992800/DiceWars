//
//  MainScene.cpp
//  DiceWars
//
//  Created by wsli on 16/10/24.
//
//
#include "GameScene.hpp"
#include "MainScene.hpp"
 
bool MainScene::init()
{
        if (!Scene::init() )
        {
                return false;
        }
        
        Layer* layer = Layer::create();
        this->addChild(layer);
        
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        _playItem = MenuItemImage::create("playbutton.png",
                                          "playbutton.png",
                                          CC_CALLBACK_1(MainScene::menuStartGameCallback, this));
        _playItem->setPosition(Vec2(origin.x + visibleSize.width - 2*_playItem->getContentSize().width ,
                                    origin.y +_playItem->getContentSize().height/2));
        
        auto menu = Menu::create(_playItem, NULL);
        menu->setPosition(Vec2::ZERO);
        layer->addChild(menu, 3);
        
        LayerColor* back_ground = LayerColor::create(Color4B(255,255,255,255.0));
        layer->addChild(back_ground);
        
        return true;
}



void MainScene::menuStartGameCallback(Ref* pSender)
{
        auto gameScene = GameScene::create();
        Director::getInstance()->pushScene(gameScene);
}
