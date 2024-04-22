#include "head.h"
#include "core.h"
#include "windows.h"
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
                                                    getchar();
                                                }
                                                else{
                                                    addTag(tagName);
                                                    printf("OK!\n");
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
                                                    getchar();
                                                }
                                                else{
                                                    struct place* father = getHashTreapNodeData(&placeTraep, makeHashValue(fatherName));
                                                    if(father == NULL){
                                                        printf("The father place is no exist!");
                                                        getchar();
                                                    }
                                                    else{
                                                        addPlace(placeName, fatherName);
                                                        printf("OK!");
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
                                                    getchar();
                                                }
                                                else{
                                                    printf("OK!\n");
                                                    getchar();
                                                }
                                            }
                                            else if(op1002_ == 2){

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
                    if(enable){
                        printf("ok");
                        static char* op122[]= {"admin", "middium", "user", "back"};
                    }
                    else{
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