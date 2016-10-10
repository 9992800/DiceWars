//
//  MapBasicInfo.hpp
//  TesMap
//
//  Created by Wansheng Li on 16/10/10.
//
//

#ifndef _MapBasicInfo_hpp_
#define _MapBasicInfo_hpp_

typedef struct DataBean_s {
        std::vector<int> datas;
}DataBean;

typedef struct LayerBean_s{
        std::string name;
        int width;
        int height;
        float opacity;
}LayerBean;

typedef struct ImageBean_s{
        std::string source;
        int width;
        int height;
}ImageBean;

typedef struct TileSetBean_s{
        std::string name;
        int tilewidth;
        int tileheight;
        int tilecount;
        int columns;
        ImageBean imageBean;
}TileSetBean;

typedef struct SimpleMapInfoBean_s{
        int widthInTiles;
        int heightInTiles;
        int tileWidth;
        int tileHeight;
        int hexsidelength;
        std::string staggeraxis;
        std::string staggerindex;
        TileSetBean tileSetBean;
}SimpleMapInfoBean;



#endif /* _MapBasicInfo_hpp_ */
