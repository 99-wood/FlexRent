#ifndef _PLACE
#define _PLACE
//place有层级，不同的层级代表着区域，城市，小区等概念
#include "typedefine.h"
#include "voidlist.h"
#include "hashtreap.h"
//Palce的深度、层级
//有city、area、community
enum depth{
    city=1,area,community,
};

struct VoidTreap placeTraep;
struct Place{
    char* name;
    struct Place* father;
    struct VoidList sons;
    enum depth level;
};

//创建并初始化name,level
//且父、子节点指针默认为空默认为空
struct Place* newPlace2(char* n, enum depth l);
//向某一层级的Place的son链表中加入新的节点
//同时绑定父节点
//p要么是House*类型，要么是Place*类型
void addPlace(struct Place*,void* p);

#endif