//
//  DiceGame.hpp
//  DiceWars
//
//  Created by Wansheng Li on 16/10/12.
//
//

#ifndef DiceGame_hpp
#define DiceGame_hpp

#include "cocos2d.h"
#include "../RandomMap/RandomMap.hpp"
#include "AreaData.hpp"
#include "GamePlayer.hpp"
#include "JoinData.hpp"
#include "GameConfig.hpp"


USING_NS_CC;

class DiceGame : public Ref{
        
        friend class AreaData;
        friend class GameAI;
public:
        static DiceGame* getInstance();
        virtual ~DiceGame();
         
         TMXTiledMap* initGame(int playerNum);
        
        int startManulAttack(Vec2 position);
        int startAIAttack();
        inline int getPlayerTc(int playerId){
                return this->_player[playerId]->getAreaTc();
        }
        inline int getPlayerJun(int playerId){
                return this->_jun[playerId];
        }
        
        void afterBattle(int batlleResult);
        std::set<int> startSupply();
        inline int getCurrentStatus(){return _gameStatus;}
        inline void next_player(){
                if (++_ban >= CURRENT_PLAYERS){
                        _ban = 0;
                }
        }
        
        
        inline std::vector<int> getFightValue(int idx){                
                int area_id = (idx == 0) ? _area_from : _area_to;
                AreaData* area = this->_areaData[area_id];
                return area->getFightValues();
        }
        
protected:
        DiceGame();
        
        std::string createMapXMLString();
        void intAreaDrawObject(TMXTiledMap* map);
        bool init();
         
        void makeNewMap();
        void setAreaLine(int cell, int dir);
        SimpleMapInfoBean initMapBasicInfo();
        int percolate(int pt, int cmax, int an);
        
        void set_area_tc(int pid);
        
        int startBattle(); 
       
public:
        static int  CURRENT_PLAYERS;
        
private:
        int                             _userId;
        std::vector<int>                _mapData;
        std::vector<AreaData*>          _areaData;
        std::vector<GamePlayer*>        _player;
        std::vector<JoinData*>          _join;
        std::vector<int>                _jun;
        std::vector<int>                _cel;
        std::vector<int>                _rcel;
        std::vector<int>                _num;
        std::vector<int>                _chk;
private:
        int     _gameStatus;
        int     _ban;
        int     _area_from;
        int     _area_to;
        TMXTiledMap* _cur_map;};
#endif /* DiceGame_hpp */
