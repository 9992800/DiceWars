//
//  PopupOkDialog.cpp
//  DiceWars
//
//  Created by Wansheng Li on 2016/10/30.
//
//

#include "PopUpOkDialog.hpp"
PopUpOkDialog* PopUpOkDialog::create(BaseDialogConfig config){
        PopUpOkDialog *pRet = new(std::nothrow) PopUpOkDialog(config);
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
PopUpOkDialog::PopUpOkDialog(BaseDialogConfig config):PopUpBaseDialog(config){
        
}

PopUpOkDialog::~PopUpOkDialog(){
        
}
bool PopUpOkDialog::init(){
        return true;
} 
void PopUpOkDialog::onEnter(){
        
}
void PopUpOkDialog::onExit(){
        
}

void PopUpOkDialog::setCallBack(CallFunc* callback){
        
}
