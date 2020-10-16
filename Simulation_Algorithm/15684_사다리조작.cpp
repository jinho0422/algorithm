#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

int N, M, H;
bool check[33][12];
int result;
bool resultFlag;

typedef struct _pos {
	int h, y;
}pos;

vector<pos> Vec; // ��ٸ��� ���� �� �ִ� �� ����..

void DFS(int depth, int start);

int main() {
	//�Է�
	result = 10;
	scanf("%d %d %d", &N, &M, &H);
	for (int a, b, i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		check[a][b + 1] = true;
	}
	// ��ٸ��� ���� �� �ִ� ���̸� vector�� �ִ´�.
	for (int hang = 1; hang <= H; hang++) {
		for (int yal = 1; yal < N; yal++) {
			if (check[hang][yal]) continue;
			int newY = hang;
			int newX = yal + 1;

			if (!check[newY][newX]) Vec.push_back(pos({ hang, yal }));
		}
	}

	DFS(0, 0);
	//���
	if (resultFlag) printf("%d\n", result);
	else printf("-1\n");
	return 0;
}
// ��ٸ� Ÿ��..
bool solve() {
	for (int i = 1; i <= N; i++) {
		int sh = 1, sy = i; // ������ ��� ��
		int befh = 1, befy = i; // ���� �����
		while (1) {
			if (check[sh][sy]) {
				if (sh == 1 && sy == i) {
					befh = sh, befy = sy;
					sy--;
				}
				else {
					if (sh == befh && sy - 1 == befy) {
						befh = sh, befy = sy;
						sh++;
					}
					else {
						befh = sh, befy = sy;
						sy--;
					}
				}
			}
			else if (!check[sh][sy]) {
				if (check[sh][sy + 1]) {
					if (sh == 1 && sy == i) {
						befh = sh, befy = sy;
						sy++;
					}
					else {
						if (sh == befh && sy + 1 == befy) {
							befh = sh, befy = sy;
							sh++;
						}
						else {
							befh = sh, befy = sy;
							sy++;
						}
					}
				}
				else {
					befh = sh, befy = sy;
					sh++;
				}
			}
			if (sh > H) {
				if (sy != i) return false;
				break;
			}
		}
	}
	return true;
}

// 3�� ������ ��ٸ� ������ �ؼ� �������� ����..
void DFS(int depth, int start) {
	if (result <= depth) return;
	if (depth <= 3) {
		bool flag = solve();	
		if (flag) {
			resultFlag = true;
			if (result > depth) result = depth;
			return;
		}
		if (depth == 3) return;
	}

	for (int i = start; i < Vec.size(); i++) {
		if (!check[Vec[i].h][Vec[i].y]) {
			int newY = Vec[i].h;
			int newX = Vec[i].y + 1;
			if (!check[newY][newX]) {
				check[newY][newX] = true;
				DFS(depth + 1, i + 1);
				check[newY][newX] = false;
			}
		}
	}
}