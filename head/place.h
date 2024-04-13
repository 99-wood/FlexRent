#ifndef _PLACE
#define _PLACE
//place有层级，不同的层级代表着区域，城市，小区等概念
#include "typedefine.h"
#include "voidlist.h"

enum depth{
    city=1,area,community,
};

struct Place{
    char* name;
    struct Place* father;
    struct VoidList sons;
    depth level;
};

//创建一个新的Place
Place* newPlace();
//向某一层级的Place中添加子Place
Place* addPlace(void* p);

#endif