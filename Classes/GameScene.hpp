#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameConfig.hpp"

USING_NS_CC;

class GameScene : public Scene
{
public: 
        virtual bool init();
     
        void menuEndTurnCallback(cocos2d::Ref* pSender);
    
        void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
        void onTouchesEnded(const std::vector<Touch*>& touches, Event *event);
        
        static GameScene* create(int pn)
        {
                GameScene *pRet = new(std::nothrow) GameScene(pn);
                if (pRet && pRet->init())
                {
                        pRet->autorelease();
                        return pRet;
                }
                else
                {
                        delete pRet;
                        pRet = nullptr;
                        return nullptr;
                }
        }
        
        virtual ~GameScene(){
                _menu_items.clear();
        }
        
protected:
        void afterBattle(int res);
private:
        GameScene(int pn):_player_num(pn),
        _randomMap(nullptr),
        _endTurnItem(nullptr),
        _startAIItem(nullptr),
        _lowestPostion_y(0.f),
        _isMoved(false){
                _menu_items = Vector<MenuItem*>(MAX_PLAYER);
        }
        
        void playBattleAnimation(CallFunc* callback);
        void playSupplyAnimation(CallFunc* callback);
        void playAnimation(int result);
private:
        TMXTiledMap*    _randomMap;
        MenuItemImage*  _endTurnItem;
        MenuItemImage*  _startAIItem;
        float           _lowestPostion_y;
        int             _player_num;
        
        Vector<MenuItem*> _menu_items;
        bool            _isMoved;
        Sprite* _tamara;
        Layer* _gameLayer;
};

#endif // __HELLOWORLD_SCENE_H__
