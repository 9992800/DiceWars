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


USING_NS_CC;


#define XMAX (32)
#define YMAX (28)
#define PUT_DICE (3)
#define STOCK_MAX (64)
#define AREA_MAX (32)
#define CEL_MAX (XMAX * YMAX)
#define MAX_PLAYER (8)


#define SET_SIZE_TOZERO(target, SIZE) {\
        for (int i = 0; i < SIZE; i++){\
                target[i] = 0;\
        }\
} \


#define SET_SIZE_TOZERO2(target1, target2, SIZE) {\
        for (int i = 0; i < SIZE; i++){\
                target1[i] = 0;\
                target2[i] = 0;\
        }\
} \

#define SET_SIZE_TOIDX(target, SIZE) {\
        for (int i = 0; i < SIZE; i++){\
                target[i] = i;\
        }\
}

class DiceGame : public Ref{
        
        friend class AreaData;
public:
        static DiceGame* getInstance();
        std::string createMapXMLString();
        
        virtual ~DiceGame();
        
protected:
        DiceGame();
        
        bool init();
        
        std::vector<int> initRandomMapData();
        void makeNewMap();
        void setAreaLine(int cell, int dir);
        
private:
        SimpleMapInfoBean initMapBasicInfo();
        std::vector<int> _mapData;
        
        int percolate(int pt, int cmax, int an);
        
public:
        static int  CURRENT_PLAYERS;
        
private:
        int                             _userId;
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
