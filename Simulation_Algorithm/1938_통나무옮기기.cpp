#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N;
char str[51];
int board[51][51];
bool check[2][51][51]; // 0 : ,통나무 가로 1 : 통나무 세로
int dirY[8] = { -1, 1, 0, 0, -1, 1, 1, -1 };
int dirX[8] = { 0, 0, -1, 1, 1, 1, -1, -1 };
int type, endtype; // type : 통나무가 가로인지 세로인지, endtype : 끝나는 곳이 가로인지 세로인지..

typedef struct _pos {
	int h, y, n; //  h : hang, y : yal, n : 가로인지 세로인지..
}pos;
vector<pos> start;
vector<pos> endd;
queue<pos> Q;
int BFS();

int main() {
	//입력
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < N; yal++) {
			board[hang][yal] = str[yal] - '0';
			if (board[hang][yal] == 'B' - '0') {
				start.push_back(pos({ hang, yal, 0 }));
				board[hang][yal] = 0;
			}
			else if (board[hang][yal] == 'E' - '0') {
				endd.push_back(pos({ hang, yal, 0 }));
				board[hang][yal] = 0;
			}
		}
	}
	//가운데가 중심이므로.. 중심을 기준으로 type선정
	if (start[0].h != start[1].h) type = 1; 
	if (endd[0].h != endd[1].h) endtype = 1;

	printf("%d\n", BFS());
	return 0;
}

bool move(int t, int hang, int yal, int d) {
	if (t == 0) {
		for (int i = -1; i < 2; i++) {
			int newY = hang + dirY[d];
			int newX = yal + i + dirX[d];
			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[newY][newX] == 1) return false;
		}
	}
	else if (t == 1) {
		for (int i = -1; i < 2; i++) {
			int newY = hang + i + dirY[d];
			int newX = yal + dirX[d];
			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[newY][newX] == 1) return false;
		}
	}
	return true;
}

bool move1(int t, int hang, int yal, int d) {
	int newY = hang + dirY[d];
	int newX = yal + dirX[d];
	if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[newY][newX] == 1) return false;
	return true;
}

bool turns(int hang, int yal) {
	for (int dir = 0; dir < 8; dir++) {
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];
		if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[newY][newX] == 1) return false;
	}
	return true;
}
// 중심값을 중심으로 움직인다..
int BFS() {
	check[type][start[1].h][start[1].y] = true;
	Q.push(pos({ start[1].h, start[1].y, type }));
	int time = 0;
	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();
			//목적지에 도달하고 type도 같으면 return time..
			if (p.n == endtype && p.h == endd[1].h && p.y == endd[1].y) return time;

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];
				//중심값이 경계값을 넘어가면 continue..
				if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;
				// 통나무가 가로일 때 위 아래로 움직이거나 통나무가 세로일 때 좌우로 움직일때
				if ((p.n == 0 && (dir == 0 || dir == 1)) || (p.n == 1 && (dir == 2 || dir == 3))) {
					// 중심값이 지나지 않은 곳이라면 move함수를 통해 움직일 수 있는지 판단
					if (!check[p.n][newY][newX]) {
						bool flag = move(p.n, p.h, p.y, dir);
						if (flag) {
							check[p.n][newY][newX] = true;
							Q.push(pos({ newY, newX, p.n }));
						}
					}	
				}
				// 통나무가 가로일 때 좌우로 움직이거나 통나무가 세로일 때 위아래로 움직일 때
				else {
					//중심값이 지나지 않은 곳이라면 move1함수를 통해 움직일 수 있는지 판단
					if (!check[p.n][newY][newX]) {
						bool flag = move1(p.n, newY, newX, dir);
						if (flag) {
							check[p.n][newY][newX] = true;
							Q.push(pos({ newY, newX, p.n }));
						}
					}
				}
			}
			//  90도 turn을 할때 세로일때 가로로 방문했던곳인지, 가로일때 세로로 방문했던 곳인지 판단하고 방문하지 않았을 시
			if ((p.n == 1 && !check[0][p.h][p.y]) || (p.n == 0 && !check[1][p.h][p.y])) {
				bool flag = turns(p.h, p.y);
				if (flag) {
					if (p.n == 1) {
						check[0][p.h][p.y] = true;
						Q.push(pos({ p.h, p.y, 0 }));
					}
					else if (p.n == 0) {
						check[1][p.h][p.y] = true;
						Q.push(pos({ p.h, p.y, 1 }));
					}
				}
			}
		}
		time++;
	}
	return 0;
}