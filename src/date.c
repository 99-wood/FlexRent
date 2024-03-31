#include"date.h"
//非闰年的月份与天数的映射
int MonReDay[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int DaysAccum[13]={0,0,31,59,90,120,151,181,212,243,273,304,334};
bool LeapJudge(int year){
    if(year%100==0){
        if(year%400==0){
            return true;
        }else{
            return false;
        }
    }else if(year%4==0){
        return true;
    }else{
        return false;
    }
}
int cmpDate(struct Date a, struct Date b){
    int hybridA=a.day+100*a.month+100000*a.year,hybridB=b.day+100*b.month+10000*b.year;
    if(hybridA>hybridB){
        return 1;
    }else if(hybridA==hybridB){
        return 0;
    }else{
        return -1;
    }
}
int subDate(struct Date a, struct Date b){
    int days=0,tempYear=a.year;
    //间隔年的日期累积
    for(int i=tempYear;i<b.year;i++){
        if(LeapJudge(i)){
            days=days+366;
        }else{
            days=days+365;
        }
    }
    //端点年份处理,对b
    if(LeapJudge(b.year) && (b.month>=3)){
        days=days+DaysAccum[b.month]+b.day;
    }else{
        days=days+DaysAccum[b.month]+b.day-1;
    }
    //对a
    if(LeapJudge(a.year) && (a.month>=3)){
        days=days-(DaysAccum[a.month]+a.day+1);
    }else{
        days=days-(DaysAccum[a.month]+a.day);
    }
    return days;
}
bool SetDate(struct Date* date,int y,int m, int d){
    if(LeapJudge(date->year) && m==2 && d>29){
        return false;
    }
    if(m>12 && m<1){
        return false;
    }
    if(d>MonReDay[m] || d<1){
        return false;
    }
    date->year=y,date->month=m,date->day=d;
    return true;
}

