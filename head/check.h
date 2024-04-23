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
bool ireturnTrue(int a){
    return true;
}
bool cmpS(void* a, void* b){
    return ((struct House*)a) -> S < ((struct House*)b) -> S;
}
bool cmpViewDate(void* a, void* b){
    return cmpDate(((struct ViewHouseMsg*)a) -> reqTime, ((struct ViewHouseMsg*)b) -> reqTime) < 0;
}
bool cmpRentDate(void* a, void* b){
    return cmpDate(((struct RentHouseMsg*)a) -> begin, ((struct RentHouseMsg*)b) -> begin) < 0;
}
char keyWord[20];
int pre[20];
void initPre(){
    // KMP算法预处理
    int len = strlen(keyWord);
    memset(pre, -1, sizeof(pre));
    for(int i = 1; i < len; ++i){
        int pos = pre[i - 1];
        while(true){
            if(keyWord[pos + 1] == keyWord[i]){
                pre[i] = pos + 1;
                break;
            }
            if(pos == -1) break;
            pos = pre[pos];
        }
    }
}
bool isKeyExist(char str[]){
    // KMP算法
    int len1 = strlen(str), len2 = strlen(keyWord);
    int now = -1;
    for(int i = 0; i < len1; ++i){
        while(str[i] != keyWord[now + 1]){
            if(now == -1) break;
            now = pre[now];
        }
        if(str[i] != keyWord[now + 1]){
            now++;
        }
        else{
            now = -1;
        }
        if(now == len2 - 1) return true;
    }
    return false;
}
bool checkHouseKey(void* a){
    initPre();
    struct House* house = (struct House*)a;
    return isKeyExist(house->address) || 
           isKeyExist(house->ownerName) == 0 || 
           isKeyExist(house->ownerPhone) == 0 || 
           isKeyExist(house->father->name) == 0 || 
           (house->direction >= 0 && isKeyExist(tag[house->direction].name) == 0) || 
           (house->decorationLevel >= 0 && isKeyExist(tag[house->decorationLevel].name)) ||
           (house->houseType >= 0 && isKeyExist(tag[house->houseType].name) == 0);
}
bool checkUserKey(void* a){
    initPre();
    struct User* user = (struct User*)a;
    return isKeyExist(user -> name) || 
           isKeyExist(user -> phoneNumber) == 0;
}
bool checkMiddiumKey(void* a){
    initPre();
    struct Middium* middium = (struct Middium*)a;
    return isKeyExist(middium -> name) || 
           isKeyExist(middium -> phoneNumber) == 0;
}
bool checkVMsgKey(void* a){
    initPre();
    struct ViewHouseMsg* msg = (struct ViewHouseMsg*)a;
    struct House* house = getVoidTreapNodeData(&houseTreap, msg -> houseId);
    struct Middium* middium = getVoidTreapNodeData(&middiumTreap, msg -> middiumId);
    struct User* user = getVoidTreapNodeData(&userTreap, msg -> userId);
    return checkHouseKey(house) || checkMiddiumKey(middium) || checkUserKey(user);
}
bool checkRMsgKey(void* a){
    initPre();
    struct RentHouseMsg* msg = (struct RentHouseMsg*)a;
    struct House* house = getVoidTreapNodeData(&houseTreap, msg -> houseId);
    struct Middium* middium = getVoidTreapNodeData(&middiumTreap, msg -> middiumId);
    struct User* user = getVoidTreapNodeData(&userTreap, msg -> userId);
    return checkHouseKey(house) || checkMiddiumKey(middium) || checkUserKey(user);
}
#endif