#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

int N, M, T;
int board[51][51];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int checkPoint;
int result;

typedef struct _pos {
	int h, y, dust; // h : ��, y : ��, dust : ������ ����
}pos;
vector<pos> Vec; // �� �࿭�� ������ ������ Vec�� ����
vector<pos> cleanAir; // ����û���� ����..

void upAirrotation(int startH, int startY); // �ݽð���� ���� ������ �Լ�
void downAirrotation(int startH, int startY); // �ð���� ���� ������ �Լ�

int main() {
	//�Է�
	scanf("%d %d %d", &N, &M, &T);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == -1) cleanAir.push_back(pos({ hang, yal, -1 })); // ����û���� ��ġ ����..
		}
	}
	for (int i = 0; i < T; i++) {
		Vec.clear();//�ʱ�ȭ
		// �ð����� ������ �ִ� ���� ��ġ�� ���� ���� ����..
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < M; yal++) {
				if (board[hang][yal] > 0) Vec.push_back(pos({ hang, yal, board[hang][yal] }));
			}
		}
		//���� ��Ʈ����..
		int sz = Vec.size();
		for (int s = 0; s < sz; s++) {
			int dustCnt = Vec[s].dust / 5;
			for (int dir = 0; dir < 4; dir++) {
				int newY = Vec[s].h + dirY[dir];
				int newX = Vec[s].y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || board[newY][newX] == -1) continue;
			board[Vec[s].h][Vec[s].y] -= dustCnt;
			board[newY][newX] += dustCnt;
			}
		}
		// ����û����� ������..
		upAirrotation(cleanAir[0].h, cleanAir[0].y);
		downAirrotation(cleanAir[1].h, cleanAir[1].y);
	}
	//�����
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == 0 || board[hang][yal] == -1) continue;
			result += board[hang][yal];
		}
	}
	// ���
	printf("%d\n", result);
	return 0;
}

void upAirrotation(int startH, int startY) {
	for (int hang = startH - 1; hang > 0; hang--) {
		board[hang][startY] = board[hang - 1][startY];
	}
	for (int yal = startY; yal < M - 1; yal++) {
		board[0][yal] = board[0][yal + 1];
	}
	for (int hang = 0; hang < startH; hang++) {
		board[hang][M - 1] = board[hang + 1][M - 1];
	}
	for (int yal = M - 1; yal > startY + 1; yal--) {
		board[startH][yal] = board[startH][yal - 1];
	}
	board[startH][startY + 1] = 0;
}

void downAirrotation(int startH, int startY) {
	for (int hang = startH + 1; hang < N - 1; hang++) {
		board[hang][startY] = board[hang + 1][startY];
	}
	for (int yal = startY; yal < M - 1; yal++) {
		board[N - 1][yal] = board[N - 1][yal + 1];
	}
	for (int hang = N - 1; hang > startH; hang--) {
		board[hang][M - 1] = board[hang - 1][M - 1];
	}
	for (int yal = M - 1; yal > 1; yal--) {
		board[startH][yal] = board[startH][yal - 1];
	}
	board[startH][startY + 1] = 0;
}