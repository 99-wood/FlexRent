#include "head.h"
#include "core.h"
#include "check.h"
#include <windows.h>
char name[20], phoneNumber[20], pwd[20];
int id;
int main(){
    initSystem();
    modeset(240,9100);
    while(true){
        static char* op[] = {"Welcome to Flexrent", "Login", "Register", "Exit"};
        int op_ = UiPrint(op, 4);
        if(op_ == 0){ //Easter egg
            printf("This is an Easter egg!");
            fflush(stdin);
            getchar();
        }
        else if(op_ == 1){ //Login
            static char* op1[]= {"Admin", "Agency", "User", "Back"};
            while(true){
                int op1_ = UiPrint(op1, 4);
                if(op1_ == 0){ //admin
                    printf("please enter your password:");
                    getpwd(pwd, sizeof(pwd) / sizeof(char));
                    if(strcmp(pwd, getAdminPassword()) == 0){ //成功登录 admin
                        static char* op10[]= {"Property Management", "Information Inquiry", "Agency Management", "Modify System", "Change Password", "Exit"};
                        while(true){
                            int op10_ = UiPrint(op10, 6);
                            if(op10_ == 0){ //房源管理
                                static char* op100[]= {"Set Tag", "Set Place", "Set Property", "Back"};
                                while(true){
                                    int op100_ = UiPrint(op100, 4);
                                    if(op100_ == 0){ //管理 tag
                                        static char* op1000[]= {"Print All Tags", "Add Tag", "Back"};
                                        while(true){
                                            int op1000_ = UiPrint(op1000, 3);
                                            if(op1000_ == 0){ //打印所有 tag
                                                if(tagCnt == 0){
                                                    printf("there is no Tag\n");
                                                }
                                                else{
                                                    printf("|  id  |        tag name        |\n");
                                                    printf("---------------------------------\n");
                                                    for(int i = 0; i < tagCnt; ++i){
                                                        printf("| %04d |    %-20s|\n", i, tag[i].name);
                                                    }
                                                    printf("---------------------------------\n");
                                                }
                                                fflush(stdin);
                                                getchar();
                                            }
                                            else if(op1000_ == 1){//添加 tag
                                                char tagName[20];
                                                printf("Please enter the tag Name:");
                                                gets(tagName);
                                                bool exist = false;
                                                for(int i = 0; i < tagCnt; ++i){
                                                    if(strcmp(tagName, tag[i].name) == 0){
                                                        exist = true;
                                                        break;
                                                    }
                                                }
                                                if(exist){
                                                    printf("The Tag have existed!");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                                else{
                                                    addTag(tagName);
                                                    printf("OK!\n");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                            }
                                            else{
                                                break;
                                            }
                                        }
                                    }
                                    else if(op100_ == 1){ //地点管理
                                        static char* op1001[]= {"Print Place Tree", "Add Place", "Back"};
                                        while(true){
                                            int op1001_ = UiPrint(op1001, 3);
                                            if(op1001_ == 0){
                                                printPlaceTree(&placeRoot, 0);
                                                fflush(stdin);
                                                getchar();
                                            }
                                            else if(op1001_ == 1){
                                                char placeName[20], fatherName[20];
                                                printf("Please enter the place's name:");
                                                gets(placeName);
                                                printf("Plesae enter the place's father's name, if the place is a privince, just enter Enter");
                                                gets(fatherName);
                                                if(strlen(fatherName) == 0){
                                                    addPlace(placeName, "root");
                                                    printf("OK!");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                                else{
                                                    struct place* father = getHashTreapNodeData(&placeTraep, makeHashValue(fatherName));
                                                    if(father == NULL){
                                                        printf("The father place is no exist!");
                                                        fflush(stdin);
                                                        getchar();
                                                    }
                                                    else{
                                                        addPlace(placeName, fatherName);
                                                        printf("OK!");
                                                        fflush(stdin);
                                                        getchar();
                                                    }
                                                }
                                            }
                                            else{
                                                break;
                                            }
                                        }
                                    }
                                    else if(op100_ == 2){ //房源管理
                                        static char* op1002[] = {"Print All House", "Add House", "Delete House", "Modify House", "Back"};
                                        while(true){
                                            int op1002_ = UiPrint(op1002, 5);
                                            if(op1002_ == 0){ //打印所有房子
                                                printAll(&placeRoot, 0);
                                                fflush(stdin);
                                                getchar();
                                            }
                                            else if(op1002_ == 1){ // 添加房子
                                                char ownerName[20], ownerPhone[20], placeName[20], address[20];
                                                int S, floor;
                                                printf("Please Enter the owner's name:");
                                                gets(ownerName);
                                                printf("Please Enter the owner's phone number:");
                                                gets(ownerPhone);
                                                printf("Please Enter the placeName:");
                                                gets(placeName);
                                                printf("Please Enter the address:");
                                                if(getHashTreapNodeData(&placeTraep, makeHashValue(placeName)) == NULL){
                                                    printf("There's no this place!\n");
                                                    fflush(stdin);
                                                    getchar();
                                                    continue;
                                                }
                                                gets(address);
                                                printf("Please Enter the house's Area:");
                                                scanf("%d", &S);
                                                printf("Please Enter the house's floor:");
                                                scanf("%d", &floor);
                                                struct House* house = addHouse(ownerName, ownerPhone, placeName, address, S, floor);
                                                if(house == NULL){
                                                    printf("Wrong infomation!\n");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                                else{
                                                    printf("OK!\n");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                            }
                                            else if(op1002_ == 2){
                                                printf("Please Enter the house's ID to delete the House.");
                                                int id;
                                                scanf("%d", &id);
                                                if(id < cntHouse){
                                                    struct House* house = getVoidTreapNodeData(&houseTreap, id);
                                                    delHouse(house);
                                                    printf("The House have been deleted!\n");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                                else{
                                                    printf("The ID is wrong!");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                            }
                                            else if(op1002_ == 3){ //修改房子信息
                                                printf("Please Enter the house's ID to delete the House.");
                                                int id;
                                                scanf("%d", &id);
                                                if(id >= cntHouse){
                                                    printf("The ID is wrong!");
                                                    fflush(stdin);
                                                    getchar();
                                                    continue;
                                                }
                                                struct House* house = getVoidTreapNodeData(&houseTreap, id);
                                                static char* op10023[] = {"Set Price", "Set Direction", "Set Decoration Level", "Set House Type", "Set Owner", "Back"};
                                                while(true){
                                                    int op10023_ = UiPrint(op10023, 6);
                                                    if(op10023_ == 0){ //修改价格
                                                        printf("Please Enter the Price");
                                                        int price;
                                                        scanf("%d", &price);
                                                        setPrice(house, price);
                                                        printf("OK!\n");
                                                        fflush(stdin);
                                                        getchar();
                                                    }
                                                    else if(op10023_ == 1){ // 修改方向
                                                        char str[20];
                                                        printf("Please Enter the direction.\n");
                                                        fflush(stdin);
                                                        gets(str);
                                                        int tagId = findTag(str);
                                                        if(tagId == -1){
                                                            printf("The tag is not exist. Do you want to add it now? Enter \"yes\" to add the Tag.\n");
                                                            char tmp[20];
                                                            fflush(stdin);
                                                            gets(str);
                                                            if(strcmp(str, "yes") == 0){
                                                                tagId = addTag(str);
                                                            }
                                                            else continue;
                                                        }
                                                        setdirection(house, tagId);
                                                        printf("OK!\n");
                                                        fflush(stdin);
                                                        getchar();
                                                    }
                                                    else if(op10023_ == 2){ // 修改装修情况
                                                        char str[20];
                                                        printf("Please Enter the decoration level.\n");
                                                        fflush(stdin);
                                                        gets(str);
                                                        int tagId = findTag(str);
                                                        if(tagId == -1){
                                                            printf("The tag is not exist. Do you want to add it now? Enter \"yes\" to add the Tag.\n");
                                                            char tmp[20];
                                                            fflush(stdin);
                                                            gets(str);
                                                            if(strcmp(str, "yes") == 0){
                                                                tagId = addTag(str);
                                                            }
                                                            else continue;
                                                        }
                                                        setdecorationLevel(house, tagId);
                                                        printf("OK!\n");
                                                        fflush(stdin);
                                                        getchar();
                                                    }
                                                    else if(op10023_ == 3){ // 修改房屋类型
                                                        char str[20];
                                                        printf("Please Enter the house type.\n");
                                                        fflush(stdin);
                                                        gets(str);
                                                        int tagId = findTag(str);
                                                        if(tagId == -1){
                                                            printf("The tag is not exist. Do you want to add it now? Enter \"yes\" to add the Tag.\n");
                                                            char tmp[20];
                                                            fflush(stdin);
                                                            gets(str);
                                                            if(strcmp(str, "yes") == 0){
                                                                tagId = addTag(str);
                                                            }
                                                            else continue;
                                                        }
                                                        setHouseType(house, tagId);
                                                        printf("OK!\n");
                                                        fflush(stdin);
                                                        getchar();
                                                    }
                                                    else if(op10023_ == 4){ // 修改房屋主人
                                                        char ownerName[20], ownerPhone[20];
                                                        printf("Please Enter the owner's name:");
                                                        fflush(stdin);
                                                        gets(ownerName);
                                                        printf("Please Enter the owner's phone number:");
                                                        fflush(stdin);
                                                        gets(ownerPhone);
                                                        printf("|%s|\n", ownerPhone);
                                                        setOwner(house, ownerName, ownerPhone);
                                                        printf("OK!\n");
                                                        fflush(stdin);
                                                        getchar();
                                                    }
                                                    else{
                                                        break;
                                                    }
                                                }
                                            }
                                            else{
                                                break;
                                            }
                                        }
                                    }
                                    else{
                                        break;
                                    }
                                }
                            }
                            else if(op10_ == 1){ //信息查询
                                static char* op101[] = {"House", "View House Infomation", "Rent House Infomation", "Back"};
                                while(true){
                                    int op101_ = UiPrint(op101, 4);
                                    if(op101_ == 0){ //房源信息查询与统计
                                        struct VoidList val;
                                        initVoidList(&val);
                                        static char* op1010[] = {"Select All", "Select One Place", "Fuzzy Query", "Sort", "Back"};
                                        while(true){
                                            int op1010_ = UiPrint(op1010, 5);
                                            if(op1010_ == 0){ //全选
                                                clearVoidList(&val);
                                                val = *filterVoidList(&houseList, &returnTrue);
                                                printf("OK!\n");
                                                fflush(stdin);
                                                getchar();
                                            }
                                            else if(op1010_ == 1){ //选择某个区
                                                char placeName[20];
                                                printf("Please Enter the place name:");
                                                fflush(stdin);
                                                gets(placeName);
                                                struct Place* place = (struct Place*)getHashTreapNodeData(&placeTraep, makeHashValue(placeName));
                                                if(place == NULL || place -> level != 3){
                                                    printf("There 's no this place!");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                                else{
                                                    clearVoidList(&val);
                                                    val = *filterVoidList(&place -> sons, &returnTrue);
                                                    printf("OK!\n");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                            }
                                            else if(op1010_ == 2){
                                                printf("Please Enter the key words:");
                                                fflush(stdin);
                                                gets(keyWord);
                                                clearVoidList(&val);
                                                struct VoidList tmp = val;
                                                val = *filterVoidList(&tmp, &checkHouseKey);
                                                clearVoidList(&tmp);
                                                printf("OK!\n");
                                                fflush(stdin);
                                                getchar();
                                            }
                                            else if(op1010_ == 3){ //排序
                                                int len = val.cnt;
                                                void** array = VoidListToVoidArray(&val);
                                                sort(array, 0, len - 1, &cmpS);
                                                clearVoidList(&val);
                                                val = *VoidArrayToVoidList(array, len);
                                                free(array);
                                            }
                                            else{
                                                break;
                                            }
                                            int len = val.cnt;
                                            void** array = VoidListToVoidArray(&val);
                                            for(int i = 0; i < len; ++i){
                                                printHouse((struct House*)array[i]);
                                                printf("\n");
                                            }
                                            free(array);
                                            getchar();
                                        }
                                        clearVoidList(&val);
                                    }
                                    else if(op101_ == 1){ //看房信息与统计

                                    }
                                    else if(op101_ == 2){ //租房信息查询与统计

                                    }
                                    else{
                                        break;
                                    }
                                }
                            }
                            else if(op10_ == 2){ //中介管理
                            }
                            else{
                                quitSystem();
                                return 0;
                            }
                        }
                    }
                }
                else if(op1_ == 1){ //middium
                    printf("please enter your id:");
                    scanf("%d", &id);
                    printf("please enter your password:");
                    getpwd(pwd, sizeof(pwd) / sizeof(char));
                    bool enable = false;
                    if(id < cntMiddium){
                        struct Middium* middium = NULL;
                        middium = (struct Middium*)getVoidTreapNodeData(&middiumTreap, id);
                        if(middium != NULL && strcmp(middium -> password, pwd) == 0){
                            enable = true;
                        }
                    }
                    if(enable){
                        printf("ok");
                    }
                    else{
                    }
                }
                else if(op1_ == 2){ //user
                    printf("please enter your id:");
                    scanf("%d", &id);
                    printf("please enter your password:");
                    getpwd(pwd, sizeof(pwd) / sizeof(char));
                    bool enable = false;
                    if(id < cntUser){
                        struct User* user = NULL;
                        user = (struct User*)getVoidTreapNodeData(&userTreap, id);
                        if(user != NULL && strcmp(user -> password, pwd) == 0){
                            enable = true;
                        }
                    }
                    if(enable){ //成功登录user
                        static char* op12[]= {"", "", "", ""};
                    }
                }
                else{ //back
                    break;
                }
            }
        }
        else if(op_ == 2){ //rigister
            while(true){
                printf("please enter your name(English):");
                gets(name);
                printf("please enter your phone number:");
                gets(phoneNumber);
                while(true){
                    printf("please enter your password:");
                    getpwd(pwd, sizeof(pwd) / sizeof(char));
                    printf("please enter your password again:");
                    char tmp[20];
                    getpwd(tmp, sizeof(tmp) / sizeof(char));
                    if(strcmp(pwd, tmp) != 0){
                        printf("wrong, please enter again\n");
                    }
                    else break;
                }
                system("CLS");
                printf("your name is \"%s\", your phone number is \"%s\", please enter \"yes\" to creat account", name, phoneNumber);
                char tmp[20];
                gets(tmp);
                if(strcmp(tmp, "yes") == 0) break;
            }
            struct User* user = addUser(name, pwd, phoneNumber);
            printf("your id is %d\n, enter Enter to continue", user -> id);
            getchar();
        }
        else{
            quitSystem();
            return 0;
        }
    }
    // addTag("bei");
    // addPlace("liaonin", "root");
    // addPlace("beijing", "root");
    // addPlace("chaoyang", "beijing");
    // addPlace("shenyang", "liaonin");
    // addPlace("hunnan", "shenyang");
    // addPlace("11", "niumo");
    // printPlaceTree(&placeRoot, 0);
    // struct House* house1 = addHouse("fw", "123", "hunnan", "No195", 100, 2);
    // struct House* house2 = addHouse("fw", "123", "hunnan", "No194", 10000, -18);
    // struct House* house3 = addHouse("fw", "123", "hunnan", "No191", 10000, -18);
    // setdirection(house2, findTag("bei"));
    // setPrice(house2, 1000);
    // // delHouse(house);
    // // printHouse(house);
    // // printf("%s", tag[house -> direction].name);
    // // printf("%d", house -> price);
    // struct Middium* middium = addMiddium("js", "12345", "23456");
    // struct Middium* middium_ = (struct Middium*)getVoidTreapNodeData(&middiumTreap, 0);
    // // printf("%s\n", middium_ -> name);
    // struct User* user = addUser("fw", "1234567890", "23456789");
    // // printf("%d\n", user -> viewMsgList.cnt);
    // // printf("%s", user);
    // // struct User* user_ = (struct User*)getVoidTreapNodeData(&userTreap, 0);
    // // printf("%s", user_ -> name);
    // struct Date date;
    // date.year = 2020;
    // date.day = 11;
    // date.month = 12;
    // // viewHouse(user, house1, middium, date);
    // // viewHouse(user, house3, middium, date);
    // // viewHouse(user, house2, middium, date);
    // rentHouse(user, house1, middium, date, date);
    // date.year++;
    // rentHouse(user, house1, middium, date, date);
    // struct IntListNode* now = house1 -> rentMsgList.head;
    // struct Date l, r;
    // l.year = r.year =2020;
    // l.month = 1;
    // l.day = 1;
    // r.month = 12;
    // r.day = 31;
    // bool flag = true;
    // while(now != NULL){
    //     int msgId = now -> value;
    //     struct RentHouseMsg* msg = (struct RentHouseMsg*)getVoidTreapNodeData(&rMsgTreap, msgId);
    //     if(!(cmpDate(r, msg -> begin) < 0 || cmpDate(msg -> end, l) < 0)) {
    //         flag = false;
    //         break;
    //     }
    //     now = now -> nxt;
    // }
    // if(flag) printf("ok");
    // else printf("no");
    return 0;
}