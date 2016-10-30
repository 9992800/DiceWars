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
PopUpOkCancelDialog::PopUpOkCancelDialog(BaseDialogConfig config):PopUpBaseDialog(config){
        
}
PopUpOkCancelDialog::~PopUpOkCancelDialog(){
        
}
bool PopUpOkCancelDialog::init(){
        return true;
} 
void PopUpOkCancelDialog::setCallBack(CallFunc* callback){
        
}

void PopUpOkCancelDialog::onEnter(){
        
}
void PopUpOkCancelDialog::onExit(){
        
}
