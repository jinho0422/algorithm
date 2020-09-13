#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
//이 문제는 MST 문제이지만 간선에 가중치는 존재하지 않고 모든 노드를 방문할 수 있는 최소 엣지 방문 횟수를 답으로 원하기 때문에 N -1이 답이다.
// MST는 항상 간선의 갯수가 N -1개이기 때문이다.
int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %d", &N, &M);
		for (int a, b, i = 0; i < M; i++) {
			scanf("%d %d", &a, &b);
		}
		printf("%d\n", N - 1);
	}
	return 0;
}