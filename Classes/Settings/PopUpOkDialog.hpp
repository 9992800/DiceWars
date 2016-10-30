//
//  PopupOkDialog.hpp
//  DiceWars
//
//  Created by Wansheng Li on 2016/10/30.
//
//

#ifndef PopupOkDialog_hpp
#define PopupOkDialog_hpp
#include "PopUpBaseDialog.hpp"

class PopUpOkDialog: public PopUpBaseDialog{
public:
        PopUpOkDialog(BaseDialogConfig config);
        ~PopUpOkDialog();
        bool init();
        void setCallBack(CallFunc* callback);
        static PopUpOkDialog* create(BaseDialogConfig config);
        
protected:
        void onEnter();
        void onExit();
};

#endif /* PopupOkDialog_hpp */
