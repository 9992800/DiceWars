//
//  AreaData.cpp
//  DiceWars
//
//  Created by Wansheng Li on 16/10/12.
//
//

#include "AreaData.hpp"
AreaData::AreaData()
:_size(0),
_cpos(0),
_arm(0),
_dice(0),
_left(0),
_right(0),
_top(0),
_bottom(0),
_cx(0),
_cy(0),
_len_min(0)
{
        _join       = new int[32]();
        _line_cel   = new int[100]();
        _line_dir   = new int[100]();
}


AreaData::~AreaData(){
        delete[] _join;
        delete[] _line_cel;
        delete[] _line_dir;
}
