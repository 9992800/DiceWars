//
//  DiceGame.hpp
//  DiceWars
//
//  Created by Wansheng Li on 16/10/12.
//
//

#ifndef DiceGame_hpp
#define DiceGame_hpp

#include "cocos2d.h"
#include "../RandomMap/RandomMap.hpp"
#include "AreaData.hpp"
#include "GamePlayer.hpp"
#include "JoinData.hpp"
#include "GameConfig.hpp"


USING_NS_CC;

class DiceGame : public Ref{
        
        friend class AreaData;
        friend class GameAI;
public:
        static DiceGame* getInstance();
        virtual ~DiceGame();
         
         TMXTiledMap* initGame(Layer* gameLayer, int playerNum);
        
        void startAttack(Vec2 position, CallFunc* callback);
        void startAIAttack(CallFunc* callback);
        inline int getPlayerTc(int playerId){
                return this->_player[playerId]->getAreaTc();
        }
        void afterBattle();
        inline bool isManualTurn(){return _userId == this->_jun[_ban];}
        
protected:
        DiceGame();
        
        std::string createMapXMLString();
        void intAreaDrawObject(TMXTiledMap* map);
        bool init();
         
        void makeNewMap();
        void setAreaLine(int cell, int dir);
        SimpleMapInfoBean initMapBasicInfo();
        int percolate(int pt, int cmax, int an);
        
        void set_area_tc(int pid);

        void playBattleAnimation(CallFunc* callback);
        inline void next_player(){
                if (++_ban >= CURRENT_PLAYERS){
                        _ban = 0;
                }
        }
       
public:
        static int  CURRENT_PLAYERS;
        
private:
        int                             _userId;
        int                             _selected_area;
        std::vector<int>                _mapData;
        std::vector<AreaData*>          _areaData;
        std::vector<GamePlayer*>        _player;
        std::vector<JoinData*>          _join;
        std::vector<int>                _jun;
        std::vector<int>                _cel;
        std::vector<int>                _rcel;
        std::vector<int>                _num;
        std::vector<int>                _chk;
private:
        int     _gameStatus;
        int     _ban;
        int     _area_from;
        int     _area_to;
        TMXTiledMap* _cur_map;
        Sprite* _tamara;
        EventListenerCustom* _frameDisplayedListener;
        Layer* _gameLayer;
};
#endif /* DiceGame_hpp */
