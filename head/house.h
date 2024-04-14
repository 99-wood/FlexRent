#ifndef _HOUSE
#define _HOUSE

#include "typedefine.h"
#include "date.h"
#include "viewhousemsg.h"
#include "renthousemsg.h"
#include "intlist.h"
enum HouseState{
    deleted, enable, using
};
struct House{
    int id; //房源编号
    int price; //租金
    int S; //面积
    int floor;
    enum HouseState state;
    char * ownerName;
    char * ownerPhone;
    struct Place * father;
    char * introduce; //房屋介绍
    char * address; //房源地址
    struct Date buildDate; //建造日期
    struct IntList direction; //房屋朝向 tag
    struct IntList decorationLevel; //装修程度 tag
    struct IntList houseType; //房型 tag
    struct IntList viewMsgList; //看房信息 id
    struct IntList rentMsgList; //租房信息 id
};

#endif