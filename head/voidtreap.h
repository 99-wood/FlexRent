#ifndef _VOIDTREAP
#define _VOIDTREAP

#include "typedefine.h"
#include <stdlib.h>
// void*类型treap节点
struct VoidTreapNode{
    int id;
    int rnd;
    void * data;
    struct VoidTreapNode *l, *r;
    int siz;
};
// void*类型treap
struct VoidTreap{
    struct VoidTreapNode * root;
};

struct VoidTreapNode * newVoidTreapNode(void * data, int id);

void initVoidTreap(struct VoidTreap * treap);

void pushupVoidTreapNode(struct VoidTreapNode * node);

struct VoidTreapNode * mergeVoidTreap(struct VoidTreapNode * x, struct VoidTreapNode * y);

void splitVoidTreap1(struct VoidTreapNode * p, int id, struct VoidTreapNode * x, struct VoidTreapNode *y);

// 添加节点 
void addVoidTreapNode(struct VoidTreap * treap, void * data, int id);

// 查询id对应的指针数据
void * getVoidTreapNodeData(struct VoidTreap * treap, int id);

#endif