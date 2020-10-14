#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N;
int board[51][10]; // 각 이닝에서 선수들의 타석에서의 상황
int check[10];
int player[10]; // 배정된 선수들을 넣는 배열
int scoreResult; // 결과값

deque<int> Q; // 배정된 선수를 넣는다..
vector<int> Vec; // 각 이닝별 점수획득 상황을 보기 위해..

void DFS(int depth);

int main() {
	//입력
	scanf("%d", &N);
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= 9; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	DFS(1);
	printf("%d\n", scoreResult);
	return 0;
}

int score() {
	int cnt = 0; // 배정된 선수들이 낼 수 있는 총 스코워
	for (int hang = 1; hang <= N; hang++) {
		int out = 0; // out
		while (!Q.empty()) {
			int p = Q.front();
			Q.pop_front();

			if (board[hang][p] == 0) { // board[hang][yal] == 0 이면 아웃인 상황이기 때문에 out++
				out++;
				Q.push_back(p); // 다음 이닝을 위해 front에서 back으로 넣어준다..(회전)
				if (out == 3) break; // out이 3번이면 이닝 종료
			}
			else { // board[hang][yal] != 0 이면 안타를 친 경우이므로
				Q.push_back(p); 
				Vec.push_back(1);// 안타친 사람은 1로 표시하고 나머지를 0으로 한다..
				for (int i = 1; i < board[hang][p]; i++) Vec.push_back(0);			
			}
		}
		int sz = Vec.size();
		if (sz >= 4) {// sz가 4이상이면 득점이 있을 수 있는 상황이므로 Vec에 1이 있는지 1루 2루 3루를 빼고 샌다..
			for (int i = 0; i < sz - 3; i++) {
				if (Vec[i] == 1) cnt++;
			}
		}
		Vec.clear(); // 이닝 종료 후 베이스 초기화
	}
	return cnt;
}
// 1~9번순으로 각 선수를 배정
void DFS(int depth) {
	if (depth == 4) DFS(depth + 1); // 4번에는 1번선수를 넣어야되기때문에..
	if (depth == 10) {
		player[4] = 1;
		while (!Q.empty()) Q.pop_front();// 초기화
		for (int i = 1; i < depth; i++) Q.push_back(player[i]);
		int result = score();
		if (scoreResult < result) scoreResult = result; // 결과값 갱신..
		return;
	}
	for (int s = 2; s <= 9; s++) {
		if (!check[s]) {
			check[s] = true;
			player[depth] = s;
			DFS(depth + 1);
			player[depth] = 0;
			check[s] = false;
		}
	}
}