#ifndef _VIEW_HOUSE_MESSAGE
#define _VIEW_HOUSE_MESSAGE

#include "typedefine.h"
#include "time.h"
#include "date.h"

enum ViewHouseMsgState{
    cnacel, success, finish
};
struct ViewHouseMsg{
    int id;
    struct House * house;
    struct User * user;
    struct Middium * middium;
    struct Date reqTime;
    enum ViewHouseMsgState state;
};

struct VHMListNode{
    struct ViewHouseMsg * data;
    struct VHMListNode * nxt;
};

struct VHMList{
    struct VHMListNode head;
    int cnt;
};

#endif