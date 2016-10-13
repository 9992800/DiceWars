//
//  JoinData.hpp
//  DiceWars
//
//  Created by Wansheng Li on 16/10/12.
//
//

#ifndef JoinData_hpp
#define JoinData_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class JoinData: public Ref{
public:
        JoinData();
        virtual ~JoinData();
        
        enum {
                CELL_DIR_RIGHT_TOP      = 0,
                CELL_DIR_RIGHT_MID      = 1,
                CELL_DIR_RIGHT_BOTTOM   = 2,
                CELL_DIR_LEFT_BOTTOM    = 3,
                CELL_DIR_LEFT_MID       = 4,
                CELL_DIR_LEFT_TOP       = 5
        };
        
        void initdir(int cellIdx);
        
        inline int getJoinDir(int dirIdx){ return _dir[dirIdx];}
private:
        int next_cel(int cellIdx, int dirIdx);
private:
        int* _dir;
};
#endif /* JoinData_hpp */
