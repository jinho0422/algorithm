#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

int board[100][100];
bool check[100][100];
int dirY[2] = { 0, 0 };
int dirX[2] = { -1, 1 };
int min_length;
int result;

typedef struct _pos {
	int h, y, cnt;
}pos;

vector<int> Vec;

void searchEnd(int start);

int main() {
	freopen("test.txt", "r", stdin);
	for (int i, t = 1; t <= 10; t++) {
		//사다리 입력받기
		min_length = 2147000000;
		scanf("%d", &i);
		for (int hang = 0; hang < 100; hang++) {
			for (int yal = 0; yal < 100; yal++) {
				scanf("%d", &board[hang][yal]);
				// 첫번째 행렬에서 사다리를 탈 수 있는 곳을 저장!
				if (hang == 0) {
					if (board[hang][yal] == 1) {
						Vec.push_back(yal);
					}
				}
			}
		}
		for (int s = 0; s < Vec.size(); s++) {
			//사다리를 탈 수 있는 출발점에서 도작지점까지 가는지를 판단.
			searchEnd(Vec[s]);
			//다음 출발 사람을 위해 visitcheck 리셋.
			memset(check, false, sizeof(check));	
		}
		printf("#%d %d\n", t, result);
		// 다음 테스트 케이스를 위해 출발점 리셋!
		Vec.clear();
	}
	return 0;
}


void searchEnd(int start) {
	queue<pos> Q;
	check[0][start] = true;
	Q.push(pos({ 0, start, 0 }));
	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		// 도착지점을 찾았을 때 결과값을 result에 넣어준다.
		if (p.h == 99) {
			//움직인 거리가 최소이면 일때
			if (min_length >= p.cnt) {
				min_length = p.cnt;
				result = start;
			}
			break;
		}
		bool sideFlag = false;
		//좌 우 를 살피고 좌 우에 갈 곳이 있으면 queue에 넣어준다.
		for (int dir = 0; dir < 2; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];
			// 사다리가 아닌곳으로 가면 continue;
			if (newY < 0 || newY > 99 || newX < 0 || newX > 99) continue;

			if (board[newY][newX] != 0 && !check[newY][newX]) {
				check[newY][newX] = true;
				sideFlag = true;
				Q.push(pos({ newY, newX, p.cnt + 1}));
			}
		}
		//좌 우에 갈 곳이 없으면 아래로 전진한다.
		if (!sideFlag) {
			check[p.h + 1][p.y] = true;
			Q.push(pos({ p.h + 1, p.y, p.cnt + 1}));
		}
	}
}