#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Scene
{
public: 
        virtual bool init();
     
        void menuEndTurnCallback(cocos2d::Ref* pSender);
    
        void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
        void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
     
        CREATE_FUNC(GameScene);
        
private:
        TMXTiledMap* _randomMap;
        MenuItemImage* _endTurnItem;
        float _lowestPostion_y;
};

#endif // __HELLOWORLD_SCENE_H__
