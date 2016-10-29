#include "GameScene.hpp"
#include "SimpleAudioEngine.h"
#include "game/DiceGame.hpp"
enum
{
        kTagTileMap = 1,
};

// on "init" you need to initialize your instance

#pragma mark - initialize
bool GameScene::init()
{
        //////////////////////////////
        // 1. super init first        
        if ( !Scene::init() )
        {
                return false;
        }
        
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        /////////////////////////////
        // 2. init game data;
        _gameLayer = Layer::create();
        this->addChild(_gameLayer, 2);
        initGameLayer(origin);
        
        /////////////////////////////
        // 3. init controller;
        _controllerLayer = Layer::create();
        this->addChild(_controllerLayer, 3);
        
        Vec2 menu_start = Vec2(origin.x + visibleSize.width - 60, origin.y + visibleSize.height - 60);
        initPlayerTc(menu_start);
        
        initCtrlButton(origin,visibleSize);
        
        initFightDice(origin, visibleSize);
        
        initActionListener(origin, visibleSize);

        return true;
}

void GameScene::initCtrlButton(Vec2 origin, Size visibleSize){
        _endTurnItem = MenuItemImage::create("NextButton.png", "NextButton.png",
                                             CC_CALLBACK_1(GameScene::menuEndTurnCallback, this));
        _endTurnItem->setPosition(Vec2(origin.x + visibleSize.width - _endTurnItem->getContentSize().width,
                                       origin.y +_endTurnItem->getContentSize().height));
        _endTurnItem->setVisible(false);
        
        _startAIItem = MenuItemImage::create("start.png", "start.png",
                                             CC_CALLBACK_1(GameScene::menuEndTurnCallback, this));
        _startAIItem->setPosition(Vec2(origin.x + visibleSize.width - _startAIItem->getContentSize().width,
                                       origin.y +_startAIItem->getContentSize().height));
        
        auto menu = Menu::create(_endTurnItem, _startAIItem, NULL);
        menu->setPosition(Vec2::ZERO);
        _controllerLayer->addChild(menu, 4);
}

void GameScene::initFightDice(Vec2 origin, Size visibleSize){
        
        Vec2 from_start = Vec2((origin.x + visibleSize.width) / 2 - 10,
                               (origin.y + visibleSize.height) / 6);
        for (int i = 0; i < MAX_DICE_PER_AREA; i++){
                auto label_value = Label::createWithSystemFont("0", "Helvetica", 20);
                label_value->setColor(Color3B(0,255,0));
                label_value->setPosition(from_start + Vec2(i * -20, 0));
                _fight_from.push_back(label_value);
                _controllerLayer->addChild(label_value, 4);
                label_value->setVisible(false);
        }
        
        Vec2 from_to = Vec2((origin.x + visibleSize.width) / 2 + 10,
                            (origin.y + visibleSize.height) / 6);
        for (int i = 0; i < MAX_DICE_PER_AREA; i++){
                auto label_value = Label::createWithSystemFont("0", "Helvetica", 20);
                label_value->setColor(Color3B(0,0,255));
                label_value->setPosition(from_to + Vec2(i * 20, 0));
                _fight_to.push_back(label_value);
                _controllerLayer->addChild(label_value, 4);
                label_value->setVisible(false);
        }
}

void GameScene::initPlayerTc(Vec2 menu_start){
        
        static std::string menu_image = "maps/player_";
        for (int i = 0; i < _player_num; i++){
                
                int player_uid = DiceGame::getInstance()->getPlayerJun(i);
                
                std::ostringstream s;
                s << menu_image << player_uid <<".png";
                auto player_tc = MenuItemImage::create(s.str(), "");
                player_tc->setPosition(menu_start - Vec2(0, i * (player_tc->getContentSize().height) + 5));
                
                std::string tc_i = DiceGame::getInstance()->getPlayerTc(player_uid);                
                auto label_tc = Label::createWithSystemFont(tc_i, "Helvetica", 12);
                label_tc->setColor(Color3B(255,0,0));
                label_tc->setPosition(Vec2(player_tc->getContentSize() / 2));
                player_tc->addChild(label_tc);
                _tc_values.insert(player_uid, label_tc);
                
                _menu_items.insert(i, player_tc);
        }
        
        auto menu = Menu::createWithArray(_menu_items);
        menu->setPosition(Vec2::ZERO);
        _controllerLayer->addChild(menu, 4);
}

void GameScene::initGameLayer(Vec2 origin){
        _randomMap = DiceGame::getInstance()->initGame(_player_num);
        _randomMap->setPosition(origin);
        _gameLayer->addChild(_randomMap, 2, kTagTileMap);
        
        
        LayerColor* back_ground = LayerColor::create(Color4B(255,255,255,255.0));
        _gameLayer->addChild(back_ground);
        _tamara = Sprite::create("spine/grossinis_sister1.png");
        _gameLayer->addChild(_tamara, 4);
        _tamara->setPosition(Vec2(100, 100));
}

