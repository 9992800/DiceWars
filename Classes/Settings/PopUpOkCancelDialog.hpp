//
//  PopUpOkCancelDialog.hpp
//  DiceWars
//
//  Created by Wansheng Li on 2016/10/30.
//
//

#ifndef PopUpOkCancelDialog_hpp
#define PopUpOkCancelDialog_hpp

#include "PopUpBaseDialog.hpp"

class PopUpOkCancelDialog: public PopUpBaseDialog{
public:
        PopUpOkCancelDialog(BaseDialogConfig config);
        ~PopUpOkCancelDialog();
        bool init(); 
        static PopUpOkCancelDialog* create(BaseDialogConfig config);
        void setCallBack(CallFunc* callback);
protected:
        void onEnter();
        void onExit();
};

#endif /* PopUpOkCancelDialog_hpp */
