#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int L, C;
char ch;
char str[18];

vector<char> Vec;

void DFS(int depth, int start, int first, int second);

int main() {
	scanf("%d %d", &L, &C);
	for (int i = 0; i < C;) {
		scanf("%c", &ch);
		if (ch == ' ' || ch == '\n') continue;
		else {
			i++;
			Vec.push_back(ch);
		}
	}
	sort(Vec.begin(), Vec.end());
	DFS(0, 0, 0, 0);

	return 0;
}

void DFS(int depth, int start, int first, int second) {
	if (depth == L) {
		if (first >= 1 && second >= 2) {
			for (int s = 0; s < depth; s++) {
				printf("%c", str[s]);
			}
			printf("\n");
		}

		return;
	}

	for (int i = start; i < Vec.size(); i++) {

		if (Vec[i] == 'a' || Vec[i] == 'e' || Vec[i] == 'i' || Vec[i] == 'o' || Vec[i] == 'u') {
			str[depth] = Vec[i];
			DFS(depth + 1, i + 1, first + 1, second);

		}

		else {
			str[depth] = Vec[i];
			DFS(depth + 1, i + 1, first, second + 1);
		}
	}
}