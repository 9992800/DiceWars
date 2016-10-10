//
//  RandomMap.cpp
//  TesMap
//
//  Created by Wansheng Li on 16/10/10.
//
//

#include "RandomMap.hpp"

RandomMap* RandomMap::create(SimpleMapInfoBean infos){
        RandomMap* ret = new (std::nothrow)RandomMap();
        if (ret->init()){
                ret->autorelease();
                return ret;
        }
        
        CC_SAFE_DELETE(ret);
        
        return nullptr;
}

RandomMap::RandomMap():tinyxml2::XMLDocument()
                        ,_widthInTiles(32)
                        ,_heightInTiles(28)
                        ,_tileWidth(80)
                        ,_tileHeight(80)
                        ,_hexsidelength(40)
                        ,_staggeraxis("x")
                        ,_staggerindex("odd")
{
}


void RandomMap::initRootMap(){
        
        _rootElement = this->NewElement("map");
        _rootElement->SetAttribute("version", "1.0");
        _rootElement->SetAttribute("orientation", "hexagonal");
        _rootElement->SetAttribute("renderorder", "right-down");
        _rootElement->SetAttribute("width", _widthInTiles);
        _rootElement->SetAttribute("height", _heightInTiles);
        _rootElement->SetAttribute("tilewidth", _tileWidth);
        _rootElement->SetAttribute("tileheight", _tileHeight);
        _rootElement->SetAttribute("hexsidelength", _heightInTiles);
        _rootElement->SetAttribute("staggeraxis", _staggeraxis.c_str());
        _rootElement->SetAttribute("staggerindex", _staggerindex.c_str());
        _rootElement->SetAttribute("nextobjectid", 1);
        
        this->InsertFirstChild(_rootElement);
}

void RandomMap::initTilesSet(){
        XMLElement * tilesSet = this->NewElement("tileset");
        
        {
                XMLElement* image = this->NewElement("image");
                tilesSet->InsertEndChild(image);
        }
        tilesSet->SetAttribute("firstgid", "1");
        _rootElement->InsertEndChild(tilesSet);
}

bool RandomMap::init(){
        this->initRootMap();
        this->initTilesSet();
        return true;
}


