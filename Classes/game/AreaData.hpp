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
#include "JoinData.hpp"

USING_NS_CC;

class DiceGame;

class AreaData: public Ref{
public:
        AreaData(int id);
        virtual ~AreaData();
        
        inline void increaseSize(int cell) {
                _size++;
                _cell_idxs.insert(cell);
        }
        inline void removeAreaTooSmall(int areaId) {
                if (_size <= 5){
                        _size = 0;
                        _cell_idxs.clear();
                }
        }
        inline bool isEmpty() {return _size == 0;}
        
        void initBound(int vertical, int horizen);
        inline void initCenter(){
                _cx = (_left + _right) / 2;
                _cy = (_top + _bottom) / 2;
        }
        void calcLenAndPos(int vertical, int horizen, int cell_idx, DiceGame* game);
        
        inline bool isNeedOwner(){return _size != 0 && _arm < 0;}
        inline void setOwner(int ownerId){_arm = ownerId;}
        inline int  getOwner(){return _arm;}
        
        bool initDice(){
                if (_size > 0){
                        _dice = 1;
                        return true;
                }
                
                return false;
        }
        
        inline bool needDice(int player_uid){
                return _size != 0 && _arm == player_uid && _dice < 8;
        }
        inline void increaseDice(){_dice++;}
        
        void initAreaLine(int cell, int dir, DiceGame* game);
        
        void drawArea(DrawNode* drawNode){
                drawBorder(drawNode);
                drawPolyGon(drawNode, _arm);
        }
        
        void drawAsSelected(DrawNode* drawNode){
                drawPolyGon(drawNode, -1);
        }
        void drawAsUnselected(DrawNode* drawNode){
                drawPolyGon(drawNode, _arm);
        }
        
private:
        void drawBorder(DrawNode* drawNode);
        void drawPolyGon(DrawNode* drawNode, int owner);
        
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
        int     _areaId;
        
        
        std::vector<int>    _join;
        std::vector<int>    _line_cel;
        std::vector<int>    _line_dir;
        std::set<int>       _cell_idxs;
};
#endif /* AreaData_hpp */
