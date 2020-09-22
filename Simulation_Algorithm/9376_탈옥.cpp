#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int N, M;
char str[105];
char board[105][105];
bool check[3][105][105];
int doorCnt[3][105][105]; // 죄수 0, 죄수 1, 문을 열어주는 사람 2 을 통해 문을 열고 간 갯수를 칸마다 적어주는 배열..
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int result[105][105]; // 3사람이 문을 열고 지나간 곳을 더한 배열..
int minResult;

typedef struct _pos {
	int h, y, cnt; // h : hang, y : yal, cnt : 문을 열었던 갯수..
}pos;

struct cmp {
	bool operator() (pos p, pos q) {
		return p.cnt > q.cnt;
	}
};

vector<pos> Vec;
priority_queue<pos, vector<pos>, cmp> Q; // 우선순위 큐를 쓴 이유는 최소한으로 문을 열고 들어간 경우를 doorCnt에 갱신하기위해..

void BFS(int hang, int yal, int type);

int main() {
	//입력
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		//초기화..
		minResult = 987654321;
		scanf("%d %d", &N, &M);
		memset(board, '.', sizeof(board));
		memset(check, false, sizeof(check));
		memset(doorCnt, 0, sizeof(doorCnt));
		memset(result, 0, sizeof(result));
		Vec.clear();

		int num = 1;
		Vec.push_back(pos({ 0, 0, 0 })); // 문을 열어주는 사람 2
		for (int hang = 0; hang < N; hang++) {
			scanf("%s", str);
			for (int yal = 0; yal < M; yal++) {
				board[hang + 1][yal + 1] = str[yal];
				if (board[hang + 1][yal + 1] == '$') {
					board[hang + 1][yal + 1] = '.';
					Vec.push_back(pos({ hang + 1, yal + 1, num++ })); // 죄수 0, 죄수 1
				}
				if (board[hang + 1][yal + 1] == '*') result[hang + 1][yal + 1] = -1; // 결과값에서 빼주기위해 '*'이면 결과값을 -1로 변경..
			}
		}
		//3명의 사람이 최소 몇개의 문을 열고 들어갔는지 각각의 자리에 갱신하는 BFS..
		for (int s = 0; s < Vec.size(); s++) BFS(Vec[s].h, Vec[s].y, Vec[s].cnt);

		// 3사람의 최소 몇개의 문을 열고 들어갔는지를 모두 더해준다..
		for (int hang = 1; hang < N + 1; hang++) {
			for (int yal = 1; yal < M + 1; yal++) {
				for (int i = 0; i < 3; i++) {
					result[hang][yal] += doorCnt[i][hang][yal];
				}
				if (board[hang][yal] == '#') result[hang][yal] -= 2; // 문이였던 경우는 3명이  모두 + 1을 해줬으므로 -2를 해준다..
				if (result[hang][yal] != -1) {
					if (minResult > result[hang][yal]) minResult = result[hang][yal];
				}
			}
		}
		//출력
		printf("%d\n", minResult);
	}
	return 0;
}

void BFS(int hang, int yal, int type) {
	check[type][hang][yal] = true;
	doorCnt[type][hang][yal] = 0;
	Q.push(pos({ hang, yal, 0 }));

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N + 1 || newX < 0 || newX > M + 1) continue;
			//지나갈수있는곳.
			if (!check[type][newY][newX] && board[newY][newX] == '.') {
				check[type][newY][newX] = true;
				doorCnt[type][newY][newX] = p.cnt;
				Q.push(pos({ newY, newX, p.cnt }));
			}
			// 문인경우
			if (!check[type][newY][newX] && board[newY][newX] == '#') {
				check[type][newY][newX] = true;
				int newCnt = p.cnt + 1;
				doorCnt[type][newY][newX] = newCnt;
				Q.push(pos({ newY, newX, newCnt }));
			}
		}
	}
}