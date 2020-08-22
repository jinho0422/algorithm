#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

int N, M;
int board[51][51];
int check[14];
int result;

typedef struct _pos {
	int h, y;
}pos;

vector<pos> home; // ���� ��ǥ�� �ִ� vector
vector<pos> chicken; // ġŲ���� ��ǥ���ִ� vector

void DFS(int depth, int start);

int main() {
	//�Է�
	result = 214700000;
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) home.push_back(pos({ hang, yal }));
			if (board[hang][yal] == 2) chicken.push_back(pos({ hang, yal }));
		}
	}
	DFS(0, 0);
	printf("%d\n", result);
	return 0;
}
void DFS(int depth, int start) {
	//���� ���ϴ� ġŲ���� ������ ����
	if (depth == M) {
		int movesum = 0; // ������ ġŲ���Ÿ��� �ּҸ� ��� ���� ��
		// �ϳ��� ġŲ������ ��� ���� �� ���鼭 �ּ��� �Ÿ��� ã�Ƽ� movemin����
		for (int i = 0; i < home.size(); i++) {
			int movemin = 214700000; // ������ �ּ��� �Ÿ��� �ִ� ġŲ�� �Ÿ�
			for (int j = 0; j < depth; j++) {
				int chH = chicken[check[j]].h;
				int chY = chicken[check[j]].y;

				int move = abs(home[i].h - chH) + abs(home[i].y - chY);
				if (movemin > move) movemin = move;
			}
			movesum += movemin;
		}
		// ġŲ���߿� �����ؼ� ���� �� ��� ���� ���� ���� �Ÿ��� �ִ� ġŲ���� ���� �Ÿ� ����
		if (result > movesum) result = movesum;
		return;
	}
	for (int i = start; i < chicken.size(); i++) {
		check[depth] = i;
		DFS(depth + 1, i + 1);
		check[depth] = 0;
	}
}