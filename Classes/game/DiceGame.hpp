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
        
public:
        static DiceGame* getInstance();
        virtual ~DiceGame();
        
        TMXTiledMap* createMap();
        void startGame();
        
protected:
        DiceGame();
        
        std::string createMapXMLString();
        void drawBorderForArea();
        bool init();
         
        void makeNewMap();
        void setAreaLine(int cell, int dir);
        SimpleMapInfoBean initMapBasicInfo();
        int percolate(int pt, int cmax, int an);
        
        void set_area_tc(int pid);
        
public:
        static int  CURRENT_PLAYERS;
        
private:
        
        DrawNode* _drawNode;
        
private:
        int                             _userId;
        std::vector<int>                _mapData;
        std::vector<AreaData*>          _areaData;
        std::vector<GamePlayer*>        _player;
        std::vector<JoinData*>          _join;
        std::vector<int>                _jun;
        std::vector<int>                _cel;
        std::vector<int>                _rcel;
        std::vector<int>                _num;
        std::vector<int>                _chk;
};
#endif /* DiceGame_hpp */
