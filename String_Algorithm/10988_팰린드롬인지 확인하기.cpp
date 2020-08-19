#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

char str[102];

// 문장의 앞뒤의 상황을 보고 결정하는 것이므로 deque를 사용
deque<char> Q;

int main() {
	//입력
	scanf("%s", str);

	for (int s = 0; str[s] != '\0'; s++) {
		Q.push_back(str[s]);
	}
	bool flag = false;
	while (1) {
		// 팰린드롬이 아니거나 Q가 비었거나 1개이면 빠져나온다
		if (flag == true || Q.size() == 0 || Q.size() == 1) break;
		char f = Q.front();
		Q.pop_front();
		char b = Q.back();
		Q.pop_back();
		//문장의 앞뒤를 비교
		if (f == b) continue;
		else flag = true;
	}
	// 출력
	if (flag) printf("0\n");
	else printf("1\n");

	return 0;
}