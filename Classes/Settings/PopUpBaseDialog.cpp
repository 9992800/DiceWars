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
PopUpBaseDialog::PopUpBaseDialog(BaseDialogConfig config){
        
        _baseConfig = config;
        
        _backGound = Sprite::create(_baseConfig._backGroundImg);
        setContentSize(_backGound->getTexture()->getContentSize());
        addChild(_backGound, 0, kTagBackGrd);
        
        _title = Label::createWithSystemFont(config._title, "", config._titleFontSize);
        addChild(_title, 1, kTagTittle);
        
        _content = Label::createWithSystemFont(config._content, "", config._contentFontSize);
        addChild(_content, 1, kTagContent);
        
        Size layer_size = getContentSize();
        Size title_size = _title->getContentSize();
        Vec2 top(layer_size.width / 2, title_size.height / 2 + 10);
        _title->setPosition(top);
        
        Size content_size = _content->getContentSize();
        Vec2 content(layer_size.width / 2, title_size.height / 2 + 30);
        _content->setPosition(content);
        _content->setDimensions(layer_size.width - _baseConfig._padding * 2, layer_size.height - _baseConfig._paddingTop);
        _content->setHorizontalAlignment(TextHAlignment::LEFT);
}

PopUpBaseDialog::~PopUpBaseDialog(){
        
}
