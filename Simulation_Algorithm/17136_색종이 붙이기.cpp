#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int board[10][10];
int paper[6];
int oneNum;
int result;

void DFS(int hang, int yal, int cnt);

int main() {
	//입력
	result = 987654321;
	for (int i = 1; i <= 5; i++) paper[i] = 5;
	for (int hang = 0; hang < 10; hang++) {
		for (int yal = 0; yal < 10; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) oneNum++; // 업애야될 갯수
		}
	}
	//없애야될곳이 없으면 0출력
	if (oneNum == 0) {
		printf("0\n");
		return 0;
	}
	DFS(0, 0, oneNum);
	//출력
	if (result != 987654321) printf("%d\n", result);
	else printf("-1\n");
	return 0;
}
// 없앨 수 있는지 보기.. false : 없앨 수 없음, true : 없앨 수 있음
bool solve(int hang, int yal, int s) {
	if (hang + s > 10 || yal + s > 10) return false; // 경계값을 넘어가는 것..
	if (paper[s] == 0) return false; // 종이가 없으면
	for (int i = hang; i < hang + s; i++) {
		for (int j = yal; j < yal + s; j++) {
			if (board[i][j] == 0) return false; // 정사각형이 아니면..
		}
	}
	return true;
}

void DFS(int hang, int yal, int cnt) {
	if (yal >= 10) {
		hang += 1, yal = 0; // 경계값을 넘으면 hang + 1, yal = 0
	}
	// 업애야될곳을 모두 없앴으면
	if (cnt == 0) {
		int sum = 25;
		for (int i = 1; i <= 5; i++) sum -= paper[i]; //사용한 종이 갱신..
		if (result > sum) result = sum; // 결과값 갱신..
		return;
	}
	if (hang >= 10) return; // 10, 10까지 가면 리턴..
	//채워야 될 곳이 나타나면
	if (board[hang][yal] == 1) {
		for (int s = 5; s >= 1; s--) {
			bool flag = solve(hang, yal, s);
			if (flag) {
				paper[s]--;
				for (int i = hang; i < hang + s; i++) {
					for (int j = yal; j < yal + s; j++) {
						cnt--;
						board[i][j] = 0;
					}
				}
				DFS(hang, yal + s, cnt);
				paper[s]++;
				for (int i = hang; i < hang + s; i++) {
					for (int j = yal; j < yal + s; j++) {
						cnt++;
						board[i][j] = 1;
					}
				}
			}
		}
	}
	else DFS(hang, yal + 1, cnt); // 채워야될 곳이 없으면 yal + 1
}
