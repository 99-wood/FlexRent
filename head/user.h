#ifndef _USER
#define _USER

#include "typedefine.h"
#include "viewhousemsg.h"
#include "renthousemsg.h"
#include "intlist.h"

struct User{
    char * name;
    int id;
    char * password;
    char * phoneNumber;
    struct IntList viewMsgList;
    struct IntList rentMsgList;
};

void modifyPassword(struct User * user, char * password);
#endif