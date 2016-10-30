//
//  PopUpBaseDialog.hpp
//  DiceWars
//
//  Created by Wansheng Li on 2016/10/30.
//
//

#ifndef PopUpBaseDialog_hpp
#define PopUpBaseDialog_hpp


#include "cocos2d.h"
USING_NS_CC;

typedef struct BaseDialogConfig_tg {
        std::string     _backGroundImg;
        std::string     _title;
        std::string     _content;
        int             _titleFontSize;
        int             _contentFontSize;
        int             _padding;
        int             _paddingTop;
}BaseDialogConfig;

class PopUpBaseDialog: public Layer{
public:
        PopUpBaseDialog(BaseDialogConfig config);
        ~PopUpBaseDialog();
        virtual bool init()=0;
        
protected:
        BaseDialogConfig        _baseConfig;
        Sprite*                 _backGound;
        Label*                  _title;
        Label*                  _content;

};

#endif /* PopUpBaseDialog_hpp */
