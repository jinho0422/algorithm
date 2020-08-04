#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int F, S, G, U, D;
bool check[1000001];


queue<int> Q;
void BFS(int start);

int main() {
	scanf("%d %d %d %d %d", &F, &S, &G, &U, &D);
	BFS(S);

	return 0;
}

void BFS(int start) {
	check[start] = true;
	Q.push(start);
	int time = 0;

	while (!Q.empty()) {
		int sz = Q.size();

		for (int s = 0; s < sz; s++) {
			int p = Q.front();
			Q.pop();
			if (p == G) {
				printf("%d\n", time);
				return;
			}
			if (p + U <= F) {
				if (!check[p + U]) {
					check[p + U] = true;
					Q.push(p + U);
				}
			}
			if (p - D >= 1) {
				if (!check[p - D]) {
					check[p - D] = true;
					Q.push(p - D);
				}
			}
		}
		time++;
	}
	printf("use the stairs\n");
}