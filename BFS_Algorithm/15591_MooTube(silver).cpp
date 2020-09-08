#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, Q;
bool check[5001];
int finalResult;

typedef struct _pos {
	int B, W;
}pos;

vector<pos> Vec[5001]; // 연결된 동영상의 usado를 넣어 놓는다.. 
vector<int> result[5001]; // 한 동영상에서 각각의 동영상과의 usado의 최소를 넣는다.
queue<pos> Qq;

void BFS(int start,int maxU);

int main() {
	//입력
	scanf("%d %d", &N, &Q);
	for (int p, q, r, i = 0; i < N - 1; i++) {
		scanf("%d %d %d", &p, &q, &r);
		Vec[p].push_back(pos({ q, r }));
		Vec[q].push_back(pos({ p, r }));
	}
	// 한 동영상에서 각각의 동영상의 유사도의 최소를 찾는다.
	for (int i = 1; i <= N; i++) {
		memset(check, false, sizeof(check)); // 한 동영상에서 각 동영상의 유사도를 찾고나서는 방문 초기화..
		BFS(i, 1000000001);
	}
	//출력
	for (int k, v, i = 0; i < Q; i++) {
		finalResult = 0; // 결과값
		scanf("%d %d", &k, &v);
		for (int j = 0; j < result[v].size(); j++) {
			if (k <= result[v][j]) finalResult++;
		}
		printf("%d\n", finalResult);
	}
	return 0;
}

void BFS(int start, int maxU) {

	check[start] = true;
	Qq.push(pos({ start, maxU }));

	while (!Qq.empty()) {
		pos p = Qq.front();
		Qq.pop();

		int sz = Vec[p.B].size();

		for (int s = 0; s < sz; s++) {
			int first = Vec[p.B][s].B;
			int second = Vec[p.B][s].W;

			if (!check[first]) {
				check[first] = true;
				// 만약 현재의 동영상에서 연결된 동영상으로갈때 유사도가 그 전의 연결된 유사도 보다 클때..
				if (second > p.W) {
					result[start].push_back(p.W);
					Qq.push(pos({ first, p.W }));
				}
				// 작을 때
				else {
					result[start].push_back(second);
					Qq.push(pos({ first, second }));
				}
			}
		}
	}
}