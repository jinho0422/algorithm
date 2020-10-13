#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

int N, L;
int board[101][101];
bool check[2][101]; //check[0][0~100] --> hang이 경사로로 완벽한지 check[1][0~100] --> yal의 경사로가 완벽한지
int result;

queue<int> Q;

void solve(int depth, int start);

int main() {
	//입력
	scanf("%d %d", &N, &L);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	//행의 경사로 찾기
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			Q.push(board[hang][yal]);
		}
		solve(0, hang);
		while (!Q.empty()) Q.pop();
		//왼쪽에서 볼때 경사로가 안될시..
		if (!check[0][hang]) {
			for (int yal = N - 1; yal >= 0; yal--) {
				Q.push(board[hang][yal]);
			}
			solve(0, hang);
			while (!Q.empty()) Q.pop();
		}
	}
	//열의 경사로 찾기
	for (int yal = 0; yal < N; yal++) {
		for (int hang = 0; hang < N; hang++) {
			Q.push(board[hang][yal]);
		}
		solve(1, yal);
		while (!Q.empty()) Q.pop();
		// 위에서 볼때 경사로가 안될시..
		if (!check[1][yal]) {
			for (int hang = N - 1; hang >= 0; hang--) {
				Q.push(board[hang][yal]);
			}
			solve(1, yal);
			while (!Q.empty()) Q.pop();
		}
	}
	//결과값 갱신 & 출력
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i][j]) result++;
		}
	}
	printf("%d\n", result);
	return 0;
}

void solve(int depth, int start) {
	int first = Q.front();
	int checkFirst = Q.front(); // 최고점 찾기
	int cnt = 0; // L만큼 있는지 판단하기 위해..
	bool flag = false; // 다음번 단계가 높아지는지 낮아지는지 판단.
	while (!Q.empty()) {
		int p = Q.front();
		if (checkFirst < p) checkFirst = p; // 최고점 갱신
		if (first == p) { // 이전이랑 높이가 같으면 cnt++
			Q.pop();
			cnt++;
		}
		// 높이가 다를시
		else if (first != p) {
			if (first > p) { // 이전의 높이가 더 클 시
				flag = true;
				if (checkFirst == first) cnt = L; // 최고점이면 cnt == L로만들어준다
			}

			else if (first < p) { // 현재의 높이가 더 클 때
				if (flag) { // 만약 이전에 내려왔던 적이 있으면
					if (cnt < 2 * L) return; // 다시 올라갈 수 있는지 판단
					else flag = false;

				}
			}
			// cnt가 경사로의 길이보다 클때..
			if (cnt >= L) {
				if (abs(first - p) == 1) {
					first = p;
					cnt = 0;
				}
				else return;
			}
			else return;
		}
	}
	// 활주로로 사용할 수 있는지 갱신..
	if (cnt >= L) check[depth][start] = true;
}