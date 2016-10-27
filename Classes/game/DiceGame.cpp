//
//  DiceGame.cpp
//  DiceWars
//
//  Created by Wansheng Li on 16/10/12.
//
//

#include "DiceGame.hpp"
#include "ScreenCoordinate.hpp"
#include "GameAI.hpp"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
using namespace spine;

static DiceGame* s_SharedGame = nullptr;
int DiceGame::CURRENT_PLAYERS = 6;
enum
{
        kTagTileMap = 1,
};

DiceGame* DiceGame::getInstance(){
        
        if (!s_SharedGame){
                s_SharedGame = new (std::nothrow)DiceGame();
                CCASSERT(s_SharedGame, "FATAL: Not enough memory");
                s_SharedGame->init();
        }
        
        return s_SharedGame;
}

DiceGame::DiceGame():_userId(0),
_selected_area(AREA_UNSELECTED),
_gameStatus(GAME_STATUS_INIT),
_ban(0),
_area_from(-1),
_area_to(-1),
_cur_map(nullptr){
        _join           = std::vector<JoinData*>(CEL_MAX);
        _areaData       = std::vector<AreaData*>(AREA_MAX);
        _player         = std::vector<GamePlayer*>(MAX_PLAYER);
        _jun            = std::vector<int>(MAX_PLAYER);
        _cel            = std::vector<int>(CEL_MAX);
        _rcel           = std::vector<int>(CEL_MAX);
        _num            = std::vector<int>(CEL_MAX);
        _chk            = std::vector<int>(AREA_MAX);
        
        _tamara = Sprite::create("spine/grossinis_sister1.png");
}

bool DiceGame::init(){
        
        for (int i = 0; i < CEL_MAX; i++){
                JoinData* join_data = new JoinData();
                join_data->initdir(i);
                _join[i] = join_data;
        }
        
        return true;
}

DiceGame::~DiceGame(){
        
        for (AreaData* p : _areaData){
                delete p;
        }
        for (GamePlayer* p : _player){
                delete p;
        }
        for (JoinData* p : _join){
                delete p;
        }
        
        _join.clear();
        _areaData.clear();
        _player.clear();
        _jun.clear();
        _cel.clear();
        _rcel.clear();
        _num.clear();
        _chk.clear();
}

std::string DiceGame::createMapXMLString(){
        
        this->makeNewMap();         
        
        for (int i = 0; i < CEL_MAX; i++){
                int area_id = this->_cel[i];
                AreaData* area = this->_areaData[area_id];
                int payer_uid = area->getOwner();
                if (area_id > 0)
                        _mapData.push_back(payer_uid + 1);
                else
                        _mapData.push_back(0);
        }
        
        SimpleMapInfoBean simpleBean = this->initMapBasicInfo();
        
        RandomMap* mapxml = RandomMap::create(simpleBean);
        std::string xmls = mapxml->getXmlString();
        
        return xmls;
}

void DiceGame::intAreaDrawObject(TMXTiledMap* map){
        
        for (int i = 0; i < AREA_MAX; i++){
                DrawNode* draw_node = DrawNode::create();
                map->addChild(draw_node, 1);
                AreaData* area = this->_areaData[i];
                area->intDrawObject(draw_node);
        }
}

SimpleMapInfoBean DiceGame::initMapBasicInfo(){
        SimpleMapInfoBean simpleBean;
        int row = XMAX, columns = YMAX;
        
        MapResolustionConfig config =  MapResolustion::getConfig();
        
        MapBasicBean mapBasic = {row, columns, config.mapTileWidth, config.mapTileHeight, config.hexsidelength,
                "y", "odd", "hexagonal", "right-down"};
        simpleBean.mapBasicBean = mapBasic;
        
        TileSetBean tileSet = {"game", config.tilesetWidth, config.tilesetHeight,
                6, 3, {config.imgSource, config.imageWidth, config.imageHeight}};
        
        simpleBean.tileSetBean = tileSet;
        
        LayerBean layer = {"map", row, columns, 1.0};
        layer.datas = _mapData;
        simpleBean.layerBean = layer;
        
        return simpleBean;
}


