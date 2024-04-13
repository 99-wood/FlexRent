#include "hashtreap.h"

struct HashTreapNode * newHashTreapNode(void * data, struct HashValue id){
    struct HashTreapNode * node = (struct HashTreapNode *)malloc(sizeof(struct HashTreapNode));
    node -> data = data;
    node -> id = id;
    node -> rnd = rand();
    node -> l = node -> r = NULL;
    node -> siz = 1;
    return node;
}

void initHashTreap(struct HashTreap * treap){
    treap -> root = NULL;
};

void pushupHashTreapNode(struct HashTreapNode * node){
    node -> siz = 1;
    if(node -> l) node -> siz += node -> l -> siz;
    if(node -> r) node -> siz += node -> r -> siz;
    return;
}

struct HashTreapNode * mergeHashTreap(struct HashTreapNode * x, struct HashTreapNode * y){
    if(!x || !y) return x == NULL ? y : x;
    if(cmpHashValue(x -> id, y -> id)){
        struct HashTreapNode * tmp = x;
        x = y;
        y = tmp;
    }
    if(x -> rnd < y -> rnd){
        x -> r = mergeHashTreap(x -> r, y);
        pushupHashTreapNode(x);
        return x;
    }
    else{
        y -> l = mergeHashTreap(x, y -> l);
        pushupHashTreapNode(y);
        return y;
    }
}

void splitHashTreap1(struct HashTreapNode * p, struct HashValue id, struct HashTreapNode * x, struct HashTreapNode *y){
    if(!p){
        x = y = NULL;
        return;
    }
    if(cmpHashValue(id, p -> id) ){
        x = p;
        splitHashTreap1(p -> r, id, x -> r, y);
        return;
    }
    else{
        y = p;
        splitHashTreap1(p -> l, id, x, y -> l);
        return;
    }
}

void addHashTreapNode(struct HashTreap * treap, void * data, struct HashValue id){
    struct HashTreapNode * node = newHashTreapNode(data, id);
    struct HashTreapNode *x, *y;
    splitHashTreap1(treap -> root, id, x, y);
    treap -> root = mergeHashTreap(mergeHashTreap(x, node), y);
    return;
}

void * getHashTreapNodeData(struct HashTreap * treap, struct HashValue id){
    struct HashTreapNode *x, *y, *z;
    splitHashTreap1(treap -> root, preHashValue(id), x, y);
    splitHashTreap1(y, id, y, z);
    void * ans = NULL;
    if(y) ans = y -> data;
    treap -> root = mergeHashTreap(mergeHashTreap(x, y), z);
    return ans;
}