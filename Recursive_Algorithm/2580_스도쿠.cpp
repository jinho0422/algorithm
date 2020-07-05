#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int board[10][10];
bool checkHang[10][10];
bool checkYal[10][10];
bool check[10][10];
bool flag;

typedef struct _pos {
	int h, y;
}pos;

pos zero[81];
int num;

void DFS(int depth);

int main() {
	for (int hang = 0; hang < 9; hang++) {
		for (int yal = 0; yal < 9; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 0) zero[num++] = { hang, yal };
			else {
				checkHang[hang][board[hang][yal]] = true;
				checkYal[board[hang][yal]][yal] = true;
				check[(hang / 3 * 3) + yal / 3][board[hang][yal]] = true;
			}
		}
	}

	DFS(0);

	return 0;
}

void DFS(int depth) {
	if (flag) return;
	if (depth == num) {
		flag = true;
		for (int hang = 0; hang < 9; hang++) {
			for (int yal = 0; yal < 9; yal++) {
				printf("%d ", board[hang][yal]);
			}
			printf("\n");
		}
		return;
	}
	for (int i = 1; i <= 9; i++) {
		if (!checkHang[zero[depth].h][i] && !checkYal[i][zero[depth].y] && !check[zero[depth].h / 3 * 3 + zero[depth].y / 3][i]) {
			checkHang[zero[depth].h][i] = true;
			checkYal[i][zero[depth].y] = true;
			check[zero[depth].h / 3 * 3 + zero[depth].y / 3][i] = true;
			board[zero[depth].h][zero[depth].y] = i;
			DFS(depth + 1);
			checkHang[zero[depth].h][i] = false;
			checkYal[i][zero[depth].y] = false;
			check[zero[depth].h / 3 * 3 + zero[depth].y / 3][i] = false;
			board[zero[depth].h][zero[depth].y] = 0;
		}
	}
}