#ifndef _VIEW_HOUSE_MESSAGE
#define _VIEW_HOUSE_MESSAGE

#include "typedefine.h"
#include "time.h"
#include "date.h"
#include "voidlist.h"
#include "voidtreap.h"

enum ViewHouseMsgState{
    cancel, normal, finish
};
int cntViewMsg;
struct VoidList vMsgList;
struct VoidTreap vMsgTreap;
struct ViewHouseMsg{
    int id;
    struct Date reqTime;
    enum ViewHouseMsgState state;
    int houseId;
    int userId;
    int middiumId;
};

// struct VHMListNode{
//     struct ViewHouseMsg * data;
//     struct VHMListNode * nxt;
// };

// struct VHMList{
//     struct VHMListNode head;
//     int cnt;
// };

#endif