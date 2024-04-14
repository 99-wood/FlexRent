#ifndef _RENT_HOUSE_MSG
#define _RENT_HOUSE_MSG

#include "typedefine.h"
#include "date.h"


struct RentHouseMsg{
    int id;
    struct Date begin, end;
    struct House * house;
    struct User * user;
    struct Middium * middium;
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