void GameScene::initActionListener(Vec2 origin, Size visibleSize){
        
        Size cs = _randomMap->getContentSize();
        _lowestPostion_y = visibleSize.height + origin.y - cs.height - 6;
        Director::getInstance()->setDepthTest(true);
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
        listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


#pragma mark - battle logic
void GameScene::afterBattle(int batlleResult){
        
        _tamara->stopAllActions();
        _tamara->setVisible(false);
        
        for (int i = 0; i < MAX_DICE_PER_AREA; i++){
                _fight_from[i]->setVisible(false);
                _fight_to[i]->setVisible(false);
        }
        
        std::map<int, std::string> survival = DiceGame::getInstance()->afterBattle(batlleResult);
        for (std::map<int, std::string>::iterator it = survival.begin();
             it != survival.end(); it++){
                Label* tc_label = _tc_values.at(it->first);
                if (nullptr != tc_label)
                        tc_label->setString(it->second);
        }
        
        if (GAME_STATUS_INUSERTURN == DiceGame::getInstance()->getCurrentStatus()){
                return;
        }
        
        int result = DiceGame::getInstance()->startAIAttack();
        this->playAnimation(result);
}

void GameScene::afterSupply(){
       
        DiceGame::getInstance()->next_player();
        int result = DiceGame::getInstance()->startAIAttack();
        this->playAnimation(result);
}

void GameScene::playAnimation(int result){
        
        
        if (ATTACK_RES_GOTSUPPLY == result){
                CallFunc* callback = CallFunc::create(std::bind(&GameScene::afterSupply, this));
                DiceGame::getInstance()->startSupply(callback);
                
        }else if (ATTACK_RES_NONE == result){
                
                _endTurnItem->setVisible(true);
        }
        else if (ATTACK_RES_WIN || ATTACK_RES_DEFEATED){
                
                std::vector<int> fight_from = DiceGame::getInstance()->getFightValue(0);
                std::vector<int> fight_to = DiceGame::getInstance()->getFightValue(1);
                
                this->playBattleAnimation(result, fight_from, fight_to);
        }
}

void GameScene::playBattleAnimation(int result, std::vector<int> from, std::vector<int> to){
        
        for (int i = 0; i < from.size(); i++){
                _fight_from[i]->setVisible(true);
                std::ostringstream s;
                s << from[i];
                _fight_from[i]->setString(s.str());
        }
        
        for (int i = 0; i < to.size(); i++){
                _fight_to[i]->setVisible(true);
                std::ostringstream s;
                s << to[i];
                _fight_to[i]->setString(s.str());
        }
        
        CallFunc* callback = CallFunc::create(std::bind(&GameScene::afterBattle, this, result));
        _tamara->setVisible(true);
        
        auto cache = AnimationCache::getInstance();
        cache->addAnimationsWithFile("spine/animations-2.plist");
        auto animation2 = cache->getAnimation("dance_1");
        
        auto action2 = Animate::create(animation2);
        
        
        Sequence*  s = Sequence::create(action2, callback, nullptr);        
        _tamara->runAction(s);
        _tamara->setScale(2.0);//TODO::
} 

#pragma mark - touch action listener
void GameScene::menuEndTurnCallback(Ref* pSender)
{        
        if (pSender == _startAIItem){
                _startAIItem->setVisible(false);
                int res = DiceGame::getInstance()->startAIAttack();
                this->playAnimation(res);
        }else {
                this->playAnimation(ATTACK_RES_GOTSUPPLY);
                _endTurnItem->setVisible(false);
        }
}

void GameScene::onTouchesMoved(const std::vector<Touch*>& touches, Event* event){
        _isMoved = true;
        auto touch = touches[0];
        
        auto diff = touch->getDelta();
        diff.x = 0;
        auto currentPos = _randomMap->getPosition();
        auto origin = Director::getInstance()->getVisibleOrigin();
        
        auto map_size = _randomMap->getContentSize();
        
        if (origin.y < (currentPos.y + diff.y)){
                diff.y = origin.y - currentPos.y;
        }
        
        if ((currentPos.y + diff.y) < _lowestPostion_y){
                diff.y = _lowestPostion_y - currentPos.y;
        }
        
        _randomMap->setPosition(currentPos + diff);
}


void GameScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *event){
        if (_isMoved) {
                _isMoved = false;
                return;
        }
        
        if (GAME_STATUS_INUSERTURN != DiceGame::getInstance()->getCurrentStatus()){
                return;
        }
         
        auto touch = touches[0];
        auto position = touch->getLocation();
        
        Vec2 inMap = _randomMap->convertToNodeSpace(position);
        int result = DiceGame::getInstance()->startManulAttack(inMap);
        this->playAnimation(result);
}
