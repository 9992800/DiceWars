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
        
        void initdir(int cellIdx);
private:
        int next_cel(int cellIdx, int dirIdx);
private:
        int* _dir;
};
#endif /* JoinData_hpp */
