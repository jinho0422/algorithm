/*
	모든 섬을 다리로 연결하려고 나라는 N*M크기이고 1인 부분은 땅, 0 인부분은 바다이다.
	다리는 다른 섬간의 세로 or 가로로만 지을 수 있다.(중간에 섬이 있으면 안되고 다리의 길이가 1이여도 안된다.)
	모든 섬을 연결하는 다리 길이의 최솟값을 구하자.

	BFS를 이용하여 각각의 섬의 번호를 매기고 각 섬의 위치에서 다른 섬까지의 거리를
	백터에 넣어 유니온파인드를하여 MST를 사용하였다.
	*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
int board[10][10];
bool check[10][10]; // 섬의 번호를 매기기위해..
int parent[7]; // 유니온 파인드를 위해..
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int num; // 섬의 번호
int result;

typedef struct _pos {// 섬의 번호를 매기기위해 hang, yal을 Q에 넣기위해..
	int h, y;
}pos;

typedef struct _pos1 { // 백터의 시작섬과 끝섬과 그 다리의 길이를 넣기위해..
	int A, B, W;
}pos1;

bool cmp(const pos1 p, const pos1 q) { // MST를 사용하기 위해서는 백터 정렬이 필요..
	return p.W < q.W;
}

vector<pos1> Vec;

void BFS(int hang, int yal, int n);

int find_(int x) { // 유니온파인드를 위해(부모를 찾기위해..)
	if (parent[x] == x) return x;
	return parent[x] = find_(parent[x]);
}

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}


	num = 1;

	for (int hang = 0; hang < N; hang++) { // BFS를 이용한 섬의 번호 매기기..
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == 1 && !check[hang][yal]) {
				BFS(hang, yal, num);
				num++;
			}
		}
	}

	for (int i = 1; i < num; i++) { // 유니온 파인드를 위해 parent를 자기 자신으로 설정..
		parent[i] = i;
	}

	for (int hang = 0; hang < N; hang++) { // 맵에서 섬이면 바다가 아니면..
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] != 0) {
				for (int dir = 0; dir < 4; dir++) { // 상하좌우로 보고
					int cnt = 0; int copy_hang = hang; int copy_yal = yal; // 다리를 퍼트리기위한 초기값.
					while (1) {
						int newY = copy_hang + dirY[dir];
						int newX = copy_yal + dirX[dir];
						if (newY < 0 || newY > N -1 || newX < 0 || newX > M -1 || board[hang][yal] == board[newY][newX]) break;
						// 맵의크기를 벗어나거나 같은 섬이면 넘긴다..
						if (board[newY][newX] == 0) { // 바다이면 다리의 크기를 증가시키고 같은 방향으로 나가기 위해 hang, yal의 값을 바꿔준다.
							copy_hang = newY; copy_yal = newX; cnt++;
						}
						if (board[newY][newX] != 0 && board[newY][newX] != board[hang][yal]) { // 바다가 아니고 하나의 섬에서 다른 섬에 도착하는 경우
							if (cnt == 1) break; // 다리의 크기가 1이면 빠져나온다..
							Vec.push_back(pos1({ board[hang][yal], board[newY][newX], cnt })); // 다리의 크기가 1이 아니면 백터에 넣는다.
							break;
						}
					}
				}
			}
		}
	}

	sort(Vec.begin(), Vec.end(), cmp); // MST를 사용하기 위한 정렬..

	int sz = Vec.size();
	int area_num = 1; // 모든 섬이 다 연결됬는지르 보기 위한 초기값.
	bool flag = false;

	for (int s = 0; s < sz; s++) { // 유니온파인드...
		int a_head = find_(Vec[s].A);
		int b_head = find_(Vec[s].B);

		if (a_head != b_head) {// 부모의 값이 다르면 유니온..
			parent[a_head] = b_head;
			result += Vec[s].W; // 다리의 길이를 더해준다..
			area_num++; // 연결된 섬의 개수를 체크
			if (area_num == num - 1) flag = true; // 모든 섬이 연결되면 flag true
		}
	}
	if (flag) printf("%d\n", result);
	else printf("-1\n");

	return 0;
}

void BFS(int hang, int yal, int n) {
	queue<pos> Q;
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));
	board[hang][yal] = n;

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

			if (board[newY][newX] == 1 && !check[newY][newX]) {
				check[newY][newX] = true;
				board[newY][newX] = n;
				Q.push(pos({ newY, newX }));
			}
		}
	}
}