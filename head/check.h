#ifndef _CHECK
#define _CHECK
#include "typedefine.h"
#include "voidtreap.h"
#include "house.h"
#include "middium.h"
#include "user.h"
#include "head.h"
bool returnTrue(void* a){
    return true;
}
bool cmpS(void* a, void* b){
    return ((struct House*)a) -> S < ((struct House*)b) -> S;
}
char keyWord[20];
bool checkHouseKey(void* a){
    struct House* house = (struct House*)a;
    return strcmp(house->address, keyWord) == 0 || strcmp(house->ownerName, keyWord) == 0 || 
        strcmp(house->ownerPhone, keyWord) == 0 || strcmp(house->father->name, keyWord) == 0 || 
        (house->direction >= 0 && strcmp(tag[house->direction].name, keyWord) == 0) || (house->decorationLevel >= 0 && strcmp(tag[house->decorationLevel].name, keyWord) == 0) ||
        (house->houseType >= 0 && strcmp(tag[house->houseType].name, keyWord) == 0);
}
#endif