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
int dirX[4] = { 0, 1, 0, -1 }; // 0 : ��, 1 : ��, 2 : ��, 3 : ��
int result;

void DFS(int depth);

int main() {
	//�Է�
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	// �����̴� ���� ã��
	DFS(0);
	printf("%d\n", result);
	return 0;
}

void moveBoard(int dir) {
	queue<int> Q;
	switch (dir) {
	case 0 : // �������� '��' �� ��
		for (int yal = 0; yal < N; yal++) {
			int checkNum = -1; // checkNum�� -1�� �س��� ������ board�� ���� ��ġ�� �ʱ� ����..
			for (int hang = 0; hang < N; hang++) {
				if (tmpBoard[hang][yal] == 0) continue;
				if (checkNum == tmpBoard[hang][yal]) { // ���� checkNum�� tmpBoard[hang][yal]�� ���ٴ� ���� ���� �� �� �ִ°��̹Ƿ�
					Q.push(checkNum * 2); // checkNum�� �ι踦 Q�� �ִ´�.
					checkNum = -1; // �ʱ�ȭ
				}
				else if (checkNum != tmpBoard[hang][yal]) { // ���� checkNum�� �ٸ�����
					if (checkNum == -1) { // ������ ���� ���� ���̹Ƿ�
						checkNum = tmpBoard[hang][yal]; // checnNum�� tmpBoard[hang][yal]��
					}
					else { // ���� -1�� �ƴϸ� �������� �ʴ� ���̹Ƿ�
						Q.push(checkNum); // checkNum�� Q�� �ְ�
						checkNum = tmpBoard[hang][yal]; // checkNum�� ������ tmpBoard[hang][yal] �� �ٲ��ش�..
					}
				}
				tmpBoard[hang][yal] = 0; // �ϳ��� ���� ������ Q�� ��� �͵��� �ֱ�����..
			}
			if (checkNum != -1) Q.push(checkNum); // checkNum�� -1�� �ƴϸ� �������� ���� Ȯ���ϱ� ���� �����ִ� ���� Q�� �ִ´�
			int sz = Q.size();
			for (int s = 0; s < sz; s++) { // Q ũ�⸸ŭ tmpBoard����
				tmpBoard[s][yal] = Q.front();
				Q.pop();
			}
		}
		break;

	case 1 : // ��
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

	case 2 : // ��
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

	case 3 : // ��
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
	// 5���� �����̴� ���� 5���� (0, 1, 2, 3) �� ã����
	if (depth == 5) {
		memcpy(tmpBoard, board, sizeof(tmpBoard)); // board�� tmpBoard�� �����ؼ� tmpBoard�� �ľ�
		for (int d = 0; d < 5; d++) {
			moveBoard(tmp[d]); // 5���� �������� üũ..
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