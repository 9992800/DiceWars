//
//  DiceGame.hpp
//  DiceWars
//
//  Created by Wansheng Li on 16/10/12.
//
//

#ifndef DiceGame_hpp
#define DiceGame_hpp

#include <stdio.h>
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
        
        TMXTiledMap* createMap();
        void startGame();
        
        void startAttack(TMXTiledMap* map, Vec2 position);
        
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
};
#endif /* DiceGame_hpp */
