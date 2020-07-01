#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N;

struct cmp {
	bool operator() (int p, int q) {
		return p < q;
	}
};

struct cmp1 {
	bool operator() (int p, int q) {
		return p > q;
	}
};

priority_queue<int, vector<int>, cmp> min_Q;
priority_queue<int, vector<int>, cmp1> max_Q;

int main() {
	scanf("%d", &N);
	for (int num, i = 0; i < N; i++) {
		scanf("%d", &num);
		if (i == 0) {
			min_Q.push(num);
			printf("%d\n", num);
			continue;
		}
		int min_sz = min_Q.size();
		int max_sz = max_Q.size();

		if (min_sz <= max_sz) {
			min_Q.push(num);
			int minNum = min_Q.top();
			int maxNum = max_Q.top();

			if (minNum > maxNum) {
				min_Q.pop();
				max_Q.pop();
				min_Q.push(maxNum);
				max_Q.push(minNum);
			}
			printf("%d\n", min_Q.top());
		}
		else {
			max_Q.push(num);
			int minNum = min_Q.top();
			int maxNum = max_Q.top();
			if (minNum > maxNum) {
				min_Q.pop();
				max_Q.pop();
				min_Q.push(maxNum);
				max_Q.push(minNum);
			}
			printf("%d\n", min_Q.top());
		}
	}
	return 0;
}