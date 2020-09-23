#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

int N, M;
char str[31];
char board[31][31];
bool check[31][31];
int dirY[4] = { -1, 0, 1, 0 };
int dirX[4] = { 0, 1, 0, -1 };
int result;

typedef struct _pos {
	int h, y;
}pos;
vector<pos> Vec;

void DFS(int depth, int hang, int yal, int d, int endd);

int main() {
	//�Է�
	int t = 0;
	while (scanf("%d %d", &N, &M) != EOF) { // N, M���Է��̾��������� �׽�Ʈ���̽���������..
		t++;
		result = 987654321;
		for (int hang = 0; hang < N; hang++) {
			scanf("%s", str);
			for (int yal = 0; yal < M; yal++) {
				board[hang][yal] = str[yal];
				if (board[hang][yal] == '.') Vec.push_back(pos({ hang, yal })); // '.'�� ������ Vec�� �ִ´�..
			}
		}
		// '.'�� ��� ���� DFS�� ����..
		for (int s = 0; s < Vec.size(); s++) {
			check[Vec[s].h][Vec[s].y] = true;
			DFS(0, Vec[s].h, Vec[s].y, -1, Vec.size() -1);
			check[Vec[s].h][Vec[s].y] = false;
		}
		if (result == 987654321) printf("Case %d: -1\n", t);
		else printf("Case %d: %d\n", t, result);
		Vec.clear();
	}
	return 0;
}

void DFS(int depth, int hang, int yal, int d, int endd) {
	vector<pos> dots; // ��Ʈ��ŷ�� �ϱ� ����.. (�������� ����..)
	if (depth >= result) return; // ��������� ũ�� return,..
	if (endd == 0) {
		if (result > depth) result = depth; // ���� ��� ���� �湮�ߴٸ� ����� ����..
		return;
	}

	for (int dir = 0; dir < 4; dir++) {
		if (d == dir) continue;
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];

		if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1 || check[newY][newX] || board[newY][newX] == '*') continue;
		//�����ִ°��̶��.. �� �������� �������������� ����..
		if (!check[newY][newX] && board[newY][newX] == '.') {
			check[newY][newX] = true;
			dots.push_back(pos{ newY, newX });
			int sH = newY, sY = newX;
			while (1) {
				int H = sH + dirY[dir];
				int Y = sY + dirX[dir];

				if (H < 0 || H > N - 1 || Y < 0 || Y > M - 1 || check[H][Y] || board[H][Y] == '*') break;
				
				if (!check[H][Y] && board[H][Y] == '.') {
					check[H][Y] = true;
					dots.push_back(pos({ H, Y }));
					sH = H, sY = Y;
				}
			}
			DFS(depth + 1, sH, sY, dir, endd - dots.size());
			for (int s = 0; s < dots.size(); s++) check[dots[s].h][dots[s].y] = false;
			dots.clear();
		}
	}
}