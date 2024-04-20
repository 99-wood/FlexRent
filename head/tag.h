#ifndef _TAG
#define _TAG

#include "typedefine.h"
#include "string.h"

struct Tag{
    int id;
    char * name;
    int cnt;
};
#define MAX_TAG_CNT 120
struct Tag tag[MAX_TAG_CNT];
int tagCnt;

int addTag(char str[]){
    if(tagCnt >= MAX_TAG_CNT) return 0;
    tag[tagCnt].name = (char*)malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(tag[tagCnt].name, str);
    tag[tagCnt].id = tagCnt;
    tag[tagCnt].cnt = 0;
    ++tagCnt;
    return 0;
}
int findTag(char str[]){
    for(int i = 0; i < tagCnt; ++i){
        if(strcmp(tag[i].name, str) == 0) return i;
    }
    return -1;
}

// struct TagListNode{
//     struct Tag * data;
//     struct TagListNode * nxt;
// };

// struct TagList{
//     struct TagListNode head;
//     int cnt;
// };
#endif