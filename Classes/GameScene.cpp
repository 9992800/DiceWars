#include "GameScene.hpp"
#include "SimpleAudioEngine.h"
#include "game/DiceGame.hpp"
enum
{
        kTagTileMap = 1,
};

// on "init" you need to initialize your instance
bool GameScene::init()
{
        //////////////////////////////
        // 1. super init first        
        if ( !Scene::init() )
        {
                return false;
        }
        
         
        
        auto layer = Layer::create();
        this->addChild(layer, 10);
        

        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
                
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
        layer->addChild(menu, 30);
        
        
        /////////////////////////////
        
        // 3. init game;
        _gameLayer = Layer::create();
        this->addChild(_gameLayer, 5);
        
        _randomMap = DiceGame::getInstance()->initGame(_player_num);
        _randomMap->setPosition(Vec2(origin.x, origin.y));         
        _gameLayer->addChild(_randomMap, 2, kTagTileMap);//TODO:: element zorder.
        
        Vec2 menu_start = Vec2(origin.x + visibleSize.width - 60, origin.y + visibleSize.height - 60);
        
        static std::string menu_image = "maps/player_";
        for (int i = 0; i < _player_num; i++){
                std::ostringstream s;
                s << menu_image << i <<".png";
                
                auto player_tc = MenuItemImage::create(s.str(), "");
                player_tc->setPosition(menu_start - Vec2(0, i * (player_tc->getContentSize().height) + 5));
                
                int tc_i = DiceGame::getInstance()->getPlayerTc(i);
                std::ostringstream s2;
                s2 << tc_i;
                auto label_tc = Label::createWithSystemFont(s2.str(), "Helvetica", 12);
                label_tc->setColor(Color3B(255,0,0));
                label_tc->setPosition(Vec2(player_tc->getContentSize()/ 2));
                player_tc->addChild(label_tc);
                
                _menu_items.insert(i, player_tc);
        }
        
        auto menu2 = Menu::createWithArray(_menu_items);
        menu2->setPosition(Vec2::ZERO);
        layer->addChild(menu2, 40);
        
        LayerColor* back_ground = LayerColor::create(Color4B(255,255,255,255.0));
        _gameLayer->addChild(back_ground);
        
        Size cs = _randomMap->getContentSize();
        _lowestPostion_y = visibleSize.height + origin.y - cs.height - 6;
        
        
        Director::getInstance()->setDepthTest(true);
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
        listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
                
        
        _tamara = Sprite::create("spine/grossinis_sister1.png");
        _gameLayer->addChild(_tamara, 100);
        _tamara->setPosition(Vec2(100, 100));
                 
        return true;
}

void GameScene::afterBattle(int batlleResult){
        
        
        _tamara->stopAllActions();
        _tamara->setVisible(false);
        
        if (DiceGame::getInstance()->afterBattle(batlleResult)){
                _endTurnItem->setVisible(true);
        }else{
                int result = DiceGame::getInstance()->startAIAttack();                
                this->playAnimation(result);
        }
}

void GameScene::playAnimation(int result){
        CallFunc* cc = CallFunc::create(std::bind(&GameScene::afterBattle, this,result));
        if (ATTACK_RES_NOACTION == result){
                this->playSupplyAnimation(cc);
        }else{
                this->playBattleAnimation(cc);
        }
}

void GameScene::playBattleAnimation(CallFunc* callback){
        
        _tamara->setVisible(true);
        
        auto cache = AnimationCache::getInstance();
        cache->addAnimationsWithFile("spine/animations-2.plist");
        auto animation2 = cache->getAnimation("dance_1");
        
        auto action2 = Animate::create(animation2);
        Sequence*  s = Sequence::create(action2, callback, nullptr);
        _tamara->runAction(s);
} 

void GameScene::playSupplyAnimation(CallFunc* callback){
        _tamara->setVisible(true);
        
        auto cache = AnimationCache::getInstance();
        cache->addAnimationsWithFile("spine/animations-2.plist");
        auto animation2 = cache->getAnimation("dance_1");
        
        auto action2 = Animate::create(animation2);
        Sequence*  s = Sequence::create(action2, callback, nullptr);
        _tamara->runAction(s);
}


void GameScene::menuEndTurnCallback(Ref* pSender)
{
        if (pSender == _startAIItem){
                _startAIItem->setVisible(false);
                int result = DiceGame::getInstance()->startAIAttack();
                this->playAnimation(result);
        }else{
                _endTurnItem->setVisible(false);
                this->playAnimation(ATTACK_RES_NOACTION);
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
