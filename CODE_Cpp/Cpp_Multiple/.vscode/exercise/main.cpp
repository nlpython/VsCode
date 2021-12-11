#include<iostream>
#include<string>
#include"stack.h"
#include"priority.h"
#include"ToStringAndPush.h"

using namespace std;
int main() {
	string input;
	std::cin >> input;		//用户输入表达式
	stack num;
	stack optr;
	for (unsigned int i = 0; i < input.size(); i++) {
		if (priority(input[i]) == -1) {
			num.push(input[i]);
		}											
		else if (priority(input[i]) == 1 && optr.isempty()) {
			optr.push(input[i]);
			num.push('#');
		}
		else if (priority(input[i]) == 1 && !optr.isempty()) {
			int y = num.pop();
			int x = num.pop();
			if (optr.pop() == 1) { ToStringAndPush(x + y,num); }
			if (optr.pop() == 2) { ToStringAndPush(x - y, num); }
			optr.pop();
			optr.push(input[i]);
			num.push('#');	
		}											
		else if (priority(input[i]) == 2) {
			i++;
			int x = num.pop();
			int y = input[i]-48;
			if (input[i - 1] == '*') { ToStringAndPush(x * y, num); }
			else{ ToStringAndPush(x / y, num); }
		}
	}
	if (!optr.isempty()) {
		int y = num.pop();
		int x = num.pop();
		if (optr.pop() == 1) { ToStringAndPush(x + y, num); }
		if (optr.pop() == 2) { ToStringAndPush(x - y, num); }
		optr.pop();
	}
	
	num.traverse();

	return 0;
}