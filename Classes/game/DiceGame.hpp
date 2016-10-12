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

class DiceGame : public Ref{
public:
        static DiceGame* getInstance();
        std::string createMapXMLString();
        
        virtual ~DiceGame();
        
protected:
        DiceGame();
        
        bool init();
        
        std::vector<int> RandomMapData();
        
private:
        SimpleMapInfoBean initMapBasicInfo(std::vector<int> datas);
        std::vector<int> _mapData;
        
public:
        static int ROWMAX;
        static int COLMAX;
        static int MAX_PLAYER;
        static int PUT_DICE;
        static int STOCK_MAX;
        static int AREA_MAX;
        static int CEL_MAX;
private:
        int             _userId;
        AreaData*       _areaData[];
        GamePlayer*     _player;
        JoinData*       _join[];
        int*            _jun;
        int*            _cel;
        int*            _rcel;
        int*            _num;
};
#endif /* DiceGame_hpp */
