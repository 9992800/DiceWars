//
//  MainScene.hpp
//  DiceWars
//
//  Created by wsli on 16/10/24.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;

USING_NS_CC;

class MainScene : public Scene
{
public:
        virtual bool init()override;
        virtual ~MainScene();
        CREATE_FUNC(MainScene);
        void update(float delta)override;
private:
        
        void menuStartGameCallback(cocos2d::Ref* pSender);
        void menuSetPlayerNum(cocos2d::Ref* pSender);
private:
        
        MenuItemImage* _playItem;
        MenuItemImage *_playNum_2, *_playNum_3, *_playNum_4,
                      *_playNum_5, *_playNum_6, *_playNum_7,
                      *_playNum_8;
        
        int _selected_num;
        
        
        int _count;
        LoadingBar* _loadingBar;
        
};

#endif /* MainScene_hpp */
