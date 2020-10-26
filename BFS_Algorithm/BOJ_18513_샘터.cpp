#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cmath>
#include <map>
using namespace std;

map<int, int> Map; // 집이 지어졌는지 판단하기 위해..

int N, K;
int board[100001];
int dirY[2] = { -1, 1 };
long long result;// 만약 샘터가 몰려있으면 최대 1~10만을 모두 더해야되므로..

typedef struct _pos {
	int n, num;
}pos;
queue<pos> Q;

int BFS();

int main() {
	scanf("%d %d", &N, &K);
	for (int a, i = 0; i < N; i++) {
		scanf("%d", &a);
		board[i] = a;
		Map[a]++;
		Q.push(pos({ a, i}));
	}
	printf("%lld\n",BFS());
	return 0;
}
int BFS() {
	int k = 0;

	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();
			for (int dir = 0; dir < 2; dir++) {
				int newX = p.n + dirY[dir];
				if (Map[newX] == 0) {
					Map[newX]++;
					Q.push(pos({ newX, p.num}));
					result += abs(board[p.num] - newX);
					k++;
					if (k == K) return result;
				}
			}
		}
	}
}