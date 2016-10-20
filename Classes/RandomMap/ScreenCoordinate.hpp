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
        CREATE_FUNC(ScreenCoordinate);
        ScreenCoordinate(void);
        virtual ~ScreenCoordinate();
        
        bool init();
//        void setScreenConfig();
        
private:
        std::vector<float> _cpos_x;
        std::vector<float> _cpos_y;
};

#endif /* ScreenCoordinate_hpp */
