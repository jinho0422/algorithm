#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M;
int board[501][501];
int numbers[10001];

//선수의 번호(number)와, 선수의 랭킹점수(cnt)
typedef struct _pos {
	int number, cnt;
}pos;


// 선수의 정보를 정렬하기위해서.. 랭킹점수가 높을수록, 랭킹점수가 같다면 선수 번호를 오름차순으로..
bool cmp (const pos& p, const pos& q) {
	if (p.cnt == q.cnt) return p.number < q.number;
	return p.cnt > q.cnt;
}
pos second[10001];

int main() {
	while (1) {
		//입력
		scanf("%d %d", &N, &M);
		if (N == 0 && M == 0) break;
		//선수 번호가 몇번까지 있는지 판단하기 위해서
		int max_num = 0;
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < M; yal++) {
				scanf("%d", &board[hang][yal]);
				if (max_num < board[hang][yal]) max_num = board[hang][yal];
				numbers[board[hang][yal]]++;
			}
		}
		int player = 0;
		for (int i = 1; i <= max_num; i++) {
			if (numbers[i] != 0) {
				second[player++] = { i, numbers[i] };
			}
		}
		// cmp 정렬을 통해 정렬하고, 랭킹의 최대값은 오직 하나이므로 다음 번 랭킹 값을 통해 같으면 계속적으로 print..
		sort(second, second + player, cmp);
		int secondFirst = second[1].cnt;
		for (int s = 1; s < player; s++) {
			if (second[s].cnt == secondFirst) {
				printf("%d ", second[s].number);
			}
			else break;
		}
		printf("\n");
		// 다음 케이스를 위해 선수의 정보가 들어있는 numbers배열 초기화.
		memset(numbers, 0, sizeof(numbers));
	}

	return 0;
}