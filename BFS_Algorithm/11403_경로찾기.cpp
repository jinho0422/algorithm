#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int N;
int board[101][101];
bool check[101];

vector<int> Vec[101];

void BFS(int start);

int main() {
	//입력
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) { // 만약 hang(i)에서 yal(j)로 가는 것이 있으므로 vector에 넣는다.
				Vec[hang].push_back(yal);
			}
		}
	}
	for (int i = 0; i < N; i++) { // 0부터 N -1까지 하나의 정점에서 갈 수 있는 곳을 BFS를 통해 이동한다..
		BFS(i);
		memset(check, false, sizeof(check));// 초기화
	}
	//출력
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			printf("%d ", board[hang][yal]);
		}
		printf("\n");
	}
	return 0;
}

void BFS(int start) {
	queue<int> Q;
	Q.push(start);
	while (!Q.empty()) {
		int p = Q.front();
		Q.pop();
		int sz = Vec[p].size();
		for (int s = 0; s < sz; s++) {
			int first = Vec[p][s];

			if (!check[first]) {
				check[first] = true;
				Q.push(first);
				board[start][first] = 1;
			}
		}
	}
}