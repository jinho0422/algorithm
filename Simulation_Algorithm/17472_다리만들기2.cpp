#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

int N, M;
int board[11][11];
bool check[11][11];
int parents[10];
int dirY[4] = { -1, 1, 0, 0 };
int dirX[4] = { 0, 0, -1, 1 };
int islandNum;
int result;

typedef struct _pos {
	int h, y, n; // h : hang, y : yal, n : 섬의 번호
}pos;
queue<pos> Q; // 섬의 번호를 매기기 위해..
vector<pos> Vec; // 다리를 만들 수 있는 섬의 한 구역을 넣는다.

typedef struct _pos1 {
	int A, B, W; // A : 섬의 번호 B : 섬의 번호 W : 다리의 길이
}pos1;
vector<pos1> bridge; // 섬과 섬의 번호와 다리의 길이를 가지고 있는 vectdor

bool cmp(const pos1& p, const pos1& q) {
	return p.W < q.W;
}

void BFS(int hang, int yal);

int find_(int x) {
	if (parents[x] == x) return x;
	return parents[x] = find_(parents[x]);
}

int main() {
	//입력
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) board[hang][yal] = -1;
		}
	}
	//섬의 번호 붙이기
	islandNum = 1;
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == -1 && !check[hang][yal]) {
				BFS(hang, yal);
				islandNum++;
			}
		}
	}
	// 섬과 섬사이의 다리의 길이가 2이상의 다리 찾기
	for (int s = 0; s < Vec.size(); s++) {
		for (int dir = 0; dir < 4; dir++) {
			int sh = Vec[s].h, sy = Vec[s].y;
			int cnt = 0;
			while (1) {
				int newY = sh + dirY[dir];
				int newX = sy + dirX[dir];
				
				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == board[Vec[s].h][Vec[s].y]) break;

				if (board[newY][newX] != 0) {
					if (cnt > 1) bridge.push_back(pos1({ board[Vec[s].h][Vec[s].y], board[newY][newX], cnt}));	
					break;
				}
				cnt++;
				sh = newY, sy = newX;	
			}
		}
	}
	//유니온파인드..
	for (int i = 1; i <= islandNum; i++) parents[i] = i;
	sort(bridge.begin(), bridge.end(), cmp);

	int checkCnt = 1;
	for (int i = 0; i < bridge.size(); i++) {
		int headA = find_(bridge[i].A);
		int headB = find_(bridge[i].B);

		if (headA != headB) {
			parents[headA] = headB;
			result += bridge[i].W;
			checkCnt++;
			if (checkCnt == islandNum - 1) { // 모든 섬이 연결되면 결과값 출력
				printf("%d\n", result);
				return 0;
			}
		}
	}
	printf("-1\n");
	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	board[hang][yal] = islandNum;
	Q.push(pos({ hang, yal, islandNum }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		bool flag = false;

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

			if (!flag && board[newY][newX] == 0) { // 다리를 만들수 있는 구역이면 Vec에 넣는다.
				Vec.push_back(pos({ p.h, p.y, islandNum }));
				flag = true;
			}

			if (board[newY][newX] == -1 && !check[newY][newX]) {
				check[newY][newX] = true;
				board[newY][newX] = p.n;
				Q.push(pos({ newY, newX, p.n }));
			}
		}
	}
}