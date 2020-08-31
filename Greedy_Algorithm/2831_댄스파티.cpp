#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <algorithm>
#include <math.h>
using namespace std;

int N;
int result;

priority_queue<int, vector<int>, greater<int>> upW, upM, downW, downM;

int main() {
	//입력
	scanf("%d", &N);
	for (int m, i = 0; i < N; i++) {
		scanf("%d", &m);
		if (m > 0) upW.push(m); // 키큰 여자를 좋아하는 남자
		if (m < 0) downW.push(abs(m)); // 키 작은 여자를 좋아하는 남자

	}
	for (int w, i = 0; i < N; i++) {
		scanf("%d", &w);
		if (w > 0) upM.push(w); // 키큰 남자를 좋아하는 여자
		if (w < 0) downM.push(abs(w)); // 키 작은 남자를 좋아하는 여자
	}
	// 키작은 남자와 키큰 여자를 좋아하는 사람을 매칭..
	while (1) {
		if (upW.size() == 0 || downM.size() == 0) break;
		int Mkey = upW.top();
		int Wkey = downM.top();
		downM.pop();	
		if (Mkey < Wkey) { // 만약 남자가 키가작고 여자가 키가 크면
			result++; // 결과값 증가
			upW.pop();
		}
	}
	// 키큰 남자와 키 작은 여자를 좋아하는 사람들 매칭..
	while (1) {
		if (upM.size() == 0 || downW.size() == 0) break;
		int Mkey = downW.top();
		int Wkey = upM.top();
		downW.pop();
		if (Mkey > Wkey) {
			result++;
			upM.pop();
		}
	}
	printf("%d\n", result);
	return 0;
}
