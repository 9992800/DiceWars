//
//  JoinData.cpp
//  DiceWars
//
//  Created by Wansheng Li on 16/10/12.
//
//

#include "JoinData.hpp"
JoinData::JoinData(){
        _dir = new int[6]();
}

void JoinData::initdir(int cellIdx){
        for (int i = 0; i < 6; i++){
                _dir[i] = next_cel(cellIdx, i);
        }
}

int JoinData::next_cel(int cellIdx, int dirIdx){
        return 0;
}