void DiceGame::makeNewMap(){
        
        SET_SIZE_TOIDX(_num, CEL_MAX);
        for (int i = 0; i <  CEL_MAX; i++){
                int radom = random(0, CEL_MAX - 1);
                
                int tmp = this->_num[i];
                this->_num[i] = this->_num[radom];
                this->_num[radom] = tmp;
        }
        
        SET_SIZE_TOZERO2(_cel, _rcel, CEL_MAX);
        int radom = random(0, CEL_MAX -1);
        _rcel[radom] = 1;
        /*create original area data*/
        for (int i = 1; i < AREA_MAX; ++i){
                int valaible_cel = 9999;
                int selected_cell;
                for (int j = 0; j < CEL_MAX; j++){
                        
                        if (_cel[j] <= 0
                            && _num[j] <= valaible_cel
                            && _rcel[j] != 0){
                                
                                valaible_cel = _num[j];
                                selected_cell = j;
                        }
                }
                
                if (9999 == valaible_cel){
                        break;
                }
                
                int next_cel = this->percolate(selected_cell, 8, i);
                if (0 ==  next_cel){
                        break;
                }                
        };
        /*make all cells around created area been in used*/
        for (int i = 0; i < CEL_MAX; i++){
                if (_cel[i] > 0){
                        continue;
                }
                
                int areaIdx = 0;
                bool areaNotUsed = false;
                for (int j = 0; j < DIR_INAREA; j++) {
                        int joined_cell = _join[i]->getJoinDir(j);
                        if (joined_cell < 0){
                                continue;
                        }
                        
                        if (this->_cel[joined_cell] == 0){
                                areaNotUsed = true;
                        }else{
                                areaIdx = _cel[joined_cell];
                        }
                }
                
                if (!areaNotUsed){
                        _cel[i] = areaIdx;
                }
        }
                 
        for (int i = 0 ; i < AREA_MAX; i++){
                
                if (nullptr != this->_areaData[i]){
                        delete this->_areaData[i];
                }
                this->_areaData[i] = new AreaData(i);
        }
        
        for (int i = 0; i < CEL_MAX; i++){
                int area_id = this->_cel[i];
                if (area_id > 0){
                        this->_areaData[area_id]->increaseSize(i);
                }
        }
        
        for (int i = 1; i < AREA_MAX; i++){
                this->_areaData[i]->removeAreaTooSmall(i);
        }
        
        for (int i = 0; i < CEL_MAX; i++){
                int areaId = this->_cel[i];
                if (this->_areaData[areaId]->isEmpty() ){
                        this->_cel[i] = 0;
                }
        }
        
        for (int j = 0; j < CEL_MAX; j++){
                int area_id = this->_cel[j];
                if (j % AREA_MAX == 0){
                        printf("]\r\n[");
                }
                printf(" %d ", area_id);
        }         
        
        int cell_idx = 0;
        for (int i = 0; i < YMAX; i++){
                for (int j = 0; j < XMAX; j++){
                        int area_id = this->_cel[cell_idx];
                        if (area_id > 0){
                                AreaData* area = this->_areaData[area_id];
                                area->initBound(i, j);
                        }
                        
                        ++cell_idx;
                }
        }
        
        
        for (int i = 1; i < AREA_MAX; i++){
                AreaData* area = this->_areaData[i];
                area->initCenter();
        }
        
        
        cell_idx = 0;
        for (int i = 0; i < YMAX; i++){
                
                for (int j = 0; j < XMAX; j++){
                        
                        int area_id = this->_cel[cell_idx];
                        
                        if (area_id > 0){
                                AreaData* area = this->_areaData[area_id];
                                area->calcLenAndPos(i, j, cell_idx, this);
                        }
                        
                        cell_idx++;
                }
        }
        
        
        int tmpAreaId[AREA_MAX] = {0};
        int player_uid = 0;
        
        while(true){
                int available_area = 0;
                for (int i = 1; i < AREA_MAX; i++){
                        AreaData* area = this->_areaData[i];
                        if (area->isNeedOwner()){
                                tmpAreaId[available_area] = i;
                                ++available_area;
                        }
                        
                }
                
                if (0 == available_area){
                        break;
                }
                
                int random_area = tmpAreaId[random<int>(0, available_area - 1)];
                this->_areaData[random_area]->setOwner(player_uid);
                
                ++player_uid;
                if (player_uid >= CURRENT_PLAYERS){
                        player_uid = 0;
                }
        }
        
        SET_SIZE_TOZERO(this->_chk, AREA_MAX);
        
        for (int i = 0; i < CEL_MAX; i++){
                int area_id = this->_cel[i];
                
                if (area_id == 0 || this->_chk[area_id]){
                        continue;
                }
                
                for (int j = 0; j < DIR_INAREA; j++){
                        if (this->_chk[area_id]){
                                break;
                        }
                        
                        int joined_cell = this->_join[i]->getJoinDir(j);
                        if (joined_cell >= 0
                            && this->_cel[joined_cell] != area_id){
                                
                                this->setAreaLine(i, j);
                                this->_chk[area_id] = 1;
                        }
                }
        }
        
        int total_dice = 0;
        for (int i = 1; i < AREA_MAX; i++){
                if (this->_areaData[i]->initDice()){
                        total_dice++;
                }
        }
        
        total_dice = total_dice * (PUT_DICE - 1);
        player_uid = 0;
        for (int i = 0; i < total_dice; i++){
                
                int tempArea[AREA_MAX] = {0};
                int available_area = 0;
                
                
                for (int j = 1; j < AREA_MAX; j++){
                        if (this->_areaData[j]->needDice(player_uid)){
                                tempArea[available_area] = j;
                                ++available_area;
                        }
                }
                
                if (0 == available_area){
                        break;
                }
                
                int random_area = tempArea[random(0, available_area - 1)];
                this->_areaData[random_area]->increaseDice();
                
                ++player_uid;
                if (player_uid >= CURRENT_PLAYERS){
                        player_uid = 0;
                }
        }
}


