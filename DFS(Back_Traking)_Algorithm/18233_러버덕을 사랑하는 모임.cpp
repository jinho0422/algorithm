/*
	https://www.acmicpc.net/problem/18233
	DFS + 시뮬레이션을 이용해 알고리즘 구현..
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int N, P, E;
bool check[21][1000001];
int tmp[21]; //회원번호를 넣기 위한 배열..
int result[21]; // 결과값을 넣을 배열..
bool flag;

typedef struct _pos {// 회원이 러버덕을 원하는 최소값과 최대값을 넣는 struct
	int a, b;
}pos;
vector<pos> Vec;

void solve(int depth, int start);

int main() {
	scanf("%d %d %d", &N, &P, &E);
	for (int a, b, i = 0; i < N; i++) {
		scanf("%d %d", &a, &b);
		Vec.push_back(pos({ a, b })); // 최대값과 최소값을 넣는 Vec

	}

	solve(0, 0); // DFS
	if (!flag) printf("-1\n"); // 줄 수 없는 경우라면 -1
	else { // 줄 수 있는 경우라면 각각 회원이 가질 수 있는 러버덕의 갯 수 출력
		for (int i = 0; i < N; i++) {
			printf("%d ", result[i]);
		}
		printf("\n");
	}
	return 0;
}

void solve(int depth, int start) {
	if (flag) return; // 정답을 한개만 출력하기 위해..

	if (depth == P) { // 줄 수 있는 회원이 되면..
		memset(result, 0, sizeof(result)); // 결과값을 초기화..
		int sum = 0; // 결과 E를 찾기위한 sum
		int min_sum = 0; // 회원 각각이 원하는 최소한을 더하는 sum
		int max_sum = 0; // 회원 각각이 원하는 최대한을 더하는 sum
		for (int i = 0; i < depth; i++) {
			result[tmp[i]] = Vec[tmp[i]].a;
			min_sum += Vec[tmp[i]].a;
			max_sum += Vec[tmp[i]].b;
			sum += result[tmp[i]];
		}

		if (min_sum <= E && max_sum >= E) { // 회원각각의 최소값과 최대값에 속하면

			for (int i = 0; i < depth; i++) { // 선택된 회원들 사이에서 
				int gap = Vec[tmp[i]].b - Vec[tmp[i]].a;
				if (sum + gap < E) { // 회원의 최대와 최소를 빼서 sum에 더한값이 결과값보다 작으면
					result[tmp[i]] += gap; // 회원의 결과값을 바꿔주고
					sum += gap; // 최대와 최소의 차이를 sum에 더해주고
					continue;
				}
				if (sum + gap >= E) { // 같거나 크면
					result[tmp[i]] += (E - sum); //원하는 결과값에서 지금까지 더해진 sum을 빼서 회원의 결과값을 갱신..
					flag = true; // 결과값을 이뤘다는 flag true..
					return;
				}
			}
		}
		return;
	}

	for (int s = start; s < Vec.size(); s++) { // 줄 수 있는 회원의 수를 뽑는다..(조합으로)
		tmp[depth] = s;
		solve(depth + 1, s + 1);
	}
}