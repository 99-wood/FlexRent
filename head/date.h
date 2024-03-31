#ifndef _DATE
#define _DATE

#include "typedefine.h"
// 日期结构体
struct Date{
    int year, month, day;
};
//修改日期,返回假则格式错误。
bool SetDate(struct Date* date,int y,int m, int d);
// 比较两个日期的大小，大于返回大于 0 的数，小于返回小于 0 的数，等于返回 0
int cmpDate(struct Date a, struct Date b);
// 计算日期相差天数，b-a。不包含末端
int subDate(struct Date a, struct Date b);
//判断闰年
bool LeapJudge(int year);
#endif