#ifndef _VOID_LIST
#define _VOID_LIST

#include "typedefine.h"
// void* 类型单向链表节点
struct VoidListNode{
    void* value; //值
    struct VoidListNode * nxt; // 下一个节点地址
};

// void* 类型单向链表
struct VoidList{
    struct VoidListNode * head; // 首节点
    int cnt; //节点个数
};

// 链表初始化
void initVoidList(struct VoidList * list);

// 获得元素个数并返回
int getVoidListCnt(struct VoidList * list);

// 查询是否出现某个值
bool findVoidListValue(struct VoidList * list, int w);

// 将链表转为 void* 数组，返回数组首地址
void** VoidListToVoidArray(struct VoidList * list);

// 将 int* 数组转为链表，返回链表
struct VoidList * VoidArrayToVoidList(void* array[], int len);

// 链表头部插入节点
void addVoidListHead(struct VoidList * list, void* w);

// 链表尾部插入节点
void addVoidListTail(struct VoidList * list, void* w);

// 在特定节点后插入节点
// void addVoidListNode(struct VoidList * list, struct VoidListNode * node, int w);

// 删除链表头部节点
void delVoidListHead(struct VoidList * list);

// 删除链表尾部节点
void delVoidListTail(struct VoidList * list);

// 删除特定节点
// void delVoidListNode(struct VoidList * list, struct VoidListNode * node);

// 筛选满足条件的节点
struct VoidList * filterVoidList(struct VoidList * list, bool (*check)(void*));

#endif