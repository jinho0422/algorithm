#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;
#include <cstdio>
#include <queue>

using namespace std;

int N;
int board[1002];
int dij_board[1002];

typedef struct _pos {
	int j, m, c; // j : 현재위치, m : 움직일 수 있는 횟수, c : 지금까지 점프한 횟수
}pos;

struct cmp { // 최소로 점프한 횟수부터 차례대로 나오기 위한 정렬
	bool operator() (pos p, pos q) {
		return p.c > q.c;
	}
};
priority_queue<pos, vector<pos>, cmp> Q;

void BFS(int start, int move, int cnt);

int main() {
	//입력
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &board[i]);
	}
	// 다직스트라를 쓰기위해 dij_board를 Max값으로 초기화
	for (int i = 1; i < N; i++) {
		dij_board[i] = INF;
	}
	BFS(0, 0, 0);
	return 0;
}

void BFS(int start, int move, int cnt) {
	Q.push(pos({start, board[start], cnt}));

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();
		// 마지막에 도달했으면 출력
		if (p.j == N - 1) {
			printf("%d\n", p.c);
			return;
		}
		//현재의 위치에서 1~ p.m까지 이동할 수 있는 범위에서
		for (int i = 1; i <= p.m; i++) {
			if (p.j + i > N - 1) continue; // 점프했을 때 갈 수 없는 곳이면 continue..
			if (dij_board[p.j + i] > dij_board[p.j] + 1) { // 만약 점프해야되는 곳이 현재의 점프한 횟수의 + 1보다 크면 
				dij_board[p.j + i] = dij_board[p.j] + 1; // 움직인다..
				Q.push(pos({ p.j + i, board[p.j + i], p.c + 1 }));
			}
		}
	}
	//도달한 것이 없으면 -1 출력
	printf("-1\n");
}