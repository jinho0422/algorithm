#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int N, M;
char str[1004];
char board[1004][1004];
bool Jcheck[1004][1004];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int moveResult;
bool flag;
// 불과 지훈이의 위치를 확인하기 위한 struct..
typedef struct _pos {
	int h, y;
}pos;

queue<pos> fQ; // 불의 위치를 저장하기 위한 queue
queue<pos> jQ; // 지훈이의 움직인 위치를 저장하기 위한 queue

void BFS();

int main() {
	//입력
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == 'F') fQ.push(pos({ hang, yal })); // 불이면 fQ에 위치 저장
			
			if (board[hang][yal] == 'J') { // 지훈이면 jQ에 위치 저장
				Jcheck[hang][yal] = true;
				jQ.push(pos({ hang, yal }));
			}
		}
	}
	BFS();
	if (!flag) printf("IMPOSSIBLE\n"); // 탈출이 가능하지 않으면 출력..
	return 0;
}

void BFS() {
	moveResult = 1; // 지훈이가 움직인 결과값..
	while (!jQ.empty()) { // 지훈이가 움직일 수 있는 위치가 없을때까지..
		int fsz = fQ.size(); // fQ의 크기만큼 불이 움직일 수 있는 곳을 찾는다..
		for (int s = 0; s < fsz; s++) {
			pos fp = fQ.front();
			fQ.pop();
			for (int dir = 0; dir < 4; dir++) {
				int newY = fp.h + dirY[dir];
				int newX = fp.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;
				// 움직일 수있는 위치가 J 이거나 . 이면 그위치에 F를 설정하고 불을 움직인다..
				if (board[newY][newX] == 'J' || board[newY][newX] == '.') {
					board[newY][newX] = 'F';
					fQ.push(pos({ newY, newX }));
				}
			}
		}

		int jsz = jQ.size();
		for (int s = 0; s < jsz; s++) {
			pos jp = jQ.front();
			jQ.pop();
			if (jp.h == 0 || jp.h == N - 1 || jp.y == 0 || jp.y == M - 1) { // 빌딩의 끝쪽에 있으면 탈출 할 수 있으므로 결과값을 출력한다..
				printf("%d\n", moveResult);
				flag = true;
				return;
			}
			for (int dir = 0; dir < 4; dir++) {
				int newY = jp.h + dirY[dir];
				int newX = jp.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

				if (board[newY][newX] == '.' && !Jcheck[newY][newX]) { // 지훈이가 갔던 곳이 아니고 '.'이면 움직인다..
					Jcheck[newY][newX] = true;
					jQ.push(pos({ newY, newX }));
					board[newY][newX] = 'J'; // 움직임을 넣어주고
					if (board[jp.h][jp.y] == 'J') board[jp.h][jp.y] = '.'; // 만약 지훈이가 있던곳인데 불이 옮겨붙었다면 그대로 놓고 J가 있으면 '.'으로 바꿔준다.
				}
			}
		}
		moveResult++;
	}
}