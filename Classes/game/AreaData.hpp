//
//  AreaData.hpp
//  DiceWars
//
//  Created by Wansheng Li on 16/10/12.
//
//

#ifndef AreaData_hpp
#define AreaData_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "JoinData.hpp"

USING_NS_CC;

class DiceGame;

class AreaData: public Ref{
public:
        AreaData();
        virtual ~AreaData();
        
        inline void increaseSize() { _size++;}
        inline void removeAreaTooSmall(int areaId) {if (_size <= 5) _size = 0;}
        inline bool isEmpty() {return _size == 0;}
        
        void initBound(int vertical, int horizen);
        void initCenter();
        void calcLenAndPos(int vertical, int horizen, int cell_idx, DiceGame* game);
        
        inline bool isNeedOwner(){return _size != 0 && _arm < 0;}
        inline void setOwner(int ownerId){_arm = ownerId;}
        
        bool initDice();
        bool needDice(int player_uid);
        inline void increaseDice(){_dice++;}
        
        void initAreaLine(int cell, int dir, DiceGame* game);
        
private:
        int     _size;
        int     _cpos;
        int     _arm;
        int     _dice;
        int     _left;
        int     _right;
        int     _top;
        int     _bottom;
        int     _cx;
        int     _cy;
        int     _len_min;
        
        
        std::vector<int>    _join;
        std::vector<int>    _line_cel;
        std::vector<int>    _line_dir;
};
#endif /* AreaData_hpp */