#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

int N, M;
int board[501];
int result;

vector<int> Vec;


int main() {
	scanf("%d %d", &N, &M);
	for (int a, i = 0; i < M; i++) {
		scanf("%d", &a);
		board[i] = a;
	}
	int tmp = board[0];
	for (int i = 0; i < M; i++) {
		if (tmp >= board[i]) Vec.push_back(i);
		else if (tmp < board[i]) {
			int sz = Vec.size();
			for (int s = 0; s < sz; s++) {
				result += tmp - board[Vec[s]];
			}
			Vec.clear();
			tmp = board[i];
		}	
	}
	int sz = Vec.size();
	tmp = board[M - 1];
	for (int s = sz - 1; s >= 0; s--) {
		if (tmp >= board[Vec[s]]) result += tmp - board[Vec[s]];
		else if (tmp < board[Vec[s]]) tmp = board[Vec[s]];
	}
	printf("%d\n", result);
	return 0;
}