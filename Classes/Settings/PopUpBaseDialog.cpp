//
//  PopUpBaseDialog.cpp
//  DiceWars
//
//  Created by Wansheng Li on 2016/10/30.
//
//
enum{
        kTagBackGrd = 1,
        kTagTittle,
        kTagContent,
};
#include "PopUpBaseDialog.hpp"
PopUpBaseDialog::PopUpBaseDialog(BaseDialogConfig config):Layer::Layer(){
        
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Vec2 center = origin + visibleSize / 2;
        this->setPosition(center);

        
        _baseConfig = config;
        
        _backGound = Sprite::create(_baseConfig._backGroundImg);
        this->setContentSize(_backGound->getTexture()->getContentSize());
        addChild(_backGound, 0, kTagBackGrd);
        
        
        
        _title = Label::createWithSystemFont(config._title, "", config._titleFontSize);
        
        Size layer_size = getContentSize();
        Size title_size = _title->getContentSize();
        
        _title->setIgnoreAnchorPointForPosition(false);
        _title->setAnchorPoint(Vec2(0.5, 1.0));
        Vec2 top(0, 0);
        _title->setPosition(top);
        _title->setColor(Color3B::RED);
        addChild(_title, 1, kTagTittle);

        
        
        _content = Label::createWithSystemFont(config._content, "", config._contentFontSize);
        addChild(_content, 1, kTagContent);
        
        
        Size content_size = _content->getContentSize();
        Vec2 content(0, title_size.height / 2 + 30);
//        _content->setPosition(Vec2::ZERO);
        _content->setDimensions(layer_size.width - _baseConfig._padding * 2, layer_size.height - _baseConfig._paddingTop);
        _content->setHorizontalAlignment(TextHAlignment::LEFT);
}

PopUpBaseDialog::~PopUpBaseDialog(){
        
}
