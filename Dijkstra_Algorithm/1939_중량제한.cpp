/*
	N(2<= N <= 10000)개의 섬으로 이루어진 나라가 있다. 이들 중 몇개의 섬 사이에는 다리가 설치되어 있어서 차들이 다닐 수 있다.
	두 개의 섬에 공장을 세워 두고 물품을 생산하는 일을 하고 있다. 물품을 생산하다 보면 공장에서 다른 공장으로
	생산 중이던 물품을 수송해야할 일이 생기곤 한다. 그런데 각각의 다리마다 중량제한이 있기 때문에 무턱대고 물품을 옮길 순 없다.
	만약 중량제한을 초과하는 양의 물품이 다리를 지나게 되면 다리가 무너지게 된다.
	한 번 이동에서 옮길 수 있는 물품들의 중량의 최댓값을 구하는 알고리즘 구현..

	서로 같은 두 도시 사이에 여러 개의 다리가 있을 수도 있으므로 한곳을 여러번 방문 할 수 있다는
	생각으로 dijkstra알고리즘을 사용하였다. 그리고 dijkstra를 항상 INF(214700000)으로 했었지만
	이 문제에서는 dijkstra를 0으로 사용(다리의 중량이 1보다 크거나 같기 때문에)하여 최대값을 갱신하는 알고리즘구현.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, M;
int dij_board[10001];
int factoryStart, factoryEnd; // 공장이 있는 두곳..

typedef struct _pos {
	int B, W;
}pos;
vector<pos> Vec[10001]; // 한 도시에서 다른도시로 가는 도시와 다리에서 견딜 수 있는 무게 W를 가지는 struct

void solve(int start);

int main() {
	scanf("%d %d", &N, &M);
	for (int a, b, c, i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		Vec[a].push_back(pos({ b, c }));// 도시는 양뱡향이므로..
		Vec[b].push_back(pos({ a, c }));
	}
	scanf("%d %d", &factoryStart, &factoryEnd);

	solve(factoryStart); // 공장의 시작..
	printf("%d\n", dij_board[factoryEnd]);

	return 0;
}

void solve(int start) {
	queue<pos> Q;
	dij_board[start] = 2147000000; // 공장의 시작지점을 최대값으로 넣고..BFS_dijkstra
	Q.push(pos({ start, 2147000000 }));

	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop();
		if (p.B == factoryEnd || p.W < dij_board[p.B]) continue; // 가기위한 공장이거나 dijkstra에 넣어있는 값이 그 곳의 최대중량이므로 작으면 갈 필요가 없으므로 continue..

		int sz = Vec[p.B].size();
		for (int s = 0; s < sz; s++) {
			int first = Vec[p.B][s].B; // 가는 곳..
			int second = Vec[p.B][s].W; // 가는곳의 다리가 버틸 수 있는 중량..

			if (second > dij_board[p.B]) second = dij_board[p.B]; // 지금 현재 위치에서 버틸 수 있는 최대중량보다 가는 곳이 버틸 수 있는 다리 중량이 크면 현재에서 버틸 수 있는 중량으로..

			if (dij_board[first] < second) { // 만약 가는곳이 버틸 수 있는 중량이 최대값으로 갱신 할 수있으면..
				dij_board[first] = second;
				Q.push(pos({ first, dij_board[first] }));
			}
		}
	}
}