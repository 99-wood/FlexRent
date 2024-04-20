#ifndef _RENT_HOUSE_MSG
#define _RENT_HOUSE_MSG

#include "typedefine.h"
#include "date.h"
#include "voidlist.h"
#include "voidtreap.h"

struct VoidList rMsgList;
struct VoidTreap rMsgTreap;
int cntRentMsg;

struct RentHouseMsg{
    int id;
    struct Date begin, end;
    int houseId;
    int userId;
    int middiumId;
};

// struct RHMListNode{
//     struct RentHouseMsg * data;
//     struct RHMListNode * nxt;
// };

// struct RHMList{
//     struct RHMListNode head;
//     int cnt;
// };
#endif