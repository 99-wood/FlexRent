#include "intlist.h"
#include <stdio.h>
#include <stdlib.h>

void initIntList(struct IntList * list){
    list -> head = NULL;
    list -> cnt = 0;
}

int getIntListCnt(struct IntList * list){
    return list -> cnt;
}

bool findIntListValue(struct IntList * list, int w){
    struct IntListNode * p = list -> head;
    while(p != NULL){
        if(p -> value == w){
            return true;
        }
        p = p -> nxt;
    }
    return false;
}

int * IntListToIntArray(struct IntList * list){
    int * intArray = (int *)malloc(sizeof(int) * list -> cnt);
    struct IntListNode * p = list -> head; 
    for(int i = 0; p != NULL; p = p -> nxt, ++i){
        intArray[i] = p -> value;
    }
    return intArray;
}

struct IntList * IntArrayToIntList(int * array, int len){
    struct IntList * list = (struct IntList *)malloc(sizeof(struct IntList));
    initIntList(list);
    if(len == 0) return list;
    struct IntListNode * p = (struct IntListNode *)malloc(sizeof(struct IntListNode));
    list -> head = p;
    list -> cnt = len;
    p -> nxt = NULL;
    p -> value = array[0];
    for(int i = 1; i < len; ++i){
        p -> nxt = (struct IntListNode *)malloc(sizeof(struct IntListNode));
        p = p -> nxt;
        p -> value = array[i];
        p -> nxt = NULL;
    }
    return list;
}

void addIntListHead(struct IntList * list, int w){
    struct IntListNode * p = (struct IntListNode *)malloc(sizeof(struct IntListNode));
    p -> nxt = list -> head;
    p -> value = w;
    list -> head = p;
    ++list -> cnt;
    return; 
}

void addIntListTail(struct IntList * list, int w){
    struct IntListNode * tmp = (struct IntListNode*)malloc(sizeof(struct IntListNode));
    tmp -> nxt = NULL;
    tmp -> value = w;
    if(list -> head == NULL){
        list -> head = tmp;
        ++list -> cnt;
        return;
    }
    struct IntListNode * p = list -> head;
    while(p -> nxt != NULL) p = p -> nxt;
    p -> nxt = tmp;
    ++list -> cnt;
    return; 
}

void delIntListHead(struct IntList * list){
    if(list -> head == NULL) return;
    struct IntListNode * head = list -> head;
    list -> head = head -> nxt;
    --list -> cnt;
    free(head);
    return;
}

void delIntListTail(struct IntList * list){
    if(list -> head == NULL) return;
    if(list -> cnt == 1){
        free(list -> head);
        list -> head = NULL;
        --list -> cnt;
        return;
    }
    struct IntListNode * p = list -> head;
    while(p -> nxt -> nxt != NULL) p = p -> nxt;
    free(p -> nxt);
    p -> nxt = NULL;
    --list -> cnt;
    return;
}

struct IntList * filterIntList(struct IntList * list, bool (* check)(int)){
    int * array = IntListToIntArray(list);
    int cnt = 0;
    for(int i = 0; i < list -> cnt; ++i){
        if(check(array[i])){
            array[cnt++] = array[i];
        }
    }
    struct IntList * ans = IntArrayToIntList(array, cnt);
    free(array);
    return ans;
}


void clearIntList(struct IntList * list){
    for(struct IntListNode * p = list -> head; p != NULL;){
        struct IntListNode * nxt = p -> nxt;
        free(p);
        p = nxt;
    }
    list -> head = NULL;
    list -> cnt = 0;
    return;
}