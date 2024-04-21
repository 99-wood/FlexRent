#ifndef _CORE
#define _CORE
#include "typedefine.h"
#include "voidtreap.h"
#include "house.h"
#include "middium.h"
#include "user.h"
#include "head.h"
#include "windows.h"

int __L, __R;

/*tool*/
void sort(void* val[], int l, int r, bool (*cmp)(void*, void*)){
    if(l == r) return;
    int mid = (l + r) >> 1;
    sort(val, l, mid, cmp);
    sort(val, mid + 1, r, cmp);
    void* tmp[] = malloc(sizeof(void*) * (r + 1));
    int px = l, py = mid + 1, p = l;
    while(px <= mid && py <= r){
        if(cmp(val[px], val[py])){
            tmp[p++] = val[px++];
        }
        else{
            tmp[p++] = val[py++];
        }
    }
    while(px <= mid) tmp[p++] = val[p++] = val[px++];
    while(py <= r) tmp[p++] = val[py++];
    for(int i = l; i <= r; ++i) val[i] = tmp[i];
    free(tmp);
    return;
}
bool 

/*Admin*/
void setAdminPassword(char newPassword[]){
    free(admin.password);
    int len = strlen(newPassword);
    admin.password = (char*)malloc(sizeof(char) * (len + 1));
    for(int i = 0; i <= len; ++i){
        admin.password[i] = newPassword[i];
    }
    return;
}

/*place*/

int addPlace(char name[], char fatherName[]){
    // printf("%d", str)
    struct Place *place, *father;
    if(strcmp(fatherName, "root") == 0) father = &placeRoot;
    else father = (struct Place*)getHashTreapNodeData(&placeTraep, makeHashValue(fatherName));
    
        // printf("Yes");
    if(father == NULL) return 1;
    else{
        place = (struct Place*)malloc(sizeof(struct Place));
        place -> father = father;
        place -> level = father -> level + 1;
        place -> name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
        initVoidList(&(place -> sons));
        strcpy(place -> name, name);
        addVoidListHead(&(father->sons), place);
        addHashTreapNode(&placeTraep, place, makeHashValue(name));
        // printf("no");
        return 0;
    }
}

void printPlaceTree(struct Place * rt, int len){
    // printf("yes");
    for(int i = 0; i < len; ++i) printf(" ");
    int cnt = 0;
    printf("|-");
    cnt += 2;
    printf("%s", rt -> name);
    if(rt -> level == 3){
        printf("\n");
        return;
    }
    else printf("-|\n");
    cnt += 1;
    for(struct VoidListNode * p = rt -> sons.head; p != NULL; p = p -> nxt){
        printPlaceTree((struct Place *)(p -> value), len + cnt + strlen(rt -> name));
    }
    return;
}

