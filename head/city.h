#ifndef _CITY
#define _CITY

#include "typedefine.h"
#include "area.h"
#include "intlist.h"
#include <string.h>
struct City{
    char * name;
    struct AreaList AreaList;
};

struct CityListNode{
    struct City * data;
    struct CityListNode * nxt;
};

struct CityList{
    struct CityListNode head;
    int cnt;
};
//CityList创建、初始化
CityList* newCityList();
//新CityNode创建
City* newCityNode();
//查询City下的Area,即用即删
AreaList* findAreaInCity(City* city,const char* c);


#endif