int DiceGame::percolate(int pt, int cmax, int an){
        if (cmax < 3){
                cmax = 3;
        }
        
        int cell_in_area = pt;
        int next_f[CEL_MAX] = {0};
        
        int cell_num_in_area = 0;
        while (cell_num_in_area < cmax){
                this->_cel[cell_in_area] = an;
                ++cell_num_in_area;
                
                for (int j = 0; j < DIR_INAREA; j++){
                        int joined_cell = this->_join[cell_in_area]->getJoinDir(j);
                        if (joined_cell >= 0){
                                next_f[joined_cell] = 1;
                        }
                }
                
                
                int cell_value = 9999;
                for (int j = 0; j < CEL_MAX; j++){
                        if (next_f[j] != 0 &&
                            this->_cel[j] <= 0 &&
                            this->_num[j] < cell_value){
                                
                                cell_value = this->_num[j];
                                cell_in_area = j;
                        }
                }
                
                if (9999 == cell_value){
                        break;
                }
        }
        
        
        for (int i = 0; i < CEL_MAX; i++){
                
                if (next_f[i] != 0 && this->_cel[i] <= 0){
                        
                        this->_cel[i] = an;
                        ++cell_num_in_area;
                        
                        for (int j = 0; j < DIR_INAREA; j++){
                                int joined_cell = this->_join[i]->getJoinDir(j);
                                if (joined_cell >= 0){
                                        this->_rcel[joined_cell] = 1;
                                }
                        }
                }
        }
        
        return cell_in_area;
}

void DiceGame::setAreaLine(int cell, int dir){
        
        int cur_area = this->_cel[cell];
        AreaData* area = this->_areaData[cur_area];
        
        area->initAreaLine(cell, dir, this);
}

void DiceGame::set_area_tc(int pid){
        
        GamePlayer* player = this->_player[pid];
        
        SET_SIZE_TOIDX(this->_chk, AREA_MAX);
        
        bool found = false;
        do {
                found = false;
                
                for (int i = 1; i < AREA_MAX; i++){
                        
                        AreaData* area = this->_areaData[i];
                        if (area->isEmpty() || area->getOwner() != pid){
                                continue;
                        }
                        
                        for (int j = 0; j < AREA_MAX; j++){
                                
                                AreaData* area_another = this->_areaData[j];
                                if (area_another->isEmpty()
                                    || area_another->getOwner() != pid
                                    || !area->isJoinedWithArea(j)
                                    || this->_chk[j] == this->_chk[i]){
                                        continue;
                                }
                                
                                if (this->_chk[i] > this->_chk[j]){
                                        this->_chk[i] = this->_chk[j];
                                }else{
                                        this->_chk[j] = this->_chk[i];
                                }
                                found = true;
                                break;
                        }
                        
                        if (found){
                                break;
                        }
                }
                
        } while (found);
        
        int tcArr[AREA_MAX] = {0};
        for (int i = 1;  i < AREA_MAX; i++) {
                if (!this->_areaData[i]->isEmpty()
                    && this->_areaData[i]->getOwner() == pid){
                        ++tcArr[this->_chk[i]];
                }
        }
        
        
        int tc = 0;
        for (int i = 0; i < AREA_MAX; i++){
                if (tcArr[i] > tc){
                        tc = tcArr[i];
                }
        }
        
        player->setAreaTc(tc);
        printf("\r\n\r\n---player:(%d) tc=%d---", pid, tc);
}

#pragma mark - main pullic function


