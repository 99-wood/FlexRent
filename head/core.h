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
#include "viewhousemsg.h"
#include "renthousemsg.h"
#include <sys/stat.h>

int __L, __R;

/*tool*/
void sort(void* val[], int l, int r, bool (*cmp)(void*, void*)){
    if(l >= r) return;
    int mid = (l + r) >> 1;
    sort(val, l, mid, cmp);
    sort(val, mid + 1, r, cmp);
    void** tmp = (void**)malloc(sizeof(void*) * (r + 1));
    int px = l, py = mid + 1, p = l;
    while(px <= mid && py <= r){
        if(cmp(val[px], val[py])){
            tmp[p++] = val[px++];
        }
        else{
            tmp[p++] = val[py++];
        }
    }
    while(px <= mid) tmp[p++] = val[px++];
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
    house -> direction = -1;
    house -> decorationLevel = -1;
    house -> houseType = -1;
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
    addVoidListHead(&houseList, house);
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
void setHouseType(struct House* house, int tagId){
    if(house != NULL) house -> houseType = tagId;
}
void setOwner(struct House* house, char ownerName[], char ownerPhone[]){
    free(house -> ownerName);
    free(house -> ownerPhone);
    house -> ownerName = (char*)malloc(sizeof(char) * (strlen(ownerName) + 1));
    house -> ownerPhone = (char*)malloc(sizeof(char) * (strlen(ownerPhone) + 1));
    strcpy(house -> ownerName, ownerName);
    strcpy(house -> ownerPhone, ownerPhone);
    return;
}
void printHouse(struct House* house){
    if(house == NULL) return;
    if(house -> state == deleted) return;
    printf("id: %05d Area: %3d city: %s address: %s", house -> id, house -> S, house -> father -> father -> name, house -> address);
    if(house -> price != -1) printf(" price: %d", house -> price);
    printf(" owner: %s owner'sPhone: %s", house -> ownerName, house -> ownerPhone);
}

bool isAvailable(struct House* house, struct Date start, struct Date end){
    for(struct IntListNode* p = house -> rentMsgList.head; p != NULL; p = p -> nxt){
        struct RentHouseMsg* msg = (struct RentHouseMsg*)getVoidTreapNodeData(&rMsgTreap, p -> value);
        if(cmpDate(msg -> end, start) < 0 || cmpDate(end, msg -> begin) < 0) continue;
        else{
            return false;
        }
    }
    return true;
}

int getRentTime(struct House* house, struct Date start, struct Date end){ //查询框{}
    int ans = 0;
    for(struct IntListNode* p = house -> rentMsgList.head; p != NULL; p = p -> nxt){
        struct RentHouseMsg* msg = (struct RentHouseMsg*)getVoidTreapNodeData(&rMsgTreap, p -> value);
        if(cmpDate(msg -> end, start) < 0 || cmpDate(end, msg -> begin) < 0) continue; // []{} || {}[]
        else if(cmpDate(msg -> begin, start) <= 0 && cmpDate(end, msg -> end) <= 0){ //[{}]
            ans += subDate(start, end);
        }
        else if(cmpDate(start, msg -> begin) <= 0 && cmpDate(msg -> end, end) <= 0){ //{[]}
            ans += subDate(msg -> begin, msg -> end);
        }
        else if(cmpDate(start, msg -> begin) <= 0 && cmpDate(end, msg -> end) <= 0){ //{[}]
            ans += subDate(msg -> begin, end);
        }
        else{ //[{]}
            ans += subDate(start, msg -> end);
        }
    }
    return ans;
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
    msg -> middiumId = middium -> id;
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
struct ViewHouseMsg* viewHouse(struct User* user, struct House* house, struct Middium* middium, struct Date date){
    if(middium == NULL){
        middium = getVoidTreapNodeData(&middiumTreap, rand() % cntMiddium);
    }
    return newViewHouseMsg(user, house, middium, date);
}
void cancelViewHouse(struct ViewHouseMsg* msg){
    if(msg != NULL) msg -> state = cancel;
    return;
}
void finishViewHouse(struct ViewHouseMsg* msg){
    if(msg != NULL) msg -> state = finish;
    return;
}
void printVMsg(struct ViewHouseMsg* msg){
    if(msg == NULL) return;
    printf("id: %05d houseID: %05d agencyID: %05d userID: %05d", msg -> id, msg -> houseId, msg -> middiumId, msg -> userId);
    printf(" time: %04d-%02d-%02d", msg -> reqTime.year, msg -> reqTime.month, msg -> reqTime.day);
    if(msg -> state == normal) printf("state: normal");
    else if(msg -> state == cancel) printf("state: cancel");
    else if(msg -> state == finish) printf("state: finish");
    return;
}
void printRMsg(struct RentHouseMsg* msg){
    if(msg == NULL) return;
    printf("id: %05d houseID: %05d agencyID: %05d userID: %05d", msg -> id, msg -> houseId, msg -> middiumId, msg -> userId);
    printf(" begin_time: %04d-%02d-%02d end_time: %04d-%02d-%02d", msg -> begin.year, msg -> begin.month, msg -> begin.day, msg -> end.year, msg -> end.month, msg -> end.day);
    // if(msg -> state == normal) printf("state: normal");
    // else if(msg -> state == cancel) printf("state: cancel");
    // else if(msg -> state == finish) printf("state: finish");
    return;
}
struct VoidList* VmsgIdListToVmsgList(struct IntList* list){
    struct VoidList* ans = (struct VoidList*)malloc(sizeof(struct VoidList));
    initVoidList(ans);
    for(struct IntListNode* p = list -> head; p != NULL; p = p -> nxt){
        struct ViewHouseMsg* val = getVoidTreapNodeData(&vMsgTreap, p -> value);
        addVoidListHead(ans, val);
    }
    return ans;
}
struct VoidList* RmsgIdListToRmsgList(struct IntList* list){
    struct VoidList* ans = (struct VoidList*)malloc(sizeof(struct VoidList));
    initVoidList(ans);
    for(struct IntListNode* p = list -> head; p != NULL; p = p -> nxt){
        struct RentHouseMsg* val = getVoidTreapNodeData(&rMsgTreap, p -> value);
        addVoidListHead(ans, val);
    }
    return ans;
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
struct RentHouseMsg* rentHouse(struct User* user, struct House* house, struct Middium* middium, struct Date begin, struct Date end){
    if(middium == NULL){
        middium = getVoidTreapNodeData(&middiumTreap, rand() % cntMiddium);
    }
    return newRentHouseMsg(user, house, middium, begin, end);
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
    strcpy(middium -> phoneNumber, phoneNumber);
    initIntList(&middium -> viewMsgList);
    initIntList(&middium -> rentMsgList);
    addVoidListHead(&middiumList, middium);
    addVoidTreapNode(&middiumTreap, middium, middium -> id);
    return middium;
}

void changeMiddiumPassword(struct Middium* middium, char newPassword[]){
    if(middium == NULL) return;
    free(middium -> password);
    middium -> password = (char*)malloc(sizeof(char) * (strlen(newPassword) + 1));
    strcpy(middium -> password, newPassword);
    return;
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
void changeUserPassword(struct User* user, char newPassword[]){
    if(user != NULL){
        free(user -> password);
        user -> password = (char*)malloc(sizeof(char) * (strlen(newPassword) + 1));
        strcpy(user -> password, newPassword);
    }
    return;
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
    if(rt -> level == 3) return;
    for(struct VoidListNode * p = rt -> sons.head; p != NULL; p = p -> nxt){
        outputPlaceTree((struct Place *)(p -> value));
    }
    return;
}
void outputHouse(){
    printf("%d\n", cntHouse);
    for(int i = 0; i < cntHouse; ++i){
        // int a;
        // scanf("%d", &a);
        struct House* house = (struct House*)getVoidTreapNodeData(&houseTreap, i);
        // printf("%d\n", house);
        // getchar();
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
        printf("\n");
        printf("%d\n", house -> rentMsgList.cnt);
        for(struct IntListNode* j = house -> rentMsgList.head; j != NULL; j = j -> nxt){
            printf("%d ", j -> value);
        }
        printf("\n");
    }
    return;
}
void outputMiddium(){
    printf("%d\n", cntMiddium);
    for(int i = 0; i < cntMiddium; ++i){
        struct Middium* middium = (struct Middium*)getVoidTreapNodeData(&middiumTreap, i);
        printf("%s\n", middium -> name);
        printf("%d\n", middium -> id);
        printf("%s\n", middium -> password);
        printf("%s\n", middium -> phoneNumber);
        printf("%d\n", middium -> viewMsgList.cnt);
        for(struct IntListNode* j = middium -> viewMsgList.head; j != NULL; j = j -> nxt){
            printf("%d ", j -> value);
        }
        printf("\n");
        printf("%d\n", middium -> rentMsgList.cnt);
        for(struct IntListNode* j = middium -> rentMsgList.head; j != NULL; j = j -> nxt){
            printf("%d ", j -> value);
        }
        printf("\n");
    }
}
void outputUser(){
    printf("%d\n", cntUser);
    for(int i = 0; i < cntUser; ++i){
        struct User* user = (struct User*)getVoidTreapNodeData(&userTreap, i);
        printf("%s\n", user -> name);
        printf("%d\n", user -> id);
        printf("%s\n", user -> password);
        printf("%s\n", user -> phoneNumber);

        printf("%d\n", user -> viewMsgList.cnt);
        for(struct IntListNode* j = user -> viewMsgList.head; j != NULL; j = j -> nxt){
            printf("%d ", j -> value);
        }
        printf("\n");
        printf("%d\n", user -> rentMsgList.cnt);
        for(struct IntListNode* j = user -> rentMsgList.head; j != NULL; j = j -> nxt){
            printf("%d ", j -> value);
        }
        printf("\n");
    }
}
void outputViewMsg(){
    printf("%d\n", cntViewMsg);
    for(int i = 0; i < cntViewMsg; ++i){
        struct ViewHouseMsg* now = (struct ViewHouseMsg*)getVoidTreapNodeData(&vMsgTreap, i);
        printf("%d\n", now -> id);
        printf("%d %d %d\n", now -> reqTime.year, now -> reqTime.month, now -> reqTime.day);
        printf("%d\n", now -> houseId);
        printf("%d\n", now -> userId);
        printf("%d\n", now -> middiumId);
        printf("%d\n", now -> state);
    }
}
void outputRentMsg(){
    printf("%d\n", cntRentMsg);
    for(int i = 0; i < cntRentMsg; ++i){
        struct RentHouseMsg* now = (struct RentHouseMsg*)getVoidTreapNodeData(&rMsgTreap, i);
        printf("%d\n", now -> id);
        printf("%d %d %d %d %d %d\n", now -> begin.year, now -> begin.month, now -> begin.day, now -> end.year, now -> end.month, now -> end.day);
        printf("%d\n", now -> houseId);
        printf("%d\n", now -> userId);
        printf("%d\n", now -> middiumId);
    }
}
void outputPassword(){
    printf("%s\n", getAdminPassword());
    return;
}
void outputSystem(char fileName[]){
    freopen(fileName, "w", stdout);
    outputPassword();
    outputTag();
    outputPlaceTree(&placeRoot);
    printf("FINISH\n");
    printf("FINISH\n");
    outputHouse();
    outputMiddium();
    outputUser();
    outputViewMsg();
    outputRentMsg();
    freopen("CON", "a", stdout);
    return;
}
void inputTag(){
    int n;
    scanf("%d\n", &n);
    for(int i = 0; i < n; ++i){
        char name[20];
        gets(name);
        addTag(name);
    }
    return;
}
void inputPlaceTree(){
    char name[20], father[20];
    gets(father);
    gets(name);
    while(strcmp(name, "FINISH") != 0){
        // printf("%s\n", father);
        // getchar();
        // printf("%s\n", name);
        // getchar();
        addPlace(name, father);
        gets(father);
        gets(name);
    }
    return;
}
void inputHouse(){
    int n;
    scanf("%d\n", &n);
    int id, price, S, floor, state, direction, decorationLevel, houseType;
    char ownerName[20], ownerPhone[20], father[20], address[20];
    for(int i = 0; i < n; ++i){
        scanf("%d\n", &id);
        scanf("%d\n", &price);
        scanf("%d\n", &S);
        scanf("%d\n", &floor);
        scanf("%d\n", &state);
        printf("|%d|\n", S);
        gets(ownerName);
        gets(ownerPhone);
        gets(father);
        gets(address);
        scanf("%d\n", &direction);
        scanf("%d\n", &decorationLevel);
        scanf("%d\n", &houseType);
        struct House* house = addHouse(ownerName, ownerPhone, father, address, S, floor);
        setPrice(house,price);
        house -> state = state;
        setdirection(house, direction);
        setdecorationLevel(house, decorationLevel);
        setHouseType(house, houseType);
        int m;
        scanf("%d\n", &m);
        // if(m == 0) getchar();
        for(int j = 0; j < m; ++j){
            int a;
            scanf("%d\n", &a);
            // addIntListHead(&house -> viewMsgList, a);
        }
        // Sleep(10000);
        scanf("%d\n", &m);
        // if(m == 0) getchar();
        for(int j = 0; j < m; ++j){
            int a;
            scanf("%d\n", &a);
            // addIntListHead(&house -> rentMsgList, a);
        }
    }
    return;
}
void inputMiddium(){
    int n;
    scanf("%d\n", &n);
    int id;
    char name[20], password[20], phoneNumber[20];
    for(int i = 0; i < n; ++i){
        gets(name);
        scanf("%d\n", &id);
        gets(password);
        gets(phoneNumber);
        printf("%s\n", phoneNumber);
        struct Middium* middium = addMiddium(name, password, phoneNumber);

        int m;
        scanf("%d\n", &m);
        // if(m == 0) getchar();
        // freopen("CON", "w", stdout);
        for(int j = 0; j < m; ++j){
            int a;
            scanf("%d\n", &a);
            // addIntListHead(&middium -> viewMsgList, a);
        }
        scanf("%d\n", &m);
        // if(m == 0) getchar();
        for(int j = 0; j < m; ++j){
            int a;
            scanf("%d\n", &a);
            // addIntListHead(&middium -> rentMsgList, a);
        }
    }
    return;
}
void inputUser(){
    int n;
    scanf("%d\n", &n);
    printf("|%d|", n);
    char name[20], password[20], phoneNumber[20];
    int id;
    for(int i = 0; i < n; ++i){
        gets(name);
        scanf("%d\n", &id);
        gets(password);
        gets(phoneNumber);
        printf("|%s|\n", name);
        printf("|%s|\n", password);
        printf("|%s|\n", phoneNumber);
            // printf("|%s|", phoneNumber);
        struct User* user = addUser(name, password, phoneNumber);

        int m;
        scanf("%d\n", &m);
        // if(m == 0) getchar();
        for(int j = 0; j < m; ++j){
            int a;
            scanf("%d\n", &a);
            // addIntListHead(&user -> viewMsgList, a);
        }
        scanf("%d\n", &m);
        // if(m == 0) getchar();
        for(int j = 0; j < m; ++j){
            int a;
            scanf("%d\n", &a);
            // addIntListHead(&user -> rentMsgList, a);
        }
    }
}
void inputVMsg(){
    int n;
    scanf("%d\n", &n);
    printf("|%d|", n);
    int id, houseId, userId, middiumId, state;
    struct Date t;
    for(int i = 0; i < n; ++i){
        scanf("%d\n", &id);
        scanf("%d%d%d\n", &t.year, &t.month, &t.day);
        scanf("%d\n", &houseId);
        scanf("%d\n", &userId);
        scanf("%d\n", &middiumId);
        scanf("%d\n", &state);
        struct House* house = (struct House*)getVoidTreapNodeData(&houseTreap, houseId);
        struct Middium* middium = (struct Middium*)getVoidTreapNodeData(&middiumTreap, middiumId);
        struct User* user = (struct User*)getVoidTreapNodeData(&userTreap, userId);
        struct ViewHouseMsg* msg = viewHouse(user, house, middium, t);
        msg -> state = state;
    }
    return;
}
void inputRMsg(){
    int n;
    scanf("%d\n", &n);
    printf("|%d|", n);
    int id, houseId, userId, middiumId;
    struct Date s, t;
    for(int i = 0; i < n; ++i){
        scanf("%d\n", &id);
        scanf("%d%d%d\n", &s.year, &s.month, &s.day);
        scanf("%d%d%d\n", &t.year, &t.month, &t.day);
        scanf("%d\n", &houseId);
        scanf("%d\n", &userId);
        scanf("%d\n", &middiumId);
        struct House* house = (struct House*)getVoidTreapNodeData(&houseTreap, houseId);
        struct Middium* middium = (struct Middium*)getVoidTreapNodeData(&middiumTreap, middiumId);
        struct User* user = (struct User*)getVoidTreapNodeData(&userTreap, userId);
        rentHouse(user, house, middium, s, t);
    }
    return;
}
void inputPassword(){
    char password[20];
    gets(password);
    setAdminPassword(password);
    return;
}
void inputSystem(char fileName[]){
    freopen(fileName, "r", stdin);
    inputPassword();
    inputTag();
    inputPlaceTree();
    inputHouse();
    inputMiddium();
    inputUser();
    inputVMsg();
    inputRMsg();
    freopen("CON", "r", stdin);
}
bool isFileExists(char fileName[]) {
  struct stat buffer;   
  return (stat(fileName, &buffer) == 0); 
}
/*init*/
void initSystem(){
    // setAdminPassword("123456");
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
    initVoidList(&houseList);
    placeRoot.name = "root";
    placeRoot.level = 0;
    if(isFileExists("data.out")){
        inputSystem("data.out");
    }
    else{
        setAdminPassword("123456");
    }
    return;
}
void quitSystem(){
    printf("Enter \"yes\" to save\n");
    char input[20];
    fflush(stdin);
    gets(input);
    if(strcmp(input, "yes") == 0){
        outputSystem("data.out");
    }
    else{
        outputSystem("CON");
        getchar();
    }
    return;
}
#endif
