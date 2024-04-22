#include "head.h"
#include "core.h"
int main(){
    initSystem();
    while(true){
        int op1_ = UiPrint(op1, 4);
        if(op1_ == 0){
            printf("hihao");
            getchar();
        }
        else if(op1_ == 1){
            char* op12[]= {"admin", "middium", "user", "back"};
            while(1){
                int op12_ = UiPrint(op12, 4);
                if(op12_ == 0){

                }
                else if(op12_ == 1){

                }
                else if(op12_ == 2){

                }
                else{
                    break;
                }
            }
            
        }
        else if(op1_ == 2){

        }
        else{
            printf("wcnm");
            return 0;
        }
    }
    addTag("bei");
    addPlace("liaonin", "root");
    addPlace("beijing", "root");
    addPlace("chaoyang", "beijing");
    addPlace("shenyang", "liaonin");
    addPlace("hunnan", "shenyang");
    addPlace("11", "niumo");
    printPlaceTree(&placeRoot, 0);
    struct House* house1 = addHouse("fw", "123", "hunnan", "No195", 100, 2);
    struct House* house2 = addHouse("fw", "123", "hunnan", "No194", 10000, -18);
    struct House* house3 = addHouse("fw", "123", "hunnan", "No191", 10000, -18);
    setdirection(house2, findTag("bei"));
    setPrice(house2, 1000);
    // delHouse(house);
    // printHouse(house);
    // printf("%s", tag[house -> direction].name);
    // printf("%d", house -> price);
    struct Middium* middium = addMiddium("js", "12345", "23456");
    struct Middium* middium_ = (struct Middium*)getVoidTreapNodeData(&middiumTreap, 0);
    // printf("%s\n", middium_ -> name);
    struct User* user = addUser("fw", "1234567890", "23456789");
    // printf("%d\n", user -> viewMsgList.cnt);
    // printf("%s", user);
    // struct User* user_ = (struct User*)getVoidTreapNodeData(&userTreap, 0);
    // printf("%s", user_ -> name);
    struct Date date;
    date.year = 2020;
    date.day = 11;
    date.month = 12;
    // viewHouse(user, house1, middium, date);
    // viewHouse(user, house3, middium, date);
    // viewHouse(user, house2, middium, date);
    rentHouse(user, house1, middium, date, date);
    date.year++;
    rentHouse(user, house1, middium, date, date);
    struct IntListNode* now = house1 -> rentMsgList.head;
    struct Date l, r;
    l.year = r.year =2020;
    l.month = 1;
    l.day = 1;
    r.month = 12;
    r.day = 31;
    bool flag = true;
    while(now != NULL){
        int msgId = now -> value;
        struct RentHouseMsg* msg = (struct RentHouseMsg*)getVoidTreapNodeData(&rMsgTreap, msgId);
        if(!(cmpDate(r, msg -> begin) < 0 || cmpDate(msg -> end, l) < 0)) {
            flag = false;
            break;
        }
        now = now -> nxt;
    }
    if(flag) printf("ok");
    else printf("no");
}