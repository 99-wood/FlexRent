#ifndef _UI
#define _UI
#include "typedefine.h"

#include<stdio.h>
#include <conio.h>
#include<windows.h>
#include<string.h>
#include<ctype.h>
// char* c[]={"string","ying"};
void color(short x)	//自定义函根据参数改变颜色 
{
    if(x>=0 && x<=15)//参数在0-15的范围颜色
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//只有一个参数，改变字体颜色 
    else//默认的颜色白色
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
} 
void Print(char* c[],int line,int num){
	system("CLS");
    printf("                         ---------------------------------------------------------\n");
	for(int i=0;i<num;i++){
        printf("                        |      ");
		if(i==line){
            color(4);
            printf("*");
            printf("%-50s",c[i]);
        }
		else{
            color(16);
            printf(" ");
            printf("%-50s",c[i]);
        }
        color(16);
        printf("|\n");
	}
    printf("                         ---------------------------------------------------------");
}
int UiPrint(char* CC[],int num){   
    int ch1=0;
    int ch2=0;
    int line=0;
    Print(CC,line,num);
    while (1)
    {
        if (ch1=getch())
        { 
        if(ch1 == 13){
            system("CLS");
            return line;
        }
        if(ch1 == 224){
            int con=0;
            ch2=getch();//第一次调用getch()，返回值224
            //  printf("%d",ch2);
            switch (ch2)//第二次调用getch()
            {
            case 72: line=(line-1+num)%num; break;  
            case 80: line=(line+1)%num; break;  
            case 13: system("CLS"); return line;                                
            default: break;
                break;
            }
            Print(CC,line,num);
        }
        } 
    }
    return 0;
}
void modeset(int w,int h) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size = {w, h};
	SetConsoleScreenBufferSize(hOut,size);
	SMALL_RECT rc = {1,1, w, h};
	SetConsoleWindowInfo(hOut ,true ,&rc);
	system("cls");
	return;
}
void getpwd(char *pwd, int pwdlen){
    char ch = 0;
    int i = 0;
    while(i<pwdlen){
        ch = _getch();
        if(ch == '\r'){ //回车结束输入
            printf("\n");
            break;
        }
        if(ch=='\b' && i>0){ //按下删除键
            i--;
            printf("\b \b");
        }
        else if(isprint(ch)){ //输入可打印字符
            pwd[i] = ch;
            printf("*");
            i++;
        }
    }
    pwd[i] = 0;
}
#endif