/*
	https://www.acmicpc.net/problem/14226
	
	priority_queue를 활용한 BFS를 이용하여 알고리즘 구현.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int N;
bool check[1001][1001]; // 2차원 check 배열을 사용한 이유는 같은 값에 도달했을 때 같은 클립보드가 복사 되있는지를 판단해서 넣기위해서이다.

typedef struct _pos { // s == 현재 이모티콘 수, c == 클립보드에 저장된 이모티콘 수 t == 시간
	int s, c, t;
}pos;

struct cmp { // 시간이 작은 순서대로 queue에서 뽑기 위해..
	bool operator() (pos p, pos q) {
		return p.t > q.t;
	}
};

void BFS(int start, int time);

int main() {
	scanf("%d", &N);
	BFS(1, 0);// 시작점 1, 시간 0의 초기값으로 BFS함수를 시작..
	return 0;
}

void BFS(int start, int time) {
	priority_queue<pos, vector<pos>, cmp> Q;
	Q.push(pos({ start, 0, time })); // priority_queue에 시작점 1, 클립보드에 있는 초기 이모티콘 수 0, 시간 0

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();

		if (!check[p.c][p.s]) { // 시간의 흐름으로 가고있을 때 현재 이모티콘의 수와 클립보드에 저장된 이모티콘 수를 판단
			check[p.c][p.s] = true; // 아직 check되지 않은 것만 확인..
			//printf("%d %d %d\n", p.s, p.c, p.t);
			if (p.s == N) { // 화면에 만들고 싶은 이모티콘의 갯수이면..
				printf("%d\n", p.t); // 시간 출력
				return;
			}

			if (p.c != 0 && p.s + p.c <= 1000) { // 클립보드에 복사된 이모티콘 갯수가 0이 아니고 현재의 갯수와 클립보드에 복사된 수의 합이 1000보다 작거나 같으면
				Q.push(pos({ p.s + p.c, p.c, p.t + 1 }));
			}

			Q.push(pos({ p.s, p.s, p.t + 1 })); // 클립보드에 현재의 이모티콘 갯수 복사..

			if (p.s - 1 > 0) { // 현재의 이모티콘의 갯수에서 한개를 삭제했을 때 0보다 크면..
				Q.push(pos({ p.s - 1, p.c, p.t + 1 }));
			}
		}
	}
}