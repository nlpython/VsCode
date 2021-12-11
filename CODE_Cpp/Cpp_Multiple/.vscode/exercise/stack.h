#pragma once
#include<iostream>
class stack						//栈类
{
public:
	stack();
	~stack();
	void clearstack();					//清空
	int isempty();						//判空
	int length();						//求长度
	char gettop();						//取栈顶元素
	int push(char a);					//进栈
	int pop();							//出栈
	int traverse();						//遍历
	void print();
protected:
	char* top;				//栈顶指针
	char* base;				//栈底指针
};