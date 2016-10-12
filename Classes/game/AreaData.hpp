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

USING_NS_CC;

class AreaData: public Ref{
public:
        AreaData();
        virtual ~AreaData();
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
        int*    _join;
        int*    _line_cel;
        int*    _line_dir;
};
#endif /* AreaData_hpp */