/*house*/
struct House* addHouse(char ownerName[], char ownerPhone[], char placeName[], char address[], int S, int floor){
    struct Place* place = getHashTreapNodeData(&placeTraep, makeHashValue(placeName));
    if(place == NULL || place -> level < 3) return NULL;
    struct House* house = (struct House*)malloc(sizeof(struct House));
    house -> price = -1;
    house -> S = S;
    house -> floor = floor;
    house -> id = cntHouse++;
    house -> ownerName = (char*)malloc(sizeof(char) * (strlen(ownerName) + 1));
    house -> ownerPhone = (char*)malloc(sizeof(char) * (strlen(ownerPhone) + 1));
    house -> address = (char*)malloc(sizeof(char) * (strlen(address) + 1));
    strcpy(house -> ownerName, ownerName);
    strcpy(house -> ownerPhone, ownerPhone);
    strcpy(house -> address,address);
    house -> father = place;
    house -> state = enable;
    initIntList(&(house -> viewMsgList));
    initIntList(&(house -> rentMsgList));
    addVoidListHead(&(place -> sons), house);
    addVoidTreapNode(&houseTreap, house, house -> id);
    return house;
}
void delHouse(struct House* house){
    house -> state = deleted;
    return;
}
void setdirection(struct House* house, int tagId){
    if(house != NULL) house -> direction = tagId;
    return;
}
void setdecorationLevel(struct House* house, int tagId){
    if(house != NULL) house -> decorationLevel = tagId;
    return;
}
void setPrice(struct House* house, int price){
    if(house != NULL) house -> price = price;
}
void printHouse(struct House* house){
    if(house == NULL) return;
    if(house -> state == deleted) return;
    printf("%5d %3d %20s\n", house -> id, house -> S, house -> address);
}
struct ViewHouseMsg* newViewHouseMsg(struct User* user, struct House* house, struct Middium* middium, struct Date date){
    struct ViewHouseMsg* msg = (struct ViewHouseMsg*)malloc(sizeof(struct ViewHouseMsg));
    msg -> houseId = house -> id;
    msg -> userId = user -> id;
    msg -> reqTime = date;
    msg -> state = normal;
    msg -> id = cntViewMsg++;
    addVoidListHead(&vMsgList, msg);
    addVoidTreapNode(&vMsgTreap, msg, msg -> id);
    addIntListHead(&user -> viewMsgList, msg -> id);
    addIntListHead(&house -> viewMsgList, msg -> id);
    addIntListHead(&middium -> viewMsgList, msg -> id);
    return msg;
}
void viewHouse(struct User* user, struct House* house, struct Middium* middium, struct Date date){
    if(middium == NULL){
        middium = getVoidTreapNodeData(&middiumTreap, rand() % cntMiddium);
    }
    newViewHouseMsg(user, house, middium, date);
}
void cancalViewHouse(struct ViewHouseMsg* msg){
    if(msg != NULL) msg -> state = cancel;
    return;
}
void finishViewHouse(struct ViewHouseMsg* msg){
    if(msg != NULL) msg -> state = finish;
    return;
}
struct RentHouseMsg* newRentHouseMsg(struct User* user, struct House* house, struct Middium* middium, struct Date begin, struct Date end){
    struct RentHouseMsg* msg = (struct RentHouseMsg*)malloc(sizeof(struct RentHouseMsg));
    msg -> houseId = house -> id;
    msg -> userId = user -> id;
    msg -> begin = begin;
    msg -> end = end;
    msg -> id = cntRentMsg++;
    addVoidListHead(&vMsgList, msg);
    addVoidTreapNode(&vMsgTreap, msg, msg -> id);
    addIntListHead(&user -> rentMsgList, msg -> id);
    addIntListHead(&house -> rentMsgList, msg -> id);
    addIntListHead(&middium -> rentMsgList, msg -> id);
    return msg;
}
void rentHouse(struct User* user, struct House* house, struct Middium* middium, struct Date begin, struct Date end){
    if(middium == NULL){
        middium = getVoidTreapNodeData(&middiumTreap, rand() % cntMiddium);
    }
    newRentHouseMsg(user, house, middium, begin, end);
}

/*middium*/
struct Middium* addMiddium(char name[], char passord[], char phoneNumber[]){
    struct Middium* middium = (struct Middium*)malloc(sizeof(struct Middium));
    middium -> password = (char*)malloc(sizeof(char) * (strlen(passord) + 1));
    middium -> phoneNumber = (char*)malloc(sizeof(char) * (strlen(phoneNumber) + 1));
    initIntList(&middium -> viewMsgList);
    initIntList(&middium -> rentMsgList);
}

/*init*/
void initSystem(){
    setAdminPassword("123456");
    // initVoidTreap(&rentHouseMsg);
    initVoidTreap(&vMsgTreap);
    initVoidList(&vMsgList);
    initVoidTreap(&rMsgTreap);
    initVoidList(&rMsgList);
    // initVoidTreap(&users);
    initVoidTreap(&middiumTreap);
    initVoidList(&middiumList);
    initVoidTreap(&houseTreap);
    initHashTreap(&placeTraep);
    initVoidList(&HouseList);
    placeRoot.name = "root";
    placeRoot.level = 0;
}
#endif
