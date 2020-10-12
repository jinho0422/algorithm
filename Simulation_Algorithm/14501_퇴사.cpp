#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
using namespace std;

int N;
int result;

typedef struct _pos {
	int t, m; // t : 업무에 필요한 시간 m : 받는 돈
}pos;
vector<pos> Vec;

void DFS(int depth, int sum);

int main() {
	//입력
	scanf("%d", &N);
	for (int a, b, i = 0; i < N; i++) {
		scanf("%d %d", &a, &b);
		Vec.push_back(pos({ a, b }));
	}
	DFS(0, 0);
	printf("%d\n", result);
	return 0;
}

void DFS(int depth, int sum) {
	if (depth <= N) { // 퇴사일 전까지는 결과값 갱신..
		if (result < sum) result = sum;
	}
	if (depth >= N) return; // 퇴사일이 넘어서면 return..
	//그 시기에 일을 하는경우
	if(depth + Vec[depth].t <= N) DFS(depth + Vec[depth].t, sum + Vec[depth].m);
	//일을 안하고 넘어가는 경우
	if (depth + 1 <= N) DFS(depth + 1, sum);
}