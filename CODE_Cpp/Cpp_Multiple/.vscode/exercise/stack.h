#pragma once
#include<iostream>
class stack						//ջ��
{
public:
	stack();
	~stack();
	void clearstack();					//���
	int isempty();						//�п�
	int length();						//�󳤶�
	char gettop();						//ȡջ��Ԫ��
	int push(char a);					//��ջ
	int pop();							//��ջ
	int traverse();						//����
	void print();
protected:
	char* top;				//ջ��ָ��
	char* base;				//ջ��ָ��
};