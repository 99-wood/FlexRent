#ifndef _CORE
#define _CORE
#include "typedefine.h"
#include "voidtreap.h"
#include "house.h"
#include "middium.h"
#include "user.h"
#include "head.h"
#include "windows.h"
#include "ui.h"

int __L, __R;

/*tool*/
void sort(void* val[], int l, int r, bool (*cmp)(void*, void*)){
    if(l == r) return;
    int mid = (l + r) >> 1;
    sort(val, l, mid, cmp);
    sort(val, mid + 1, r, cmp);
    void** tmp = (void*)malloc(sizeof(void*) * (r + 1));
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


/*Admin*/
char* getAdminPassword(){
    return admin.password;
}
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
    if(place == NULL || place -> level < 3 || S <= 0) return NULL;
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
    printf("id: %05d Area: %3d city: %s address: %s", house -> id, house -> S, house -> father -> father -> name, house -> address);
    if(house -> price != -1) printf(" price:", house -> price);
    printf(" owner: %s owner'sPhone: %s", house -> ownerName, house -> ownerPhone);
}
// void printAll(struct Place* place)
void printAll(struct Place * rt, int len){
    // printf("yes");
    for(int i = 0; i < len; ++i) printf(" ");
    int cnt = 0;
    printf("|-");
    cnt += 2;
    printf("%s", rt -> name);
    if(rt -> level == 3){
        printf("-|\n");
        cnt += 1;
        // printf("%d", rt -> sons.cnt);
        for(struct VoidListNode * p = rt -> sons.head; p != NULL; p = p -> nxt){
            if(((struct House*)(p -> value)) -> state == deleted) continue;
            for(int i = 0; i < len + cnt + strlen(rt -> name); ++i) printf(" ");
            printf("|-");
            printHouse((struct House *)(p -> value));
            printf("\n");
        }
        return;
    }
    else printf("-|\n");
    cnt += 1;
    for(struct VoidListNode * p = rt -> sons.head; p != NULL; p = p -> nxt){
        printAll((struct Place *)(p -> value), len + cnt + strlen(rt -> name));
    }
    return;
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
    msg -> middiumId = middium -> id;
    msg -> begin = begin;
    msg -> end = end;
    msg -> id = cntRentMsg++;
    addVoidListHead(&rMsgList, msg);
    addVoidTreapNode(&rMsgTreap, msg, msg -> id);
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
struct Middium* addMiddium(char name[], char password[], char phoneNumber[]){
    struct Middium* middium = (struct Middium*)malloc(sizeof(struct Middium));
    middium -> id = cntMiddium++;
    middium -> name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    middium -> password = (char*)malloc(sizeof(char) * (strlen(password) + 1));
    middium -> phoneNumber = (char*)malloc(sizeof(char) * (strlen(phoneNumber) + 1));
    strcpy(middium -> name, name);
    strcpy(middium -> password, password);
    initIntList(&middium -> viewMsgList);
    initIntList(&middium -> rentMsgList);
    addVoidListHead(&middiumList, middium);
    addVoidTreapNode(&middiumTreap, middium, middium -> id);
    return middium;
}
/*user*/

struct User* addUser(char name[], char password[], char phoneNumber[]){
    struct User* user = (struct User*)malloc(sizeof(struct User));
    user -> id = cntUser++;
    user -> name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    user -> password = (char*)malloc(sizeof(char) * (strlen(password) + 1));
    user -> phoneNumber = (char*)malloc(sizeof(char) * (strlen(phoneNumber) + 1));
    strcpy(user -> name, name);
    strcpy(user -> password, password);
    strcpy(user -> phoneNumber, phoneNumber);
    initIntList(&user -> viewMsgList);
    initIntList(&user -> rentMsgList);
    addVoidListHead(&userList, user);
    addVoidTreapNode(&userTreap, user, user -> id);
    return user;
}

/*init*/
void initSystem(){
    setAdminPassword("123456");
    // initVoidTreap(&rentHouseMsg);
    initVoidTreap(&vMsgTreap);
    initVoidList(&vMsgList);
    initVoidTreap(&rMsgTreap);
    initVoidList(&rMsgList);
    initVoidTreap(&userTreap);
    initVoidList(&userList);
    initVoidTreap(&middiumTreap);
    initVoidList(&middiumList);
    initVoidTreap(&houseTreap);
    initHashTreap(&placeTraep);
    initVoidList(&HouseList);
    placeRoot.name = "root";
    placeRoot.level = 0;
}

void outputTag(){
    printf("%d\n", tagCnt);
    for(int i = 0; i < tagCnt; ++i){
        printf("%s\n", tag[i].name);
    }
    return;
}

void outputPlaceTree(struct Place* rt){
    if(rt -> level != 0){
        printf("%s\n%s\n", rt -> father -> name, rt -> name);
    }
    for(struct VoidListNode * p = rt -> sons.head; p != NULL; p = p -> nxt){
        outputPlaceTree((struct Place *)(p -> value));
    }
    return;
}
void outputHouse(){
    for(int i = 0; i < cntHouse; ++i){
        struct House* house = (struct House*)getVoidTreapNodeData(&houseTreap, i);
        printf("%d\n", i);
        printf("%d\n", house -> price);
        printf("%d\n", house -> S);
        printf("%d\n", house -> floor);
        printf("%d\n", house -> state);
        printf("%s\n", house -> ownerName);
        printf("%s\n", house -> ownerPhone);
        printf("%s\n", house -> father -> name);
        printf("%s\n", house -> address);
        printf("%d\n", house -> direction);
        printf("%d\n", house -> decorationLevel);
        printf("%d\n", house -> houseType);
        printf("%d\n", house -> viewMsgList.cnt);
        for(struct IntListNode* j = house -> viewMsgList.head; j != NULL; j = j -> nxt){
            printf("%d ", j -> value);
        }
        printf("%d\n", house -> rentMsgList.cnt);
        for(struct IntListNode* j = house -> rentMsgList.head; j != NULL; j = j -> nxt){
            printf("%d ", j -> value);
        }
    }
    return;
}
void outputRentMsg(){
    printf("%d\n", rMsgList.cnt);
    for(struct VoidListNode* p = (struct VoidListNode*)rMsgList.head; p != NULL; p = p -> nxt){
        struct RentHouseMsg* now = (struct RentHouseMsg*)p -> value;
        printf("%d\n", now -> id);
        printf("%d %d %d %d %d %d\n", now -> begin.year, now -> begin.month, now -> begin.day, now -> end.year, now -> end.month, now -> end.day);
        printf("%d\n", now -> houseId);
        printf("%d\n", now -> userId);
        printf("%d\n", now -> middiumId);
    }
}
void outputViewMsg(){
    printf("%d\n", vMsgList.cnt);
    for(struct VoidListNode* p = (struct VoidListNode*)vMsgList.head; p != NULL; p = p -> nxt){
        struct ViewHouseMsg* now = (struct ViewHouseMsg*)p -> value;
        printf("%d\n", now -> id);
        printf("%d %d %d\n", now -> reqTime.year, now -> reqTime.month, now -> reqTime.day);
        printf("%d\n", now -> houseId);
        printf("%d\n", now -> userId);
        printf("%d\n", now -> middiumId);
        printf("%d\n", now ->state);
    }
}
void outputSystem(char fileName[]){
    freopen(fileName, "w", stdout);
    outputTag();
    outputPlaceTree(&placeRoot);
    printf("FINISH\n");
    printf("FINISH\n");
    outputHouse();
    freopen("CON", "w", stdout);
    return;
}
void quitSystem(){
    outputSystem("data.out");
    return;
}
#endif
