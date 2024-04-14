#ifndef _MIDDIUM
#define _MIDDIUM
#include "viewhousemsg.h"
#include "renthousemsg.h"
#include "intlist.h"
struct Middium{
    char * name;
    int id;
    char* password;
    char* phoneNumber;
    struct IntList viewMsgList;
    struct IntList rentMsgList;
};
#endif