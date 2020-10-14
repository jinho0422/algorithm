#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;
int N;
int board[17][17];
bool check[17][17];
int dirY[3] = { 0, 1, 1 }; // 0 : 오른쪽, 1 : 대각오른쪽, 2: 아래쪽
int dirX[3] = { 1, 1, 0 };
int result;

void DFS(int hang, int yal, int d, int f);

int main() {
	//입력
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	check[0][0] = check[0][1] = true;
	// 도착점 벽(1)이 아니면 DFS
	if(board[N -1][N -1] == 0) DFS(0, 1, 0, N - 1); // hang, yal, 움직이는 방향, 끝나는 점
	//출력
	printf("%d\n", result);
	return 0;
}
// 현재의 위치에서 오른쪽 아래쪽 대각선오른쪽 모두 아무것도 없으면 true 반환
bool moveCheck(int hang, int yal) {

	for (int dir = 0; dir < 3; dir++) {
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];

		if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[newY][newX] == 1 || check[newY][newX]) return false;
	}
	return true;
}

void DFS(int hang, int yal, int d, int f) {
	//도착지점에 도착하면 결과값 + 1
	if (hang == N - 1 && yal == N - 1) {
		result++;
		return;
	}
	//파이프 움직이는 방향을 보고
	for (int dir = 0; dir < 3; dir++) {
		if ((d == 0 && dir == 2) || d == 2 && dir == 0) continue; // 이전이 가로로 있을때는 세로로 파이프를못놓고, 반대로도 못놓으므로 continue
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];
		// 아래쪽과 오른쪽으로 파이프가 이동할때
		if (dir == 0 || dir == 2) {
			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[newY][newX] == 1) continue;
			if (board[newY][newX] == 0 && !check[newY][newX]) {
				check[newY][newX] = true;
				DFS(newY, newX, dir, f);
				check[newY][newX] = false;
			}
		}
		//대각선으로 이동할때
		else if (dir == 1) {
			bool flag = moveCheck(hang, yal);
			//true이면 대각선으로 파이프 이동가능..
			if (flag) {
				for (int d = 0; d < 3; d++) check[hang + dirY[d]][yal + dirX[d]] = true;		
				DFS(newY, newX, dir, f);
				for (int d = 0; d < 3; d++) check[hang + dirY[d]][yal + dirX[d]] = false;
			}
		}
	}
}