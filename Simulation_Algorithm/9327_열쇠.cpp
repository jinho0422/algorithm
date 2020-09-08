#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int N, M;
char str[104];
char board[104][104];
bool check[104][104];
bool keyFlag[27];
int dirY[4] = { -1, 0, 0, 1 };
int dirX[4] = { 0, -1, 1, 0 };
bool flag;
int result;

typedef struct _pos {
	int h, y;
}pos;
queue<pos> Q;

void BFS(int hang, int yal);

int main() {
	//입력
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		//초기화
		result = 0;
		memset(board, '.', sizeof(board)); // 시작점을 0, 0으로 하기 위해 빌딩의 벽을 들어갈 수 있는 '.'로 해놓는다.
		memset(keyFlag, false, sizeof(keyFlag));
		scanf("%d %d", &N, &M);
		for (int hang = 1; hang <= N; hang++) {
			scanf("%s", str);
			for (int yal = 0; yal < M; yal++) {
				board[hang][yal + 1] = str[yal];
			}
		}
		scanf("%s", str);
		// 열쇠를 keyFlag를 통해서 있는지 없는지 판단.. true : 열쇠 있음 false : 열쇠 없음
		for (int i = 0; str[i] != '\0'; i++) {
			if (str[i] == '0') break;
			keyFlag[str[i] - 'a'] = true;
		}

		while (1) {
			flag = false; // BFS를 돌면서 만약 열쇠를 찾으면 flag : true, 아니면 flag : false
			while (!Q.empty()) Q.pop(); // queue초기화
			memset(check, false, sizeof(check)); // 방문체크초기화
			BFS(0, 0);
			if (!flag) break;
		}
		//출력
		printf("%d\n", result);
	}
	return 0;
}

void BFS(int hang, int yal) {
	check[hang][yal] = true;
	Q.push(pos({ hang, yal }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int newY = p.h + dirY[dir];
			int newX = p.y + dirX[dir];

			if (newY < 0 || newY > N + 1 || newX < 0 || newX > M + 1) continue;
			// 지나갈수 있는 곳
			if (board[newY][newX] == '.' && !check[newY][newX]) {
				check[newY][newX] = true;
				Q.push(pos({ newY, newX }));
			}
			// 문서를 찾은 곳
			else if (board[newY][newX] == '$' && !check[newY][newX]) {
				check[newY][newX] = true;
				result++;
				board[newY][newX] = '.';
				Q.push(pos({ newY, newX }));
				
			}
			// 열쇠를 습득한 곳
			else if (board[newY][newX] >= 'a' && board[newY][newX] <= 'z' && !check[newY][newX]) {
				check[newY][newX] = true;
				keyFlag[board[newY][newX] - 'a'] = true;
				board[newY][newX] = '.';
				flag = true;
				Q.push(pos({ newY, newX }));
			}
			// 열쇠로 문을 열은 곳
			else if (board[newY][newX] >= 'A' && board[newY][newX] <= 'Z' && !check[newY][newX]) {
				if (keyFlag[board[newY][newX] - 'A']) {
					check[newY][newX] = true;
					board[newY][newX] = '.';
					Q.push(pos({ newY, newX }));
					
				}
			}
		}
	}
}