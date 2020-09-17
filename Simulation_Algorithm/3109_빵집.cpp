#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
char str[502];
char board[10002][502];
bool check[10002][502];
int dirY[3] = { -1, 0, 1 };
int dirX[3] = { 1, 1, 1 };
int result;
bool flag;
bool resultFlag;

typedef struct _pos {
	int h, y;
}pos;

void DFS(int hang, int yal);

int main() {
	//입력
	scanf("%d %d", &N, &M);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < M; yal++) {
			board[hang][yal] = str[yal];
		}
	}
	// 열의 맨 왼쪽을 DFS로 맨 오른쪽까지 갈 수 있는지 확인..
	for (int hang = 0; hang < N; hang++) {
		flag = false; //  가스관이 맨 오른쪽까지 갔는지 확인하는 flag
		DFS(hang, 0);
		if (resultFlag) break; // 가스관을 설치하는 것을 오른쪽 위 대각선, 오른쪽, 오른쪽 아래 대각선으로 했으므로
	}
	//출력
	printf("%d\n", result);
	return 0;
}

void DFS(int hang, int yal) {
	if (flag) return; // 가스관이 설치됬으면 return..
	if (resultFlag) return; // 더이상 가스관을 연결할 수 없을때는 return..
	if (yal == M - 1) { // 맨 오른쪽 열에 가스관이 연결되었을때..
		result++;
		flag = true;
		return;
	}
	for (int dir = 0; dir < 3; dir++) {
		if (flag) return; // 가스관이 설치됬으면 return..
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];

		if (newY < 0 || newY > N - 1 || newX < 0 || newX > M - 1) {
			if (newX == M) resultFlag = true; // 만약 행의 마지막에 닿게되면 그 밑에는 가스관을 더이상 설치할 수 없으므로 resultFlag true로 해놓고 빠져나간다.
			continue;
		}
		if (!check[newY][newX] && board[newY][newX] == '.') {
			check[newY][newX] = true;
			DFS(newY, newX);
		}
	}
}