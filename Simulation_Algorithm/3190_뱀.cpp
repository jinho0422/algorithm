#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, K, L;
int time;
char direction;
bool appleCheck[102][102];
bool snakeCheck[102][102];
int dirY[4] = { 0, 1, 0, -1 };
int dirX[4] = { 1, 0, -1, 0 };
int timeResult;

typedef struct _pos {
	int h, y, dd; // h : 행, y : 열, dd : 움직이는 방향
}pos;
deque<pos> Q;
typedef struct _pos1 {
	int t; // t : 시간
	char c; // c : 회전하는 방향
}pos1;
vector<pos1> Vec;

void solve(int hang, int yal, int d);

int main() {
	//입력
	scanf("%d %d", &N, &K);
	for (int a, b, i = 0; i < K; i++) {
		scanf("%d %d", &a, &b);
		appleCheck[a][b] = true;
	}
	scanf("%d", &L);
	for (int i = 0; i < L; i++) {
		scanf("%d %c", &time, &direction);
		Vec.push_back(pos1({ time, direction }));
	}
	Vec.push_back(pos1({ -1, -1 })); // 회전을 처리하는 Vec에 마지막을 위해서..
	solve(1, 1, 0);
	//출력
	printf("%d\n", timeResult);

	return 0;
}

void solve(int hang, int yal, int d) {
	snakeCheck[hang][yal] = true;
	timeResult = 0; // 시간결과값
	int cnt = 0; // 회전을 하는지 확인하기 위한 cnt..
	Q.push_back(pos({ hang, yal, d }));
	while (1) {
		pos p = Q.front();
		int newY = p.h + dirY[p.dd];
		int newX = p.y + dirX[p.dd];
		if (newY <= 0 || newY > N || newX <= 0 || newX > N || snakeCheck[newY][newX]) {
			timeResult++;
			break;
		}
		// 움직인 공간에 사과가 있으면
		if (appleCheck[newY][newX] && !snakeCheck[newY][newX]) {
			snakeCheck[newY][newX] = true;
			appleCheck[newY][newX] = false;
			Q.push_front(pos({ newY, newX, p.dd }));
		}
		//움직인 공간에 사과가 없으면 뱀의 꼬리를 잘라낸다
		if (!appleCheck[newY][newX] && !snakeCheck[newY][newX]) {
			snakeCheck[newY][newX] = true;
			Q.push_front(pos({ newY, newX, p.dd }));
			pos q = Q.back();
			Q.pop_back();
			snakeCheck[q.h][q.y] = false;
		}
		timeResult++; // 결과값 증가

		if (Vec[cnt].t == timeResult) { // 움직인 시간에서 회전을 해야된다면..
			if(Vec[cnt].c == 'D') { // 시계방향회전
				pos f = Q.front(); // 뱀의 머리를 회전시킨다..
				Q.pop_front();
				f.dd++;
				if (f.dd == 4) f.dd = 0;
				Q.push_front(pos({ f.h, f.y, f.dd }));
			}
			else { // 반시계방향회전
				pos f = Q.front();
				Q.pop_front();
				f.dd--;
				if (f.dd == -1) f.dd = 3;
				Q.push_front(pos({ f.h, f.y, f.dd }));
			}
			cnt++; // 다음 회전하는 시간을 체크하기위해..
		}
	}
}