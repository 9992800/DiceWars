//
//  PopUpOkCancelDialog.cpp
//  DiceWars
//
//  Created by Wansheng Li on 2016/10/30.
//
//

#include "PopUpOkCancelDialog.hpp"

PopUpOkCancelDialog* PopUpOkCancelDialog::create(BaseDialogConfig config){
        PopUpOkCancelDialog *pRet = new(std::nothrow) PopUpOkCancelDialog(config);
        if (pRet && pRet->init())
        {
                pRet->autorelease();
                return pRet;
        }
        else
        {
                delete pRet;
                pRet = nullptr;
                return nullptr;
        }
}


PopUpOkCancelDialog*  PopUpOkCancelDialog::create(BaseDialogConfig config, ccMenuCallback callback1, ccMenuCallback callback2){
        
        PopUpOkCancelDialog* dialog = PopUpOkCancelDialog::create(config);
        dialog->setCallBack(callback1, callback2);
        
        return dialog;
}
PopUpOkCancelDialog::PopUpOkCancelDialog(BaseDialogConfig config):PopUpBaseDialog(config){
        
}
PopUpOkCancelDialog::~PopUpOkCancelDialog(){
        
}
bool PopUpOkCancelDialog::init(){
        
        Size s = this->getContentSize();
        LayerColor::initWithColor(Color4B(255, 100, 100, 128), s.width, s.height);
        
        _okButton = MenuItemImage::create("DIALOG_OK.png", "DIALOG_OK.png");
        Size ok_size = _okButton->getContentSize();
        _okButton->setPosition(Vec2(s.width / 2 - ok_size.width,  ok_size.height / 2 + 30));
        
        _cancelButton = MenuItemImage::create("DIALOG_CANCEL.png", "DIALOG_CANCEL.png");
        Size cancel_size = _cancelButton->getContentSize();
        _cancelButton->setPosition(Vec2(s.width / 2 + cancel_size.width, cancel_size.height / 2 + 30));
        
        auto menu = Menu::create(_okButton, _cancelButton, nullptr);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1, kTagOkButton);
        
        return true;
} 
void PopUpOkCancelDialog::setCallBack(ccMenuCallback callback1, ccMenuCallback callback2){
        _okButton->setCallback(callback1);
        _cancelButton->setCallback(callback2);
} 
