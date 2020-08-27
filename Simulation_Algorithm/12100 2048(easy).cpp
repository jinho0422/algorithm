#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

int N;
int board[21][21];
int tmpBoard[21][21];
int tmp[5];
int dirY[4] = { -1, 0, 1, 0 };
int dirX[4] = { 0, 1, 0, -1 }; // 0 : 상, 1 : 우, 2 : 하, 3 : 좌
int result;

void DFS(int depth);

int main() {
	//입력
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	// 움직이는 방향 찾기
	DFS(0);
	printf("%d\n", result);
	return 0;
}

void moveBoard(int dir) {
	queue<int> Q;
	switch (dir) {
	case 0 : // 움직임이 '상' 일 때
		for (int yal = 0; yal < N; yal++) {
			int checkNum = -1; // checkNum을 -1로 해놓은 이유는 board의 값과 겹치지 않기 위해..
			for (int hang = 0; hang < N; hang++) {
				if (tmpBoard[hang][yal] == 0) continue;
				if (checkNum == tmpBoard[hang][yal]) { // 만약 checkNum이 tmpBoard[hang][yal]과 같다는 것은 합쳐 질 수 있는것이므로
					Q.push(checkNum * 2); // checkNum의 두배를 Q에 넣는다.
					checkNum = -1; // 초기화
				}
				else if (checkNum != tmpBoard[hang][yal]) { // 만약 checkNum이 다를때는
					if (checkNum == -1) { // 겹쳐질 것이 없던 것이므로
						checkNum = tmpBoard[hang][yal]; // checnNum을 tmpBoard[hang][yal]로
					}
					else { // 만약 -1이 아니면 겹쳐지지 않는 것이므로
						Q.push(checkNum); // checkNum을 Q에 넣고
						checkNum = tmpBoard[hang][yal]; // checkNum을 현재의 tmpBoard[hang][yal] 로 바꿔준다..
					}
				}
				tmpBoard[hang][yal] = 0; // 하나의 줄이 끝나고 Q에 담긴 것들을 넣기위해..
			}
			if (checkNum != -1) Q.push(checkNum); // checkNum이 -1이 아니면 곂쳐지는 것을 확인하기 위해 남아있는 것을 Q에 넣는다
			int sz = Q.size();
			for (int s = 0; s < sz; s++) { // Q 크기만큼 tmpBoard갱신
				tmpBoard[s][yal] = Q.front();
				Q.pop();
			}
		}
		break;

	case 1 : // 우
		for (int hang = 0; hang < N; hang++) {
			int checkNum = -1;
			for (int yal = N -1; yal >= 0; yal--) {
				if (tmpBoard[hang][yal] == 0) continue;
				if (checkNum == tmpBoard[hang][yal]) {
					Q.push(checkNum * 2);
					checkNum = -1;
				}
				else if (checkNum != tmpBoard[hang][yal]) {
					if (checkNum == -1) {
						checkNum = tmpBoard[hang][yal];
					}
					else {
						Q.push(checkNum);
						checkNum = tmpBoard[hang][yal];
					}
				}
				tmpBoard[hang][yal] = 0;
			}
			if (checkNum != -1) Q.push(checkNum);
			int sz = Q.size();
			for (int s = 0; s < sz; s++) {
				tmpBoard[hang][N -1 - s] = Q.front();
				Q.pop();
			}
		}
		break;

	case 2 : // 하
		for (int yal = 0; yal < N; yal++) {
			int checkNum = -1;
			for (int hang = N -1; hang >= 0; hang--) {
				if (tmpBoard[hang][yal] == 0) continue;
				if (checkNum == tmpBoard[hang][yal]) {
					Q.push(checkNum * 2);
					checkNum = -1;
				}
				else if (checkNum != tmpBoard[hang][yal]) {
					if (checkNum == -1) {
						checkNum = tmpBoard[hang][yal];
					}
					else {
						Q.push(checkNum);
						checkNum = tmpBoard[hang][yal];
					}
				}
				tmpBoard[hang][yal] = 0;
			}
			if (checkNum != -1) Q.push(checkNum);
			int sz = Q.size();
			for (int s = 0; s < sz; s++) {
				tmpBoard[N -1 - s][yal] = Q.front();
				Q.pop();
			}
		}
		break;

	case 3 : // 좌
		for (int hang = 0; hang < N; hang++) {
		int checkNum = -1;
		for (int yal = 0; yal < N; yal++) {
			if (tmpBoard[hang][yal] == 0) continue;
			if (checkNum == tmpBoard[hang][yal]) {
				Q.push(checkNum * 2);
				checkNum = -1;
			}
			else if (checkNum != tmpBoard[hang][yal]) {
				if (checkNum == -1) {
					checkNum = tmpBoard[hang][yal];
				}
				else {
					Q.push(checkNum);
					checkNum = tmpBoard[hang][yal];
				}
			}
			tmpBoard[hang][yal] = 0;
		}
		if (checkNum != -1) Q.push(checkNum);
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			tmpBoard[hang][s] = Q.front();
			Q.pop();
		}
	}
		break;
	}
}

void DFS(int depth) {
	// 5번의 움직이는 방향 5개를 (0, 1, 2, 3) 을 찾으면
	if (depth == 5) {
		memcpy(tmpBoard, board, sizeof(tmpBoard)); // board를 tmpBoard에 복사해서 tmpBoard로 파악
		for (int d = 0; d < 5; d++) {
			moveBoard(tmp[d]); // 5번의 움직임을 체크..
		}

		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < N; yal++) {
				if (result < tmpBoard[hang][yal]) result = tmpBoard[hang][yal];
			}
		}
		return;
	}

	for (int i = 0; i < 4; i++) {
		tmp[depth] = i;
		DFS(depth + 1);
		tmp[depth] = 0;
	}
}