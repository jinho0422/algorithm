#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

char str[102];
string ss;
int main() {
	scanf("%s", str);
	ss = str;
	int sz = ss.length();
	for (int s = 0; s < ss.length() / 10; s++) {
		string sss = ss.substr(10 * s, 10);
		cout << sss << '\n';
	}
	string sss = ss.substr(10 * (sz / 10), sz % 10);
	cout << sss << '\n';
	return 0;
}