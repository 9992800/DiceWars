//
//  ScreenCoordinate.cpp
//  DiceWars
//
//  Created by wsli on 16/10/20.
//
//

#include "ScreenCoordinate.hpp"
#include "DiceGame.hpp"
#include "MapBasicInfo.hpp"

ScreenCoordinate::ScreenCoordinate(void){
        _cpos_x = std::vector<float>(XMAX);
        _cpos_y = std::vector<float>(YMAX);
}

ScreenCoordinate::~ScreenCoordinate(){
        _cpos_x.clear();
        _cpos_y.clear();
}

bool ScreenCoordinate::init(){
        Size cellSize = MapResolustion::getScreenCell();
        int count = 0;
        for (int i = 0; i <YMAX; i++){
                
                for (int j = 0; j < XMAX; j++){
                        
                        _cpos_x[count] = j * cellSize.width;
                        if (i % 2 == 1){
                                _cpos_x[count] += cellSize.width / 2;
                        }
                        
                        _cpos_y[count] = i * cellSize.height;
                        ++count;
                }
        }
        
        return true;
}
