#include<iostream>
#include"stack.h"
#include"priority.h"

	stack::stack() {
		base = new char[50];
		top = base;
	}

	stack::~stack() {
		delete[] base;
	}

	void stack::clearstack() {
		for (; top > base; top--) {
			top--;
			*top = '0';
		}
	}						//���
	int stack::isempty() {
		if (top == base) return 1;
		else return 0;
	}						//�п�

	int stack::length() {
		return top - base;
	}						//�󳤶�

	char stack::gettop() {
		return *(top - 1);
	}					//ȡջ��Ԫ��
	int stack::push(char a) {
		*top = a;
		top++;
		return 0;
	}					//��ջ
	int stack::pop() {
		if (priority(*(top - 1)) == 0) {
			top--;
		}												//����ǡ�#����top�����ƶ�һλ
		if (priority(*(top - 1)) == -1) {
			int x = 0;
			for (int rank = 1; top > base && *(top-1) != '#' ; rank = rank * 10) {
				top--;
				x = x + ((*top) - 48) * rank;
			}											//��������ֵĻ�������ֵΪ����
			return x;
		}
		else if (priority(*(top - 1)) == 1) {
			top--;
			if ((*top) == '+') return 1;
			if ((*top) == '-') return 2;
		}												//���Ϊ�ַ���+����1��-����2
		else {
			return 3;
		}
	}													//��ջ
	int stack::traverse() {
		for (char* a = base,*b = (top-1); a <= b; a++) {
			std::cout << *a;
		}
		return 0;
	}						//����