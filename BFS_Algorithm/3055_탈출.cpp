#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N, M;
char str[51];
char board[51][51];
bool check[51][51];
bool waterCheck[51][51];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int result;
bool flag;

typedef struct _pos {
	int h, y; // h : hang, y : yal
}pos;
pos endd[1]; // 도착지점 저장
queue<pos> water;
queue<pos> Q;

void BFS();

int main() {
	//입력
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			//water인 경우 water queue에 저장
			if (board[hang][yal] == '*') {
				waterCheck[hang][yal] = true;
				water.push(pos({ hang, yal }));
			}
			// 고슴도치인 경우 Q queue에 저장
			else if (board[hang][yal] == 'S') {
				check[hang][yal] = true;
				Q.push(pos({ hang, yal }));
			}
			// 비버의 굴인 경우 도착지점 저장..
			else if (board[hang][yal] == 'D') {
				endd[0] = { hang, yal };
			}
		}
	}
	BFS();
	//출력
	if (!flag) printf("KAKTUS\n");
	else printf("%d\n", result);
	return 0;
}

void BFS() {

	while (!Q.empty() || !water.empty()) {
		//water의 size만큼 돌리면서(물의 움직임)
		int wsz = water.size();
		for (int s = 0; s < wsz; s++) {
			pos p = water.front();
			water.pop();

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
				// 땅이거나 동시에 움직이므로 S인경우 물로 채운다..
				if (!waterCheck[newY][newX] && (board[newY][newX] == '.' || board[newY][newX] == 'S')) {
					waterCheck[newY][newX] = true;
					board[newY][newX] = '*';
					water.push(pos({ newY, newX}));
				}
			}
		}
		// 고슴도치의 움직임을 Q의 szie만큰 돌리면서
		int ssz = Q.size();
		for (int s = 0; s < ssz; s++) {
			pos p = Q.front();
			Q.pop();
			// 만약 도착지점이면 탈출..
			if (p.h == endd[0].h && p.y == endd[0].y) {
				flag = true;
				return;
			}
			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
				// 땅이거나 비버의 굴이면 
				if (!check[newY][newX] && (board[newY][newX] == '.' || board[newY][newX] == 'D')) {
					board[p.h][p.y] = '.'; // 물이 올수도있기때문에 고슴도치의 흔적을 지우고
					board[newY][newX] = 'S'; // 현재의 이동으로 고슴도치를 이동
					check[newY][newX] = true;
					Q.push(pos({ newY, newX}));
				}
			}
		}
		result++; // 결과값 갱신
	}
}