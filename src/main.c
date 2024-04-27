#include "head.h"
#include "core.h"
#include "check.h"
#include <windows.h>
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
                    char pwd[20];
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
                                                fflush(stdin);
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
                                                fflush(stdin);
                                                gets(placeName);
                                                printf("Plesae enter the place's father's name, if the place is a privince, just enter Enter");
                                                fflush(stdin);
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
                                                fflush(stdin);
                                                gets(ownerName);
                                                printf("Please Enter the owner's phone number:");
                                                fflush(stdin);
                                                gets(ownerPhone);
                                                printf("Please Enter the placeName:");
                                                fflush(stdin);
                                                gets(placeName);
                                                printf("Please Enter the address:");
                                                if(getHashTreapNodeData(&placeTraep, makeHashValue(placeName)) == NULL){
                                                    printf("There's no this place!\n");
                                                    fflush(stdin);
                                                    getchar();
                                                    continue;
                                                }
                                                fflush(stdin);
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
                                                            gets(tmp);
                                                            if(strcmp(tmp, "yes") == 0){
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
                                                            gets(tmp);
                                                            if(strcmp(tmp, "yes") == 0){
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
                                                            gets(tmp);
                                                            if(strcmp(tmp, "yes") == 0){
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
                                static char* op101[] = {"House", "View House Infomation", "Rent House Infomation", "Agency", "Back"};
                                while(true){
                                    int op101_ = UiPrint(op101, 5);
                                    if(op101_ == 0){ //房源信息查询与统计
                                        struct VoidList val;
                                        initVoidList(&val);
                                        static char* op1010[] = {"Select All", "Select One Place", "Fuzzy Query", "Sort with Area", "Sort with ID", "Sort with Price", "Is a property available?", "Time Range Query", "Back"};
                                        while(true){
                                            int op1010_ = UiPrint(op1010, 9);
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
                                            else if(op1010_ == 2){ //模糊查询
                                                printf("Please Enter the key words:");
                                                fflush(stdin);
                                                gets(keyWord);
                                                struct VoidList tmp = *filterVoidList(&val, &returnTrue);
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
                                            else if(op1010_ == 4){ //id排序
                                                int len = val.cnt;
                                                void** array = VoidListToVoidArray(&val);
                                                sort(array, 0, len - 1, &cmpID);
                                                clearVoidList(&val);
                                                val = *VoidArrayToVoidList(array, len);
                                                free(array);
                                            }
                                            else if(op1010_ == 5){ //价格排序
                                                int len = val.cnt;
                                                void** array = VoidListToVoidArray(&val);
                                                sort(array, 0, len - 1, &cmpprice);
                                                clearVoidList(&val);
                                                val = *VoidArrayToVoidList(array, len);
                                                free(array);
                                            }
                                            else if(op1010_ == 6){ //查询某房源是否可用
                                                int houseID, userID;
                                                printf("Please enter the house ID:"); scanf("%d", &houseID);
                                                if(houseID >= cntHouse){
                                                    printf("Wrong ID!");
                                                    fflush(stdin);
                                                    getchar();
                                                    continue;
                                                }
                                                struct Date begin, end;
                                                printf("Please enter the begin date(yyyy-mm-dd):");scanf("%d-%d-%d", &begin.year, &begin.month, &begin.day);
                                                printf("Please enter the end date(yyyy-mm-dd):");scanf("%d-%d-%d", &end.year, &end.month, &end.day);
                                                if(isLegal(begin) == false || isLegal(end) == false || cmpDate(begin, end) > 0){
                                                    // printf("%d-%d-%d\n", begin.year, begin.month, begin.day);
                                                    // printf("%d-%d-%d\n", end.year, end.month, end.day);
                                                    printf("Wrong date!");
                                                    fflush(stdin);
                                                    getchar();
                                                    continue;
                                                }
                                                struct House* house = getVoidTreapNodeData(&houseTreap, houseID);
                                                if(isAvailable(house, begin, end)){
                                                    printf("available!\n");
                                                }
                                                else{
                                                    printf("not available!\n");
                                                }
                                                fflush(stdin);
                                                getchar();
                                                continue;
                                            }
                                            else if(op1010_ == 7){ //时间区间查询
                                                struct Date begin, end;
                                                printf("Please enter the begin date(yyyy-mm-dd):");scanf("%d-%d-%d", &begin.year, &begin.month, &begin.day);
                                                printf("Please enter the end date(yyyy-mm-dd):");scanf("%d-%d-%d", &end.year, &end.month, &end.day);
                                                if(isLegal(begin) == false || isLegal(end) == false || cmpDate(begin, end) > 0){
                                                    // printf("%d-%d-%d\n", begin.year, begin.month, begin.day);
                                                    // printf("%d-%d-%d\n", end.year, end.month, end.day);
                                                    printf("Wrong date!");
                                                    fflush(stdin);
                                                    getchar();
                                                    continue;
                                                }
                                                int len = val.cnt;
                                                void** array = VoidListToVoidArray(&val);
                                                int sumS = 0, cnt = 0;
                                                int sumT = 0, cntR = 0;
                                                for(int i = 0; i < len; ++i){
                                                    if(((struct House*)array[i]) -> state != deleted){
                                                        struct House* house = (struct House*)array[i];
                                                        printHouse(house);
                                                        int t = getRentTime(house, begin, end);
                                                        sumT += t;
                                                        if(t) ++cntR;
                                                        printf(" rent_time: %d\n", t);
                                                        sumS += house -> S;
                                                        ++cnt;
                                                        printf("\n");
                                                    }
                                                }
                                                if(cnt > 0){
                                                    printf("total:%d\n", cnt);
                                                    printf("Average area:%d\n", sumS / cnt);
                                                    printf("Average rent_time:%lf\n", (double)sumT / cnt);
                                                    printf("rent_ratio:%lf%%\n", (double)cntR / cnt * 100);
                                                }
                                                free(array);
                                                fflush(stdin);
                                                getchar();
                                                continue;
                                            }
                                            else{
                                                break;
                                            }
                                            int len = val.cnt;
                                            void** array = VoidListToVoidArray(&val);
                                            int sumS = 0, cnt = 0;
                                            for(int i = 0; i < len; ++i){
                                                if(((struct House*)array[i]) -> state != deleted){
                                                    struct House* house = (struct House*)array[i];
                                                    printHouse(house);
                                                    ++cnt;
                                                    sumS += house -> S;
                                                    printf("\n");
                                                }
                                            }
                                            if(cnt > 0){
                                                printf("total:%d\n", cnt);
                                                printf("Average area:%d\n", sumS / cnt);
                                            }
                                            free(array);
                                            fflush(stdin);
                                            getchar();
                                        }
                                        clearVoidList(&val);
                                    }
                                    else if(op101_ == 1){ //看房信息与统计
                                        struct VoidList val;
                                        initVoidList(&val);
                                        static char* op1010[] = {"Select All", "Select One House", "Select One Agency", "Select One User", "Select Time", "Fuzzy Query", "Sort with ID", "Sort with Time", "Back"};
                                        while(true){
                                            int op1010_ = UiPrint(op1010, 9);
                                            if(op1010_ == 0){ //全选
                                                clearVoidList(&val);
                                                val = *filterVoidList(&vMsgList, &returnTrue);
                                                printf("OK!\n");
                                                fflush(stdin);
                                                getchar();
                                            }
                                            else if(op1010_ == 1){ //选择某个房子
                                                printf("Please Enter the house ID:");
                                                int houseId;
                                                scanf("%d", &houseId);
                                                if(houseId >= cntHouse){
                                                    printf("There 's no this place!");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                                else{
                                                    clearVoidList(&val);
                                                    struct House* house = getVoidTreapNodeData(&houseTreap, houseId);
                                                    struct IntList tmp = *filterIntList(&house -> viewMsgList, &ireturnTrue);
                                                    val = *VmsgIdListToVmsgList(&tmp);
                                                    clearIntList(&tmp);
                                                    printf("OK!\n");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                            }
                                            else if(op1010_ == 2){ //选择某个中介
                                                printf("Please Enter the agency ID:");
                                                int middiumId;
                                                scanf("%d", &middiumId);
                                                if(middiumId >= cntMiddium){
                                                    printf("There 's no this agency!");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                                else{
                                                    clearVoidList(&val);
                                                    struct Middium* middium = getVoidTreapNodeData(&middiumTreap, middiumId);
                                                    // printf("|%d|", middium -> id);
                                                    // Sleep(10000);
                                                    struct IntList tmp = *filterIntList(&middium -> viewMsgList, &ireturnTrue);
                                                    val = *VmsgIdListToVmsgList(&tmp);
                                                    clearIntList(&tmp);
                                                    printf("OK!\n");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                            }
                                            else if(op1010_ == 3){ //选择某个用户
                                                printf("Please Enter the user ID:");
                                                int userId;
                                                scanf("%d", &userId);
                                                if(userId >= cntUser){
                                                    printf("There 's no this user!");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                                else{
                                                    clearVoidList(&val);
                                                    struct User* user = getVoidTreapNodeData(&userTreap, userId);
                                                    struct IntList tmp = *filterIntList(&user -> viewMsgList, &ireturnTrue);
                                                    val = *VmsgIdListToVmsgList(&tmp);
                                                    clearIntList(&tmp);
                                                    printf("OK!\n");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                            }
                                            else if(op1010_ == 4){ //选择区间
                                                struct Date begin, end;
                                                printf("Please enter the begin date(yyyy-mm-dd):");scanf("%d-%d-%d", &begin.year, &begin.month, &begin.day);
                                                printf("Please enter the end date(yyyy-mm-dd):");scanf("%d-%d-%d", &end.year, &end.month, &end.day);
                                                if(isLegal(begin) == false || isLegal(end) == false || cmpDate(begin, end) > 0){
                                                    // printf("%d-%d-%d\n", begin.year, begin.month, begin.day);
                                                    // printf("%d-%d-%d\n", end.year, end.month, end.day);
                                                    printf("Wrong date!");
                                                    fflush(stdin);
                                                    getchar();
                                                    continue;
                                                }
                                                struct VoidList tmp = *filterVoidList(&val, &returnTrue);
                                                __Ldate = begin;
                                                __Rdate = end;
                                                val = *filterVoidList(&tmp, &checkVmsgTime);
                                                clearVoidList(&tmp);
                                                printf("OK!\n");
                                                fflush(stdin);
                                                getchar();
                                            }
                                            else if(op1010_ == 5){ //模糊查询
                                                printf("Please Enter the key words:");
                                                fflush(stdin);
                                                gets(keyWord);
                                                struct VoidList tmp = *filterVoidList(&val, &returnTrue);
                                                val = *filterVoidList(&tmp, &checkVMsgKey);
                                                clearVoidList(&tmp);
                                                printf("OK!\n");
                                                fflush(stdin);
                                                getchar();
                                            }
                                            else if(op1010_ == 6){ //id排序
                                                int len = val.cnt;
                                                void** array = VoidListToVoidArray(&val);
                                                sort(array, 0, len - 1, &cmpViewId);
                                                clearVoidList(&val);
                                                val = *VoidArrayToVoidList(array, len);
                                                free(array);
                                            }
                                            else if(op1010_ == 7){ //时间排序
                                                int len = val.cnt;
                                                void** array = VoidListToVoidArray(&val);
                                                sort(array, 0, len - 1, &cmpViewDate);
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
                                                printVMsg((struct ViewHouseMsg*)array[i]);
                                                printf("\n");
                                            }
                                            printf("cnt: %d\n", val.cnt);
                                            free(array);
                                            fflush(stdin);
                                            getchar();
                                        }
                                        clearVoidList(&val);
                                    }
                                    else if(op101_ == 2){ //租房信息查询与统计
                                        struct VoidList val;
                                        initVoidList(&val);
                                        static char* op1010[] = {"Select All", "Select One House", "Select One Agency", "Select One User", "Fuzzy Query", "Sort with ID", "Sort with Begin_time", "Back"};
                                        while(true){
                                            int op1010_ = UiPrint(op1010, 8);
                                            if(op1010_ == 0){ //全选
                                                clearVoidList(&val);
                                                val = *filterVoidList(&rMsgList, &returnTrue);
                                                printf("OK!\n");
                                                fflush(stdin);
                                                getchar();
                                            }
                                            else if(op1010_ == 1){ //选择某个房子
                                                printf("Please Enter the house ID:");
                                                int houseId;
                                                scanf("%d", &houseId);
                                                if(houseId >= cntHouse){
                                                    printf("There 's no this place!");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                                else{
                                                    clearVoidList(&val);
                                                    struct House* house = getVoidTreapNodeData(&houseTreap, houseId);
                                                    struct IntList tmp = *filterIntList(&house -> rentMsgList, &ireturnTrue);
                                                    val = *RmsgIdListToRmsgList(&tmp);
                                                    clearIntList(&tmp);
                                                    printf("OK!\n");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                            }
                                            else if(op1010_ == 2){ //选择某个中介
                                                printf("Please Enter the agency ID:");
                                                int middiumId;
                                                scanf("%d", &middiumId);
                                                if(middiumId >= cntMiddium){
                                                    printf("There 's no this agency!");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                                else{
                                                    clearVoidList(&val);
                                                    struct Middium* middium = getVoidTreapNodeData(&middiumTreap, middiumId);
                                                    struct IntList tmp = *filterIntList(&middium -> rentMsgList, &ireturnTrue);
                                                    val = *RmsgIdListToRmsgList(&tmp);
                                                    clearIntList(&tmp);
                                                    printf("OK!\n");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                            }
                                            else if(op1010_ == 3){ //选择某个用户
                                                printf("Please Enter the user ID:");
                                                int userId;
                                                scanf("%d", &userId);
                                                if(userId >= cntUser){
                                                    printf("There 's no this user!");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                                else{
                                                    clearVoidList(&val);
                                                    struct User* user = getVoidTreapNodeData(&userTreap, userId);
                                                    struct IntList tmp = *filterIntList(&user -> rentMsgList, &ireturnTrue);
                                                    val = *RmsgIdListToRmsgList(&tmp);
                                                    clearIntList(&tmp);
                                                    printf("OK!\n");
                                                    fflush(stdin);
                                                    getchar();
                                                }
                                            }
                                            else if(op1010_ == 4){ //模糊查询
                                                printf("Please Enter the key words:");
                                                fflush(stdin);
                                                gets(keyWord);
                                                struct VoidList tmp = *filterVoidList(&val, &returnTrue);
                                                val = *filterVoidList(&tmp, &checkRMsgKey);
                                                clearVoidList(&tmp);
                                                printf("OK!\n");
                                                fflush(stdin);
                                                getchar();
                                            }
                                            else if(op1010_ == 5){ //排序
                                                int len = val.cnt;
                                                void** array = VoidListToVoidArray(&val);
                                                sort(array, 0, len - 1, &cmpRentId);
                                                clearVoidList(&val);
                                                val = *VoidArrayToVoidList(array, len);
                                                free(array);
                                            }
                                            else if(op1010_ == 6){ //日期排序
                                                int len = val.cnt;
                                                void** array = VoidListToVoidArray(&val);
                                                sort(array, 0, len - 1, &cmpRentDate);
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
                                                printRMsg((struct RentHouseMsg*)array[i]);
                                                printf("\n");
                                            }
                                            free(array);
                                            fflush(stdin);
                                            getchar();
                                        }
                                        clearVoidList(&val);
                                    }
                                    else if(op101_ == 3){ //中介信息查询与统计
                                        struct VoidList val;
                                        initVoidList(&val);
                                        static char* op1010[] = {"Select All", "Fuzzy Query", "Sort with ID", "Sort with Turnover", "Time Range Query", "Back"};
                                        while(true){
                                            int op1010_ = UiPrint(op1010, 6);
                                            if(op1010_ == 0){ //全选
                                                clearVoidList(&val);
                                                val = *filterVoidList(&middiumList, &returnTrue);
                                                printf("OK!\n");
                                                fflush(stdin);
                                                getchar();
                                            }
                                            else if(op1010_ == 1){ //模糊查询
                                                printf("Please Enter the key words:");
                                                fflush(stdin);
                                                gets(keyWord);
                                                struct VoidList tmp = *filterVoidList(&val, &returnTrue);
                                                val = *filterVoidList(&tmp, &checkMiddiumKey);
                                                clearVoidList(&tmp);
                                                printf("OK!\n");
                                                fflush(stdin);
                                                getchar();
                                            }
                                            else if(op1010_ == 2){ //id排序
                                                int len = val.cnt;
                                                void** array = VoidListToVoidArray(&val);
                                                sort(array, 0, len - 1, &cmpMiddiumId);
                                                clearVoidList(&val);
                                                val = *VoidArrayToVoidList(array, len);
                                                free(array);
                                            }
                                            else if(op1010_ == 3){ //成交量排序
                                                int len = val.cnt;
                                                void** array = VoidListToVoidArray(&val);
                                                sort(array, 0, len - 1, &cmpMiddiumRentRatio);
                                                clearVoidList(&val);
                                                val = *VoidArrayToVoidList(array, len);
                                                free(array);
                                            }
                                            else if(op1010_ == 4){ //区间查询
                                                struct Date begin, end;
                                                printf("Please enter the begin date(yyyy-mm-dd):");scanf("%d-%d-%d", &begin.year, &begin.month, &begin.day);
                                                printf("Please enter the end date(yyyy-mm-dd):");scanf("%d-%d-%d", &end.year, &end.month, &end.day);
                                                if(isLegal(begin) == false || isLegal(end) == false || cmpDate(begin, end) > 0){
                                                    // printf("%d-%d-%d\n", begin.year, begin.month, begin.day);
                                                    // printf("%d-%d-%d\n", end.year, end.month, end.day);
                                                    printf("Wrong date!");
                                                    fflush(stdin);
                                                    getchar();
                                                    continue;
                                                }
                                                int len = val.cnt;
                                                void** array = VoidListToVoidArray(&val);
                                                int cnt = 0;
                                                int sumT = 0, cntR = 0;
                                                for(int i = 0; i < len; ++i){
                                                    struct Middium* middium = (struct Middium*)array[i];
                                                    printMiddium(middium);
                                                    int t = getMiddiumRentTime(middium, begin, end);
                                                    sumT += t;
                                                    if(t) ++cntR;
                                                    printf(" rent_time: %d\n", t);
                                                    ++cnt;
                                                }
                                                if(cnt > 0){
                                                    printf("total:%d\n", cnt);
                                                    printf("Average rent_time:%lf\n", (double)sumT / cnt);
                                                }
                                                free(array);
                                                fflush(stdin);
                                                getchar();
                                                continue;
                                            }
                                            else{
                                                break;
                                            }
                                            int len = val.cnt;
                                            void** array = VoidListToVoidArray(&val);
                                            for(int i = 0; i < len; ++i){
                                                printMiddium((struct Middium*)array[i]);
                                                printf("\n");
                                            }
                                            free(array);
                                            fflush(stdin);
                                            getchar();
                                        }
                                        clearVoidList(&val);
                                    }
                                    else{
                                        break;
                                    }
                                }
                            }
                            else if(op10_ == 2){ //中介管理
                                static char* op102[] = {"Add Agency", "Change Agency Password", "Back"};
                                while (true)
                                {
                                    int op102_ = UiPrint(op102, 3);
                                    if(op102_ == 0){ //创建中介账户
                                        char name[20], phone[20], password[20];
                                        printf("please enter name(English):");
                                        fflush(stdin);
                                        gets(name);
                                        printf("please enter phone number:");
                                        fflush(stdin);
                                        gets(phone);
                                        printf("please enter password:");
                                        getpwd(password, sizeof(password) / sizeof(char));
                                        printf("name is \"%s\", phone number is \"%s\", password is \"%s\", please enter \"yes\" to creat account", name, phone, password);
                                        char tmp[20];
                                        fflush(stdin);
                                        gets(tmp);
                                        if(strcmp(tmp, "yes") == 0){
                                            struct Middium* middium = addMiddium(name, password, phone);
                                            printf("Create the account! ID is %03d\n", middium -> id);
                                            fflush(stdin);
                                            getchar();
                                        }
                                        else{
                                            printf("Not create account!\n");
                                            fflush(stdin);
                                            getchar();
                                        }
                                    }
                                    else if(op102_ == 1){ //修改中介密码
                                        char password[20];
                                        int id;
                                        printf("please enter ID:");
                                        scanf("%d", &id);
                                        if(id >= cntMiddium){
                                            printf("Wrong ID!\n");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        printf("please enter new password:");
                                        getpwd(password, sizeof(password) / sizeof(char));
                                        printf("password is \"%s\", please enter \"yes\" to creat account", password);
                                        char tmp[20];
                                        fflush(stdin);
                                        gets(tmp);
                                        if(strcmp(tmp, "yes") == 0){
                                            struct Middium* middium = getVoidTreapNodeData(&middiumTreap, id);
                                            changeMiddiumPassword(middium, password);
                                            printf("Change the password!\n");
                                            fflush(stdin);
                                            getchar();
                                        }
                                        else{
                                            printf("Not change the password!\n");
                                            fflush(stdin);
                                            getchar();
                                        }
                                    }
                                    else{
                                        break;
                                    }
                                }
                                
                            }
                            else if(op10_ == 3){ //系统
                                static char* op103[] = {"System backup", "System recovery", "Back"};
                                while(true){
                                    int op103_ = UiPrint(op103, 3);
                                    if(op103_ == 0){
                                        printf("Please enter the file name:");
                                        char fileName[100];
                                        fflush(stdin);
                                        gets(fileName);
                                        outputSystem(fileName);
                                        printf("OK");
                                        fflush(stdin);
                                        getchar();
                                    }
                                    else if(op103_ == 1){
                                        printf("Please enter the file name:");
                                        char fileName[100];
                                        fflush(stdin);
                                        gets(fileName);
                                        if(isFileExists(fileName)){
                                            // printf("OK");
                                            // Sleep(3000);
                                            if(strcmp("data.out", fileName) == 0){
                                                printf("This file is the current archive!");
                                                fflush(stdin);
                                                getchar();
                                                continue;
                                            }
                                            // if(isFileExists("data.out")){
                                            //     system("del data.out");
                                            // }
                                            char script[100] = "copy ";
                                            int len = strlen(fileName);
                                            for(int i = 0; i < len; ++i){
                                                script[i + 5] = fileName[i];
                                            }
                                            script[5 + len + 0] = ' ';
                                            script[5 + len + 1] = 'd';
                                            script[5 + len + 2] = 'a';
                                            script[5 + len + 3] = 't';
                                            script[5 + len + 4] = 'a';
                                            script[5 + len + 5] = '.';
                                            script[5 + len + 6] = 'o';
                                            script[5 + len + 7] = 'u';
                                            script[5 + len + 8] = 't';
                                            script[5 + len + 9] = '\0';
                                            // printf("%s\n", script);
                                            // Sleep(3000);
                                            system(script);
                                            printf("OK, restart to open");
                                            fflush(stdin);
                                            getchar();
                                        }
                                        else{
                                            printf("No this file!");
                                            fflush(stdin);
                                            getchar();
                                        }
                                    }
                                    else{
                                        break;
                                    }
                                }
                            }
                            else if(op10_ == 4){ //修改密码
                                char newPassword[20];
                                char pwd[20];
                                printf("please enter your password:");
                                getpwd(pwd, sizeof(pwd) / sizeof(char));
                                if(strcmp(pwd, getAdminPassword())!= 0){
                                    printf("Wrong Password!\n");
                                    fflush(stdin);
                                    getchar();
                                    continue;
                                }
                                while(true){
                                    printf("please enter your new password:");
                                    getpwd(newPassword, sizeof(newPassword) / sizeof(char));
                                    printf("please enter your new password again:");
                                    char tmp[20];
                                    getpwd(tmp, sizeof(tmp) / sizeof(char));
                                    if(strcmp(newPassword, tmp) != 0){
                                        printf("wrong, please enter again\n");
                                    }
                                    else break;
                                }
                                setAdminPassword(newPassword);
                                printf("OK!");
                                fflush(stdin);
                                getchar();
                            }
                            else{
                                quitSystem();
                                return 0;
                            }
                        }
                    }
                }
                else if(op1_ == 1){ //middium
                    char name[20], phoneNumber[20], pwd[20];
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
                    if(enable){ //成功登录 middium
                        struct Middium* middium = (struct Middium*)getVoidTreapNodeData(&middiumTreap, id);
                        printf("ok");
                        static char* op11[] = {"House", "View Houes Infomation", "Rent Houes Infomation", "Change Password", "Exit"};
                        while(true){
                            int op11_ = UiPrint(op11, 5);
                            if(op11_ == 0){ //房源信息查询与统计
                                        struct VoidList val;
                                        initVoidList(&val);
                                        static char* op1010[] = {"Select All", "Select One Place", "Fuzzy Query", "Sort with Area", "Sort with ID", "Sort with Price", "Is a property available?", "Time Range Query", "Back"};
                                        while(true){
                                            int op1010_ = UiPrint(op1010, 9);
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
                                            else if(op1010_ == 2){ //模糊查询
                                                printf("Please Enter the key words:");
                                                fflush(stdin);
                                                gets(keyWord);
                                                struct VoidList tmp = *filterVoidList(&val, &returnTrue);
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
                                            else if(op1010_ == 4){ //id排序
                                                int len = val.cnt;
                                                void** array = VoidListToVoidArray(&val);
                                                sort(array, 0, len - 1, &cmpID);
                                                clearVoidList(&val);
                                                val = *VoidArrayToVoidList(array, len);
                                                free(array);
                                            }
                                            else if(op1010_ == 5){ //价格排序
                                                int len = val.cnt;
                                                void** array = VoidListToVoidArray(&val);
                                                sort(array, 0, len - 1, &cmpprice);
                                                clearVoidList(&val);
                                                val = *VoidArrayToVoidList(array, len);
                                                free(array);
                                            }
                                            else if(op1010_ == 6){ //查询某房源是否可用
                                                int houseID, userID;
                                                printf("Please enter the house ID:"); scanf("%d", &houseID);
                                                if(houseID >= cntHouse){
                                                    printf("Wrong ID!");
                                                    fflush(stdin);
                                                    getchar();
                                                    continue;
                                                }
                                                struct Date begin, end;
                                                printf("Please enter the begin date(yyyy-mm-dd):");scanf("%d-%d-%d", &begin.year, &begin.month, &begin.day);
                                                printf("Please enter the end date(yyyy-mm-dd):");scanf("%d-%d-%d", &end.year, &end.month, &end.day);
                                                if(isLegal(begin) == false || isLegal(end) == false || cmpDate(begin, end) > 0){
                                                    // printf("%d-%d-%d\n", begin.year, begin.month, begin.day);
                                                    // printf("%d-%d-%d\n", end.year, end.month, end.day);
                                                    printf("Wrong date!");
                                                    fflush(stdin);
                                                    getchar();
                                                    continue;
                                                }
                                                struct House* house = getVoidTreapNodeData(&houseTreap, houseID);
                                                if(isAvailable(house, begin, end)){
                                                    printf("available!\n");
                                                }
                                                else{
                                                    printf("not available!\n");
                                                }
                                                fflush(stdin);
                                                getchar();
                                                continue;
                                            }
                                            else if(op1010_ == 7){ //时间区间查询
                                                struct Date begin, end;
                                                printf("Please enter the begin date(yyyy-mm-dd):");scanf("%d-%d-%d", &begin.year, &begin.month, &begin.day);
                                                printf("Please enter the end date(yyyy-mm-dd):");scanf("%d-%d-%d", &end.year, &end.month, &end.day);
                                                if(isLegal(begin) == false || isLegal(end) == false || cmpDate(begin, end) > 0){
                                                    // printf("%d-%d-%d\n", begin.year, begin.month, begin.day);
                                                    // printf("%d-%d-%d\n", end.year, end.month, end.day);
                                                    printf("Wrong date!");
                                                    fflush(stdin);
                                                    getchar();
                                                    continue;
                                                }
                                                int len = val.cnt;
                                                void** array = VoidListToVoidArray(&val);
                                                int sumS = 0, cnt = 0;
                                                int sumT = 0;
                                                for(int i = 0; i < len; ++i){
                                                    if(((struct House*)array[i]) -> state != deleted){
                                                        struct House* house = (struct House*)array[i];
                                                        printHouse(house);
                                                        int t = getRentTime(house, begin, end);
                                                        sumT += t;
                                                        printf(" rent_time: %d\n", t);
                                                        sumS += house -> S;
                                                        ++cnt;
                                                        printf("\n");
                                                    }
                                                }
                                                if(cnt > 0){
                                                    printf("total:%d\n", cnt);
                                                    printf("Average area:%d\n", sumS / cnt);
                                                    printf("Average rent_time:%lf\n", (double)sumT / cnt);
                                                }
                                                free(array);
                                                fflush(stdin);
                                                getchar();
                                                continue;
                                            }
                                            else{
                                                break;
                                            }
                                            int len = val.cnt;
                                            void** array = VoidListToVoidArray(&val);
                                            int sumS = 0, cnt = 0;
                                            for(int i = 0; i < len; ++i){
                                                if(((struct House*)array[i]) -> state != deleted){
                                                    struct House* house = (struct House*)array[i];
                                                    printHouse(house);
                                                    ++cnt;
                                                    sumS += house -> S;
                                                    printf("\n");
                                                }
                                            }
                                            if(cnt > 0){
                                                printf("total:%d\n", cnt);
                                                printf("Average area:%d\n", sumS / cnt);
                                            }
                                            free(array);
                                            fflush(stdin);
                                            getchar();
                                        }
                                        clearVoidList(&val);
                                    }
                            else if(op11_ == 1){
                                struct VoidList val;
                                initVoidList(&val);
                                static char* op1010[] = {"Select my", "Select Time", "Fuzzy Query", "Sort with ID", "Sort with Time", "Finish Infomation", "Back"};
                                while(true){
                                    int op1010_ = UiPrint(op1010, 7);
                                    if(op1010_ == 0){ //选择自己
                                        clearVoidList(&val);
                                        // printf("|%d|", middium -> id);
                                        // Sleep(10000);
                                        struct IntList tmp = *filterIntList(&middium -> viewMsgList, &ireturnTrue);
                                        val = *VmsgIdListToVmsgList(&tmp);
                                        clearIntList(&tmp);
                                        printf("OK!\n");
                                        fflush(stdin);
                                        getchar();
                                    }
                                    else if(op1010_ == 1){ //选择区间
                                        struct Date begin, end;
                                        printf("Please enter the begin date(yyyy-mm-dd):");scanf("%d-%d-%d", &begin.year, &begin.month, &begin.day);
                                        printf("Please enter the end date(yyyy-mm-dd):");scanf("%d-%d-%d", &end.year, &end.month, &end.day);
                                        if(isLegal(begin) == false || isLegal(end) == false || cmpDate(begin, end) > 0){
                                            // printf("%d-%d-%d\n", begin.year, begin.month, begin.day);
                                            // printf("%d-%d-%d\n", end.year, end.month, end.day);
                                            printf("Wrong date!");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        struct VoidList tmp = *filterVoidList(&val, &returnTrue);
                                        __Ldate = begin;
                                        __Rdate = end;
                                        val = *filterVoidList(&tmp, &checkVmsgTime);
                                        clearVoidList(&tmp);
                                        printf("OK!\n");
                                        fflush(stdin);
                                        getchar();
                                    }
                                    else if(op1010_ == 2){ //模糊查询
                                        printf("Please Enter the key words:");
                                        fflush(stdin);
                                        gets(keyWord);
                                        struct VoidList tmp = *filterVoidList(&val, &returnTrue);
                                        val = *filterVoidList(&tmp, &checkVMsgKey);
                                        clearVoidList(&tmp);
                                        printf("OK!\n");
                                        fflush(stdin);
                                        getchar();
                                    }
                                    else if(op1010_ == 3){ //id排序
                                        int len = val.cnt;
                                        void** array = VoidListToVoidArray(&val);
                                        sort(array, 0, len - 1, &cmpViewId);
                                        clearVoidList(&val);
                                        val = *VoidArrayToVoidList(array, len);
                                        free(array);
                                    }
                                    else if(op1010_ == 4){ //时间排序
                                        int len = val.cnt;
                                        void** array = VoidListToVoidArray(&val);
                                        sort(array, 0, len - 1, &cmpViewDate);
                                        clearVoidList(&val);
                                        val = *VoidArrayToVoidList(array, len);
                                        free(array);
                                    }
                                    else if(op1010_ == 5){
                                        printf("Please enter the ID:");
                                        int id;
                                        scanf("%d", &id);
                                        if(id >= cntViewMsg){
                                            printf("Wrong ID!\n");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        else{
                                            struct ViewHouseMsg* msg = getVoidTreapNodeData(&vMsgTreap, id);
                                            if(msg -> middiumId != middium -> id){
                                                printf("Wrong ID!\n");
                                                fflush(stdin);
                                                getchar();
                                                continue;
                                            }
                                            finishViewHouse(msg);
                                            printf("OK\n");
                                            getchar();
                                        }
                                    }
                                    else{
                                        break;
                                    }
                                    int len = val.cnt;
                                    void** array = VoidListToVoidArray(&val);
                                    for(int i = 0; i < len; ++i){
                                        printVMsg((struct ViewHouseMsg*)array[i]);
                                        printf("\n");
                                    }
                                    printf("cnt: %d\n", val.cnt);
                                    free(array);
                                    fflush(stdin);
                                    getchar();
                                }
                                clearVoidList(&val);
                            }
                            else if(op11_ == 2){ //租房信息
                                static char* op111[] = {"Show Infomation", "Add Infomation", "Back"};
                                while(true){
                                    int op110_ = UiPrint(op111, 3);
                                    if(op110_ == 0){ //打印信息
                                        struct VoidList val;
                                        struct IntList tmp = *filterIntList(&middium -> rentMsgList, &ireturnTrue);
                                        val = *RmsgIdListToRmsgList(&tmp);
                                        clearIntList(&tmp);
                                        int len = val.cnt;
                                        void** array = VoidListToVoidArray(&val);
                                        for(int i = 0; i < len; ++i){
                                            printRMsg((struct RentHouseMsg*)array[i]);
                                            printf("\n");
                                        }
                                        free(array);
                                        fflush(stdin);
                                        getchar();
                                    }
                                    else if(op110_ == 1){
                                        int houseID, userID;
                                        printf("Please enter the house ID:"); scanf("%d", &houseID);
                                        if(houseID >= cntHouse){
                                            printf("Wrong ID!");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        printf("Please enter the user ID:"); scanf("%d", &userID);
                                        if(userID >= cntUser){
                                            printf("Wrong ID!");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        struct Date begin, end;
                                        printf("Please enter the begin date(yyyy-mm-dd):");scanf("%d-%d-%d", &begin.year, &begin.month, &begin.day);
                                        printf("Please enter the end date(yyyy-mm-dd):");scanf("%d-%d-%d", &end.year, &end.month, &end.day);
                                        if(isLegal(begin) == false || isLegal(end) == false || cmpDate(begin, end) > 0){
                                            printf("Wrond date!");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        struct House* house = getVoidTreapNodeData(&houseTreap, houseID);
                                        struct User* user = getVoidTreapNodeData(&userTreap, userID);
                                        if(isAvailable(house, begin, end) == false){
                                            printf("Not availiable!");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        rentHouse(user, house, middium, begin, end);
                                        printf("OK!");
                                        fflush(stdin);
                                        getchar();
                                    }
                                    else{
                                        break;
                                    }
                                }
                            }
                            else if(op11_ == 3){ //修改密码
                                char newPassword[20];
                                char pwd[20];
                                printf("please enter your password:");
                                getpwd(pwd, sizeof(pwd) / sizeof(char));
                                if(strcmp(pwd, middium -> password)!= 0){
                                    printf("Wrong Password!\n");
                                    fflush(stdin);
                                    getchar();
                                    continue;
                                }
                                while(true){
                                    printf("please enter your new password:");
                                    getpwd(newPassword, sizeof(newPassword) / sizeof(char));
                                    printf("please enter your new password again:");
                                    char tmp[20];
                                    getpwd(tmp, sizeof(tmp) / sizeof(char));
                                    if(strcmp(newPassword, tmp) != 0){
                                        printf("wrong, please enter again\n");
                                    }
                                    else break;
                                }
                                changeMiddiumPassword(middium, newPassword);
                                printf("OK!");
                                fflush(stdin);
                                getchar();
                            }
                            else{
                                quitSystem();
                                return 0;
                            }
                        }
                    }
                }
                else if(op1_ == 2){ //user
                    char name[20], phoneNumber[20], pwd[20];
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
                        struct User* user = (struct User*)getVoidTreapNodeData(&userTreap, id);
                        static char* op12[] = {"House", "Middium", "View House Infomathon", "Rent House Infomathon", "Change Password", "Exit"};
                        while(true){
                            int op12_ = UiPrint(op12, 6);
                            if(op12_ == 0){ //房源信息查询与统计
                                struct VoidList val;
                                initVoidList(&val);
                                static char* op1010[] = {"Select All", "Select One Place", "Fuzzy Query", "Sort with Area", "Sort with ID", "Sort with Price", "Is a property available?", "Back"};
                                while(true){
                                    int op1010_ = UiPrint(op1010, 8);
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
                                    else if(op1010_ == 2){ //模糊查询
                                        printf("Please Enter the key words:");
                                        fflush(stdin);
                                        gets(keyWord);
                                        struct VoidList tmp = *filterVoidList(&val, &returnTrue);
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
                                    else if(op1010_ == 4){ //id排序
                                        int len = val.cnt;
                                        void** array = VoidListToVoidArray(&val);
                                        sort(array, 0, len - 1, &cmpID);
                                        clearVoidList(&val);
                                        val = *VoidArrayToVoidList(array, len);
                                        free(array);
                                    }
                                    else if(op1010_ == 5){ //价格排序
                                        int len = val.cnt;
                                        void** array = VoidListToVoidArray(&val);
                                        sort(array, 0, len - 1, &cmpprice);
                                        clearVoidList(&val);
                                        val = *VoidArrayToVoidList(array, len);
                                        free(array);
                                    }
                                    else if(op1010_ == 6){ //查询某房源是否可用
                                        int houseID, userID;
                                        printf("Please enter the house ID:"); scanf("%d", &houseID);
                                        if(houseID >= cntHouse){
                                            printf("Wrong ID!");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        struct Date begin, end;
                                        printf("Please enter the begin date(yyyy-mm-dd):");scanf("%d-%d-%d", &begin.year, &begin.month, &begin.day);
                                        printf("Please enter the end date(yyyy-mm-dd):");scanf("%d-%d-%d", &end.year, &end.month, &end.day);
                                        if(isLegal(begin) == false || isLegal(end) == false || cmpDate(begin, end) > 0){
                                            // printf("%d-%d-%d\n", begin.year, begin.month, begin.day);
                                            // printf("%d-%d-%d\n", end.year, end.month, end.day);
                                            printf("Wrong date!");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        struct House* house = getVoidTreapNodeData(&houseTreap, houseID);
                                        if(isAvailable(house, begin, end)){
                                            printf("available!\n");
                                        }
                                        else{
                                            printf("not available!\n");
                                        }
                                        fflush(stdin);
                                        getchar();
                                        continue;
                                    }
                                    else{
                                        break;
                                    }
                                    int len = val.cnt;
                                    void** array = VoidListToVoidArray(&val);
                                    int sumS = 0, cnt = 0;
                                    for(int i = 0; i < len; ++i){
                                        if(((struct House*)array[i]) -> state != deleted){
                                            struct House* house = (struct House*)array[i];
                                            printHouse(house);
                                            ++cnt;
                                            sumS += house -> S;
                                            printf("\n");
                                        }
                                    }
                                    if(cnt > 0){
                                        printf("total:%d\n", cnt);
                                        printf("Average area:%d\n", sumS / cnt);
                                    }
                                    free(array);
                                    fflush(stdin);
                                    getchar();
                                }
                                clearVoidList(&val);
                            }
                            else if(op12_ == 1){ //中介信息查询与统计
                                struct VoidList val;
                                initVoidList(&val);
                                static char* op1010[] = {"Select All", "Fuzzy Query", "Sort with ID", "Sort with Turnover", "Time Range Query", "Back"};
                                while(true){
                                    int op1010_ = UiPrint(op1010, 6);
                                    if(op1010_ == 0){ //全选
                                        clearVoidList(&val);
                                        val = *filterVoidList(&middiumList, &returnTrue);
                                        printf("OK!\n");
                                        fflush(stdin);
                                        getchar();
                                    }
                                    else if(op1010_ == 1){ //模糊查询
                                        printf("Please Enter the key words:");
                                        fflush(stdin);
                                        gets(keyWord);
                                        struct VoidList tmp = *filterVoidList(&val, &returnTrue);
                                        val = *filterVoidList(&tmp, &checkMiddiumKey);
                                        clearVoidList(&tmp);
                                        printf("OK!\n");
                                        fflush(stdin);
                                        getchar();
                                    }
                                    else if(op1010_ == 2){ //id排序
                                        int len = val.cnt;
                                        void** array = VoidListToVoidArray(&val);
                                        sort(array, 0, len - 1, &cmpMiddiumId);
                                        clearVoidList(&val);
                                        val = *VoidArrayToVoidList(array, len);
                                        free(array);
                                    }
                                    else if(op1010_ == 3){ //成交量排序
                                        int len = val.cnt;
                                        void** array = VoidListToVoidArray(&val);
                                        sort(array, 0, len - 1, &cmpMiddiumRentRatio);
                                        clearVoidList(&val);
                                        val = *VoidArrayToVoidList(array, len);
                                        free(array);
                                    }
                                    else if(op1010_ == 4){ //区间查询
                                        struct Date begin, end;
                                        printf("Please enter the begin date(yyyy-mm-dd):");scanf("%d-%d-%d", &begin.year, &begin.month, &begin.day);
                                        printf("Please enter the end date(yyyy-mm-dd):");scanf("%d-%d-%d", &end.year, &end.month, &end.day);
                                        if(isLegal(begin) == false || isLegal(end) == false || cmpDate(begin, end) > 0){
                                            // printf("%d-%d-%d\n", begin.year, begin.month, begin.day);
                                            // printf("%d-%d-%d\n", end.year, end.month, end.day);
                                            printf("Wrong date!");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        int len = val.cnt;
                                        void** array = VoidListToVoidArray(&val);
                                        int cnt = 0;
                                        int sumT = 0, cntR = 0;
                                        for(int i = 0; i < len; ++i){
                                            struct Middium* middium = (struct Middium*)array[i];
                                            printMiddium(middium);
                                            int t = getMiddiumRentTime(middium, begin, end);
                                            sumT += t;
                                            if(t) ++cntR;
                                            printf(" rent_time: %d\n", t);
                                            ++cnt;
                                        }
                                        if(cnt > 0){
                                            printf("total:%d\n", cnt);
                                            printf("Average rent_time:%lf\n", (double)sumT / cnt);
                                        }
                                        free(array);
                                        fflush(stdin);
                                        getchar();
                                        continue;
                                    }
                                    else{
                                        break;
                                    }
                                    int len = val.cnt;
                                    void** array = VoidListToVoidArray(&val);
                                    for(int i = 0; i < len; ++i){
                                        printMiddium((struct Middium*)array[i]);
                                        printf("\n");
                                    }
                                    free(array);
                                    fflush(stdin);
                                    getchar();
                                }
                                clearVoidList(&val);
                            }
                            else if(op12_ == 2){  //看房信息与统计
                                struct VoidList val;
                                initVoidList(&val);
                                static char* op1010[] = {"Select Me", "Select Time", "Fuzzy Query", "Sort with ID", "Sort with Time", "Add Appointment", "Cancel Appointment", "Back"};
                                while(true){
                                    int op1010_ = UiPrint(op1010, 8);
                                    if(op1010_ == 0){ //选择某个用户
                                        clearVoidList(&val);
                                        struct IntList tmp = *filterIntList(&user -> viewMsgList, &ireturnTrue);
                                        val = *VmsgIdListToVmsgList(&tmp);
                                        clearIntList(&tmp);
                                        printf("OK!\n");
                                        fflush(stdin);
                                        getchar();
                                    }
                                    else if(op1010_ == 1){ //选择区间
                                        struct Date begin, end;
                                        printf("Please enter the begin date(yyyy-mm-dd):");scanf("%d-%d-%d", &begin.year, &begin.month, &begin.day);
                                        printf("Please enter the end date(yyyy-mm-dd):");scanf("%d-%d-%d", &end.year, &end.month, &end.day);
                                        if(isLegal(begin) == false || isLegal(end) == false || cmpDate(begin, end) > 0){
                                            // printf("%d-%d-%d\n", begin.year, begin.month, begin.day);
                                            // printf("%d-%d-%d\n", end.year, end.month, end.day);
                                            printf("Wrong date!");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        struct VoidList tmp = *filterVoidList(&val, &returnTrue);
                                        __Ldate = begin;
                                        __Rdate = end;
                                        val = *filterVoidList(&tmp, &checkVmsgTime);
                                        clearVoidList(&tmp);
                                        printf("OK!\n");
                                        fflush(stdin);
                                        getchar();
                                    }
                                    else if(op1010_ == 2){ //模糊查询
                                        printf("Please Enter the key words:");
                                        fflush(stdin);
                                        gets(keyWord);
                                        struct VoidList tmp = *filterVoidList(&val, &returnTrue);
                                        val = *filterVoidList(&tmp, &checkVMsgKey);
                                        clearVoidList(&tmp);
                                        printf("OK!\n");
                                        fflush(stdin);
                                        getchar();
                                    }
                                    else if(op1010_ == 3){ //id排序
                                        int len = val.cnt;
                                        void** array = VoidListToVoidArray(&val);
                                        sort(array, 0, len - 1, &cmpViewId);
                                        clearVoidList(&val);
                                        val = *VoidArrayToVoidList(array, len);
                                        free(array);
                                    }
                                    else if(op1010_ == 4){ //时间排序
                                        int len = val.cnt;
                                        void** array = VoidListToVoidArray(&val);
                                        sort(array, 0, len - 1, &cmpViewDate);
                                        clearVoidList(&val);
                                        val = *VoidArrayToVoidList(array, len);
                                        free(array);
                                    }
                                    else if(op1010_ == 5){ //添加看房
                                        int houseID, middiumId;
                                        printf("Please enter the house ID:"); scanf("%d", &houseID);
                                        if(houseID >= cntHouse){
                                            printf("Wrong ID!");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        printf("Please enter the agency ID, -1 for Uncertain:"); scanf("%d", &middiumId);
                                        if(middiumId >= cntMiddium){
                                            printf("Wrong ID!");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        struct Date t;
                                        printf("Please enter the begin date(yyyy-mm-dd):");scanf("%d-%d-%d", &t.year, &t.month, &t.day);
                                        if(isLegal(t) == false){
                                            printf("Wrong date!");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        struct House* house = getVoidTreapNodeData(&houseTreap, houseID);
                                        struct Middium* middium = middiumId == -1 ? NULL : getVoidTreapNodeData(&middiumTreap, middiumId);
                                        int res = viewHouse(user, house, middium, t) -> id;
                                        printf("OK! your view house id = %d\n", res);
                                        fflush(stdin);
                                        getchar();
                                    }
                                    else if(op1010_ == 6){ //取消预约
                                        int msgId;
                                        printf("Please enter the msg ID:"); scanf("%d", &msgId);
                                        if(msgId >= cntViewMsg || msgId < 0){
                                            printf("Wrong ID!");
                                            fflush(stdin);
                                            getchar();
                                            continue;
                                        }
                                        struct ViewHouseMsg* msg = getVoidTreapNodeData(&vMsgTreap, msgId);
                                        cancelViewHouse(msg);
                                        printf("OK!");
                                        fflush(stdin);
                                        getchar();
                                    }
                                    else{
                                        break;
                                    }
                                    int len = val.cnt;
                                    void** array = VoidListToVoidArray(&val);
                                    for(int i = 0; i < len; ++i){
                                        printVMsg((struct ViewHouseMsg*)array[i]);
                                        printf("\n");
                                    }
                                    printf("cnt: %d\n", val.cnt);
                                    free(array);
                                    fflush(stdin);
                                    getchar();
                                }
                                clearVoidList(&val);
                            }
                            else if(op12_ == 3){
                                struct VoidList val;
                                struct IntList tmp = *filterIntList(&user -> viewMsgList, &ireturnTrue);
                                val = *RmsgIdListToRmsgList(&tmp);
                                clearIntList(&tmp);
                                int len = val.cnt;
                                void** array = VoidListToVoidArray(&val);
                                for(int i = 0; i < len; ++i){
                                    printRMsg((struct RentHouseMsg*)array[i]);
                                    printf("\n");
                                }
                                free(array);
                                fflush(stdin);
                                getchar();
                            }
                            else if(op12_ == 4){
                                char newPassword[20];
                                char pwd[20];
                                printf("please enter your password:");
                                getpwd(pwd, sizeof(pwd) / sizeof(char));
                                if(strcmp(pwd, user -> password)!= 0){
                                    printf("Wrong Password!\n");
                                    fflush(stdin);
                                    getchar();
                                    continue;
                                }
                                while(true){
                                    printf("please enter your new password:");
                                    getpwd(newPassword, sizeof(newPassword) / sizeof(char));
                                    printf("please enter your new password again:");
                                    char tmp[20];
                                    getpwd(tmp, sizeof(tmp) / sizeof(char));
                                    if(strcmp(newPassword, tmp) != 0){
                                        printf("wrong, please enter again\n");
                                    }
                                    else break;
                                }
                                changeUserPassword(user, newPassword);
                                printf("OK!");
                                fflush(stdin);
                                getchar();
                            }
                            else{
                                quitSystem();
                                return 0;
                            }
                        }
                    }
                }
                else{ //back
                    break;
                }
            }
        }
        else if(op_ == 2){ //rigister
            char name[20], phoneNumber[20], pwd[20];
            while(true){
                printf("please enter your name(English):");
                fflush(stdin);
                gets(name);
                printf("please enter your phone number:");
                fflush(stdin);
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
                fflush(stdin);
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
    return 0;
}