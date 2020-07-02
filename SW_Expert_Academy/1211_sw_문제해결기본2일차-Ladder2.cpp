#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

int board[100][100];
bool check[100][100];
int dirY[2] = { 0, 0 };
int dirX[2] = { -1, 1 };
int min_length;
int result;

typedef struct _pos {
	int h, y, cnt;
}pos;

vector<int> Vec;

void searchEnd(int start);

int main() {
	freopen("test.txt", "r", stdin);
	for (int i, t = 1; t <= 10; t++) {
		//��ٸ� �Է¹ޱ�
		min_length = 2147000000;
		scanf("%d", &i);
		for (int hang = 0; hang < 100; hang++) {
			for (int yal = 0; yal < 100; yal++) {
				scanf("%d", &board[hang][yal]);
				// ù��° ��Ŀ��� ��ٸ��� Ż �� �ִ� ���� ����!
				if (hang == 0) {
					if (board[hang][yal] == 1) {
						Vec.push_back(yal);
					}
				}
			}
		}
		for (int s = 0; s < Vec.size(); s++) {
			//��ٸ��� Ż �� �ִ� ��������� ������������ �������� �Ǵ�.
			searchEnd(Vec[s]);
			//���� ��� ����� ���� visitcheck ����.
			memset(check, false, sizeof(check));	
		}
		printf("#%d %d\n", t, result);
		// ���� �׽�Ʈ ���̽��� ���� ����� ����!
		Vec.clear();
	}
	return 0;
}


void searchEnd(int start) {
	queue<pos> Q;
	check[0][start] = true;
	Q.push(pos({ 0, start, 0 }));
	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		// ���������� ã���� �� ������� result�� �־��ش�.
		if (p.h == 99) {
			//������ �Ÿ��� �ּ��̸� �϶�
			if (min_length >= p.cnt) {
				min_length = p.cnt;
				result = start;
			}
			break;
		}
		bool sideFlag = false;
		//�� �� �� ���ǰ� �� �쿡 �� ���� ������ queue�� �־��ش�.
		for (int dir = 0; dir < 2; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];
			// ��ٸ��� �ƴѰ����� ���� continue;
			if (newY < 0 || newY > 99 || newX < 0 || newX > 99) continue;

			if (board[newY][newX] != 0 && !check[newY][newX]) {
				check[newY][newX] = true;
				sideFlag = true;
				Q.push(pos({ newY, newX, p.cnt + 1}));
			}
		}
		//�� �쿡 �� ���� ������ �Ʒ��� �����Ѵ�.
		if (!sideFlag) {
			check[p.h + 1][p.y] = true;
			Q.push(pos({ p.h + 1, p.y, p.cnt + 1}));
		}
	}
}