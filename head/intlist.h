#ifndef _INT_LIST
#define _INT_LIST

#include <stdbool.h>
#include "typedefine.h"

// int 类型单向链表节点
struct IntListNode{
    int value; //值
    struct IntListNode * nxt; // 下一个节点地址
};

// int 类型单向链表
struct IntList{
    struct IntListNode * head; // 首节点
    int cnt; //节点个数
};

// 链表初始化
void initIntList(struct IntList * list);

// 获得元素个数并返回
int getIntListCnt(struct IntList * list);

// 查询是否出现某个值
bool findIntListValue(struct IntList * list, int w);

// 将链表转为 int 数组，返回数组首地址
int * IntListToIntArray(struct IntList * list);

// 将 int 数组转为链表，返回链表
struct IntList * IntArrayToIntList(int * array, int len);

// 链表头部插入节点
void addIntListHead(struct IntList * list, int w);

// 链表尾部插入节点
void addIntListTail(struct IntList * list, int w);

// 在特定节点后插入节点
// void addIntListNode(struct IntList * list, struct IntListNode * node, int w);

// 删除链表头部节点
void delIntListHead(struct IntList * list);

// 删除链表尾部节点
void delIntListTail(struct IntList * list);

// 删除特定节点
// void delIntListNode(struct IntList * list, struct IntListNode * node);

// 筛选满足条件的节点
struct IntList * filterIntList(struct IntList * list, bool (*check)(int));

void clearIntList(struct IntList * list);
#endif