#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
        void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
        void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
//        void onTouchesEnded(const std::vector<Touch*>& touches, Event *event);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
        
private:
        cocos2d::TMXTiledMap* _randomMap;
        float _lowestPostion_y;
};

#endif // __HELLOWORLD_SCENE_H__
