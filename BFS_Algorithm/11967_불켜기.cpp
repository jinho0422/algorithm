/*
	N * N�갣���� ����� �������ϴ� �ϼ� ���ô� �ִ��� ���� �濡 ���� ������ �;��Ѵ�.
	���ô� �����ϰ� ���� �����ִ� ����(1,1)�濡�� ����ϰ� � �濡�� �ٸ����� ���� ���� �� �� �ִ� ����ġ�� �޷��ִ�.
	���ô� ���� �����ִ� �����θ� �� �� �ְ�, �� �濡���� �����¿쿡 ������ ������ ������ �� �ִ�.
	�ִ��� ���� ���� ���� ų �� �ִ� �˰����� ����..

	(1,1)�濡���� ���� �Ѱ� �湮�ߴ� ���� ���½�Ű�� �ٽ� (1,1)���� �����Ͽ� �� �� �ִ� ���� ã��
	�װ����� ���� ų �� �ִ� ���� ��Ű�� ���½�Ű�� �� �� �ִ� ���� ã���鼭 �˰����� ����..

	
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
bool check[101][101]; // ���� �״��� �Ǵ��ϴ� check�迭
bool visited_check[101][101];// �湮�� ������ �Ǵ��ϴ� visited_check�迭..
int result;
int main_result;
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };

typedef struct _pos {
	int h, y;
}pos;

vector<pos> Vec[101][101]; // (x, y)���� ���� �� �� �ִ� �갣�� �����ϴ� Vector..
queue<pos> Q; // �湮�� ���ִ� ���� �����ϱ� ���� Q..

void BFS(int hang, int yal);

int main() {
	scanf("%d %d", &N, &M);
	for (int x, y, a, b, i = 0; i < M; i++) {
		scanf("%d %d %d %d", &x, &y, &a, &b);
		Vec[x][y].push_back(pos({ a, b }));
	}

	Q.push(pos({ 1, 1 })); // �� ó�� �갣�� ���� ���� 1, 1�� �湮..
	check[1][1] = true; // 1, 1�갣�� ���� Ų��..
	result = 1;

	while (!Q.empty()) {
		int sz = Q.size();

		for (int s = 0; s < sz; s++) { // �湮�� �� �ִ� �갣���� ���� �������ִ� �갣�� ���� Ų��..
			pos p = Q.front();
			Q.pop();

			int Vsz = Vec[p.h][p.y].size();

			for (int s1 = 0; s1 < Vsz; s1++) {
				int first = Vec[p.h][p.y][s1].h;
				int second = Vec[p.h][p.y][s1].y;

				if (!check[first][second]) {
					check[first][second] = true;
					result++;
				}
			}

		}

		if (main_result == result) break; // ���̻� ���� ų �� ������ while ���� ����������
		else main_result = result; // �ƴϸ� ���� �����ϰ� while���� ����..

		memset(visited_check, false, sizeof(visited_check)); // �湮�ߴ� ���� ���½�Ű��
		BFS(1, 1); // BFS�� ���ؼ� 1, 1���� �����¿츦 ���Ǹ鼭 �湮�� �� �ִ� ���� �������� ���� Q�� �ִ´�....
	}
	printf("%d\n", result);

	return 0;
}


void BFS(int hang, int yal) {
	visited_check[hang][yal] = true;
	queue<pos> re_Q;
	re_Q.push(pos({ hang, yal}));

	while (!re_Q.empty()) {
		pos p = re_Q.front();
		re_Q.pop();
		Q.push(pos({ p.h, p.y }));

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY <= 0 || newY > N || newX <= 0 || newX > N) continue;

			if (!visited_check[newY][newX] && check[newY][newX]) {
				re_Q.push(pos({ newY, newX }));
				visited_check[newY][newX] = true;
			}
		}
	}
}