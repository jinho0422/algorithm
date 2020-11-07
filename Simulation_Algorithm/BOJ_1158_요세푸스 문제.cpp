#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int N, K;

vector<int> Vec;

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) Vec.push_back(i);

	int cnt = N;
	int check = -1;
	printf("<");
	while (cnt > 1) {
		check = (check + K) % cnt;
		printf("%d, ", Vec[check]);
		Vec.erase(Vec.begin() + check);
		cnt--;
		check--;
	}
	printf("%d>\n", Vec[0]);

	return 0;
}