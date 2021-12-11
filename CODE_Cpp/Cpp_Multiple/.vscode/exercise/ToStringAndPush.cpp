#include"ToStringAndPush.h"
#include"stack.h"

void ToStringAndPush(int a,stack &num) {
	std::string str = std::to_string(a);
	for (unsigned int i = 0; i < str.size(); i++) {
		num.push(str[i]);
	}
}