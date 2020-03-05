/*
	정사각형 모양을 한 다섯종류(1, 2, 3, 4, 5의 길이)의 색종이가 있고 각 종류의 색종이는 5개씩 가지고있다.
	색종이를 크기가 10*10인 종이 위에 붙이려고 하는데 각 칸에는 0, 1이 색칠되어 있고 1이 적힌 칸은 모두 색종이로 덮여져야 한다.
	색종이를 붙일 때는 종이의 경계 밖으로 나가서는 안되고, 겹쳐도 안된다. 또한, 칸의 경계와 일치하게 붙여야한다.
	종이가 주어졌을 때, 1이 적힌 모든 칸을 붙이는데 필요한 색종이의 최소 갯수를 구하는 알고리즘이다.

	각각의 정사각형 색종이는 5개씩있고 1이 나타나면 5종류의 색종이를 붙일 수 있는지 업는지를 판단하면서
	해야되므로 브루투포스를 활용하여 알고리즘을 구현했다.
	*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int board[10][10];
bool check[10][10];
int paper_num; // 색종이를 붙여야되는 1의 갯수..
int result;
int paper[6] = { 0, 5, 5, 5, 5, 5 }; // 각각의 종류의 색종이의 갯수..

void solve(int hang, int yal, int num);

int main() {
	result = 987654321;
	for (int hang = 0; hang < 10; hang++) {
		for (int yal = 0; yal < 10; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) paper_num++;
		}
	}
	solve(0, 0, paper_num); // 0, 0부터 시작하여 탐색을 시작한다..
	if (result == 987654321) printf("-1\n");
	else printf("%d\n", result);
	return 0;
}

bool go_find(int i, int j, int s) { // 색종이를 붙일 수 있는지 판단..
	if (i + s > 10 || j + s > 10) return false; // 범위를 넘어가면 붙이지 못하므로 return false
	if (paper[s] == 0) return false; // 색종이의 종류가 남아있지 않으면 붙이지 못하므로 return false

	for (int hang = i; hang < i + s; hang++) {
		for (int yal = j; yal < j + s; yal++) {
			if (board[hang][yal] == 0) return false; // 색종이를 붙이다가 중간에 붙이지 않아도 되는 곳이 나타나면 return false..
		}
	}
	return true; // s의 크기의 색종이로 모든곳을 붙일 수 있으므로 return true..
}

void erase(int i, int j, int s, int n) {
	for (int hang = i; hang < i + s; hang++) {
		for (int yal = j; yal < j + s; yal++) {
			board[hang][yal] = n;
		}
	}
}

void solve(int hang, int yal, int num) {

	if (yal == 10) { // yal이 10이면 다음 행렬을 봐야되므로 hang을 1증가시키고 yal을 0으로 만든다.
		hang++; yal = 0;
	}
	if (num == 0) { // 1의 갯수가 모두 없어지면
		int sum = 0;
		for (int i = 1; i <= 5; i++) {
			sum += 5 - paper[i]; // 각각의 종류의 색종이는 5개씩 있었으므로 5개에서 남은 paper를 빼서 결과값을 만든다.
		}
		if (result > sum) result = sum; // 결과값 갱신..

		return;
	}
	if (hang == 10) return; // hang이 10이 되면 0,0 부터 9,9 까지 모두 돈 것이므로 return..

	if (board[hang][yal] == 1) { // 0,0부터 9,9까지 돌면서 1를 만났을 떼..

		for (int sz = 5; sz >= 1; sz--) { // 가장큰것부터 붙여봐야 색종이의 갯수를 적게 붙일 수 있으므로..
			bool flag = go_find(hang, yal, sz); // 어떤종류의 색종이로 붙일 수 있는지 판단..
			if (flag) {// 만약 붙일 수 있는 색종이가 된다면..
				erase(hang, yal, sz, 0); //10 *10의 색종이에서 1 --> 0으로 바꿔주고
				num -= sz * sz; // 붙여줘야되는 1의 갯수를 뺀다.
				paper[sz]--; // 붙일 수 있는 색종이의 종류를 한개 빼준다..

				solve(hang, yal + sz, num); // 붙이고 난 다음 yal 을 붙인 크기의 sz만큼 증가시켜 재귀..
				paper[sz]++; // recover..
				num += sz * sz;
				erase(hang, yal, sz, 1);
			}
		}
	}
	else solve(hang, yal + 1, num); // 만약 0이라면 yal을 1 증가하여 재귀..


}