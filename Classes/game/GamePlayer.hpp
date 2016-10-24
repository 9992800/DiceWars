//
//  GamePlayer.hpp
//  DiceWars
//
//  Created by Wansheng Li on 16/10/12.
//
//

#ifndef GamePlayer_hpp
#define GamePlayer_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class GamePlayer: public Ref{
public:
        GamePlayer(int id);
        virtual ~GamePlayer();
        inline void setAreaTc(int tc){
                _area_tc = tc;
        }
        inline int getAreaTc(){
                return _area_tc;
        }
        inline void increaseAreaC(){
                ++_area_c;
        }
        inline void addDiceC(int dice){
                _dice_c += dice;
        }
        
        inline int getDiceC(){
                return _dice_c;
        }
        inline int getDiceJun(){
                return _dice_jun;
        }
        inline void setDiceJun(int jun){
                _dice_jun = jun;
        }
        
private:
        int     _player_id;
        int     _area_c;
        int     _area_tc;
        int     _dice_c;
        int     _dice_jun;
        int     _stock;
};
#endif /* GamePlayer_hpp */
