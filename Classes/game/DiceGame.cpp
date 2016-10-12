//
//  DiceGame.cpp
//  DiceWars
//
//  Created by Wansheng Li on 16/10/12.
//
//

#include "DiceGame.hpp"

static DiceGame* s_SharedGame = nullptr;

int DiceGame::ROWMAX = 32;
int DiceGame::COLMAX = 28;
int DiceGame::MAX_PLAYER = 7;//TODO::check if can I change it
int DiceGame::PUT_DICE = 3;
int DiceGame::STOCK_MAX = 64;
int DiceGame::AREA_MAX = 32;
int DiceGame::CEL_MAX = ROWMAX * COLMAX;


DiceGame* DiceGame::getInstance(){
        
        if (!s_SharedGame){
                s_SharedGame = new (std::nothrow)DiceGame();
                CCASSERT(s_SharedGame, "FATAL: Not enough memory");
                s_SharedGame->init();
        }
        
        return s_SharedGame;
}

DiceGame::DiceGame():_userId(0){
        _areaData = new (AreaData*)[AREA_MAX];
        _player   = new GamePlayer[MAX_PLAYER + 1]();
        _join     = new JoinData[CEL_MAX]();
        
        _num      = new int[CEL_MAX]();
        _jun      = new int[8]();
        _cel      = new int[CEL_MAX]();
        _rcel     = new int[CEL_MAX]();
}

bool DiceGame::init(){
        
        for (int i = 0; i < CEL_MAX; i++) {
                _num[i] = i;
        }
        
        for (int i = 0; i < CEL_MAX; i++){
                this->_join[i] = new JoinData();
                this->_join[i].initdir(i);
        }
        
        return true;
}

DiceGame::~DiceGame(){
        delete[]        _areaData;
        delete[]        _player;
        delete[]        _join;
        
        delete[]        _num;
        delete[]        _jun;
        delete[]        _cel;
        delete[]        _rcel;
}

std::string DiceGame::createMapXMLString(){
        
        std::vector<int> datas = this->RandomMapData();
        SimpleMapInfoBean simpleBean = this->initMapBasicInfo(datas);
        
        RandomMap* mapxml = RandomMap::create(simpleBean);
        std::string xmls = mapxml->getXmlString();
        
        return xmls;
}


std::vector<int> DiceGame::RandomMapData(){
        
        return _mapData;
}


SimpleMapInfoBean DiceGame::initMapBasicInfo(std::vector<int> datas){
        SimpleMapInfoBean simpleBean;
        int row = ROWMAX, columns = COLMAX;
        
        MapBasicBean mapBasic = {row, columns, 20, 20, 10, "x", "even", "hexagonal", "right-down"};
        simpleBean.mapBasicBean = mapBasic;
        
        TileSetBean tileSet = {"game", 20, 20, 2, 2, {"test.png", 40, 20}};
        simpleBean.tileSetBean = tileSet;
        
        LayerBean layer = {"map", row, columns, 1.0};
        layer.datas = datas;
        simpleBean.layerBean = layer;
        
        return simpleBean;
}


