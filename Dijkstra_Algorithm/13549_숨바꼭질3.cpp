/*
	수빈이는 동생과 숨바꼭질을 하고 있다. 수빈이는 현재 점 N(0 ≤ N ≤ 100,000)에 있고,
	동생은 점 K(0 ≤ K ≤ 100,000)에 있다. 수빈이는 걷거나 순간이동을 할 수 있다. 
	만약, 수빈이의 위치가 X일 때 걷는다면 1초 후에 X-1 또는 X+1로 이동하게 된다. 
	순간이동을 하는 경우에는 0초 후에 2*X의 위치로 이동하게 된다.
	수빈이와 동생의 위치가 주어졌을 때, 수빈이가 동생을 찾을 수 있는 
	가장 빠른 시간이 몇 초 후인지 구하는 알고리즘 구현.

	순간이동을 하는 경우에는 경과하는 시간이 0초이므로 최소의 시간이 갱신될 수 있다.
	즉, 같은곳을 또 방문할 수 있다는 것이다. 따라서 다익스트라 알고리즘으로 구현.

*/

#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;
#include <cstdio>
#include <queue>

using namespace std;

int N, K;
int dij_board[100001]; // dijkstra_algorithm을 위해..
int dirX[3] = { -1, 1, 2 };

typedef struct _pos { // 언니의 위치 및 그 곳에서의 시간 struct
	int s, t;
}pos;

struct cmp { // priority_queue를 위해 시간이 작은 것부터 나오게 하기 위한 cmp
	bool operator() (pos p, pos q) {
		return p.t > q.t;
	}
};

priority_queue<pos, vector<pos>, cmp> Q;

int main() {
	scanf("%d %d", &N, &K);
	
	for (int i = 0; i <= 100000; i++) dij_board[i] = INF;

	dij_board[N] = 0;
	Q.push(pos({ N, 0 })); // pq에 언니의 시작점과 시간 0초를 넣는다.
	while (!Q.empty()) {
		pos p = Q.top();
		Q.pop();

		if (dij_board[K] <= p.t) continue; // 언니가 소모한 시간이 동생을 찾은 다른 이동방향보다 크면 continue..

		//printf("%d %d\n", p.s, p.t);

		for (int dir = 0; dir < 3; dir++) {
			if (dir != 2) {
				int newN = p.s + dirX[dir];

				if (newN < 0 || newN > 100000) continue; // 범위를 벗어나면 continue..

				if (dij_board[newN] > p.t + 1) { // 걸어서 이동..
					dij_board[newN] = p.t + 1; // 걸어서 이동하는하는 곳이 전에 방문했었던 이동시간보다 작으면 
					Q.push(pos({ newN, p.t + 1 })); // 갱신..
				}
			}
			else { // 순간이동..
				int newN = p.s * dirX[dir]; 
				if (newN < 0 || newN > 100000) continue;

				if (dij_board[newN] > p.t) { // 순간이동을해서 전에 방문했던 경과시간보다 작으면 갱신..
					dij_board[newN] = p.t;
					Q.push(pos({ newN, p.t }));
				}
			}
		}
	}
	printf("%d\n", dij_board[K]);

	return 0;
}