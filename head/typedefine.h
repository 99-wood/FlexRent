#ifndef _TYPE_DEFINE
#define _TYPE_DEFINE

#include<stdbool.h>

/*intlist.h*/
struct IntList; // 整型链表

/*voidlist.h*/
struct VoidList; // void*类型链表

/*date.h*/
struct Date; // 日期类型

/*tag.h*/
struct Tag; // 标签类型
struct TagListNode; // 标签链表节点
struct TagList;  // 标签链表

/*house.h*/
struct House; // 房源
struct HouseListNode; // 房源链表节点
struct HouseList; // 房源链表

/*user.h*/
struct User; // 用户
struct UserListNode; // 用户链表节点
struct UserList; // 用户链表

/*middium*/
struct Middium; // 中介
struct MiddiumListNode; // 中介链表节点
struct MiddiumList; // 中介链表

/*renthousemsg.h*/
struct RentHouseMsg; // 租房信息
struct RHMListNode; // 租房信息链表节点
struct RHMList; // 租房信息链表

/*viewhousemsg.h*/
struct ViewHouseMsg; // 看房信息
struct VHMListNode; // 看房信息链表节点
struct VHMList;  // 看房信息链表

/*city.h*/
struct City; // 城市
struct CityListNode; // 城市链表节点
struct CityList; // 城市链表

/*area.h*/
struct Area; // 区域
struct AreaListNode; // 区域链表节点
struct AreaList; // 区域链表

/*community.h*/
struct Community; // 小区
struct CommunityListNode; // 小区链表节点
struct CommunityList; // 小区链表

/*voidtreap*/
struct VoidTreapNode;
struct VoidTreap;

/*hashtreap*/
struct HashTreapNode;
struct HashTreap;


#endif