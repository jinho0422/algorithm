#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N;
char str[65];
int board[65][65];
queue<int> Q;


void DFS(int H, int Y, int size);

int main() {
	//입력
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < N; yal++) {
			board[hang][yal] = str[yal] - '0';
		}
	}
	DFS(0, 0, N);
	//Q를 하나씩 빼면서 -1이면 (를 -2이면 ) 다른 값이면 Q값을 프린트한다..
	while (!Q.empty()) {
		if (Q.front() == -1) printf("(");
		else if (Q.front() == -2) printf(")");
		else printf("%d", Q.front());
		Q.pop();
	}
	printf("\n");
	return 0;
}

void DFS(int H, int Y, int size) {
	int tmp = board[H][Y]; // 비교대상
	bool check = false; // 각 사각형이 똑같은 수를 가지고 있는지 판단..
	// 마지막으로 size == 1이면 Q에 값을 넣어준다..
	if (size == 1) {
		Q.push(tmp);
		return;
	}
	// 크기를 돌면서 모두 똑같은 값인지 판단
	for (int hang = H; hang < H + size; hang++) {
		for (int yal = Y; yal < Y + size; yal++) {
			if (tmp != board[hang][yal]) {
				check = true;
				break;
			}
		}
	}
	//만약 모두 똑같은 값이라면 Q에 넣어준다..
	if (!check) {
		Q.push(tmp);
		return;
	}
	Q.push(-1); // (를 생각하기위해
	// 4사분면을 재귀로 돌려준다..
	DFS(H, Y, size / 2);
	DFS(H, Y + size / 2, size / 2);
	DFS(H + size / 2, Y, size / 2);
	DFS(H + size / 2, Y + size / 2, size / 2);
	Q.push(-2); // )를 생각하기위해
}