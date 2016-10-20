//
//  ScreenCoordinate.hpp
//  DiceWars
//
//  Created by wsli on 16/10/20.
//
//

#ifndef ScreenCoordinate_hpp
#define ScreenCoordinate_hpp
#include "cocos2d.h"

USING_NS_CC;
class ScreenCoordinate: public Ref{
        
public:
        static ScreenCoordinate* getInstance();
        void configScreen(Size mapSize);
        Vec2 getCellPos(int cell, int dir);
        Size getCellSize(){return _cellSize;}
private:
        ScreenCoordinate(void);
        bool init();

private:
        std::vector<float> _cpos_x;
        std::vector<float> _cpos_y;
        
        std::vector<float> _axis_x;
        std::vector<float> _axis_y;
        
        Size _cellSize;
        
};

#endif /* ScreenCoordinate_hpp */
