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
        void destroyGame();
        
        int startManulAttack(Vec2 position);
        void clearManulAction();
        int startAIAttack();
        inline std::string getPlayerTc(int playerId){
                int tc = this->_player[playerId]->getAreaTc();
                std::ostringstream s;
                s << tc;
                return s.str();
        }
        inline int getPlayerJun(int idx){
                return this->_jun[idx];
        }
        inline int getCurrentPlayer(){
                return this->_jun[_ban];
        }
        
        std::map<int, int> afterBattle(int batlleResult);
        void startSupply(CallFunc* callback);
        inline int getCurrentStatus(){return _gameStatus;}
        inline int getUserTC(){return this->_player[_userId]->getAreaTc();}
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
        void initMapData();
         
        void makeNewMap();
        void setAreaLine(int cell, int dir);
        SimpleMapInfoBean initMapBasicInfo();
        int percolate(int pt, int cmax, int an);
        
        int set_area_tc(int pid);
        
        int startBattle();
        void occupyArea(int newOwner,int area);
       
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
