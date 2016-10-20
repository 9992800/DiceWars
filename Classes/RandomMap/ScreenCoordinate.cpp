//
//  ScreenCoordinate.cpp
//  DiceWars
//
//  Created by wsli on 16/10/20.
//
//

#include "ScreenCoordinate.hpp"
#include "GameConfig.hpp"
#include "MapBasicInfo.hpp"

static ScreenCoordinate*s_SharedScreen;

ScreenCoordinate* ScreenCoordinate::getInstance(){
        if (!s_SharedScreen)
        {
                s_SharedScreen = new (std::nothrow) ScreenCoordinate();
                CCASSERT(s_SharedScreen, "FATAL: Not enough memory");
                s_SharedScreen->init();
        }
        
        return s_SharedScreen;
}

ScreenCoordinate::ScreenCoordinate(void){
}

bool ScreenCoordinate::init(){
        _cpos_x = std::vector<float>(CEL_MAX);
        _cpos_y = std::vector<float>(CEL_MAX);
        
        _axis_x = std::vector<float>(DIR_INAREA + 1);
        _axis_y = std::vector<float>(DIR_INAREA + 1);
        return true;
}

void ScreenCoordinate::configScreen(Size mapSize){
        
        float w = mapSize.width / XMAX;
        float h = mapSize.height / YMAX;
        _cellSize = Size(w, h);
        
        int count = 0;
        for (int i = 0; i < YMAX; i++){
                
                for (int j = 0; j < XMAX; j++){
                        
                        _cpos_x[count] = j * _cellSize.width;
                        if (i % 2 == 1){
                                _cpos_x[count] += _cellSize.width / 2;
                        }
                        
                        _cpos_y[count] = mapSize.height - i * _cellSize.height;
                        ++count;
                }
        }
        
        _axis_x[0] = w / 2;
        _axis_x[1] = w;
        _axis_x[2] = w;
        _axis_x[3] = w / 2;
        _axis_x[4] = 0.f;
        _axis_x[5] = 0.f;
        _axis_x[6] = w / 2;
        
        _axis_y[0] = -3;
        _axis_y[1] = 3;
        _axis_y[2] = h - 3;
        _axis_y[3] = h + 3;
        _axis_y[4] = h - 3;
        _axis_y[5] = 3;
        _axis_y[6] = -3;
}
