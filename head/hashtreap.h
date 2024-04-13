#ifndef _HASHTREAP
#define _HASHTREAP
#include "typedefine.h"
#include "hash.h"
#include <stdlib.h>
// void*类型treap节点
//这个树可能
struct HashTreapNode{
    int rnd;
    struct HashValue id;
    void * data;
    struct HashTreapNode *l, *r;
    int siz;
};
// void*类型treap
struct HashTreap{
    struct HashTreapNode * root;
};

struct HashTreapNode * newHashTreapNode(void * data, struct HashValue id);

void initHashTreap(struct HashTreap * treap);

void pushupHashTreapNode(struct HashTreapNode * node);

struct HashTreapNode * mergeHashTreap(struct HashTreapNode * x, struct HashTreapNode * y);

void splitHashTreap1(struct HashTreapNode * p, struct HashValue id, struct HashTreapNode * x, struct HashTreapNode *y);

// 添加节点 
void addHashTreapNode(struct HashTreap * treap, void * data, struct HashTreap id);

// 查询id对应的指针数据
void * getHashTreapNodeData(struct HashTreap * treap, struct HashTreap id);

#endif