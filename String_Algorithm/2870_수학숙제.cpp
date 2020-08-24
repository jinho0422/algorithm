#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

int N;
char str[102];
string tmpStr;

// stirng이 들어간 vector의 원소의 크기를 오름차순으로, 크기가 같으면 숫자를 비교하여 오름차순으로
bool cmp(const string& a,const string& b) {
	if (a.size() == b.size()) {
		int sz = a.size();
		for (int i = 0; i < sz; i++) {
			if (a[i] != b[i]) return a[i] < b[i];
		}
	}
	return a.size() < b.size();
}

vector<string> Vec;

// 앞에 string 0을 제거해주는 함수..
void zeroClear() {
	while (1) {
		if (tmpStr.length() == 1 && tmpStr == "0") break;
		if (tmpStr[0] == '0') tmpStr.erase(0, 1);
		else break;
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", str);
		int cnt = 0;
		while (str[cnt] != '\0') cnt++;

		for (int j = 0; j < cnt; j++) {
			// str[j] == 숫자일 때
			if (str[j] >= '0' && str[j] <= '9') tmpStr += str[j];
			// str[j]가 숫자가 아닐때..
			else {
				if (tmpStr.length() != 0) {
					zeroClear(); // 앞쪽에 0이 있는지 판단하는 함수..
					Vec.push_back(tmpStr); // vector에 추가
					tmpStr.clear(); // 초기화
				}
			}
		}
		// 한문장이 끝나고 만약 tmpStr의 크기가 0이 아니라면 숫자가 남아있으므로
		if (tmpStr.length() != 0) {
			zeroClear();// 앞쪽에 0이 있는지 판단하고
			Vec.push_back(tmpStr); // vector에 추가
			tmpStr.clear(); // 초기화
		}
	}

	sort(Vec.begin(), Vec.end(), cmp); // 비내림차순(오름차순)으로 정렬
	// 출력
	for (int i = 0; i < Vec.size(); i++) {
		for (int j = 0; j < Vec[i].size(); j++) {
			printf("%c", Vec[i][j]);
		}
		printf("\n");
	}
	return 0;
}