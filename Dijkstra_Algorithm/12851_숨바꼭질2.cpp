/*
	https://www.acmicpc.net/problem/12851
	수빈이가 동생을 찾을 수 있는 가장 빠른 시간과 그 시간에 찾을 수 있는
	방법의 수를 찾아야 하므로 dijkstra + BFS를 활용한 알고리즘 구현.
*/

#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000 // dij 초기화를 위한 INF
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <math.h>

using namespace std;

int N, K;
int dij_board[100001];
int min_result; // 동생에게 도착하기 위한 최소시간갱신 int
int cnt; // 최소시간에 몇 번 도달하는지 count int

void solve(int start);

typedef struct _pos { //c == 수진이가 도착하는 곳, t == c에 도달하는데 걸린 시간..
	int c, t;
}pos;

struct cmp { // 최소의 시간부터 priority_queue에서 뽑아내기 위해..
	bool operator() (pos p, pos q) {
		return p.t > q.t;
	}
};

int main() {
	min_result = INF;
	scanf("%d %d", &N, &K);
	for (int i = 0; i <= 100000; i++) { // dij_board 초기화..
		dij_board[i] = INF;
	}
	
	solve(N); // 수진이의 최초 위치에서부터 BFS
	printf("%d\n%d\n", min_result, cnt);
	return 0;
}

void solve(int start) {
	priority_queue<pos, vector<pos>, cmp> Q;
	dij_board[start] = 0;
	Q.push(pos({ start, 0 })); // 수진이의 최초 위치와 최초 시간 0
	

	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();

		if (min_result < p.t) continue; // 갱신된 최소시간보다 크면 continue..

		if (p.c == K) { // 수진이가 동생을 찾았을 때..
			if (min_result > dij_board[p.c]) { // 최소시간이 갱신할 수있으면 
				min_result = dij_board[p.c]; // 갱신하고
				cnt = 1; // conunt = 1
			}
			else if (min_result == dij_board[p.c]) {
				cnt++; // 같으면 count++
			}
		}

		if (p.c + 1 <= 100000) { // 수진이가 한칸 앞으로 갈 때 100000보다 작으면
			if (dij_board[p.c + 1] >= dij_board[p.c] + 1) { // 움직인 곳이 현재의 시간 + 1보다 크면
				dij_board[p.c + 1] = dij_board[p.c] + 1; // 갱신
				Q.push(pos({ p.c + 1, p.t + 1 }));
			}
		}

		if (p.c - 1 >= 0) { // 수진이가 한칸 뒤로 갈 때  0 보다 작으면
			if (dij_board[p.c - 1] >= dij_board[p.c] + 1) { // 움직인 곳이 현재의 시간 + 1보다 크면
				dij_board[p.c - 1] = dij_board[p.c] + 1;// 갱신
				Q.push(pos({ p.c - 1, p.t + 1 }));
			}
		}

		if (p.c * 2 <= 100000) { // 수진이가 순간이동(현재위치 * 2) 할 때 100000보다 작으면
			if (dij_board[p.c * 2] >= dij_board[p.c] + 1) { // 움직인 곳이 현재의 시간 + 1보다 크면
				dij_board[p.c * 2] = dij_board[p.c] + 1;// 갱신
				Q.push(pos({ p.c * 2, p.t + 1 }));
			}
		}
	}
}