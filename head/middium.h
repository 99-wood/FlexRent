#ifndef _MIDDIUM
#define _MIDDIUM
#include "viewhousemsg.h"
#include "renthousemsg.h"
#include "intlist.h"
#include "voidlist.h"
#include "voidtreap.h"
struct VoidList middiumList;
struct VoidTreap middiumTreap;
int cntMiddium;
struct Middium{
    char * name;
    int id;
    char* password;
    char* phoneNumber;
    struct IntList viewMsgList;
    struct IntList rentMsgList;
};
#endif