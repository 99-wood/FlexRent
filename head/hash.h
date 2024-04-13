#ifndef _HASH_HASH_HASH
#define _HASH_HASH_HASH

#include <stdio.h>
#include <string.h> 
#define M1 1000000007 
#define M2 1000000009

struct HashValue{
	int hash1;
	int hash2;
};
//哈希值生成
//地名以字符串的形式被处理成哈希值，也是"它"---被处理对象，的 id
//此哈希值对应的是该地“类”的指针
struct HashValue makeHashValue(char* c);
//哈希值大小比较,
int cmpHashValue(struct HashValue h1, struct HashValue h2);

#endif