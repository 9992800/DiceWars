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
private:
        
        MenuItemImage* _playItem;
};

#endif /* MainScene_hpp */
