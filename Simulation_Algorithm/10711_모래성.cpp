/*
  N*M ũ���� ���忡�� '.'�� �ٴ��̰�, '1'~'9'������ ưư���� �����̴�.
  ��, ��, ��, ��, �밢���� ���� �ٴ��� ������ ưư���� �������� ���ų� ������ �𷡼��� ��������.
  �𷡼��� �������� �ʴ� �ð��� ���ϴ� �����̴�.

  ó������ �𷡼��� Q�� �־ �𷡼��� ������������ �Ǵ��ϰ� �������� �Ǵٸ� Q�� �ְ�
  �ƴϸ� ���� Q�� �ٽó־� �Ǵٸ� Q�� �ִ� ���� '.'�ٴٷ� ����� �ٽ� ������ �Ͽ���.
  ������ �������� ��������� ��, ��, ��, ��, �밢���� �Ǵ��ؾߵǼ� �ð��ʰ��� �߻��ߴ�.
  �׷��� �ٴٸ� Q�� �ְ� ��, ��, ��, ��, �밢���� ���鼭 �𷡼��̸� count�Ͽ� �𷡼��� �μ����� 
  ��찡 ����� Vector�� �־� �ٴٷ� ������ְ� �װ��� Q�� �־� �����ָ鼭 ��Ȳ�� �ذ��ߴ�.
  */


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
char str[1001];
char board[1001][1001];
int count_board[1001][1001]; // �𷡼��� �μ��������� conut�ϱ� ���� ����..
bool check[1001][1001]; // �𷡼��� �μ��� �������� �Ǵ��ϴ� check
int dirY[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dirX[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int result;

typedef struct _pos {
	int h, y;
}pos;

vector<pos> Vec; // �μ��� �� �ִ� �𷡼��� �ִ� Vector
queue<pos> Q; // �ٴٸ� �ִ� Q..

int main() {
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
			if (board[hang][yal] == '.') Q.push(pos({ hang, yal })); // �ٴ��� ���� Q�� �ִ´�.
		}
	}


	while (1) {

		bool result_flag = false; // ���̻� �𷡼��� �μ����� �ʴ��� �μ��� �� �ִ����� �Ǵ�..

		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();


			for (int dir = 0; dir < 8; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];

				if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) continue;

				if (board[newY][newX] != '.' && !check[newY][newX]) { // �μ����� ���� �𷡼��̸�..
					count_board[newY][newX] += 1; // �ٴٿ� �����ϰ� �����Ƿ� �𷡼��� count�� ����..
					if (count_board[newY][newX] >= board[newY][newX] - '0') {// �𷡼��� ưư�Ժ��� ������ �ٴٰ� ũ�ų� ������
						check[newY][newX] = true; // �𷡼��� �μ��� �� �ִ� �Ǵ��ϰ�
						Vec.push_back(pos({ newY, newX })); // Vector�� �ִ´�.
						result_flag = true;// ������� ������ �� �ִٴ� �Ǵ�..
					}
				}
			}
		}

		int Vsz = Vec.size();
		for (int s = 0; s < Vsz; s++) {
			pos p = Vec[s];
			Q.push(pos({ p.h, p.y })); // �ٴٸ� Q�� �ִ� ����..
			board[p.h][p.y] = '.'; // �μ��� �𷡼��� �ٴٷ� ����� ����..
		}
		Vec.clear();// Q�������ٴٸ� Ŭ����..

		if (result_flag) result++;
		else break;
	}

	printf("%d\n", result);
	return 0;
}