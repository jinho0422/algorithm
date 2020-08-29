#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

char str[1001];
string ss;

//vector에 있는 string비교
bool cmp(const string& a, const string& b) {
	int asz = a.size() -1, bsz = b.size() -1;
	if (a[asz] == b[bsz]) {
		while (1) {
			asz--, bsz--;
			if (asz == -1) return true; // 비교할 수 있는 단어가 없을 경우 왼쪽(오름차순)으로 정렬
			if (a[asz] != b[bsz]) return a[asz] < b[bsz]; // 만약 비교문자가 다르면 오름차순 정렬
		}
	}
	return a[asz] < b[bsz];
}

vector<string> Vec;

int main() {
	scanf("%s", str);
	int len = 0;
	while (str[len] != '\0') len++;
	for (int s = len - 1; s >= 0; s--) {
		ss += str[s];
		Vec.push_back(ss);
	}
	sort(Vec.begin(), Vec.end(), cmp);
	for (int s = 0; s < Vec.size(); s++) {
		for (int i = Vec[s].length() -1; i >= 0; i--) {
			printf("%c", Vec[s][i]);
		}
		printf("\n");
	}
	return 0;
}