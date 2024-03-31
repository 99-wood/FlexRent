#ifndef _USER
#define _USER

#include "typedefine.h"
#include "viewhousemsg.h"
#include "renthousemsg.h"
#include "intlist.h"
//登陆
bool UserLoad();
//用户改电话
bool PhoneChange();
//用户改密码
bool UserPassCha();
//用户新增预约
bool AddRes();
//用户删除预约
bool DeleteRes();
//用户修改预约
bool ChangeRes();
//用户预约信息查询
bool QueryRes();
//用户租房信息查询
bool QueryRent();
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