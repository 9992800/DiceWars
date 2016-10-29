#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameConfig.hpp"

USING_NS_CC;

class GameScene : public Scene
{
public: 
        virtual bool init();
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
        void afterSupply();
        
        void menuEndTurnCallback(cocos2d::Ref* pSender);
        void menuForBackCallback(cocos2d::Ref* pSender);
        
        void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
        void onTouchesEnded(const std::vector<Touch*>& touches, Event *event);
private:
        GameScene(int pn):_player_num(pn),
        _randomMap(nullptr),
        _endTurnItem(nullptr),
        _startAIItem(nullptr),
        _lowestPostion_y(0.f),
        _isMoved(false){
                _menu_items = Vector<MenuItem*>(MAX_PLAYER);
        }
        
        void initPlayerTc(Vec2 pos);
        void initCtrlButton(Vec2 origin, Size visibleSize);
        void initFightDice(Vec2 origin, Size visibleSize);
        void initGameLayer(Vec2 origin);
        void initActionListener(Vec2 origin, Size visibleSize);
        
        void playBattleAnimation(int result, std::vector<int>, std::vector<int>);
        void playAnimation(int result);
private:
        TMXTiledMap*    _randomMap;
        MenuItemImage*  _endTurnItem;
        MenuItemImage*  _startAIItem;
        MenuItemImage*  _forBackItem;

        float           _lowestPostion_y;
        int             _player_num;
        
        Vector<MenuItem*> _menu_items;
        Map<int, Label*>  _tc_values;
        bool            _isMoved;
        Sprite* _tamara;
        Layer* _gameLayer, *_controllerLayer;
        std::vector<Label*> _fight_from;
        std::vector<Label*> _fight_to;
};

#endif // __HELLOWORLD_SCENE_H__
