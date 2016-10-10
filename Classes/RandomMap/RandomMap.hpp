//
//  RandomMap.hpp
//  DiceWars
//
//  Created by wsli on 16/10/10.
//
//

#ifndef __DICE_WARS_RandomMap_H
#define __DICE_WARS_RandomMap_H

#include "MapBasicInfo.hpp"
#include "cocos2d.h"
#include "external/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class RandomMap :public cocos2d::Ref, public XMLDocument{
public:
        static RandomMap* create(SimpleMapInfoBean infos);
protected:
        RandomMap();
        bool init();
        void initRootMap();
        void initTilesSet();
private:
        int _widthInTiles;
        int _heightInTiles;
        int _tileWidth;
        int _tileHeight;
        int _hexsidelength;
        std::string _staggeraxis;
        std::string _staggerindex;
        XMLElement* _rootElement;
};

#endif /* RandomMap_hpp */
