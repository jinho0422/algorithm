#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int N, M, K, sh, sy;
int board[23][23];
bool check[23][23];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int time;
bool flag, resultFlag, retFlag; // flag : 승객을 찾은 시점 체크 , resultFlag : 결과값을 뽑을 수 있는지 체크, retFlag : 목적지에 도착할 수 있는지 체크

typedef struct _pos {
	int h, y, num; // h : hang, y : yal, num :  승객번호
}pos;

bool cmp(const pos& p, const pos& q) { // 가까운 승객이 많을 경우 행이 작거나 같은경우 열이 작은경우 정렬..
	if (p.h == q.h) return p.y < q.y;
	return p.h < q.h;
};
vector<pos> Vec; // 가까운 승객을 태운 vector
vector<int> det[23][23]; // 목적지를 넣는 vector

void BFS(int hang, int yal);
void BFS1(int hang, int yal, int checkNum);

int main() {
	//입력
	scanf("%d %d %d", &N, &M, &K);
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	scanf("%d %d", &sh, &sy);
	int num = 2;
	for (int a, b, c, d,i = 0; i < M; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		board[a][b] = num;
		det[c][d].push_back(num);
		num++;
	}
	for (int i = 0; i < M; i++) {
		//초기화
		Vec.clear();
		memset(check, false, sizeof(check));
		//승객찾기..
		BFS(sh, sy);
		// 만약 태울 수 있는 승객이 없거나 연료가 다 떨어지면..
		if (Vec.size() == 0 || K < 0) {
			resultFlag = true;
			break;
		}
		// 같은 거리에 있는 승객중에 행이 작거나 같으면 열이 작은 승객을 찾기위해..
		sort(Vec.begin(), Vec.end(), cmp);
		board[Vec[0].h][Vec[0].y] = 0; // 승객 없애기..
		memset(check, false, sizeof(check));
		// 목적지 찾기..
		BFS1(Vec[0].h, Vec[0].y, Vec[0].num);
		// 만약 연료가 없거나 목적지에 도착하지 못하면..
		if (K - time < 0 || !retFlag) {
			resultFlag = true;
			break;
		}
		// 목적지 도착 후 연료 충전..
		K += time;
	}
	//출력
	if (!resultFlag) printf("%d\n", K);
	else printf("-1\n");
	return 0;
}

void BFS(int hang, int yal) {
	// 출발지점에 승객이 있는 경우..
	if (board[hang][yal] != 0) {
		Vec.push_back(pos({ hang, yal, board[hang][yal] }));
		return;
	}
	queue<pos> Q;
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));
	flag = false;
	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY <= 0 || newY > N || newX <= 0 || newX > N || board[newY][newX] == 1) continue;

				if (board[newY][newX] == 0 && !check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX }));
				}
				if (board[newY][newX] != 0 && !check[newY][newX]) {
					check[newY][newX] = true;
					flag = true;
					Vec.push_back(pos({ newY, newX, board[newY][newX] }));
				}
			}
		}
		K--;
		if (flag || K < 0) return;
	}
}

void BFS1(int hang, int yal, int checkNum) {
	retFlag = false;
	time = 0;
	queue<pos> Q;
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));

	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();
			if (det[p.h][p.y].size() != 0) {
				for (int i = 0; i < det[p.h][p.y].size(); i++) {
					if (det[p.h][p.y][i] == checkNum) {
						sh = p.h, sy = p.y;
						retFlag = true;
						return;
					}
				}
			}
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY <= 0 || newY > N || newX <= 0 || newX > N || board[newY][newX] == 1) continue;

				if (!check[newY][newX]) {
					check[newY][newX] = true;
					Q.push(pos({ newY, newX }));
				}
			}
		}
		time++;
	}
}