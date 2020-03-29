/*
	https://www.acmicpc.net/problem/16932
	�迭�� �� ĭ���� 0�� 1 ���� �ϳ��� ����ִ�. �� ĭ�� ���� ���� ������ ��, �� ĭ�� �����Ѵٰ� �Ѵ�.
	�迭�� ĭ �ϳ��� ����ִ� ���� �����ؼ� ������ 1�� ���� ū �˰����� ����.

	1�� �����ִ� ������ BFS�� ���� �� ��ȣ�� �Ű� 2���� �迭�� 0���� �����¿츦 ���� �� ���� ���� ��� �������
	���ϸ鼭 ���� ū ������ ã�� �˰��� ����..
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
int board[1001][1001];
bool check[1001][1001];
bool checkNumber[10000001];// 0���� �����¿츦 ���� ���� ������ �湮 üũ..
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
int island;
int islandSize[10000001]; // �� ������ ũ�⸦ �ִ� �迭..
int result; // 0������  �����¿츦 ���� �����
int maxresult; // 0���� ��ȭ�¿츦 ���� �ִ� ������� �̱�����..

typedef struct _pos { // �࿭�� �ִ� struct..
	int h, y;
}pos;

queue<int> QQ; // 0���� ���� ����Ǵ� ���� �־��־� �湮üũ�� Ǯ������ queue
void BFS(int hang, int yal);

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	island = 1;

	for (int hang = 0; hang < N; hang++) { // ����ȣ �ű��..
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == 1 && !check[hang][yal]) {
				BFS(hang, yal);
				island++;
			}
		}
	}

	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < M; yal++) {
			if (board[hang][yal] == 0) { // ���� 0�̶��
				result = 0;
				for (int dir = 0; dir < 4; dir++) {// �����¿츦 ����
					int newY = hang + dirY[dir];
					int newX = yal + dirX[dir];

					if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

					if (board[newY][newX] != 0 && !checkNumber[board[newY][newX]]) { // �����ְ� �湮�� ���� �ƴ϶��
						result += islandSize[board[newY][newX]]; // ���� ũ�⸦ �����ְ�
						checkNumber[board[newY][newX]] = true;
						QQ.push(board[newY][newX]); // �� �� �湮üũ �־��ִ� queue
					}
				}
				int sz = QQ.size();
				for (int s = 0; s < sz; s++) { // �湮�޴� ���� �湮üũ�� Ǯ���ִ� ��.. (�ð��ʰ��� ��������..)
					int p = QQ.front();
					QQ.pop();
					checkNumber[p] = false;
				}

			}
			if (maxresult < result) maxresult = result;
		}
	}
	printf("%d\n", maxresult + 1);

	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	board[hang][yal] = island;
	queue<pos> Q;
	Q.push(pos({ hang, yal }));
	int num = 1;

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

			if (board[newY][newX] == 1 && !check[newY][newX]) {
				check[newY][newX] = true;
				board[newY][newX] = island;
				num++; // ���� ũ��++;
				Q.push(pos({ newY, newX }));
			}
		}
	}
	islandSize[island] = num; // ������ ���� ũ�� �־��ֱ�..
}