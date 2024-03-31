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

struct VoidTreapNode * newVoidTreapNode(void * data, int id){
    struct VoidTreapNode * node = (struct VoidTreapNode *)malloc(sizeof(struct VoidTreapNode));
    node -> data = data;
    node -> id = id;
    node -> rnd = rand();
    node -> l = node -> r = NULL;
    node -> siz = 1;
    return node;
}

void initVoidTreap(struct VoidTreap * treap){
    treap -> root = NULL;
};

void pushupVoidTreapNode(struct VoidTreapNode * node){
    node -> siz = 1;
    if(node -> l) node -> siz += node -> l -> siz;
    if(node -> r) node -> siz += node -> r -> siz;
    return;
}

struct VoidTreapNode * mergeVoidTreap(struct VoidTreapNode * x, struct VoidTreapNode * y){
    if(!x || !y) return x == NULL ? y : x;
    if(x -> id > y -> id){
        struct VoidTreapNode * tmp = x;
        x = y;
        y = tmp;
    }
    if(x -> rnd < y -> rnd){
        x -> r = mergeVoidTreap(x -> r, y);
        pushupVoidTreapNode(x);
        return x;
    }
    else{
        y -> l = mergeVoidTreap(x, y -> l);
        pushupVoidTreapNode(y);
        return y;
    }
}

void splitVoidTreap1(struct VoidTreapNode * p, int id, struct VoidTreapNode * x, struct VoidTreapNode *y){
    if(!p){
        x = y = NULL;
        return;
    }
    if(p -> id < id){
        x = p;
        splitVoidTreap1(p -> r, id, x -> r, y);
        return;
    }
    else{
        y = p;
        splitVoidTreap1(p -> l, id, x, y -> l);
        return;
    }
}

void addVoidTreapNode(struct VoidTreap * treap, void * data, int id){
    struct VoidTreapNode * node = newVoidTreapNode(data, id);
    struct VoidTreapNode *x, *y;
    splitVoidTreap1(treap -> root, id, x, y);
    treap -> root = mergeVoidTreap(mergeVoidTreap(x, node), y);
    return;
}

void * getVoidTreapNodeData(struct VoidTreap * treap, int id){
    struct VoidTreapNode *x, *y, *z;
    splitVoidTreap1(treap -> root, id - 1, x, y);
    splitVoidTreap1(y, id, y, z);
    void * ans = NULL;
    if(y) ans = y -> data;
    treap -> root = mergeVoidTreap(mergeVoidTreap(x, y), z);
    return ans;
}

#endif