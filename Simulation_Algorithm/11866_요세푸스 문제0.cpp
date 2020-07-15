#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N, K;

deque<int> Q;

int main() {
	//입력
	scanf("%d %d", &N, &K);
	// qeque를 통해 뒤에서부터 1~ N까지 넣어준다(원이라고 생각해서 deque를 썼다)
	for (int s = 1; s <= N; s++) {
		Q.push_back(s);
	}

	printf("<");
	// deque의 size가 0이 될때까지 돌려주는데
	while (1) {
		int p = 0;
		// K배수일 때까지 돌려주면서
		for (int i = 0; i < K; i++) {
			p = Q.front();
			Q.pop_front();
			// 마지막에는 front에 있는걸 back으로 넣어주지않으며 결과값이라 판명하고 출력해준다.
			if(i != K -1) Q.push_back(p);
		}
		//만약 size가 0이면 더이상 원에 남아있는 사람이 없으므로 출력을 하고 끝낸다.
		if (Q.size() != 0) printf("%d, ", p);
		else {
			printf("%d>\n", p);
			break;
		}
	}
	return 0;
}