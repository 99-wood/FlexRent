#ifndef _CORE
#define _CORE
#include "typedefine.h"
#include "voidtreap.h"
#include "house.h"
#include "head.h"
#include "windows.h"
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
    house -> direction = tagId;
    return;
}
void setdecorationLevel(struct House* house, int tagId){
    house -> decorationLevel = tagId;
    return;
}
void printHouse(struct House* house){
    if(house == NULL) return;
    if(house -> state == deleted) return;
    printf("%5d %3d %20s\n", house -> id, house -> S, house -> address);
}
/*init*/
void initSystem(){
    setAdminPassword("123456");
    initVoidTreap(&rentHouseMsg);
    initVoidTreap(&viewHouseMsg);
    initVoidTreap(&users);
    initVoidTreap(&middiums);
    initVoidTreap(&houseTreap);
    initHashTreap(&placeTraep);
    initVoidList(&HouseList);
    placeRoot.name = "root";
    placeRoot.level = 0;
}
#endif
