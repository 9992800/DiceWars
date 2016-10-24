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

USING_NS_CC;

class MainScene : public Scene
{
public:
        virtual bool init();
        
        CREATE_FUNC(MainScene);
private:
        
        void menuStartGameCallback(cocos2d::Ref* pSender);
        void menuSetPlayerNum(cocos2d::Ref* pSender);
private:
        
        MenuItemImage* _playItem;
        MenuItemImage *_playNum_2, *_playNum_3, *_playNum_4,
                      *_playNum_5, *_playNum_6, *_playNum_7,
                      *_playNum_8;
        
        
};

#endif /* MainScene_hpp */
