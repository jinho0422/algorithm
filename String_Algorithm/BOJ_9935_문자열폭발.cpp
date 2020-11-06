#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string text, bomb;

vector<char> Vec;

int main() {
	cin >> text >> bomb;
	int bsz = bomb.length();
	for (int s = 0; s < text.length(); s++) {
		Vec.push_back(text[s]);

		if (Vec.size() >= bomb.length()) {

			int tsz = Vec.size();
			bool flag = false;
			for (int i = bsz - 1; i >= 0; i--) {
				if (Vec[tsz - i -1] != bomb[bsz -1 - i]) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				for (int i = 0; i < bomb.length(); i++) Vec.pop_back();	
			}
		}
	}
	if (Vec.size() == 0) printf("FRULA\n");
	else {
		for (int i = 0; i < Vec.size(); i++) {
			printf("%c", Vec[i]);
		}
		printf("\n");
	}

	return 0;
}