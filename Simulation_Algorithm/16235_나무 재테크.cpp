#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N, M, K;
int board[11][11]; // 현재의 양분 배열
int tmpBoard[11][11]; // 겨울에 줄 양분을 가지고 있는 배열
int dirY[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dirX[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int result;

typedef struct _pos {
	int h, y;
}pos;
vector<pos> Vec; // 번식할 수 있는 나무의 hang, yal을 넣어준다..

deque<int> Q[11][11]; // 어느곳에 나무가 있는지 판단하는 deque

void spring();
void fall();
void winter();

int main() {
	//입력
	scanf("%d %d %d", &N, &M, &K);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &tmpBoard[hang][yal]);
			board[hang][yal] = 5;
		}
	}
	//나무심기
	for (int a, b, c, i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		Q[a -1][b -1].push_back(c);
	}
	//년도를 지나면서
	for (int i = 0; i < K; i++) {
		spring();
		if(Vec.size() != 0) fall();
		winter();
		if (result == 0) break; // 만약 살아남은 나무가 없으면 break;;
	}
	//출력
	printf("%d\n", result);
	return 0;
}
//봄과 여름
void spring() {
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			int sz = Q[hang][yal].size();
			if (sz == 0) continue;
			bool flag = false; // flag : false이면 양분을 먹고, true이면 양분을 만든다.
			for (int i = 0; i < sz; i++) {
				int p = Q[hang][yal].front();
				Q[hang][yal].pop_front();
				if (!flag) {
					if (board[hang][yal] >= p) {
						board[hang][yal] -= p;
						Q[hang][yal].push_back(p + 1);
						if ((p + 1) % 5 == 0) Vec.push_back(pos({ hang, yal }));
					}
					else {
						board[hang][yal] += p / 2;
						flag = true;
					}
				}
				else board[hang][yal] += p / 2;
			}
		}
	}
}
// 만약 봄과 여름이 지나면서 나이가 5의 배수였던 나무들을 Vec에 넣어 번식시킨다.
void fall() {
	for (int s = 0; s < Vec.size(); s++) {
		for (int dir = 0; dir < 8; dir++) {
			int newY = Vec[s].h + dirY[dir];
			int newX = Vec[s].y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;
			Q[newY][newX].push_front(1);
		}
	}
	Vec.clear();
}
// 겨울에는 tmpBoard의 양분만큼 양분을 채워주면 결과값 체크..
void winter() {
	result = 0;
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			board[hang][yal] += tmpBoard[hang][yal];
			result += Q[hang][yal].size();
		}
	}
}