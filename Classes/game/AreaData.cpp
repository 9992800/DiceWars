//
//  AreaData.cpp
//  DiceWars
//
//  Created by Wansheng Li on 16/10/12.
//
//

#include "AreaData.hpp"
#include "DiceGame.hpp"

AreaData::AreaData()
:_size(0),
_cpos(0),
_arm(-1),
_dice(0),
_left(XMAX),
_right(-1),
_top(YMAX),
_bottom(-1),
_cx(0),
_cy(0),
_len_min(9999)
{
        _join       = std::vector<int>(32);
        _line_cel   = std::vector<int>(100);
        _line_dir   = std::vector<int>(100);
}


AreaData::~AreaData(){
        _join.clear();
        _line_cel.clear();
        _line_dir.clear();
}


void AreaData::initBound(int vertical, int horizen){
        
        if (horizen < _left){
                _left = horizen;
        }
        
        if (horizen > _right){
                _right = horizen;
        }
        
        if (vertical < _top){
                _top = vertical;
        }
        if (vertical > _bottom){
                _bottom = vertical;
        }
}


void AreaData::initCenter(){
        _cx = (_left + _right) / 2;
        _cy = (_top + _bottom) / 2;
}


void AreaData::calcLenAndPos(int vertical, int horizen, int cell_idx, DiceGame* game){
        
        int dis_h = _cx - horizen;
        if (dis_h < 0) dis_h = 0 - dis_h;
        
        int dis_v = _cy - vertical;
        if (dis_v < 0) dis_v = 0 - dis_v;
        
        int dis_t = dis_v + dis_h;
        
        bool near_diff_area =  false;
        
        for (int i = 0; i < 6; i++){
                
                int joined_cell = game->_join[cell_idx]->getJoinDir(i);
                
                if (joined_cell > 0){
                        
                        int join_area_id = game->_cel[joined_cell];
                        if (join_area_id != game->_cel[cell_idx]){
                                near_diff_area = true;
                                _join[join_area_id] = 1;
                        }
                }
        }
        
        if (near_diff_area){
                dis_t += 4;
        }
        
        if (dis_t < _len_min){
                
                _len_min = dis_t;
                
                _cpos = vertical * XMAX + horizen;
        }
}




bool AreaData::initDice(){
        if (_size > 0){
                _dice = 1;
                return true;
        }
        
        return false;
}


bool AreaData::needDice(int player_uid){
        return _size != 0 && _arm == player_uid && _dice < 8;
}


void AreaData::initAreaLine(int cell, int dir, DiceGame* game){
        
        int cell_num = 0;
        int cur_dir = dir;
        int cur_cell = cell;
        int cur_area = game->_cel[cell];
        
        _line_cel[cell_num] = cur_cell;
        _line_dir[cell_num] = cur_dir;
        
        ++cell_num;
        
        for (int i = 0; i < 100; i++){
                
                ++cur_dir;
                if (cur_dir >= 6){
                        cur_dir = 0;
                }
                
                int joined_cell = game->_join[cur_cell]->getJoinDir(cur_dir);
                
                if (joined_cell >= 0 &&
                    game->_cel[joined_cell] == cur_area){
                        
                        cur_cell = joined_cell;
                        cur_dir -= 2;
                        if (cur_dir < 0){
                                cur_dir += 6;
                        }
                }
                
                _line_cel[cell_num] = cur_cell;
                _line_dir[cell_num] = cur_dir;
                ++cell_num;
                
                if (cur_cell == cell && cur_dir == dir){
                        return;
                }
        }
}