TMXTiledMap*  DiceGame::initGame(Layer* gameLayer, int playerNum){
       
        if (nullptr != _cur_map){
                _cur_map->removeFromParent();
        }
        
        CURRENT_PLAYERS = playerNum;
        _gameLayer = gameLayer;
        _gameLayer->addChild(_tamara, 100);
        _tamara->setPosition(Vec2(100, 100));
        
        std::string xmls = this->createMapXMLString();
        _cur_map = TMXTiledMap::createWithXML(xmls, "maps");
        
        ScreenCoordinate::getInstance()->configScreen(_cur_map->getContentSize());
        
        this->intAreaDrawObject(_cur_map);
        
        _gameLayer->addChild(_cur_map, 2, kTagTileMap);//TODO:: element zorder.
        
        
        SET_SIZE_TOIDX(_jun, MAX_PLAYER);
        
        for (int i = 0; i < CURRENT_PLAYERS; i++){
                int ramdom_p = random(0, CURRENT_PLAYERS - 1);
                int tmp = this->_jun[i];
                this->_jun[i] = this->_jun[ramdom_p];
                this->_jun[ramdom_p] = tmp;
        }
        
        for (int i = 0; i < MAX_PLAYER; i++){
                this->_player[i] = new GamePlayer(i);
        }
        
        for (int i = 0; i < MAX_PLAYER; i++){
                this->set_area_tc(i);
        }
        
        for(int i = 1; i < AREA_MAX; i++){
                AreaData* area = this->_areaData[i];
                if (area->getOwner() < 0){
                        continue;
                }
                Sprite* dice = area->createSprite();
                _cur_map->addChild(dice, 3, i + 100);
        }
        
        _gameStatus = GAME_STATUS_RUNNING;
        
        return _cur_map;
}


void DiceGame::startAttack(Vec2 position){
        
        Size map_size = _cur_map->getContentSize();
        int cell_id = ScreenCoordinate::getInstance()->getSelectedCell(map_size, position);
        int area_id = this->_cel[cell_id];
        
        AreaData* area = this->_areaData[area_id];
        int owner_uid = area->getOwner();

        if (AREA_UNSELECTED == _selected_area){
                
                if (owner_uid == _userId){
                        _selected_area = area_id;
                        area->drawAsSelected();
                }else{
                        return;
                }
                
        }else{
                if (area_id == _selected_area){
                        _selected_area = AREA_UNSELECTED;
                        area->drawAsUnselected();
                }else {
                        
                        if (area->isJoinedWithArea(_selected_area)
                            && owner_uid != _userId){
                                //TODO::AI Start attack;
                        }else{
                                return;
                        }
                }
        }
        
}


//void DiceGame::nextTurn(){
//        TMXLayer * layer = _cur_map->getLayer("map");
//        for (int i = 0; i < CEL_MAX; i++){
//                
//                int area_id = this->_cel[i];
//                AreaData* area = this->_areaData[area_id];
//                
//                if (area_id > 0 && area->getOwner() != _userId){
//                        for (int j = 0; j < CEL_MAX; j++){
//                                if (area_id != this->_cel[j]){
//                                        continue;
//                                }
//                                
//                                int col = j / XMAX;
//                                int row = j % XMAX;
//                                layer->setTileGID(1, Vec2(row, col));
//                        }
//                        
//                        area->setOwner(_userId);
//                        break;
//                }
//                
//        }
//}

void DiceGame::animationCallBack(Node* sender){
        AreaData* area_from = this->_areaData[_area_from];
        AreaData* area_to   = this->_areaData[_area_to];
        
        area_from->drawAsUnselected();
        area_to->drawAsUnselected();
        
        sender->stopAllActions();
        sender->setVisible(false);
}

bool DiceGame::startAIAttack(){
        bool is_AI_turn = false;
        
        int target = GameAI::getInstance()->com_thinking();
        if (target > 0){
                
                AreaData* area_from = this->_areaData[_area_from];
                area_from->drawAsSelected();
                
                AreaData* area_to   = this->_areaData[_area_to];
                area_to->drawAsSelected();
                
                _tamara->setVisible(true);
                
                auto cache = AnimationCache::getInstance();
                cache->addAnimationsWithFile("spine/animations-2.plist");
                auto animation2 = cache->getAnimation("dance_1");
                
                auto action2 = Animate::create(animation2);
                CallFunc * callback = CallFunc::create(std::bind(&DiceGame::animationCallBack, this, _tamara));
                
                Sequence*  s = Sequence::create(action2, callback, nullptr);
                
                _tamara->runAction(s);
               
        }
        
        int player_id = this->_jun[++_ban];
        if (player_id == _userId){
                is_AI_turn = false;
        }
        
        
        return is_AI_turn;
}

