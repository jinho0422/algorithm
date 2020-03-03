/*
 N*N ü���ǿ��� ���� ������ K���� ����Ͽ� 4���̻��� ���� ���̸� ������� ����Ѵ�.
 ü������ �� ĭ�� ���, ������, �Ķ������� �Ǿ��ְ�  1 ~ K���� ������� �����̸� �ѹ��� ������� �����Ѵ�.
 ���� �ִ� �ڸ����� �����Ϸ��� ü������ ���� ����̸� ���۸����� �� ���� ���� �״�� �����Ϸ��� ü�������� �̵��ϰ�
 �������̸� ������ �ٲ㼭 �̵�, �Ķ����̸� ������ �ٲ㼭 �̵��Ѵ�..
 */


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
int board[15][15];
int dirY[5] = { 0, 0, 0, -1, 1 };
int dirX[5] = { 0, 1, -1, 0, 0 };


deque<int> Q[15][15]; // �� ü���ǿ� ��� ���� �ִ��� Ȯ���ϱ� ���� Q..
int tmp[15]; // ���� ������ �� ������ ü�����̸� ������ �ٲ㼭 �����̱� ����..

typedef struct _pos1 { // ���� ��� �� �����̴� ������ �־��ִ� struct
	int h, y, d;
}pos1;
pos1 holes[13]; 



int change_D(int d) { // �Ķ��� or ü������ ����� ������ �ٲ��ֱ� ���� �Լ�..
	if (d == 1) return 2;
	else if (d == 2) return 1;
	else if (d == 3) return 4;
	else if (d == 4) return 3;
}

int main() {
	scanf("%d %d", &N, &K);
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	for (int a, b, c, i = 1; i <= K; i++) {
		scanf("%d %d %d", &a, &b, &c);
		Q[a][b].push_front(i); // ���� ��ȣ�� �־��ֱ�..
		holes[i] = { a, b, c }; // ���� ������ �־��ֱ�..
	}
	int result = 0;

	while (1) {
		result++;
		if (result > 1000) { // ������� 1000�� ������ ���и� ����.
			printf("-1\n");
			return 0;
		}
		for (int i = 1; i <= K; i++) {
			int ih = holes[i].h; // ������ ���� ������ ih, iy, id�� ����..
			int iy = holes[i].y;
			int id = holes[i].d;

			int sz = Q[ih][iy].size(); // i��° ���� �ִ� ť������ ����� üũ..
			bool flag = false;

			for (int s = 0; s < sz; s++) {
				if (flag) break; // i��° ���� ã�� ������ �� ������ ���� ��������..
				int p = Q[ih][iy].front();

				if (i != p) { // Q�� �ִ� ���� ���ϴ� ���� �ƴ� ���� Q�� �ڷ� �Ű��ش�.
					Q[ih][iy].pop_front();
					Q[ih][iy].push_back(p);
				}

				else if (i == p) { // i ��° ���� ��Ÿ���� 
					flag = true;
					int newY = ih + dirY[id];
					int newX = iy + dirX[id];

					if (newY <= 0 || newY > N || newX <= 0 || newX > N || board[newY][newX] == 2) {
						// �����Ϸ��� ü������ �Ķ����̰ų� ü���� ������ �����..
						int newD = change_D(id); // ���� ������ �ٲ��ְ�

						int nnewY = ih + dirY[newD];
						int nnewX = iy + dirX[newD];
						holes[i].d = newD; // ���� ���������� �ٽ�����..

						if (nnewY <= 0 || nnewY > N || nnewX <= 0 || nnewX > N || board[nnewY][nnewX] == 2) {
							//������ �مf�� �� �ٽ� �Ķ����� ü������ �����..
							for (int s1 = 0; s1 < sz - s; s1++) { // ���󺹱�..
								int p1 = Q[ih][iy].front();
								Q[ih][iy].pop_front();
								Q[ih][iy].push_back(p1);
							}
						}
						else if (board[nnewY][nnewX] == 1) { // �����Ϸ��� ü������ �������̸�
							int num = 0;
							for (int s1 = 0; s1 < sz - s; s1++) { // i��°������ ������ ���� tmp�� �����ϰ�
								int p1 = Q[ih][iy].front();
								Q[ih][iy].pop_front();

								tmp[num++] = p1;
							}
							for (int s1 = num - 1; s1 >= 0; s1--) { // �����Ϸ��� ü�������� �ݴ�� �־��ش�.
								holes[tmp[s1]].h = nnewY; // ���� ������ �ٲ��ش�.
								holes[tmp[s1]].y = nnewX;
								Q[nnewY][nnewX].push_back(tmp[s1]);
							}
							if (Q[nnewY][nnewX].size() >= 4) { // �����̰� ���� ������ ���� ���� 4���̻����� Ȯ��..
								printf("%d\n", result);
								return 0;
							}
						}
						else if (board[nnewY][nnewX] == 0) { // �����Ϸ��� ü������ ����̸� ������ ������ ���� �ִ� ������ ���� ü�������� �̵�..
							for (int s1 = 0; s1 < sz - s; s1++) {
								int p1 = Q[ih][iy].front();
								Q[ih][iy].pop_front();

								holes[p1].h = nnewY; // ���� ������ �ٲ��ش�.
								holes[p1].y = nnewX;
								Q[nnewY][nnewX].push_back(p1);
							}
							if (Q[nnewY][nnewX].size() >= 4) {// �����̰� ���� ������ ���� ���� 4���̻����� Ȯ��..
								printf("%d\n", result);
								return 0;
							}
						}
					}

					else if (board[newY][newX] == 1) { // �����Ϸ��� ü������ �������϶�..
						int num1 = 0;
						for (int s1 = 0; s1 < sz - s; s1++) {
							int p1 = Q[ih][iy].front();
							Q[ih][iy].pop_front();
							tmp[num1++] = p1;
						}

						for (int s1 = num1 - 1; s1 >= 0; s1--) {
							holes[tmp[s1]].h = newY;
							holes[tmp[s1]].y = newX;
							Q[newY][newX].push_back(tmp[s1]);
						}
						if (Q[newY][newX].size() >= 4) {
							printf("%d\n", result);
							return 0;
						}
					}

					else if (board[newY][newX] == 0) { // �����Ϸ��� ü������ ����� ��..
						for (int s1 = 0; s1 < sz - s; s1++) {
							int p1 = Q[ih][iy].front();
							Q[ih][iy].pop_front();

							holes[p1].h = newY;
							holes[p1].y = newX;
							Q[newY][newX].push_back(p1);
						}

						if (Q[newY][newX].size() >= 4) {
							printf("%d\n", result);
							return 0;
						}
					}
				}
			}
		}
	}
}
