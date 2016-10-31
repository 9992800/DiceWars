//
//  MainScene.cpp
//  DiceWars
//
//  Created by wsli on 16/10/24.
//
//
#include "GameScene.hpp"
#include "MainScene.hpp"
#include "PopUpOkDialog.hpp"

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
        
        _playItem = MenuItemImage::create("playbutton.png", "playbutton.png",
                                          CC_CALLBACK_1(MainScene::menuStartGameCallback, this));
        _playItem->setPosition(Vec2(origin.x + visibleSize.width - 2*_playItem->getContentSize().width ,
                                    origin.y +_playItem->getContentSize().height/2));
        
        
        _playNum_2 = MenuItemImage::create("maps/2.png", "maps/2_s.png",
                                           CC_CALLBACK_1(MainScene::menuSetPlayerNum, this));
        _playNum_2->setPosition(Vec2(origin.x + visibleSize.width / 2 - 3 * _playNum_2->getContentSize().width,
                                     origin.y + visibleSize.height / 2));
        
        _playNum_3 = MenuItemImage::create("maps/3.png", "maps/3_s.png",
                                           CC_CALLBACK_1(MainScene::menuSetPlayerNum, this));
        _playNum_3->setPosition(Vec2(origin.x + visibleSize.width / 2  - 2 * _playNum_3->getContentSize().width,
                                     origin.y + visibleSize.height / 2));
        
        _playNum_4 = MenuItemImage::create("maps/4.png", "maps/4_s.png",
                                           CC_CALLBACK_1(MainScene::menuSetPlayerNum, this));
        _playNum_4->setPosition(Vec2(origin.x + visibleSize.width / 2 - _playNum_4->getContentSize().width,
                                     origin.y + visibleSize.height / 2));
        
        _playNum_5 = MenuItemImage::create("maps/5.png", "maps/5_s.png",
                                          CC_CALLBACK_1(MainScene::menuSetPlayerNum, this));
        _playNum_5->setPosition(Vec2(origin.x + visibleSize.width / 2,  origin.y + visibleSize.height / 2));
        
        _playNum_6 = MenuItemImage::create("maps/6.png", "maps/6_s.png",
                                           CC_CALLBACK_1(MainScene::menuSetPlayerNum, this));
        _playNum_6->setPosition(Vec2(origin.x + visibleSize.width / 2 + _playNum_6->getContentSize().width,
                                     origin.y + visibleSize.height / 2));
        
        _playNum_7 = MenuItemImage::create("maps/7.png", "maps/7_s.png",
                                           CC_CALLBACK_1(MainScene::menuSetPlayerNum, this));
        _playNum_7->setPosition(Vec2(origin.x + visibleSize.width / 2 + 2 * _playNum_7->getContentSize().width,
                                     origin.y + visibleSize.height / 2));
        _playNum_7->setColor(Color3B(255, 0, 0));
        
        _playNum_8 = MenuItemImage::create("maps/8.png", "maps/8_s.png",
                                           CC_CALLBACK_1(MainScene::menuSetPlayerNum, this));
        _playNum_8->setPosition(Vec2(origin.x + visibleSize.width / 2 + 3 * _playNum_8->getContentSize().width,
                                     origin.y + visibleSize.height / 2));
        
        auto menu = Menu::create(_playItem,_playNum_2, _playNum_3, _playNum_4, _playNum_5, _playNum_6, _playNum_7, _playNum_8, NULL);
        menu->setPosition(Vec2::ZERO);
        layer->addChild(menu, 3);
        
        LayerColor* back_ground = LayerColor::create(Color4B(255,255,255,255.0));
        layer->addChild(back_ground);
        
        _selected_num = 6;
       
        
        BaseDialogConfig config = {"DIALOG_BACKGROUND.png",
                "吾名一叶",
                "娇兰傲梅世人赏，却少幽芬暗里藏。不看百花共争艳，独爱疏樱一枝香",
                20, 20, 50, 30};
        PopUpOkDialog* dialog = PopUpOkDialog::create(config);
        layer->addChild(dialog, 5); 
        
        return true;
}


void MainScene::menuStartGameCallback(Ref* pSender)
{
        auto gameScene = GameScene::create(_selected_num);
        Director::getInstance()->pushScene(gameScene);
}

void MainScene::menuSetPlayerNum(Ref* pSender){
        if (pSender == _playNum_2){
                _selected_num  = 2;
        }else if (pSender == _playNum_3){
                _selected_num  = 3;
        }else if (pSender == _playNum_4){
                _selected_num  = 4;
        }else if (pSender == _playNum_5){
                _selected_num  = 5;
        }else if (pSender == _playNum_6){
                _selected_num  = 6;
        }else if (pSender == _playNum_7){
                _selected_num  = 7;
        }else if (pSender == _playNum_8){
                _selected_num  = 8;
        }
}

